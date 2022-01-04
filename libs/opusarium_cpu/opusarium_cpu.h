/* SPDX-License-Identifier:	MPL-2.0 */

#ifndef OPUSARIUM_CPU_H
#define OPUSARIUM_CPU_H

#include <stdbool.h>
#include <inttypes.h>

#include <opusarium_compdeps.h>
#include <opusarium_archdeps.h>

typedef enum {
    OPUSARIUM_CPU_TYPE_PRESENT,
    OPUSARIUM_CPU_TYPE_ONLINE,
    OPUSARIUM_CPU_TYPE_SCHEDULED,
    OPUSARIUM_CPU_TYPE_ISOLATED,
} opusarium_cpu_type_t;

typedef struct opusarium_cache_align {
    uint64_t opusarium_thread_count;
} opusarium_cpu_mask_t;

#endif /* OPUSARIUM_CPU_H */
