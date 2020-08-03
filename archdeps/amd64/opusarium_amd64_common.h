/* SPDX-License-Identifier:	MPL-2.0 */

#ifndef OPUSARIUM_AMD64_COMMON_H
#define OPUSARIUM_AMD64_COMMON_H

#define OPUSARIUM_COMMON_INTERNAL_CACHELINE 64

#define opusarium_cache_align \
	opusarium_align(OPUSARIUM_COMMON_INTERNAL_CACHELINE)

#endif /* OPUSARIUM_AMD64_COMMON_H */
