#ifndef TEST_H_
#define TEST_H_

#include <ds4432.h>

#include <assert.h>
#include <stdbool.h>

#define TEST_FOR(cases) \
    TestCase case_;     \
    for (size_t i = 0; case_ = (cases)[i], i < sizeof((cases)) / sizeof(TestCase); i++)

#define TEST_DS4432_ERROR(err) ((err) == DS4432_OK       ? "DS4432_OK"     \
                                : (err) == DS4432_EINVAL ? "DS4432_EINVAL" \
                                : (err) == DS4432_EIO    ? "DS4432_EIO"    \
                                                         : "")

#define TEST_ASSERT_EQUAL_DS4432_ERROR_RET(expected_ret, actual_ret)                    \
    if ((expected_ret) != (actual_ret))                                                 \
    {                                                                                   \
        fprintf(stderr, "index: %d, expected_ret: %s, actual_ret: %s\n",                \
                i, TEST_DS4432_ERROR((expected_ret)), TEST_DS4432_ERROR((actual_ret))); \
        cnt++;                                                                          \
        continue;                                                                       \
    }

#define TEST_I2C_SIZE ((size_t)8)

typedef struct TestI2CWriter
{
    DS4432I2CWriter parent;
    uint8_t last_data[TEST_I2C_SIZE];
    size_t last_size;
} TestI2CWriter;

DS4432ErrNo test_i2c_writer_write(DS4432I2CWriter *parent, uint8_t data[], size_t size)
{
    assert(size < TEST_I2C_SIZE);
    TestI2CWriter *i2c = (TestI2CWriter *)parent;
    for (size_t i = 0; i < size; i++)
    {
        i2c->last_data[i] = data[i];
    }
    i2c->last_size = size;
    return DS4432_OK;
}

#define test_i2c_writer_init(i2c) ((i2c)->parent.write = test_i2c_writer_write, \
                                   (i2c)->last_size = 0,                        \
                                   (void)0)

bool test_i2c_data_equals(uint8_t arr0[], uint8_t arr1[], size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (arr0[i] != arr1[i])
        {
            return false;
        }
    }
    return true;
}

#define TEST_ASSERT_EQUAL_I2C_WRITTEN(expected_data, expected_size, actual_data, actual_size) \
    if ((expected_size) != (actual_size))                                                     \
    {                                                                                         \
        fprintf(stderr, "index: %d, expected_size: %d, actual_size: %d\n",                    \
                i, (expected_size), (actual_size));                                           \
        cnt++;                                                                                \
        continue;                                                                             \
    }                                                                                         \
    if (!test_i2c_data_equals((expected_data), (actual_data), (actual_size)))                 \
    {                                                                                         \
        fprintf(stderr, "index: %d,\n", i);                                                   \
        for (size_t j = 0; j < (actual_size); j++)                                            \
        {                                                                                     \
            if ((expected_data)[j] != (actual_data)[j])                                       \
            {                                                                                 \
                fprintf(stderr, "  expected_data[%d]: %d, actual_data[%d]: %d\n",             \
                        j, (expected_data)[j], j, (actual_data)[j]);                          \
            }                                                                                 \
        }                                                                                     \
        cnt++;                                                                                \
        continue;                                                                             \
    }

#endif // TEST_H_