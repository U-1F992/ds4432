#include <ds4432.h>

ds4432_error_t ds4432_init(ds4432_t *dac, ds4432_i2c_writer_t *i2c)
{
    if (dac == NULL ||
        i2c == NULL)
    {
        return DS4432_EINVAL;
    }

    dac->_i2c = i2c;

    return DS4432_OK;
}

ds4432_error_t ds4432_set(ds4432_t *dac, ds4432_memory_address_t addr, ds4432_sign_bit_t sign, uint8_t data)
{
    if (dac == NULL ||
        (addr != DS4432_OUT0 && addr != DS4432_OUT1) ||
        (sign != DS4432_SINK && sign != DS4432_SOURCE) ||
        DS4432_DATA_MAX < data)
    {
        return DS4432_EINVAL;
    }

    dac->_i2c->write(dac->_i2c,
                     (uint8_t[]){(uint8_t)addr,
                                 ((uint8_t)sign << 7) | data},
                     2);

    return DS4432_OK;
}