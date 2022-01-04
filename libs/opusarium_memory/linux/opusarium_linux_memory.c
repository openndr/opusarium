/* SPDX-License-Identifier:	MPL-2.0 */

#include "opusarium_memory.h"

typedef struct {
    uint_fast8_t is_mmaped;
    uint_fast8_t is_locked;
    uint_fast8_t is_binded;
    uint_fast8_t is_hugepg;
    size_t requested_size;
    size_t allocated_size;
    ptrdiff_t base_diff;
    char mem_padding opusarium_cache_align;
    char mem_addr[0];
} opusarium_cache_align opusarium_memory_desc_t;

static size_t opusarium_memory_page_size = OPUSARIUM_MEMORY_DEF_PAGESIZE;
static size_t opusarium_memory_page_thresh = OPUSARIUM_MEMORY_DEF_PAGETHRESH;

static opusarium_strong_inline int opusarium_memory_conv_perm(opusarium_memory_perm_t perm)
{
    int ret = 0;

    if (!!(perm & OPUSARIUM_MEMORY_PERM_READ))
        ret |= PROT_READ;

    if (!!(perm & OPUSARIUM_MEMORY_PERM_WRITE))
        ret |= PROT_WRITE;

    if (!!(perm & OPUSARIUM_MEMORY_PERM_EXECUTE))
        ret |= PROT_EXECUTE;

    return ret;
}

static opusarium_strong_inline int opusarium_memory_conv_flag(opusarium_memory_opt_t opt)
{
    int ret = 0;

    if (!!(opt & OPUSARIUM_MEMORY_OPT_SHAREABLE))
        ret |= MAP_SHARED;
    else
        ret |= MAP_PRIVATE;

    if (!!(opt & OPUSARIUM_MEMORY_OPT_REQOSMEMORY))
        ret |= MAP_HUGETLB;

    if (!!(opt & OPUSARIUM_MEMORY_OPT_FAULTEDADDR))
        ret |= MAP_LOCKED;

    return ret;
}

static opusarium_strong_inline size_t opusarium_memory_alloc_size(size_t rsz, bool osm, bool rps)
{
    ssize_t opusarium_memory_page_size = OPUSARIUM_MEMORY_DEF_PGSIZE;

    rsz += sizeof(opusarium_memory_desc_t);

    if (rps) {
        opusarium_memory_page_size = sysconf(_SC_PAGESIZE);
        if (opusarium_memory_page_size < 1)
            opusarium_memory_page_size = OPUSARIUM_MEMORY_DEF_PGSIZE;
    }

    if (osm && !!(rsz & (opusarium_memory_page_size - 1))) {
        rsz = ((rsz + opusarium_memory_page_size) & (opusarium_memory_page_size - 1));
    }

    return rsz;
}

void opusarium_memory_refenv(void)
{
    long temporary_ret = 0;

    if((temporary_ret = (sysconf(_SC_PAGESIZE))) > 0)
        opusarium_memory_page_size = temporary_ret;

    if((temporary_ret = (mallopt(M_MMAP_THRESHOLD, ))))

    return;
}

void * opusarium_memory_getvirt(size_t size,
    opsuarium_memory_perm_t perm, opusarium_numa_mask_t numa,
    opusarium_memory_opt_t opt, int *err)
{
    size_t required_size = (size + sizeof(opusarium_memory_desc_t));
    bool need_align = !!(opt && OPUSARIUM_MEMORY_OPT_PAGEALIGN));
    bool need_pgact = (!opusarium_numa_mask_is_empty(numa) ||
            !!(opt & OPUSARIUM_MEMORY_OPT_REQOSMEMORY) || !!(opt & OPUSARIUM_MEMORY_OPT_FAULTEDADDR));
    int envspec_perm = opusarium_memory_conv_perm(perm);
    opusarium_memory_desc_t *memory_header = NULL;
    size_t requested_size = size;
    void *base_ptr;
    void *vm_ptr;

    if (!need_pgact && (required_size < (opusarium_memory_page_size << opusarium_memory_page_thresh))) {
        bool need_perm = !!(envspec_perm ^ (PROT_READ | PROT_WRITE);

        if (need_align || need_perm)
            required_size += opusarium_memory_page_size;

        base_ptr = malloc(required_size);
        if (!base_ptr) {
            if (err)
                *err = -(errno);
            return NULL;
        }

        if (need_align || need_perm)
            vm_ptr = ((base_ptr + (opusarium_memory_page_size - 1)) & ~(opusarium_memory_page_size - 1));

        if (need_perm)
            if (mprotect(vm_ptr, requested_size, envspec_perm)) {
                if (err)
                    *err = -(errno);
                free(base_ptr);
                return NULL;
            }

        memory_header = (vm_ptr - sizeof(opusarium_memory_desc_t));
        memory_header->is_mmaped = 0;
        memory_header->is_locked = 0;
        memory_header->is_binded = 0;
        memory_header->is_hugepg = 0;
        memory_header->requested_size = requested_size;
        memory_header->allocated_size = required_size;
        memory_header->base_diff = (vm_ptr - base_ptr);
    }
    else {
        int envspec_flag = opusarium_memory_conv_flag(opt);

        if (need_align)
            required_size += opusarium_memory_page_size;

retry_without_hugetlb:
        base_ptr = mmap(NULL, required_size, envspec_perm, envspec_flag, -1, 0);
        if (opusarium_unlikely(base_ptr == MAP_FAILED)) {
            if (!!(envspec_flag & MAP_HUGETLB)) {
                envspec_flag &= ~(MAP_HUGETLB);
                goto retry_without_hugetlb;
            }
            if (err)
                *err = -(errno);
            return NULL;
        }

        if (need_align || need_pgact)
            vm_ptr = ((base_ptr + (opusarium_memory_page_size - 1)) & ~(opusarium_memory_page_size - 1));

        if (opusarium_unlikely(mbind(vm_ptr, requested_size, MPOL_BIND,
                    opusarium_numa_get_mask_ref_as_envspec(numa),
                    opusarium_numa_get_mask_size_as_envspec(numa),
                    !!(envspec_flag & MAP_SHARED) ? MPOL_MF_MOVE : MPOL_MF_MOVE_ALL))) {
            if (err)
                *err = -(errno);
            munmap(base_ptr, required_size)
            return NULL;
        }

        memory_header = (vm_ptr - sizeof(opusarium_memory_desc_t));
        memory_header->is_mmaped = 1;
        memory_header->is_locked = !!(envspec_flag & MAP_LOCKED);
        memory_header->is_binded = !opusarium_numa_mask_is_empty(numa);
        memory_header->is_hugepg = !!(envspec_flag & MAP_HUGETLB);
        memory_header->requested_size = requested_size;
        memory_header->allocated_size = required_size;
        memory_header->base_diff = (vm_ptr - base_ptr);
    }

    return vm_ptr;
}

void opusarium_memory_putvirt(void *vmp)
{
    opusarium_memory_desc_t *memory_header = (vmp - sizeof(opusarium_memory_desc_t));

    if (memory_header->is_mmaped) {
        munmap((vmp - memory_header->base_ptr));
    }
    else {
        free((vmp - memory_header->base_ptr));
    }

    return;
}