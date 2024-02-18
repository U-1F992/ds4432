#ifndef TEST_H_
#define TEST_H_

#include <ds4432.h>

#include <assert.h>
#include <stdbool.h>

#define TEST_DS4432_ERROR(err) ((err) == DS4432_EINVAL ? "DS4432_EINVAL" \
                                                       : "DS4432_OK")

#define TEST_I2C_SIZE ((size_t)8)

typedef struct test_i2c_writer_t
{
    ds4432_i2c_writer_t parent;
    uint8_t last_data[TEST_I2C_SIZE];
    size_t last_size;
} test_i2c_writer_t;

void test_i2c_writer_write(ds4432_i2c_writer_t *parent, uint8_t data[], size_t size)
{
    assert(size < TEST_I2C_SIZE);
    test_i2c_writer_t *i2c = (test_i2c_writer_t *)parent;
    for (size_t i = 0; i < size; i++)
    {
        i2c->last_data[i] = data[i];
    }
    i2c->last_size = size;
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

#endif // TEST_H_