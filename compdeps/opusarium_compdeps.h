/* SPDX-License-Identifier:	MPL-2.0 */

#ifndef OPUSARIUM_COMPDEPS_H
#define OPUSARIUM_COMPDEPS_H

/* Argument convention
    _i : immediate expression
    _v : variable expression
    _p : pointer expression
    _c : conditional expression
    _t : type expression
    _x : Unclassified expression

    If there's duplicated argument types,
    it will identified with following '_(underscore) + unique-name'.
    */

#if defined(OPUSARIUM_BUILD_COMPILER_GCC)
#include "gcc/opusarium_gcc_common.h"
#else /* Compiler based includes */
#error Unsupported compiler
#endif /* Compiler based includes */

#endif /* OPUSARIUM_COMPDEPS_H */
