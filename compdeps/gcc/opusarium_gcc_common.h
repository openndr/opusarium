/* SPDX-License-Identifier:	MPL-2.0 */

#ifndef OPUSARIUM_GCC_COMMON_H
#define OPUSARIUM_GCC_COMMON_H

#define opusarium_unused __attribute__((unused))
#define opusarium_strong_inline inline __attribute__((always_inline))
#define opusarium_align(v) __attribute__((aligned(v)))
#define opusarium_packed() __attribute__((packed))

#define opusarium_buitin_const(x) __builtin_constant_p(x)
#define opusarium_likley(x)	__builtin_expect((x), 1)
#define opusarium_unlikely(x) __builtin_expect((x), 0)
#define opusarium_typeof(x) __typeof__(x)

#define OPUSARIUM_INTERNAL_VPTRTYPE(t) __volatile__ t *
#define OPUSARIUM_INTERNAL_VPTRSET(v) \
	((OPUSARIUM_INTERNAL_VPTRTYPE(opusarium_typeof(v)))&(v))
#define opusarium_access_once(v) (*(OPUSARIUM_INTERNAL_VPTRSET(v)))

#define opusarium_base_of(sptr, mptr, member) \
	({(sptr) = (opusarium_typeof(sptr))(((void *)mptr) - (void *)&((opusarium_typeof(sptr)0)->member)); sptr})

#define opusarium_container_of(ptr, type, member) \
	({type *__ret; opusarium_base_of(__ret, ptr, member); __ret})

#define opusarium_typechk(type, v) \
	{opusarium_typeof(x) *__checker = (type *)0;}

#endif /* OPUSARIUM_GCC_COMMON_H */
