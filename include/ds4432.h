#ifndef DS4432_H_
#define DS4432_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>
#include <stdint.h>

#define DS4432_SLAVE_ADDRESS ((uint8_t)0x90)
#define DS4432_DATA_MIN ((uint8_t)0)
#define DS4432_DATA_MAX ((uint8_t) /* 0b0111'1111*/ 0x7F)

    typedef struct ds4432_i2c_writer_t
    {
        void (*write)(struct ds4432_i2c_writer_t *writer, uint8_t data[], size_t size);
    } ds4432_i2c_writer_t;

    typedef struct ds4432_t
    {
        ds4432_i2c_writer_t *_writer;
    } ds4432_t;

    typedef enum ds4432_error_t
    {
        DS4432_OK = 0,
        DS4432_EINVAL = 22
    } ds4432_error_t;

    typedef enum ds4432_memory_address_t
    {
        DS4432_OUT0 = 0xF8,
        DS4432_OUT1 = 0xF9
    } ds4432_memory_address_t;

    typedef enum ds4432_sign_bit_t
    {
        DS4432_SINK,
        DS4432_SOURCE
    } ds4432_sign_bit_t;

    ds4432_error_t ds4432_init(ds4432_t *ds4432, ds4432_i2c_writer_t *writer);
    ds4432_error_t ds4432_set(ds4432_t *ds4432, ds4432_memory_address_t addr, ds4432_sign_bit_t sign, uint8_t data);

#ifdef __cplusplus
}
#endif

#endif // DS4432_H_