#include <utest.h>

#include <inttypes.h>

#include <opusarium_archdeps.h>

UTEST(opusarium_archdeps, bitwise_32b_set)
{
    uint32_t test = 0x00000000;
    int ret;

    ret = opusarium_bitwise_set32(&test, 0);
    ASSERT_EQ((uint32_t)test, (uint32_t)0x00000001);
    ASSERT_EQ((uint32_t)ret, (uint32_t)1);

    ret = opusarium_bitwise_set32(&test, 0);
    ASSERT_EQ((uint32_t)test, (uint32_t)0x00000001);
    ASSERT_EQ((uint32_t)ret, (uint32_t)0);

    ret = opusarium_bitwise_set32(&test, 31);
    ASSERT_EQ((uint32_t)test, (uint32_t)0x80000001);
    ASSERT_EQ((uint32_t)ret, (uint32_t)1);

    ret = opusarium_bitwise_set32(&test, 1);
    ASSERT_EQ((uint32_t)test,0x80000003);
    ASSERT_EQ((uint32_t)ret, (uint32_t)1);
}

UTEST(opusarium_archdeps, bitwise_32b_clr)
{
    uint32_t test = 0xffffffff;
    int ret;

    ret = opusarium_bitwise_clr32(&test, 0);
    ASSERT_EQ((uint32_t)test, (uint32_t)0xfffffffe);
    ASSERT_EQ((uint32_t)ret, (uint32_t)1);

    ret = opusarium_bitwise_clr32(&test, 0);
    ASSERT_EQ((uint32_t)test, (uint32_t)0xfffffffe);
    ASSERT_EQ((uint32_t)ret, (uint32_t)0);

    ret = opusarium_bitwise_clr32(&test, 31);
    ASSERT_EQ((uint32_t)test, (uint32_t)0x7ffffffe);
    ASSERT_EQ((uint32_t)ret, (uint32_t)1);

    ret = opusarium_bitwise_clr32(&test, 1);
    ASSERT_EQ((uint32_t)test, (uint32_t)0x7ffffffc);
    ASSERT_EQ((uint32_t)ret, (uint32_t)1);
}

UTEST(opusarium_archdeps, bitwise_32b_fls)
{
    uint32_t test;

    test = 0xffffffff;
    ASSERT_EQ(opusarium_bitwise_fls32(test), (uint32_t)0);

    test = 0x80000000;
    ASSERT_EQ(opusarium_bitwise_fls32(test), (uint32_t)31);

    test = 0x00000000;
    ASSERT_EQ(opusarium_bitwise_fls32(test), (uint32_t)32);

    test = 0xffff0000;
    ASSERT_EQ(opusarium_bitwise_fls32(test), (uint32_t)16);
}

UTEST(opusarium_archdeps, bitwise_32b_flz)
{
    uint32_t test;

    test = 0x00000000;
    ASSERT_EQ(opusarium_bitwise_flz32(test), (uint32_t)0);

    test = 0x7fffffff;
    ASSERT_EQ(opusarium_bitwise_flz32(test), (uint32_t)31);

    test = 0xffffffff;
    ASSERT_EQ(opusarium_bitwise_flz32(test), (uint32_t)32);

    test = 0x0000ffff;
    ASSERT_EQ(opusarium_bitwise_flz32(test), (uint32_t)16);
}

UTEST(opusarium_archdeps, bitwise_32b_fhs)
{
    uint32_t test;

    test = 0xffffffff;
    ASSERT_EQ(opusarium_bitwise_fhs32(test), (uint32_t)31);

    test = 0x00000001;
    ASSERT_EQ(opusarium_bitwise_fhs32(test), (uint32_t)0);

    test = 0x00000000;
    ASSERT_EQ(opusarium_bitwise_fhs32(test), (uint32_t)32);

    test = 0x0000ffff;
    ASSERT_EQ(opusarium_bitwise_fhs32(test), (uint32_t)15);
}

UTEST(opusarium_archdeps, bitwise_32b_fhz)
{
    uint32_t test;

    test = 0x00000000;
    ASSERT_EQ(opusarium_bitwise_fhz32(test), (uint32_t)31);

    test = 0xfffffffe;
    ASSERT_EQ(opusarium_bitwise_fhz32(test), (uint32_t)0);

    test = 0xffffffff;
    ASSERT_EQ(opusarium_bitwise_fhz32(test), (uint32_t)32);

    test = 0xffff0000;
    ASSERT_EQ(opusarium_bitwise_fhz32(test), (uint32_t)15);
}

