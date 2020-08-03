/* SPDX-License-Identifier:	MPL-2.0 */

#ifndef OPUSARIUM_THREAD_H
#define OPUSARIUM_THREAD_H

#include <stdbool.h>
#include <inttypes.h>

#define OPUSARIUM_THREAD_ERRID (UINT64_MAX)

typedef int (*opusarium_thread_func_t)(void *);

typedef enum {
	OPUSARIUM_THREAD_STATE_FAIL = -1,
	OPUSARIUM_THREAD_STATE_IDLE = 0,
	OPUSARIUM_THREAD_STATE_PREP,
	OPUSARIUM_THREAD_STATE_TRGD,
	OPUSARIUM_THREAD_STATE_DONE,
	OPUSARIUM_THREAD_STATE_HALT,
} opusarium_thread_state_t;

typedef struct opusarium_cache_align {
	opusarium_thread_func_t thread_func;
	void *thread_arg;

	uint32_t is_avoid_mask;
	opusarium_cpu_type_t cpu_type;
	opusarium_cpu_affin_t affinity_mask;

	uint32_t is_manual_stack;
	union {
		struct {
			size_t stack_size;
			void *stack_ptr;
		} manual_stack_conf;
		struct {
			size_t stack_size;
			opusarium_memory_perm_t stack_permission;
		} default_stack_conf;
	};
} opusarium_thread_conf_t;

typedef struct opusarium_cache_align {
	opusarium_thread_state_t thread_state;
	opusarium_thread_func_t thread_func;
	void *thread_arg;
	int thread_ret;
} opusarium_thread_executor_t;

typedef struct opusarium_cache_align {
	uint64_t thread_id;
	uint64_t thread_envpid;
	uint64_t thread_envtid;
	opusarium_thread_excutor_t thread_executor;

	opusarium_cpu_mask_t affinity_mask;
	opusarium_numa_mask_t numa_mask;

	uint32_t is_manual_stack;
	size_t stack_size;
	void *stack_ptr;
} opusatrium_thread_t;

extern uint64_t opusarium_cache_align opusarium_thread_next_id;

void opusarium_thread_init(opusarium_thread_t *thread);
int opusarium_thread_spawn(opusarium_thread_t *thread, opusarium_thread_conf_t *conf);
int opusarium_thread_join(opusarium_thread_t *thread, int *thret);
int opusarium_thread_kill(opusarium_thread_t *thread);

#endif /* OPUSARIUM_THREAD_H */
