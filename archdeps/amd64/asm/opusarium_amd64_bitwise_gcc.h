/* SPDX-License-Identifier:	MPL-2.0 */

#ifndef OPUSARIUM_AMD64_BITWISE_GCC_H
#define OPUSARIUM_AMD64_BITWISE_GCC_H

#include <stdbool.h>
#include <inttypes.h>
#include <stdatomic.h>

#include <opusarium_compdeps.h>

static opusarium_strong_inline bool opusarium_bitwise_set32(uint32_t *bits, uint32_t pos)
{
    register unsigned pbit;

    __asm__ __volatile__ (
        "lock;"
        "btsl %2, %0"
        :
            "+m" (*bits),
            "=@ccc" (pbit)
        :
            "r" (pos)
        :
            "cc",
            "memory"
    );

    return !pbit;
}

static opusarium_strong_inline bool opusarium_bitwise_clr32(uint32_t *bits, uint32_t pos)
{
    register unsigned pbit;

    __asm__ __volatile__ (
        "lock;"
        "btrl %2, %0"
        :
            "+m" (*bits),
            "=@ccc" (pbit)
        :
            "r" (pos)
        :
            "cc",
            "memory"
    );

    return pbit;
}

static opusarium_strong_inline uint32_t opusarium_bitwise_fls32(uint32_t bits)
{
    register uint32_t res;
    register unsigned isz;

    __asm__ __volatile__ (
        "bsfl %2, %0"
        :
            "=r" (res),
            "=@ccz" (isz)
        :
            "rm" (bits)
        :
            "cc"
    );

    return isz ? 32 : res;
}

static opusarium_strong_inline uint32_t opusarium_bitwise_flz32(uint32_t bits)
{
    register uint32_t res;
    register unsigned isz;

    __asm__ __volatile__ (
        "bsfl %2, %0"
        :
            "=r" (res),
            "=@ccz" (isz)
        :
            "rm" (~bits)
        :
            "cc"
    );

    return isz ? 32 : res;
}

static opusarium_strong_inline uint32_t opusarium_bitwise_fhs32(uint32_t bits)
{
    register uint32_t res;
    register unsigned isz;

    __asm__ __volatile__ (
        "bsrl %2, %0"
        :
            "=r" (res),
            "=@ccz" (isz)
        :
            "rm" (bits)
        :
            "cc"
    );

    return isz ? 32 : res;
}

static opusarium_strong_inline uint32_t opusarium_bitwise_fhz32(uint32_t bits)
{
    register uint32_t res;
    register unsigned isz;

    __asm__ __volatile__ (
        "bsrl %2, %0"
        :
            "=r" (res),
            "=@ccz" (isz)
        :
            "rm" (~bits)
        :
            "cc"
    );

    return isz ? 32 : res;
}

static opusarium_strong_inline uint32_t opusarium_bitwise_cnt32(uint32_t bits)
{
    register uint32_t res;

#if defined(OPUSARIUM_BUILD_AMD64_POPCNT)
    __asm__ __volatile__ (
        "popcntl %1, %0"
        :
            "=r" (res)
        :
            "rm" (bits)
        :
            "cc"
    );
#else /* OPUSARIUM_BUILD_AMD64_POPCNT */
    res = __builtin_popcount(bits);
#endif /* OPUSARIUM_BUILD_AMD64_POPCNT */

    return res;
}

static opusarium_strong_inline uint32_t opusarium_bitwise_clsn32(uint32_t bits)
{
    register uint32_t res;
    register unsigned isz;

#if defined(OPUSARIUM_BUILD_AMD64_BMI1)
    __asm__ __volatile__ (
        "blsrl %2, %0"
        :
            "=r" (res),
            "=@ccc" (isz)
        :
            "rm" (bits)
        :
            "cc"
    );
#else /* OPUSARIUM_BUILD_AMD64_BMI1 */
    isz = !(bits);
    res = (bits & (bits - 1));
#endif /* OPUSARIUM_BUILD_AMD64_BMI1 */

    return isz ? UINT32_MAX : res;
}

