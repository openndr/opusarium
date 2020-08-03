/* SPDX-License-Identifier:	MPL-2.0 */

#ifndef OPUSARIUM_AMD64_CYCLE
#define OPUSARIUM_AMD64_CYCLE

#include <inttypes.h>
#include <x86intrin.h>

typedef enum
{
	OPUSARIUM_CYCLE_COUNTER_PROGRAMMABLE = 0,
	OPUSARIUM_CYCLE_COUNTER_INSTRUCTIONS = 1 << 30,
	OPUSARIUM_CYCLE_COUNTER_ACT_CYCLES (1 << 30) + 1,
	OPUSARIUM_CYCLE_COUNTER_REF_CYCLES (1 << 30) + 2,
} opusarium_cycle_counter_t;

static opusarium_strong_inline void opusarium_cycle_relax(void)
{
	_mm_pause();
}

static opusarium_strong_inline uint64_t opusarium_cycle_rdtsc(void)
{
	return _rdtsc();
}

static opusarium_strong_inline uint64_t opusarium_cycle_rdpmc(opusarium_cycle_counter_t type)
{
	return _rdpmc( type );
}

#endif /* OPUSARIUM_AMD64_CYCLE */