UTEST(opusarium_archdeps, bitwise_32b_cnt)
{
    uint32_t test;

    test = 0x00000000;
    ASSERT_EQ(opusarium_bitwise_cnt32(test), (uint32_t)0);

    test = 0xffffffff;
    ASSERT_EQ(opusarium_bitwise_cnt32(test), (uint32_t)32);

    test = 0x55555555;
    ASSERT_EQ(opusarium_bitwise_cnt32(test), (uint32_t)16);

    test = 0xffff0000;
    ASSERT_EQ(opusarium_bitwise_cnt32(test), (uint32_t)16);

    test = 0x0000ffff;
    ASSERT_EQ(opusarium_bitwise_cnt32(test), (uint32_t)16);
}

UTEST(opusarium_archdeps, bitwise_32b_clsn)
{
    uint32_t test;

    test = 0x00000000;
    ASSERT_EQ(opusarium_bitwise_clsn32(test), (uint32_t)UINT32_MAX);

    test = 0x00000001;
    ASSERT_EQ(opusarium_bitwise_clsn32(test), (uint32_t)0x00000000);

    test = 0x80000000;
    ASSERT_EQ(opusarium_bitwise_clsn32(test), (uint32_t)0x00000000);

    test = 0xffffffff;
    ASSERT_EQ(opusarium_bitwise_clsn32(test), (uint32_t)0xfffffffe);

    test = 0xffff0000;
    ASSERT_EQ(opusarium_bitwise_clsn32(test), (uint32_t)0xfffe0000);
}

UTEST(opusarium_archdeps, bitwise_32b_slzn)
{
    uint32_t test;

    test = 0xffffffff;
    ASSERT_EQ(opusarium_bitwise_slzn32(test), (uint32_t)0);

    test = 0xfffffffe;
    ASSERT_EQ(opusarium_bitwise_slzn32(test), (uint32_t)0xffffffff);

    test = 0x7fffffff;
    ASSERT_EQ(opusarium_bitwise_slzn32(test), (uint32_t)0xffffffff);

    test = 0x00000000;
    ASSERT_EQ(opusarium_bitwise_slzn32(test), (uint32_t)0x00000001);

    test = 0x00007fff;
    ASSERT_EQ(opusarium_bitwise_slzn32(test), (uint32_t)0x0000ffff);
}

UTEST(opusarium_archdeps, bitwise_32b_clsr)
{
    uint32_t test;
    uint32_t ret;

    test = 0x00000000;
    ret = opusarium_bitwise_clsr32(&test);
    ASSERT_EQ((uint32_t)test, (uint32_t)0x00000000);
    ASSERT_EQ((uint32_t)ret, (uint32_t)32);

    test = 0x00000001;
    ret = opusarium_bitwise_clsr32(&test);
    ASSERT_EQ((uint32_t)test, (uint32_t)0x00000000);
    ASSERT_EQ((uint32_t)ret, (uint32_t)0);

    test = 0x80000000;
    ret = opusarium_bitwise_clsr32(&test);
    ASSERT_EQ((uint32_t)test, (uint32_t)0x00000000);
    ASSERT_EQ((uint32_t)ret, (uint32_t)31);

    test = 0xffffffff;
    ret = opusarium_bitwise_clsr32(&test);
    ASSERT_EQ((uint32_t)test, (uint32_t)0xfffffffe);
    ASSERT_EQ((uint32_t)ret, (uint32_t)0);

    test = 0xffff0000;
    ret = opusarium_bitwise_clsr32(&test);
    ASSERT_EQ((uint32_t)test, (uint32_t)0xfffe0000);
    ASSERT_EQ((uint32_t)ret, (uint32_t)16);
}