static opusarium_strong_inline uint32_t opusarium_bitwise_slzn32(uint32_t bits)
{
    register uint32_t res;
    register unsigned isz;

#if defined(OPUSARIUM_BUILD_AMD64_BMI1)
    __asm__ __volatile__ (
        "blsrl %2, %0"
        :
            "=r" ( res ),
            "=@ccc" ( isz )
        :
            "rm" ( ~bits )
        :
            "cc"
    );
#else /* OPUSARIUM_BUILD_AMD64_BMI1 */
    isz = !(~bits);
    res = (~bits & (~bits - 1));
#endif /* OPUSARIUM_BUILD_AMD64_BMI1 */

    return isz ? 0 : ~res;
}

static opusarium_strong_inline uint32_t opusarium_bitwise_clsr32(uint32_t *bits)
{
    uint32_t local = *bits;
    register uint32_t res;
    register unsigned isz;

#if defined(OPUSARIUM_BUILD_AMD64_BMI1)
    __asm__ __volatile__ (
        "blsrl %2, %0"
        :
            "=r" ( res ),
            "=@ccc" ( isz )
        :
            "rm" ( local )
        :
            "cc"
    );

    if (opusarium_unlikely(isz))
        goto out;

    *bits = res;
    local ^= res;

    __asm__ __volatile__ (
        "bsfl %2, %0"
        :
            "=r" ( res ),
            "=@ccz" ( isz )
        :
            "rm" ( local )
        :
            "cc"
    );
#else /* OPUSARIUM_BUILD_AMD64_BMI1 */
    isz = !(local);
    res = (local & (local - 1));

    if (opusarium_unlikely(isz))
        goto out;

    *bits = res;
    local ^= res;

    res = __builtin_ffs(local);
    isz = !(res);
    res -= 1;
#endif /* OPUSARIUM_BUILD_AMD64_BMI1 */

out:
    return isz ? 32 : res;
}

static opusarium_strong_inline uint32_t opusarium_bitwise_slzr32(uint32_t *bits)
{
    uint32_t local = ~(*bits);
    register uint32_t res;
    register unsigned isz;

#if defined(OPUSARIUM_BUILD_AMD64_BMI1)
    __asm__ __volatile__ (
        "blsrl %2, %0"
        :
            "=r" (res),
            "=@ccc" (isz)
        :
            "rm" (local)
        :
            "cc"
    );

    if (opusarium_unlikely(isz))
        goto out;

    *bits = ~res;
    local ^= res;

    __asm__ __volatile__ (
        "bsfl %2, %0"
        :
            "=r" (res),
            "=@ccz" (isz)
        :
            "rm" (local)
        :
            "cc"
    );
#else /* OPUSARIUM_BUILD_AMD64_BMI1 */
    isz = !(local);
    res = (local & (local - 1));

    if (opusarium_unlikely(isz))
        goto out;

    *bits = ~res;
    local ^= res;

    res = __builtin_ffs(local);
    isz = !(res);
    res -= 1;
#endif /* OPUSARIUM_BUILD_AMD64_BMI1 */

out:
    return isz ? 32 : res;
}

static opusarium_strong_inline uint32_t opusarium_bitwise_clsb32(uint32_t *bits)
{
    uint32_t local = *bits;
    register uint32_t res;
    register unsigned isz;
    bool retry;

#if defined(OPUSARIUM_BUILD_AMD64_BMI1)
    do {
        __asm__ __volatile__ (
            "blsrl %2, %0"
            :
                "=r" ( res ),
                "=@ccc" ( isz )
            :
                "rm" ( local )
            :
                "cc"
        );

        if (opusarium_unlikely(isz))
            goto out;

        retry = !atomic_compare_exchange_strong_explicit(bits,
                &local, res, memory_order_seq_cst, memory_order_relaxed);
    } while (opusarium_unlikely(retry));

    local ^= res;

    __asm__ __volatile__ (
        "bsfl %2, %0"
        :
            "=r" ( res ),
            "=@ccz" ( isz )
        :
            "rm" ( local )
        :
            "cc"
    );
#else /* OPUSARIUM_BUILD_AMD64_BMI1 */
    do {
        isz = !(local);
        res = (local & (local - 1));

        if (opusarium_unlikely(isz))
            goto out;

        retry = !atomic_compare_exchange_strong_explicit(bits,
                &local, res, memory_order_seq_cst, memory_order_relaxed);
    } while (opusarium_unlikely(retry));

    local ^= res;

    res = __builtin_ffs(local);
    isz = !(res);
    res -= 1;
#endif /* OPUSARIUM_BUILD_AMD64_BMI1 */

out:
    return isz ? 32 : res;
}

