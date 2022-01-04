/* SPDX-License-Identifier:	MPL-2.0 */

#ifndef OPUSARIUM_AMD64_BITWISE_H
#define OPUSARIUM_AMD64_BITWISE_H

#if defined(OPUSARIUM_BUILD_COMPILER_GCC)
#include "asm/opusarium_amd64_bitwise_gcc.h"
#else /* Compiler based includes */
#error Unsupported compiler
#endif /* Compiler based includes */

#endif /* OPUSARIUM_AMD64_BITWISE_H */