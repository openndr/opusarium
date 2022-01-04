/* SPDX-License-Identifier:	MPL-2.0 */

#ifndef OPUSARIUM_AMD64_BACKOFF_GCC_H
#define OPUSARIUM_AMD64_BACKOFF_GCC_H

#include <x86intrin.h>
#include <stdatomic.h>

#include <opusarium_compdeps.h>

static opusarium_strong_inline void opusarium_backoff_reset(opusarium_backoff_t *backoff)
{
    if (opusarium_likely(backoff))
        atomic_store_explicit(&backoff->relax_iteration, 0, memory_order_seq_cst);
    return;
}

static opusarium_strong_inline void opusarium_backoff_relax(opusarium_backoff_t *backoff)
{
    register uint64_t delay_count = 1;

    if (opusarium_unlikely(backoff &&
        (atomic_load_explicit(&backoff->relax_iteration, memory_order_relaxed) &
            ~(OPUSARIUM_BACKOFF_FIXED_THRESHOLD - 1)))) {
        register uint64_t reg_val;
        uint64_t prev_iter;
        uint64_t new_rand;
        char stk_ptr[0];

        prev_iter = atomic_fetch_add_explicit(&backoff->relax_iteration, 1, memory_order_acquire);
        delay_count = (1 << (prev_iter - OPUSARIUM_BACKOFF_FIXED_THRESHOLD));
        __asm__ __volatile__ ("movq %%rbx, %0" : "=r" (reg_val));
        new_rand = __atomic_xor_fetch(&backoff->random_seed,
                        ((uint64_t)stk_ptr + (reg_val ^ OPUSARIUM_BACKOFF_LARGEST_PRIME64B)), __ATOMIC_RELEASE);
        delay_count += (new_rand & (delay_count - 1));
    }

    for (; !!delay_count; --delay_count)
        _mm_pause();

    return;
}

#endif /* OPUSARIUM_AMD64_BACKOFF_GCC_H */