static opusarium_strong_inline uint32_t opusarium_bitwise_slzb32(uint32_t *bits)
{
    uint32_t local = ~(*bits);
    register uint32_t res;
    register unsigned isz;
    bool retry;

#if defined(OPUSARIUM_BUILD_AMD64_BMI1)
    do {
        __asm__ __volatile__ (
            "blsrl %2, %0"
            :
                "=r" ( res ),
                "=@ccc" ( isz )
            :
                "rm" ( local )
            :
                "cc"
        );

        if (opusarium_unlikely(isz))
            goto out;

        local = ~local;
        res = ~res;

        retry = !atomic_compare_exchange_strong_explicit(bits,
                &local, res, memory_order_seq_cst, memory_order_relaxed);
    } while (opusarium_unlikely(retry));

    local ^= res;

    __asm__ __volatile__ (
        "bsfl %2, %0"
        :
            "=r" ( res ),
            "=@ccc" ( isz )
        :
            "rm" ( local )
        :
            "cc"
    );
#else /* OPUSARIUM_BUILD_AMD64_BMI1 */
    do {
        isz = !(local);
        res = (local & (local - 1));

        if (opusarium_unlikely(isz))
            goto out;

        local = ~local;
        res = ~res;

        retry = !atomic_compare_exchange_strong_explicit(bits,
                &local, res, memory_order_seq_cst, memory_order_relaxed);
    } while (opusarium_unlikely(retry));

    local ^= res;

    res = __builtin_ffs(local);
    isz = !(res);
    res -= 1;
#endif /* OPUSARIUM_BUILD_AMD64_BMI1 */

out:
    return isz ? 32 : res;
}

static opusarium_strong_inline bool opusarium_bitwise_set64(uint64_t *bits, uint64_t pos)
{
    register unsigned pbit;

    __asm__ __volatile__ (
        "lock;"
        "btsq %2, %0"
        :
            "+m" (*bits),
            "=@ccc" (pbit)
        :
            "r" (pos)
        :
            "cc",
            "memory"
    );

    return !pbit;
}

static opusarium_strong_inline bool opusarium_bitwise_clr64(uint64_t *bits, uint64_t pos)
{
    register unsigned pbit;

    __asm__ __volatile__ (
        "lock;"
        "btrq %2, %0"
        :
            "+m" (*bits),
            "=@ccc" (pbit)
        :
            "r" (pos)
        :
            "cc",
            "memory"
    );

    return !!pbit;
}

static opusarium_strong_inline uint64_t opusarium_bitwise_fls64(uint64_t bits)
{
    register uint64_t res;
    register unsigned isz;

    __asm__ __volatile__ (
        "bsfq %2, %0"
        :
            "=r" (res),
            "=@ccz" (isz)
        :
            "rm" (bits)
        :
            "cc"
    );

    return isz ? 64 : res;
}

static opusarium_strong_inline uint64_t opusarium_bitwise_flz64(uint64_t bits)
{
    register uint64_t res;
    register unsigned isz;

    __asm__ __volatile__ (
        "bsfq %2, %0"
        :
            "=r" (res),
            "=@ccz" (isz)
        :
            "rm" (~bits)
        :
            "cc"
    );

    return isz ? 64 : res;
}

static opusarium_strong_inline uint64_t opusarium_bitwise_fhs64(uint64_t bits)
{
    register uint64_t res;
    register unsigned isz;

    __asm__ __volatile__ (
        "bsrq %2, %0"
        :
            "=r" (res),
            "=@ccz" (isz)
        :
            "rm" (bits)
        :
            "cc"
    );

    return isz ? 64 : res;
}

