/* SPDX-License-Identifier:	MPL-2.0 */

#ifndef OPUSARIUM_COMMON_ENDIANS_H
#define OPUSARIUM_COMMON_ENDIANS_H

#include <inttypes.h>

#include <opusarium_compdeps.h>

static opusarium_strong_inline uint32_t opusarium_endian_is_little(void)
{
    union {
        uint32_t _holder_u32;
        uint8_t cptr[4];
    } checker = {0x01020304};

    return !(checker.cptr[0] ^ 0x01);
}

#define OPUSARIUM_ENDIAN_CHKHLP_LE opusarium_endian_is_little()
#define OPUSARIUM_ENDIAN_CHKHLP_BE !opusarium_endian_is_little()
#define OPUSARIUM_ENDIAN_CHKHLP_le OPUSARIUM_ENDIAN_CHKHLP_LE
#define OPUSARIUM_ENDIAN_CHKHLP_be OPUSARIUM_ENDIAN_CHKHLP_BE

#define opusarium_endian_check(endian) !(OPUSARIUM_ENDIAN_CHKHLP_##endian)

#endif /* OPUSARIUM_COMMON_ENDIANS_H */