UTEST(opusarium_archdeps, bitwise_32b_slzr)
{
    uint32_t test;
    uint32_t ret;

    test = 0xffffffff;
    ret = opusarium_bitwise_slzr32(&test);
    ASSERT_EQ((uint32_t)test, (uint32_t)0xffffffff);
    ASSERT_EQ((uint32_t)ret, (uint32_t)32);

    test = 0xfffffffe;
    ret = opusarium_bitwise_slzr32(&test);
    ASSERT_EQ((uint32_t)test, (uint32_t)0xffffffff);
    ASSERT_EQ((uint32_t)ret, (uint32_t)0);

    test = 0x7fffffff;
    ret = opusarium_bitwise_slzr32(&test);
    ASSERT_EQ((uint32_t)test, (uint32_t)0xffffffff);
    ASSERT_EQ((uint32_t)ret, (uint32_t)31);

    test = 0x00000000;
    ret = opusarium_bitwise_slzr32(&test);
    ASSERT_EQ((uint32_t)test, (uint32_t)0x00000001);
    ASSERT_EQ((uint32_t)ret, (uint32_t)0);

    test = 0x00007fff;
    ret = opusarium_bitwise_slzr32(&test);
    ASSERT_EQ((uint32_t)test, (uint32_t)0x0000ffff);
    ASSERT_EQ((uint32_t)ret, (uint32_t)15);
}

UTEST(opusarium_archdeps, bitwise_32b_clsb)
{
    uint32_t test;
    uint32_t ret;

    test = 0x00000000;
    ret = opusarium_bitwise_clsb32(&test);
    ASSERT_EQ((uint32_t)test, (uint32_t)0x00000000);
    ASSERT_EQ((uint32_t)ret, (uint32_t)32);

    test = 0x00000001;
    ret = opusarium_bitwise_clsb32(&test);
    ASSERT_EQ((uint32_t)test, (uint32_t)0x00000000);
    ASSERT_EQ((uint32_t)ret, (uint32_t)0);

    test = 0x80000000;
    ret = opusarium_bitwise_clsb32(&test);
    ASSERT_EQ((uint32_t)test, (uint32_t)0x00000000);
    ASSERT_EQ((uint32_t)ret, (uint32_t)31);

    test = 0xffffffff;
    ret = opusarium_bitwise_clsb32(&test);
    ASSERT_EQ((uint32_t)test, (uint32_t)0xfffffffe);
    ASSERT_EQ((uint32_t)ret, (uint32_t)0);

    test = 0xffff0000;
    ret = opusarium_bitwise_clsb32(&test);
    ASSERT_EQ((uint32_t)test, (uint32_t)0xfffe0000);
    ASSERT_EQ((uint32_t)ret, (uint32_t)16);
}

UTEST(opusarium_archdeps, bitwise_32b_slzb)
{
    uint32_t test;
    uint32_t ret;

    test = 0xffffffff;
    ret = opusarium_bitwise_slzb32(&test);
    ASSERT_EQ((uint32_t)test, (uint32_t)0xffffffff);
    ASSERT_EQ((uint32_t)ret, (uint32_t)32);

    test = 0xfffffffe;
    ret = opusarium_bitwise_slzb32(&test);
    ASSERT_EQ((uint32_t)test, (uint32_t)0xffffffff);
    ASSERT_EQ((uint32_t)ret, (uint32_t)0);

    test = 0x7fffffff;
    ret = opusarium_bitwise_slzb32(&test);
    ASSERT_EQ((uint32_t)test, (uint32_t)0xffffffff);
    ASSERT_EQ((uint32_t)ret, (uint32_t)31);

    test = 0x00000000;
    ret = opusarium_bitwise_slzb32(&test);
    ASSERT_EQ((uint32_t)test, (uint32_t)0x00000001);
    ASSERT_EQ((uint32_t)ret, (uint32_t)0);

    test = 0x00007fff;
    ret = opusarium_bitwise_slzb32(&test);
    ASSERT_EQ((uint32_t)test, (uint32_t)0x0000ffff);
    ASSERT_EQ((uint32_t)ret, (uint32_t)15);
}