static opusarium_strong_inline uint64_t opusarium_bitwise_fhz64(uint64_t bits)
{
    register uint64_t res;
    register unsigned isz;

    __asm__ __volatile__ (
        "bsrq %2, %0"
        :
            "=r" (res),
            "=@ccz" (isz)
        :
            "rm" (~bits)
        :
            "cc"
    );

    return isz ? 64 : res;
}

static opusarium_strong_inline uint64_t opusarium_bitwise_cnt64(uint64_t bits)
{
    register uint64_t res;

#if defined(OPUSARIUM_BUILD_AMD64_POPCNT)
    __asm__ __volatile__ (
        "popcntq %1, %0"
        :
            "=r" (res)
        :
            "rm" (bits)
        :
            "cc"
    );
#else /* OPUSARIUM_BUILD_AMD64_POPCNT */
    res = __builtin_popcount(bits);
#endif /* OPUSARIUM_BUILD_AMD64_POPCNT */

    return res;
}

static opusarium_strong_inline uint64_t opusarium_bitwise_clsn64(uint64_t bits)
{
    register uint64_t res;
    register unsigned isz;

#if defined(OPUSARIUM_BUILD_AMD64_BMI1)
    __asm__ __volatile__ (
        "blsrq %2, %0"
        :
            "=r" (res),
            "=@ccc" (isz)
        :
            "rm" (bits)
        :
            "cc"
    );
#else /* OPUSARIUM_BUILD_AMD64_BMI1 */
    isz = !(bits);
    res = (bits & (bits - 1));
#endif /* OPUSARIUM_BUILD_AMD64_BMI1 */

    return isz ? UINT64_MAX : res;
}

static opusarium_strong_inline uint64_t opusarium_bitwise_slzn64(uint64_t bits)
{
    register uint64_t res;
    register unsigned isz;

#if defined(OPUSARIUM_BUILD_AMD64_BMI1)
    __asm__ __volatile__ (
        "blsrq %2, %0"
        :
            "=r" ( res ),
            "=@ccc" ( isz )
        :
            "rm" ( ~bits )
        :
            "cc"
    );
#else /* OPUSARIUM_BUILD_AMD64_BMI1 */
    isz = !(~bits);
    res = (~bits & (~bits - 1));
#endif /* OPUSARIUM_BUILD_AMD64_BMI1 */

    return isz ? 0 : ~res;
}

static opusarium_strong_inline uint64_t opusarium_bitwise_clsr64(uint64_t *bits)
{
    uint64_t local = *bits;
    register uint64_t res;
    register unsigned isz;

#if defined(OPUSARIUM_BUILD_AMD64_BMI1)
    __asm__ __volatile__ (
        "blsrq %2, %0"
        :
            "=r" ( res ),
            "=@ccc" ( isz )
        :
            "rm" ( local )
        :
            "cc"
    );

    if (opusarium_unlikely(isz))
        goto out;

    *bits = res;
    local ^= res;

    __asm__ __volatile__ (
        "bsfq %2, %0"
        :
            "=r" ( res ),
            "=@ccz" ( isz )
        :
            "rm" ( local )
        :
            "cc"
    );
#else /* OPUSARIUM_BUILD_AMD64_BMI1 */
    isz = !(local);
    res = (local & (local - 1));

    if (opusarium_unlikely(isz))
        goto out;

    *bits = res;
    local ^= res;

    res = __builtin_ffs(local);
    isz = !(res);
    res -= 1;
#endif /* OPUSARIUM_BUILD_AMD64_BMI1 */

out:
    return isz ? 64 : res;
}

