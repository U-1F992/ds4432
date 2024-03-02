#include <ds4432.h>
#include "test.h"

#include <assert.h>
#include <stdio.h>

int test_init(void)
{
    printf("* %s\n", __func__);
    int cnt = 0;

    typedef struct TestCase
    {
        DS4432 *ds4432;
        DS4432I2CWriter *writer;

        DS4432ErrNo expected_ret;
        DS4432I2CWriter *expected_writer;
    } TestCase;

    DS4432 ds4432[4];
    DS4432I2CWriter writer[4];

    TestCase cases[] = {{.ds4432 = NULL, /* */ .writer = NULL, /* */ .expected_ret = DS4432_EINVAL},
                        {.ds4432 = &ds4432[1], .writer = NULL, /* */ .expected_ret = DS4432_EINVAL},
                        {.ds4432 = NULL, /* */ .writer = &writer[2], .expected_ret = DS4432_EINVAL},
                        {.ds4432 = &ds4432[3], .writer = &writer[3], .expected_ret = DS4432_OK, .expected_writer = &writer[3]}};

    TEST_FOR(cases)
    {
        DS4432ErrNo actual_ret = ds4432_init(case_.ds4432, case_.writer);
        TEST_ASSERT_EQUAL_DS4432_ERROR_RET(case_.expected_ret, actual_ret)
        if (actual_ret != DS4432_OK)
        {
            continue;
        }

        DS4432I2CWriter *actual_writer = case_.ds4432->writer;
        if (case_.expected_writer != actual_writer)
        {
            fprintf(stderr, "index: %d, expected_writer: %#x, actual_writer: %#x\n",
                    i, case_.expected_writer, actual_writer);
            cnt++;
        }
    }

    return cnt;
}

int test_set_out0_sink(void)
{
    printf("* %s\n", __func__);
    int cnt = 0;

    typedef struct TestCase
    {
        uint8_t data;

        DS4432ErrNo expected_ret;
        uint8_t *expected_data;
        size_t expected_size;
    } TestCase;

    TestCase cases[] = {{.data = 0, /*  */ .expected_ret = DS4432_OK, .expected_data = (uint8_t[]){0xF8, /* 0b0000'0000 */ 0x00}, .expected_size = 2},
                        {.data = 127, /**/ .expected_ret = DS4432_OK, .expected_data = (uint8_t[]){0xF8, /* 0b0111'1111 */ 0x7F}, .expected_size = 2},
                        {.data = 128, /**/ .expected_ret = DS4432_EINVAL}};

    TEST_FOR(cases)
    {
        DS4432 *ds4432_null = NULL;
        DS4432ErrNo actual_ret = ds4432_set_out0_sink(ds4432_null, case_.data);
        TEST_ASSERT_EQUAL_DS4432_ERROR_RET(DS4432_EINVAL, actual_ret);

        DS4432 ds4432;
        TestI2CWriter writer;
        test_i2c_writer_init(&writer);
        assert(ds4432_init(&ds4432, (DS4432I2CWriter *)&writer) == DS4432_OK);

        actual_ret = ds4432_set_out0_sink(&ds4432, case_.data);
        TEST_ASSERT_EQUAL_DS4432_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != DS4432_OK)
        {
            continue;
        }

        uint8_t *actual_data = writer.last_data;
        size_t actual_size = writer.last_size;
        TEST_ASSERT_EQUAL_I2C_WRITTEN(case_.expected_data, case_.expected_size, actual_data, actual_size);
    }

    return cnt;
}

int test_set_out0_source(void)
{
    printf("* %s\n", __func__);
    int cnt = 0;

    typedef struct TestCase
    {
        uint8_t data;

        DS4432ErrNo expected_ret;
        uint8_t *expected_data;
        size_t expected_size;
    } TestCase;

    TestCase cases[] = {{.data = 0, /*  */ .expected_ret = DS4432_OK, .expected_data = (uint8_t[]){0xF8, /* 0b1000'0000 */ 0x80}, .expected_size = 2},
                        {.data = 127, /**/ .expected_ret = DS4432_OK, .expected_data = (uint8_t[]){0xF8, /* 0b1111'1111 */ 0xFF}, .expected_size = 2},
                        {.data = 128, /**/ .expected_ret = DS4432_EINVAL}};

    TEST_FOR(cases)
    {
        DS4432 *ds4432_null = NULL;
        DS4432ErrNo actual_ret = ds4432_set_out0_source(ds4432_null, case_.data);
        TEST_ASSERT_EQUAL_DS4432_ERROR_RET(DS4432_EINVAL, actual_ret);

        DS4432 ds4432;
        TestI2CWriter writer;
        test_i2c_writer_init(&writer);
        assert(ds4432_init(&ds4432, (DS4432I2CWriter *)&writer) == DS4432_OK);

        actual_ret = ds4432_set_out0_source(&ds4432, case_.data);
        TEST_ASSERT_EQUAL_DS4432_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != DS4432_OK)
        {
            continue;
        }

        uint8_t *actual_data = writer.last_data;
        size_t actual_size = writer.last_size;
        TEST_ASSERT_EQUAL_I2C_WRITTEN(case_.expected_data, case_.expected_size, actual_data, actual_size);
    }

    return cnt;
}

