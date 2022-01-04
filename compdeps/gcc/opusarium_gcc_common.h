/* SPDX-License-Identifier:	MPL-2.0 */

#ifndef OPUSARIUM_GCC_COMMON_H
#define OPUSARIUM_GCC_COMMON_H

#undef opusarium_unused
#define opusarium_unused \
    __attribute__((unused))

#undef opusarium_strong_inline
#define opusarium_strong_inline \
    __attribute__((always_inline)) inline

#undef opusarium_align
#define opusarium_align(_i) \
    __attribute__((aligned(_i)))

#undef opusarium_packed
#define opusarium_packed() \
    __attribute__((packed))

#undef opusarium_builtin_const
#define opusarium_builtin_const(_c) \
    __builtin_constant_p(_c)

#undef opusarium_likely
#define opusarium_likely(_c) \
    __builtin_expect(!!(_c), 1)

#undef opusarium_unlikely
#define opusarium_unlikely(_c) \
    __builtin_expect(!!(_c), 0)

#undef opusarium_typeof
#define opusarium_typeof(_t) \
    __typeof__(_t)

#undef opusarium_access_once
#define opusarium_access_once(_v) \
    (*opusarium_gcc_vptrset(_v))

#undef opusarium_base_of
#define opusarium_base_of(_p_struct, _p_member, _x) \
    ({(_p_struct) = (void *)(_p_member) - (void *)&((opusarium_typeof((_p_struct)))0)->member; (_p_struct)})

#undef opusarium_container_of
#define opusarium_container_of(_p, _t, _x) \
    ({_t *_r; opusarium_base_of(_r, _p, _x); _r})

#undef opusarium_is_type
#define opusarium_is_type(_t, _v) \
    {opusarium_typeof(x) *_r = (_t *)0;}

#endif /* OPUSARIUM_GCC_COMMON_H */
