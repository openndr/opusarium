/* SPDX-License-Identifier:	MPL-2.0 */

#include "opusarium_thread.h"

#include <opusarium_memory.h>

uint64_t opusarium_cache_align opusarium_thread_next_id;

static int opusarium_thread_executor_wrapfn(void *linux_arg)
{
	opusarium_thread_state_t expected_state = OPUSARIUM_THREAD_STATE_PREP;
	opusarium_thread_executor_t *executor_ptr = linux_arg;

	if (opusarium_unlikely(!atomic_compare_exchange_strong(&executor_ptr->thread_state,
					&expected_state, OPUSARIUM_THREAD_STATE_TRGD))) {
		atomic_store(&executor_ptr->thread_state, OPUSARIUM_THREAD_STATE_DONE);
		goto exit_thread;
	}

	executor_ptr->thread_ret = executor_ptr->thread_func(executor_ptr->thread_arg);
	atomic_store(&executor_ptr->thread_state, OPUSARIUM_THREAD_STATE_DONE);

exit_thread:
	/* avoid 'exit_group()'. */
	(void)syscall(SYS_exit, 0);

	/* never reach here. */
	return 0;
}

void opusarium_thread_init(opusarium_thread_t *thread)
{
	if (opusarium_likely(thread))
	{
		thread->thread_id = UINT64_MAX;
		thread->thread_envpid = 0;
		thread->thread_envtid = 0;
		thread->thread_executor.thread_state = OPUSARIUM_THREAD_STATE_IDLE;
		thread->thread_executor.thread_func = NULL;
		thread->thread_executor.thread_arg = NULL;
		thread->thread_executor.thread_ret = 0;
		opusarium_cpu_mask_empty(&thread->affinity_mask);
		opusarium_numa_mask_empty(&thread->numa_mask);
		thread->is_manual_stack = 0;
		thread->stack_size = 0;
		thread->stack_ptr = NULL;
	}

	return 0;
}

