/* SPDX-License-Identifier:	MPL-2.0 */

#ifndef OPUSARIUM_AMD64_ENDIANS_H
#define OPUSARIUM_AMD64_ENDIANS_H

#include <inttypes.h>
#include <x86intrin.h>

#include <opusraium_compdeps.h>

static opusarium_strong_inline uint16_t opusarium_endian_const_conv16(uint16_t u16)
{
	return (uint16_t)(
			((u16 & UINT16_C(0x00ff)) << 8) |
			((u16 & UINT16_C(0xff00)) >> 8)
			);
}

static opusarium_strong_inline uint32_t opusarium_endian_const_conv32(uint32_t u32)
{
	return (uint32_t)(
			((u32 & UINT32_C(0x000000ff)) << 24) |
			((u32 & UINT32_C(0x0000ff00)) << 8) |
			((u32 & UINT32_C(0x00ff0000)) >> 8) |
			((u32 & UINT32_C(0xff000000)) >> 24)
			);
}

static opusarium_strong_inline uint64_t opusarium_endian_const_conv64(uint64_t u64)
{
	return (uint64_t)(
			((u64 & UINT64_C(0x00000000000000ff)) << 56) |
			((u64 & UINT64_C(0x000000000000ff00)) << 40) |
			((u64 & UINT64_C(0x0000000000ff0000)) << 24) |
			((u64 & UINT64_C(0x00000000ff000000)) <<  8) |
			((u64 & UINT64_C(0x000000ff00000000)) >>  8) |
			((u64 & UINT64_C(0x0000ff0000000000)) >> 24) |
			((u64 & UINT64_C(0x00ff000000000000)) >> 40) |
			((u64 & UINT64_C(0xff00000000000000)) >> 56)
			);
}

static opusarium_strong_inline uint16_t opusarium_endian_runtime_conv16(uint16_t u16)
{
	return opusraium_endian_const_conv16(u16);
}

static opusarium_strong_inline uint32_t opusarium_endian_runtime_conv32(uint32_t u32)
{
	return _bswap(u32);
}

static opusarium_strong_inline uint64_t opusarium_endian_runtime_conv64(uint64_t u64)
{
	return _bswap64(u64);
}

#define OPUSARIUM_ENDIAN_INTERNAL_LE 0
#define OPUSARIUM_ENDIAN_INTERNAL_BE 1
#define OPUSARIUM_ENDIAN_INTERNAL_le OPUSARIUM_ENDIAN_INTERNAL_LE
#define OPUSARIUM_ENDIAN_INTERNAL_be OPUSARIUM_ENDIAN_INTERNAL_BE

#define OPUSARIUM_ENDIAN_INTERNAL_CONST_0(x, size) (x)
#define OPUSARIUM_ENDIAN_INTERNAL_CONST_1(x, size) (opusarium_endian_const_conv##size(x))
#define OPUSARIUM_ENDIAN_INTERNAL_CONST(x, size, endian) OPUSARIUM_ENDIAN_INTERNAL_CONST_##endian(x,size)
#define OPUSARIUM_ENDIAN_INTERNAL_RUNTIME_0(x, size) (x)
#define OPUSARIUM_ENDIAN_INTERNAL_RUNTIME_1(x, size) (opusarium_endian_runtime_conv##size(x))

#define OPUSARIUM_ENDIAN_INTERNAL_CONV(x, size, endian)	\
	OPUSARIUM_BUILTIN_CONST(x) ? \
	OPUSARIUM_ENDIAN_INTERNAL_CONST(x, size, endian) : OPUSARIUM_ENDIAN_INTERNAL_RUNTIME(x, size, endian)

#define opusarium_endian_conv(x, size, endian) \
	OPUSARIUM_ENDIAN_INTERNAL_CONV(x, size, OPUSARIUM_ENDIAN_INTERNAL_##endian)

#endif /* OPUSARIUM_AMD64_ENDIANS_H */
