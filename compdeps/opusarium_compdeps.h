#ifndef OPUSARIUM_COMPDEPS_H
#define OPUSARIUM_COMPDEPS_H

#if defined(OPUSARIUM_BUILD_COMPILER_GCC)
#include <gcc/opusarium_gcc_common.h>
#else /* Compiler based includes */
#error Unsupported compiler
#endif /* Compiler based includes */

#endif /* OPUSARIUM_COMPDEPS_H */