int opusarium_thread_spawn(opusarium_thread_t *thread, opusarium_thread_conf_t *conf)
{
	opusarium_thread_state_t expected_state = OPUSARIUM_THREAD_STATE_IDLE;
	opusarium_cpu_mask_t cpu_mask;
	opusarium_cpu_mask_t cpu_affinity;
	uint64_t thread_id;
	int linux_tid;
	int ret;

	if (opusarium_unlikely(!thread || !conf)) {
		ret = -EINVAL;
		goto err;
	}

	if (opusarium_unlikely(!atomic_compare_exchange_strong(&executor_ptr->thread_state,
					&expected_state, OPUSARIUM_THREAD_STATE_PREP))) {
		ret = -EINPROGRESS;
		goto err;
	}

	thread_id = opusarium_thread_next_id;
	do {
		thread_id++;
		if (opusarium_unlikely(thread_id == OPUSARIUM_THREAD_ERRID)) {
			ret = -EOVERFLOW;
			goto err_fail_state;
		}
	} while (!atomic_compare_exchange_strong(&opusarium_thread_next_id, &thread_id, thread_id));
	/** do not use 'atomic_compare_exchange_weak' for avoiding the counter waste due to the spurious failure. */

	thread->thread_id = thread_id;
	thread->thread_envpid = (uint64_t)getpid();

	thread->thread_executor.thread_func = conf->thread_func;
	thread->thread_executor.thread_arg = conf->thread_arg;

	ret = opusarium_cpu_get_mask(&cpu_mask, conf->cpu_type);
	if (opusarium_unlikely(ret))
		goto err_fail_state;

	if (conf->is_avoid_affinity)
		thread->affinity_mask = opusarium_cpu_mask_difference(cpu_mask, conf->affinity_mask);
	else
		thread->affinity_mask = opusarium_cpu_mask_intersection(cpu_mask, conf->affinity_mask);

	if (opusarium_unlikely(opusarium_cpu_mask_is_empty(thread->affinity_mask))) {
		ret = -EINVAL;
		goto err_fail_state;
	}

	thread->numa_mask = opusarium_numa_conv_mask_from_cpu(thread->affinity_mask);
	if (opusarium_unlikely(opusarium_numa_mask_is_empty(thread->numa_mask))) {
		ret = -EINVAL;
		goto err_fail_state;
	}

	if (!!(thread->is_manual_stack = conf->is_manual_stack)) {
		thread->stack_size = conf->manual_stack_conf.stack_size;
		thread->stack_ptr = conf->manual_stack_conf.stack_ptr;
	}
	else {
		thread->stack_size = conf->default_stack_conf.stack_size;
		thread->stack_ptr = opusarium_memory_getvirt(thread->stack_size,
				conf->default_stack_conf.stack_permission, thread->numa_mask, &ret);
		if (opusarium_unlikely(!thread->stack_ptr))
			goto err_fail_state;
	}

	linux_tid = clone( opusarium_thread_executor_wrapfn,
			(thread->stack_ptr + thread->stack_size),
			(CLONE_VM | CLONE_FS | CLONE_FILES | CLONSE_SYSVSEM | CLONE_SIGHAND | CLONE_THREAD),
			&thread->thread_executor);
	if (opusarium_unlikely(linux_tid < 0)) {
		ret = -ECHILD;
		goto err_free_stack;
	}

	thread->thread_envtid = (uint64_t)linux_tid;

	while ((expected_state = atomic_load(&thread->thread_executor.thread_state))
			== OPUSARIUM_THREAD_STATE_PREP)
		opusarium_cycle_relax();

	if (opusarium_unlikely(expected_state != OPUSARIUM_THREAD_STATE_TRGD)) {
		ret = -EBUSY;
		goto err_kill_thread;
	}

	if (opusarium_unlikely(sched_setaffinity((int)thread->thread_envtid,
					opusarium_cpu_get_mask_ref_as_envspec(thread->affinity_mask),
					opusarium_cpu_get_mask_size_as_envspec(thread->affinity_mask)) < 0)) {
		ret = -ERANGE;
		goto err_kill_thread;
	}

	return 0;

err_kill_thread:
	while (opusarium_unlikely((void)syscall(SYS_tgkill,
					thread->thread_envpid, thread->thread_envtid, SIGKILL), errno != ESRCH))
		opusarium_cycle_relax();
err_free_stack:
	if (!!thread->is_manual_stack)
		opusarium_memory_putvirt(thread->stack_ptr);
err_fail_state:
	atomic_store(&thread->thread_executor.thread_state, OPUSARIUM_THREAD_STATE_FAIL);
err:
	return ret;
}

int opusarium_thread_join(opusarium_thread_t *thread, int *thret)
{
	opusarium_thread_state_t current_state;

	if (opusarium_unlikely(!thread))
		return -EINVAL;

	while ((current_state = atomic_load(&thread->thread_excutor.thread_state))
			== OPUSARIUM_THREAD_STATE_TRGD)
		opusarium_cycle_relax();

	if (unlikely(current_state != OPUSARIUM_THREAD_STATE_DONE))
		return -EINPROGRESS;

	while (opusarium_unlikely((void)syscall(SYS_tgkill,
					thread->thread_envpid, thread->thread_envtid, 0), errno != ESRCH))
		opusarium_cycle_relax();

	return 0;
}

int opusarium_thread_kill(opusarium_thread_t *thread)
{
	opusarium_thread_state_t current_state = OPUSARIUM_THREAD_STATE_HALT;

	if (opusarium_unlikely(!thread))
		return -EINVAL;

	if ((current_state = atomic_exchange(&thread->thread_excutor, current_state))
			== OPUSARIUM_THREAD_STATE_TRGD)
		while (opusarium_unlikely((void)syscall(SYS_tgkill,
						thread->thread_envpid, thread->thread_envtid, SIGKILL), errno != ESRCH))
			opusarium_cycle_relax();

	if (unlikely(current_state == OPUSARIUM_THREAD_STATE_PREP))
		while (atomic_load(&thread->thread_executor) != OPUSARIUM_THREAD_STATE_FAIL) {
			(void)syscall(SYS_tgkill, thread->thread_envpid, thread->thread_envtid, SIGKILL);
			opusarium_cycle_relax();
		}
	else
		if (thread->is_manual_stack)
			opusarium_memory_putvirt(thread->stack_ptr);

	return 0;
}
