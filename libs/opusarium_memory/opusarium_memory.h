/* SPDX-License-Identifier:	MPL-2.0 */

#ifndef OPUSARIUM_MEMORY_H
#define OPUSARIUM_MEMORY_H

#include <stdbool.h>
#include <inttypes.h>

#include <opusarium_compdeps.h>
#include <opusarium_archdeps.h>
#include <opusarium_numa.h>

#ifndef OPUSARIUM_MEMORY_DEF_PAGESIZE
#define OPUSARIUM_MEMORY_DEF_PAGESIZE 4096
#endif /* OPUSARIUM_MEMORY_DEF_PAGESIZE */

#ifndef OPUSARIUM_MEMORY_DEF_PAGETHRESH
#define OPUSARIUM_MEMORY_DEF_PAGETHRESH 2
#endif /* OPUSARIUM_MEMORY_DEF_PAGESIZE */

typedef enum {
    OPUSARIUM_MEMORY_PERM_READ = 0x1,
    OPUSARIUM_MEMORY_PERM_WRITE = 0x2,
    OPUSARIUM_MEMORY_PERM_EXECUTE = 0x4,
} opusarium_memory_perm_t;

typedef enum {
    OPUSARIUM_MEMORY_OPT_PAGEALIGN = 0x1,
    OPUSARIUM_MEMORY_OPT_SHAREABLE = 0x2,
    OPUSARIUM_MEMORY_OPT_REQOSMEMORY = 0x4,
    OPUSARIUM_MEMORY_OPT_FAULTEDADDR = 0x8,
} opusarium_memory_opt_t;

void opusarium_memory_refenv(void);

void * opusarium_memory_getvirt(size_t size,
    opsuarium_memory_perm_t perm, opusarium_numa_mask_t numa,
    opusarium_memory_opt_t *opt, int *err);
void opusarium_memory_putvirt(void *vmp);

#endif /* OPUSARIUM_MEMORY_H */