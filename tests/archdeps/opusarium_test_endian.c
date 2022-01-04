#include <utest.h>

#include <inttypes.h>

#include <opusarium_archdeps.h>

UTEST(opusarium_archdeps, endian_cmp_le)
{
    ASSERT_EQ(opusarium_endian_check(le), opusarium_endian_fastchk(le));
}

UTEST(opusarium_archdeps, endian_cmp_be)
{
    ASSERT_EQ(opusarium_endian_check(be), opusarium_endian_fastchk(be));
}

UTEST(opusarium_archdeps, endian_cmp_LE)
{
    ASSERT_EQ(opusarium_endian_check(LE), opusarium_endian_fastchk(LE));
}

UTEST(opusarium_archdeps, endian_cmp_BE)
{
    ASSERT_EQ(opusarium_endian_check(BE), opusarium_endian_fastchk(BE));
}

UTEST(opusarium_archdeps, endian_16b_le)
{
    char correct_16b[2] = {0x02, 0x01};
    uint16_t raw_16b = 0x0102;

    ASSERT_EQ(*(uint16_t*)correct_16b, opusarium_endian_conv(raw_16b, 16, le));
}

UTEST(opusarium_archdeps, endian_32b_le)
{
    char correct_32b[4] = {0x04, 0x03, 0x02, 0x01};
    uint32_t raw_32b = 0x01020304;

    ASSERT_EQ(*(uint32_t*)correct_32b, opusarium_endian_conv(raw_32b, 32, le));
}

UTEST(opusarium_archdeps, endian_64b_le)
{
    char correct_64b[8] = {0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01};
    uint64_t raw_64b = 0x0102030405060708;

    ASSERT_EQ(*(uint64_t*)correct_64b, opusarium_endian_conv(raw_64b, 64, le));
}

UTEST(opusarium_archdeps, endian_16b_be)
{
    char correct_16b[2] = {0x01, 0x02};
    uint16_t raw_16b = 0x0102;

    ASSERT_EQ(*(uint16_t*)correct_16b, opusarium_endian_conv(raw_16b, 16, be));
}

UTEST(opusarium_archdeps, endian_32b_be)
{
    char correct_32b[4] = {0x01, 0x02, 0x03, 0x04};
    uint32_t raw_32b = 0x01020304;

    ASSERT_EQ(*(uint32_t*)correct_32b, opusarium_endian_conv(raw_32b, 32, be));
}

UTEST(opusarium_archdeps, endian_64b_be)
{
    char correct_64b[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    uint64_t raw_64b = 0x0102030405060708;

    ASSERT_EQ(*(uint64_t*)correct_64b, opusarium_endian_conv(raw_64b, 64, be));
}

UTEST(opusarium_archdeps, endian_16b_LE)
{
    char correct_16b[2] = {0x02, 0x01};
    uint16_t raw_16b = 0x0102;

    ASSERT_EQ(*(uint16_t*)correct_16b, opusarium_endian_conv(raw_16b, 16, LE));
}

UTEST(opusarium_archdeps, endian_32b_LE)
{
    char correct_32b[4] = {0x04, 0x03, 0x02, 0x01};
    uint32_t raw_32b = 0x01020304;

    ASSERT_EQ(*(uint32_t*)correct_32b, opusarium_endian_conv(raw_32b, 32, LE));
}

UTEST(opusarium_archdeps, endian_64b_LE)
{
    char correct_64b[8] = {0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01};
    uint64_t raw_64b = 0x0102030405060708;

    ASSERT_EQ(*(uint64_t*)correct_64b, opusarium_endian_conv(raw_64b, 64, LE));
}

UTEST(opusarium_archdeps, endian_16b_BE)
{
    char correct_16b[2] = {0x01, 0x02};
    uint16_t raw_16b = 0x0102;

    ASSERT_EQ(*(uint16_t*)correct_16b, opusarium_endian_conv(raw_16b, 16, BE));
}

UTEST(opusarium_archdeps, endian_32b_BE)
{
    char correct_32b[4] = {0x01, 0x02, 0x03, 0x04};
    uint32_t raw_32b = 0x01020304;

    ASSERT_EQ(*(uint32_t*)correct_32b, opusarium_endian_conv(raw_32b, 32, BE));
}

UTEST(opusarium_archdeps, endian_64b_BE)
{
    char correct_64b[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    uint64_t raw_64b = 0x0102030405060708;

    ASSERT_EQ(*(uint64_t*)correct_64b, opusarium_endian_conv(raw_64b, 64, BE));
}