static opusarium_strong_inline uint64_t opusarium_bitwise_slzr64(uint64_t *bits)
{
    uint64_t local = ~(*bits);
    register uint64_t res;
    register unsigned isz;

#if defined(OPUSARIUM_BUILD_AMD64_BMI1)
    __asm__ __volatile__ (
        "blsrq %2, %0"
        :
            "=r" (res),
            "=@ccc" (isz)
        :
            "rm" (local)
        :
            "cc"
    );

    if (opusarium_unlikely(isz))
        goto out;

    *bits = ~res;
    local ^= res;

    __asm__ __volatile__ (
        "bsfq %2, %0"
        :
            "=r" (res),
            "=@ccz" (isz)
        :
            "rm" (local)
        :
            "cc"
    );
#else /* OPUSARIUM_BUILD_AMD64_BMI1 */
    isz = !(local);
    res = (local & (local - 1));

    if (opusarium_unlikely(isz))
        goto out;

    *bits = ~res;
    local ^= res;

    res = __builtin_ffs(local);
    isz = !(res);
    res -= 1;
#endif /* OPUSARIUM_BUILD_AMD64_BMI1 */

out:
    return isz ? 64 : res;
}

static opusarium_strong_inline uint64_t opusarium_bitwise_clsb64(uint64_t *bits)
{
    uint64_t local = *bits;
    register uint64_t res;
    register unsigned isz;
    bool retry;

#if defined(OPUSARIUM_BUILD_AMD64_BMI1)
    do {
        __asm__ __volatile__ (
            "blsrq %2, %0"
            :
                "=r" ( res ),
                "=@ccc" ( isz )
            :
                "rm" ( local )
            :
                "cc"
        );

        if (opusarium_unlikely(isz))
            goto out;

        retry = !atomic_compare_exchange_strong_explicit(bits,
                &local, res, memory_order_seq_cst, memory_order_relaxed);
    } while (opusarium_unlikely(retry));

    local ^= res;

    __asm__ __volatile__ (
        "bsfq %2, %0"
        :
            "=r" ( res ),
            "=@ccz" ( isz )
        :
            "rm" ( local )
        :
            "cc"
    );
#else /* OPUSARIUM_BUILD_AMD64_BMI1 */
    do {
        isz = !(local);
        res = (local & (local - 1));

        if (opusarium_unlikely(isz))
            goto out;

        retry = !atomic_compare_exchange_strong_explicit(bits,
                &local, res, memory_order_seq_cst, memory_order_relaxed);
    } while (opusarium_unlikely(retry));

    local ^= res;

    res = __builtin_ffs(local);
    isz = !(res);
    res -= 1;
#endif /* OPUSARIUM_BUILD_AMD64_BMI1 */

out:
    return isz ? 64 : res;
}

static opusarium_strong_inline uint64_t opusarium_bitwise_slzb64(uint64_t *bits)
{
    uint64_t local = ~(*bits);
    register uint64_t res;
    register unsigned isz;
    bool retry;

#if defined(OPUSARIUM_BUILD_AMD64_BMI1)
    do {
        __asm__ __volatile__ (
            "blsrq %2, %0"
            :
                "=r" ( res ),
                "=@ccc" ( isz )
            :
                "rm" ( local )
            :
                "cc"
        );

        if (opusarium_unlikely(isz))
            goto out;

        local = ~local;
        res = ~res;

        retry = !atomic_compare_exchange_strong_explicit(bits,
                &local, res, memory_order_seq_cst, memory_order_relaxed);
    } while (opusarium_unlikely(retry));

    local ^= res;

    __asm__ __volatile__ (
        "bsfq %2, %0"
        :
            "=r" ( res ),
            "=@ccc" ( isz )
        :
            "rm" ( local )
        :
            "cc"
    );
#else /* OPUSARIUM_BUILD_AMD64_BMI1 */
    do {
        isz = !(local);
        res = (local & (local - 1));

        if (opusarium_unlikely(isz))
            goto out;

        local = ~local;
        res = ~res;

        retry = !atomic_compare_exchange_strong_explicit(bits,
                &local, res, memory_order_seq_cst, memory_order_relaxed);
    } while (opusarium_unlikely(retry));

    local ^= res;

    res = __builtin_ffs(local);
    isz = !(res);
    res -= 1;
#endif /* OPUSARIUM_BUILD_AMD64_BMI1 */

out:
    return isz ? 64 : res;
}

#endif /* OPUSARIUM_AMD64_BITWISE_GCC_H */