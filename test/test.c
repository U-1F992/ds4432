#include <ds4432.h>
#include "test.h"

#include <assert.h>
#include <stdio.h>

int test_init(void)
{
    int cnt = 0;

    typedef struct test_case_t
    {
        ds4432_t *ds4432;
        ds4432_i2c_writer_t *writer;

        ds4432_error_t expected_ret;
        ds4432_i2c_writer_t *expected_writer;
    } test_case_t;

    ds4432_t case_1_ds4432;

    ds4432_i2c_writer_t case_2_writer;

    ds4432_t case_3_ds4432;
    ds4432_i2c_writer_t case_3_writer;

    test_case_t cases[] = {{.ds4432 = NULL, /*     */ .writer = NULL, /*     */ .expected_ret = DS4432_EINVAL},
                           {.ds4432 = &case_1_ds4432, .writer = NULL, /*     */ .expected_ret = DS4432_EINVAL},
                           {.ds4432 = NULL, /*     */ .writer = &case_2_writer, .expected_ret = DS4432_EINVAL},
                           {.ds4432 = &case_3_ds4432, .writer = &case_3_writer, .expected_ret = DS4432_OK, .expected_writer = &case_3_writer}};
    size_t size = sizeof(cases) / sizeof(test_case_t);

    for (size_t i = 0; i < size; i++)
    {
        test_case_t case_ = cases[i];

        ds4432_error_t actual_ret = ds4432_init(case_.ds4432, case_.writer);
        if (case_.expected_ret != actual_ret)
        {
            fprintf(stderr, "index: %d, expected_ret: %s, actual_ret: %s\n",
                    i, TEST_DS4432_ERROR(case_.expected_ret), TEST_DS4432_ERROR(actual_ret));
            cnt++;
            continue;
        }
        if (actual_ret != DS4432_OK)
        {
            continue;
        }

        ds4432_i2c_writer_t *actual_writer = case_.ds4432->_writer;
        if (case_.expected_writer != actual_writer)
        {
            fprintf(stderr, "index: %d, expected_writer: %#x, actual_writer: %#x\n",
                    i, case_.expected_writer, actual_writer);
            cnt++;
            continue;
        }
    }

    return cnt;
}

