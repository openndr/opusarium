/* SPDX-License-Identifier:	MPL-2.0 */

#ifndef OPUSARIUM_AMD64_BACKOFF_H
#define OPUSARIUM_AMD64_BACKOFF_H

#include <inttypes.h>

#include "amd64/opusarium_amd64_common.h"

#define OPUSARIUM_BACKOFF_FIXED_THRESHOLD 4
#define OPUSARIUM_BACKOFF_LARGEST_PRIME64B 18446744073709551557UL

typedef struct opusarium_cache_aligned {
    uint64_t relax_iteration;
    uint64_t random_seed;
} opusarium_backoff_t;

#if defined(OPUSARIUM_BUILD_COMPILER_GCC)
#include "asm/opusarium_amd64_backoff_gcc.h"
#else /* Compiler based includes */
#error Unsupported compiler
#endif /* Compiler based includes */

#endif /* OPUSARIUM_AMD64_BITWISE_H */