/* 64-bit tests */
UTEST(opusarium_archdeps, bitwise_64b_set)
{
    uint64_t test = 0x0000000000000000;
    int ret;

    ret = opusarium_bitwise_set64(&test, 0);
    ASSERT_EQ((uint64_t)test, (uint64_t)0x0000000000000001);
    ASSERT_EQ((uint64_t)ret, (uint64_t)1);

    ret = opusarium_bitwise_set64(&test, 0);
    ASSERT_EQ((uint64_t)test, (uint64_t)0x0000000000000001);
    ASSERT_EQ((uint64_t)ret, (uint64_t)0);

    ret = opusarium_bitwise_set64(&test, 63);
    ASSERT_EQ((uint64_t)test, (uint64_t)0x8000000000000001);
    ASSERT_EQ((uint64_t)ret, (uint64_t)1);

    ret = opusarium_bitwise_set64(&test, 1);
    ASSERT_EQ((uint64_t)test, (uint64_t)0x8000000000000003);
    ASSERT_EQ((uint64_t)ret, (uint64_t)1);
}


UTEST(opusarium_archdeps, bitwise_64b_clr)
{
    uint64_t test = 0xffffffffffffffff;
    int ret;

    ret = opusarium_bitwise_clr64(&test, 0);
    ASSERT_EQ((uint64_t)test, (uint64_t)0xfffffffffffffffe);
    ASSERT_EQ((uint64_t)ret, (uint64_t)1);

    ret = opusarium_bitwise_clr64(&test, 0);
    ASSERT_EQ((uint64_t)test, (uint64_t)0xfffffffffffffffe);
    ASSERT_EQ((uint64_t)ret, (uint64_t)0);

    ret = opusarium_bitwise_clr64(&test, 63);
    ASSERT_EQ((uint64_t)test, (uint64_t)0x7ffffffffffffffe);
    ASSERT_EQ((uint64_t)ret, (uint64_t)1);

    ret = opusarium_bitwise_clr64(&test, 1);
    ASSERT_EQ((uint64_t)test, (uint64_t)0x7ffffffffffffffc);
    ASSERT_EQ((uint64_t)ret, (uint64_t)1);
}

UTEST(opusarium_archdeps, bitwise_64b_fls)
{
    uint64_t test;

    test = 0xffffffffffffffff;
    ASSERT_EQ(opusarium_bitwise_fls64(test), (uint64_t)0);

    test = 0x8000000000000000;
    ASSERT_EQ(opusarium_bitwise_fls64(test), (uint64_t)63);

    test = 0x0000000000000000;
    ASSERT_EQ(opusarium_bitwise_fls64(test), (uint64_t)64);

    test = 0xffffffff00000000;
    ASSERT_EQ(opusarium_bitwise_fls64(test), (uint64_t)32);
}

UTEST(opusarium_archdeps, bitwise_64b_flz)
{
    uint64_t test;

    test = 0x0000000000000000;
    ASSERT_EQ(opusarium_bitwise_flz64(test), (uint64_t)0);

    test = 0x7fffffffffffffff;
    ASSERT_EQ(opusarium_bitwise_flz64(test), (uint64_t)63);

    test = 0xffffffffffffffff;
    ASSERT_EQ(opusarium_bitwise_flz64(test), (uint64_t)64);

    test = 0x00000000ffffffff;
    ASSERT_EQ(opusarium_bitwise_flz64(test), (uint64_t)32);
}

UTEST(opusarium_archdeps, bitwise_64b_fhs)
{
    uint64_t test;

    test = 0xffffffffffffffff;
    ASSERT_EQ(opusarium_bitwise_fhs64(test), (uint64_t)63);

    test = 0x000000000000001;
    ASSERT_EQ(opusarium_bitwise_fhs64(test), (uint64_t)0);

    test = 0x000000000000000;
    ASSERT_EQ(opusarium_bitwise_fhs64(test), (uint64_t)64);

    test = 0x0000000ffffffff;
    ASSERT_EQ(opusarium_bitwise_fhs64(test), (uint64_t)31);
}

UTEST(opusarium_archdeps, bitwise_64b_fhz)
{
    uint64_t test;

    test = 0x0000000000000000;
    ASSERT_EQ(opusarium_bitwise_fhz64(test), (uint64_t)63);

    test = 0xfffffffffffffffe;
    ASSERT_EQ(opusarium_bitwise_fhz64(test), (uint64_t)0);

    test = 0xffffffffffffffff;
    ASSERT_EQ(opusarium_bitwise_fhz64(test), (uint64_t)64);

    test = 0xffffffff00000000;
    ASSERT_EQ(opusarium_bitwise_fhz64(test), (uint64_t)31);
}