int test_set_out1_sink(void)
{
    printf("* %s\n", __func__);
    int cnt = 0;

    typedef struct TestCase
    {
        uint8_t data;

        DS4432ErrNo expected_ret;
        uint8_t *expected_data;
        size_t expected_size;
    } TestCase;

    TestCase cases[] = {{.data = 0, /*  */ .expected_ret = DS4432_OK, .expected_data = (uint8_t[]){0xF9, /* 0b0000'0000 */ 0x00}, .expected_size = 2},
                        {.data = 127, /**/ .expected_ret = DS4432_OK, .expected_data = (uint8_t[]){0xF9, /* 0b0111'1111 */ 0x7F}, .expected_size = 2},
                        {.data = 128, /**/ .expected_ret = DS4432_EINVAL}};

    TEST_FOR(cases)
    {
        DS4432 *ds4432_null = NULL;
        DS4432ErrNo actual_ret = ds4432_set_out1_sink(ds4432_null, case_.data);
        TEST_ASSERT_EQUAL_DS4432_ERROR_RET(DS4432_EINVAL, actual_ret);

        DS4432 ds4432;
        TestI2CWriter writer;
        test_i2c_writer_init(&writer);
        assert(ds4432_init(&ds4432, (DS4432I2CWriter *)&writer) == DS4432_OK);

        actual_ret = ds4432_set_out1_sink(&ds4432, case_.data);
        TEST_ASSERT_EQUAL_DS4432_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != DS4432_OK)
        {
            continue;
        }

        uint8_t *actual_data = writer.last_data;
        size_t actual_size = writer.last_size;
        TEST_ASSERT_EQUAL_I2C_WRITTEN(case_.expected_data, case_.expected_size, actual_data, actual_size);
    }

    return cnt;
}

int test_set_out1_source(void)
{
    printf("* %s\n", __func__);
    int cnt = 0;

    typedef struct TestCase
    {
        uint8_t data;

        DS4432ErrNo expected_ret;
        uint8_t *expected_data;
        size_t expected_size;
    } TestCase;

    TestCase cases[] = {{.data = 0, /*  */ .expected_ret = DS4432_OK, .expected_data = (uint8_t[]){0xF9, /* 0b1000'0000 */ 0x80}, .expected_size = 2},
                        {.data = 127, /**/ .expected_ret = DS4432_OK, .expected_data = (uint8_t[]){0xF9, /* 0b1111'1111 */ 0xFF}, .expected_size = 2},
                        {.data = 128, /**/ .expected_ret = DS4432_EINVAL}};

    TEST_FOR(cases)
    {
        DS4432 *ds4432_null = NULL;
        DS4432ErrNo actual_ret = ds4432_set_out1_source(ds4432_null, case_.data);
        TEST_ASSERT_EQUAL_DS4432_ERROR_RET(DS4432_EINVAL, actual_ret);

        DS4432 ds4432;
        TestI2CWriter writer;
        test_i2c_writer_init(&writer);
        assert(ds4432_init(&ds4432, (DS4432I2CWriter *)&writer) == DS4432_OK);

        actual_ret = ds4432_set_out1_source(&ds4432, case_.data);
        TEST_ASSERT_EQUAL_DS4432_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != DS4432_OK)
        {
            continue;
        }

        uint8_t *actual_data = writer.last_data;
        size_t actual_size = writer.last_size;
        TEST_ASSERT_EQUAL_I2C_WRITTEN(case_.expected_data, case_.expected_size, actual_data, actual_size);
    }

    return cnt;
}

int main(void)
{
    int cnt = 0;

    cnt += test_init();
    cnt += test_set_out0_sink();
    cnt += test_set_out0_source();
    cnt += test_set_out1_sink();
    cnt += test_set_out1_source();

    if (cnt == 0)
    {
        printf("OK\n");
        return 0;
    }
    else
    {
        fprintf(stderr, "%d errors found.\n", cnt);
        return 1;
    }
}