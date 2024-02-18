#ifdef ARDUINO

#ifndef DS4432_ARDUINO_H_
#define DS4432_ARDUINO_H_

#include <ds4432.h>

#include <Arduino.h>
#include <Wire.h>

class DS4432
{
public:
    DS4432(HardwareI2C *wire)
    {
        _writer.parent.write = [](ds4432_i2c_writer_t *parent, uint8_t data[], size_t size)
        {
            _Writer *writer = (_Writer *)parent;
            if (writer == NULL)
            {
                return;
            }

            writer->_wire->beginTransmission(DS4432_SLAVE_ADDRESS);
            for (size_t i = 0; i < size; i++)
            {
                writer->_wire->write(data[i]);
            }
            writer->_wire->endTransmission();
        };
        _writer._wire = wire;

        ds4432_init(&_ds4432, (ds4432_i2c_writer_t *)&_writer);
    }

    ds4432_error_t set(ds4432_memory_address_t addr, ds4432_sign_bit_t sign, uint8_t data)
    {
        return ds4432_set(&_ds4432, addr, sign, data);
    }

private:
    ds4432_t _ds4432;

    struct _Writer
    {
        ds4432_i2c_writer_t parent;
        HardwareI2C *_wire;
    };

    _Writer _writer;
};

#endif // DS4432_ARDUINO_H_

#endif // ARDUINO