UTEST(opusarium_archdeps, bitwise_64b_cnt)
{
    uint64_t test;

    test = 0x0000000000000000;
    ASSERT_EQ(opusarium_bitwise_cnt64(test), (uint64_t)0);

    test = 0xffffffffffffffff;
    ASSERT_EQ(opusarium_bitwise_cnt64(test), (uint64_t)64);

    test = 0x5555555555555555;
    ASSERT_EQ(opusarium_bitwise_cnt64(test), (uint64_t)32);

    test = 0xffffffff00000000;
    ASSERT_EQ(opusarium_bitwise_cnt64(test), (uint64_t)32);

    test = 0x00000000ffffffff;
    ASSERT_EQ(opusarium_bitwise_cnt64(test), (uint64_t)32);
}

UTEST(opusarium_archdeps, bitwise_64b_clsn)
{
    uint64_t test;

    test = 0x0000000000000000;
    ASSERT_EQ(opusarium_bitwise_clsn64(test), (uint64_t)UINT64_MAX);

    test = 0x0000000000000001;
    ASSERT_EQ(opusarium_bitwise_clsn64(test), (uint64_t)0x0000000000000000);

    test = 0x8000000000000000;
    ASSERT_EQ(opusarium_bitwise_clsn64(test), (uint64_t)0x0000000000000000);

    test = 0xffffffffffffffff;
    ASSERT_EQ(opusarium_bitwise_clsn64(test), (uint64_t)0xfffffffffffffffe);

    test = 0xffffffff00000000;
    ASSERT_EQ(opusarium_bitwise_clsn64(test), (uint64_t)0xfffffffe00000000);
}

UTEST(opusarium_archdeps, bitwise_64b_slzn)
{
    uint64_t test;

    test = 0xffffffffffffffff;
    ASSERT_EQ(opusarium_bitwise_slzn64(test), (uint64_t)0);

    test = 0xfffffffffffffffe;
    ASSERT_EQ(opusarium_bitwise_slzn64(test), (uint64_t)0xffffffffffffffff);

    test = 0x7fffffffffffffff;
    ASSERT_EQ(opusarium_bitwise_slzn64(test), (uint64_t)0xffffffffffffffff);

    test = 0x0000000000000000;
    ASSERT_EQ(opusarium_bitwise_slzn64(test), (uint64_t)0x0000000000000001);

    test = 0x000000007fffffff;
    ASSERT_EQ(opusarium_bitwise_slzn64(test), (uint64_t)0x00000000ffffffff);
}

UTEST(opusarium_archdeps, bitwise_64b_clsr)
{
    uint64_t test;
    uint64_t ret;

    test = 0x0000000000000000;
    ret = opusarium_bitwise_clsr64(&test);
    ASSERT_EQ((uint64_t)test, (uint64_t)0x0000000000000000);
    ASSERT_EQ((uint64_t)ret, (uint64_t)64);

    test = 0x0000000000000001;
    ret = opusarium_bitwise_clsr64(&test);
    ASSERT_EQ((uint64_t)test, (uint64_t)0x0000000000000000);
    ASSERT_EQ((uint64_t)ret, (uint64_t)0);

    test = 0x8000000000000000;
    ret = opusarium_bitwise_clsr64(&test);
    ASSERT_EQ((uint64_t)test, (uint64_t)0x0000000000000000);
    ASSERT_EQ((uint64_t)ret, (uint64_t)63);

    test = 0xffffffffffffffff;
    ret = opusarium_bitwise_clsr64(&test);
    ASSERT_EQ((uint64_t)test, (uint64_t)0xfffffffffffffffe);
    ASSERT_EQ((uint64_t)ret, (uint64_t)0);

    test = 0xffffffff00000000;
    ret = opusarium_bitwise_clsr64(&test);
    ASSERT_EQ((uint64_t)test, (uint64_t)0xfffffffe00000000);
    ASSERT_EQ((uint64_t)ret, (uint64_t)32);
}