int test_set(void)
{
    int cnt = 0;

    typedef struct test_case_t
    {
        ds4432_memory_address_t addr;
        ds4432_sign_bit_t sign;
        uint8_t data;

        ds4432_error_t expected_ret;
        uint8_t *expected_data;
        size_t expected_size;
    } test_case_t;

    test_case_t cases[] = {{.addr = DS4432_OUT0, .sign = DS4432_SINK, /*  */ .data = 0, /*  */ .expected_ret = DS4432_OK, .expected_data = (uint8_t[]){0xF8, /* 0b0000'0000 */ 0x00}, .expected_size = 2},
                           {.addr = DS4432_OUT1, .sign = DS4432_SINK, /*  */ .data = 0, /*  */ .expected_ret = DS4432_OK, .expected_data = (uint8_t[]){0xF9, /* 0b0000'0000 */ 0x00}, .expected_size = 2},
                           {.addr = 0, /*     */ .sign = DS4432_SINK, /*  */ .data = 0, /*  */ .expected_ret = DS4432_EINVAL},
                           {.addr = DS4432_OUT0, .sign = DS4432_SOURCE, /**/ .data = 0, /*  */ .expected_ret = DS4432_OK, .expected_data = (uint8_t[]){0xF8, /* 0b1000'0000 */ 0x80}, .expected_size = 2},
                           {.addr = DS4432_OUT1, .sign = DS4432_SOURCE, /**/ .data = 0, /*  */ .expected_ret = DS4432_OK, .expected_data = (uint8_t[]){0xF9, /* 0b1000'0000 */ 0x80}, .expected_size = 2},
                           {.addr = 0, /*     */ .sign = DS4432_SOURCE, /**/ .data = 0, /*  */ .expected_ret = DS4432_EINVAL},
                           {.addr = DS4432_OUT0, .sign = 2, /*            */ .data = 0, /*  */ .expected_ret = DS4432_EINVAL},
                           {.addr = DS4432_OUT1, .sign = 2, /*            */ .data = 0, /*  */ .expected_ret = DS4432_EINVAL},
                           {.addr = 0, /*     */ .sign = 2, /*            */ .data = 0, /*  */ .expected_ret = DS4432_EINVAL},
                           {.addr = DS4432_OUT0, .sign = DS4432_SINK, /*  */ .data = 127, /**/ .expected_ret = DS4432_OK, .expected_data = (uint8_t[]){0xF8, /* 0b0111'1111 */ 0x7F}, .expected_size = 2},
                           {.addr = DS4432_OUT1, .sign = DS4432_SINK, /*  */ .data = 127, /**/ .expected_ret = DS4432_OK, .expected_data = (uint8_t[]){0xF9, /* 0b0111'1111 */ 0x7F}, .expected_size = 2},
                           {.addr = 0, /*     */ .sign = DS4432_SINK, /*  */ .data = 127, /**/ .expected_ret = DS4432_EINVAL},
                           {.addr = DS4432_OUT0, .sign = DS4432_SOURCE, /**/ .data = 127, /**/ .expected_ret = DS4432_OK, .expected_data = (uint8_t[]){0xF8, /* 0b1111'1111 */ 0xFF}, .expected_size = 2},
                           {.addr = DS4432_OUT1, .sign = DS4432_SOURCE, /**/ .data = 127, /**/ .expected_ret = DS4432_OK, .expected_data = (uint8_t[]){0xF9, /* 0b1111'1111 */ 0xFF}, .expected_size = 2},
                           {.addr = 0, /*     */ .sign = DS4432_SOURCE, /**/ .data = 127, /**/ .expected_ret = DS4432_EINVAL},
                           {.addr = DS4432_OUT0, .sign = 2, /*            */ .data = 127, /**/ .expected_ret = DS4432_EINVAL},
                           {.addr = DS4432_OUT1, .sign = 2, /*            */ .data = 127, /**/ .expected_ret = DS4432_EINVAL},
                           {.addr = 0, /*     */ .sign = 2, /*            */ .data = 127, /**/ .expected_ret = DS4432_EINVAL},
                           {.addr = DS4432_OUT0, .sign = DS4432_SINK, /*  */ .data = 128, /**/ .expected_ret = DS4432_EINVAL},
                           {.addr = DS4432_OUT1, .sign = DS4432_SINK, /*  */ .data = 128, /**/ .expected_ret = DS4432_EINVAL},
                           {.addr = 0, /*     */ .sign = DS4432_SINK, /*  */ .data = 128, /**/ .expected_ret = DS4432_EINVAL},
                           {.addr = DS4432_OUT0, .sign = DS4432_SOURCE, /**/ .data = 128, /**/ .expected_ret = DS4432_EINVAL},
                           {.addr = DS4432_OUT1, .sign = DS4432_SOURCE, /**/ .data = 128, /**/ .expected_ret = DS4432_EINVAL},
                           {.addr = 0, /*     */ .sign = DS4432_SOURCE, /**/ .data = 128, /**/ .expected_ret = DS4432_EINVAL},
                           {.addr = DS4432_OUT0, .sign = 2, /*            */ .data = 128, /**/ .expected_ret = DS4432_EINVAL},
                           {.addr = DS4432_OUT1, .sign = 2, /*            */ .data = 128, /**/ .expected_ret = DS4432_EINVAL},
                           {.addr = 0, /*     */ .sign = 2, /*            */ .data = 128, /**/ .expected_ret = DS4432_EINVAL}};
    size_t size = sizeof(cases) / sizeof(test_case_t);

    // Nothing is expected to happen.
    assert(ds4432_set(NULL, DS4432_OUT0, DS4432_SINK, 0) == DS4432_EINVAL);

    for (size_t i = 0; i < size; i++)
    {
        test_case_t case_ = cases[i];

        ds4432_t ds4432;
        test_i2c_writer_t writer;
        test_i2c_writer_init(&writer);
        assert(ds4432_init(&ds4432, (ds4432_i2c_writer_t *)&writer) == DS4432_OK);

        ds4432_error_t actual_ret = ds4432_set(&ds4432, case_.addr, case_.sign, case_.data);
        if (case_.expected_ret != actual_ret)
        {
            fprintf(stderr, "index: %d, expected_ret: %s, actual_ret: %s\n",
                    i, TEST_DS4432_ERROR(case_.expected_ret), TEST_DS4432_ERROR(actual_ret));
            cnt++;
            continue;
        }
        if (actual_ret != DS4432_OK)
        {
            continue;
        }

        size_t actual_size = writer.last_size;
        if (case_.expected_size != actual_size)
        {
            fprintf(stderr, "index: %d, expected_size: %d, actual_size: %d\n",
                    i, case_.expected_size, actual_size);
            cnt++;
            continue;
        }

        uint8_t *actual_data = writer.last_data;
        if (!test_i2c_data_equals(case_.expected_data, actual_data, actual_size))
        {
            fprintf(stderr, "index: %d,\n", i);
            for (size_t j = 0; j < actual_size; j++)
            {
                if (case_.expected_data[j] != actual_data[j])
                {
                    fprintf(stderr, "  expected_data[%d]: %d, actual_data[%d]: %d\n",
                            j, case_.expected_data[j], j, actual_data[j]);
                }
            }
            cnt++;
            continue;
        }
    }

    return cnt;
}

int main(void)
{
    int cnt = 0;

    printf("* test_init\n");
    cnt += test_init();
    printf("* test_set\n");
    cnt += test_set();

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