UTEST(opusarium_archdeps, bitwise_64b_slzr)
{
    uint64_t test;
    uint64_t ret;

    test = 0xffffffffffffffff;
    ret = opusarium_bitwise_slzr64(&test);
    ASSERT_EQ((uint64_t)test, (uint64_t)0xffffffffffffffff);
    ASSERT_EQ((uint64_t)ret, (uint64_t)64);

    test = 0xfffffffffffffffe;
    ret = opusarium_bitwise_slzr64(&test);
    ASSERT_EQ((uint64_t)test, (uint64_t)0xffffffffffffffff);
    ASSERT_EQ((uint64_t)ret, (uint64_t)0);

    test = 0x7fffffffffffffff;
    ret = opusarium_bitwise_slzr64(&test);
    ASSERT_EQ((uint64_t)test, (uint64_t)0xffffffffffffffff);
    ASSERT_EQ((uint64_t)ret, (uint64_t)63);

    test = 0x0000000000000000;
    ret = opusarium_bitwise_slzr64(&test);
    ASSERT_EQ((uint64_t)test, (uint64_t)0x0000000000000001);
    ASSERT_EQ((uint64_t)ret, (uint64_t)0);

    test = 0x000000007fffffff;
    ret = opusarium_bitwise_slzr64(&test);
    ASSERT_EQ((uint64_t)test, (uint64_t)0x00000000ffffffff);
    ASSERT_EQ((uint64_t)ret, (uint64_t)31);
}

UTEST(opusarium_archdeps, bitwise_64b_clsb)
{
    uint64_t test;
    uint64_t ret;

    test = 0x0000000000000000;
    ret = opusarium_bitwise_clsb64(&test);
    ASSERT_EQ((uint64_t)test, (uint64_t)0x0000000000000000);
    ASSERT_EQ((uint64_t)ret, (uint64_t)64);

    test = 0x0000000000000001;
    ret = opusarium_bitwise_clsb64(&test);
    ASSERT_EQ((uint64_t)test, (uint64_t)0x0000000000000000);
    ASSERT_EQ((uint64_t)ret, (uint64_t)0);

    test = 0x8000000000000000;
    ret = opusarium_bitwise_clsb64(&test);
    ASSERT_EQ((uint64_t)test, (uint64_t)0x0000000000000000);
    ASSERT_EQ((uint64_t)ret, (uint64_t)63);

    test = 0xffffffffffffffff;
    ret = opusarium_bitwise_clsb64(&test);
    ASSERT_EQ((uint64_t)test, (uint64_t)0xfffffffffffffffe);
    ASSERT_EQ((uint64_t)ret, (uint64_t)0);

    test = 0xffffffff00000000;
    ret = opusarium_bitwise_clsb64(&test);
    ASSERT_EQ((uint64_t)test, (uint64_t)0xfffffffe00000000);
    ASSERT_EQ((uint64_t)ret, (uint64_t)32);
}

UTEST(opusarium_archdeps, bitwise_64b_slzb)
{
    uint64_t test;
    uint64_t ret;

    test = 0xffffffffffffffff;
    ret = opusarium_bitwise_slzb64(&test);
    ASSERT_EQ((uint64_t)test, (uint64_t)0xffffffffffffffff);
    ASSERT_EQ((uint64_t)ret, (uint64_t)64);

    test = 0xfffffffffffffffe;
    ret = opusarium_bitwise_slzb64(&test);
    ASSERT_EQ((uint64_t)test, (uint64_t)0xffffffffffffffff);
    ASSERT_EQ((uint64_t)ret, (uint64_t)0);

    test = 0x7fffffffffffffff;
    ret = opusarium_bitwise_slzb64(&test);
    ASSERT_EQ((uint64_t)test, (uint64_t)0xffffffffffffffff);
    ASSERT_EQ((uint64_t)ret, (uint64_t)63);

    test = 0x0000000000000000;
    ret = opusarium_bitwise_slzb64(&test);
    ASSERT_EQ((uint64_t)test, (uint64_t)0x0000000000000001);
    ASSERT_EQ((uint64_t)ret, (uint64_t)0);

    test = 0x000000007fffffff;
    ret = opusarium_bitwise_slzb64(&test);
    ASSERT_EQ((uint64_t)test, (uint64_t)0x00000000ffffffff);
    ASSERT_EQ((uint64_t)ret, (uint64_t)31);
}