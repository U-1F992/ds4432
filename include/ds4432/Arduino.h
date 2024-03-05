#ifdef ARDUINO

#ifndef DS4432_ARDUINO_H_
#define DS4432_ARDUINO_H_

#include "../ds4432.h"

#include <Arduino.h>
#include <Wire.h>

#include <assert.h>

class DS4432Wrapper
{
public:
    DS4432Wrapper(HardwareI2C *wire)
    {
        writer_.parent.write = [](DS4432I2CWriter *parent, uint8_t data[], size_t size)
        {
            Writer_ *writer = (Writer_ *)parent;
            if (writer == NULL)
            {
                return DS4432_EINVAL;
            }

            writer->wire_->beginTransmission(DS4432_SLAVE_ADDRESS >> 1);
            writer->wire_->write(data, size);
            writer->wire_->endTransmission();

            return DS4432_OK;
        };
        writer_.wire_ = wire;

        assert(ds4432_init(&ds4432_, (DS4432I2CWriter *)&writer_) == DS4432_OK);
    }

    DS4432ErrNo setOut0Sink(uint8_t data) { return ds4432_set_out0_sink(&ds4432_, data); }
    DS4432ErrNo setOut0Source(uint8_t data) { return ds4432_set_out0_source(&ds4432_, data); }
    DS4432ErrNo setOut1Sink(uint8_t data) { return ds4432_set_out1_sink(&ds4432_, data); }
    DS4432ErrNo setOut1Source(uint8_t data) { return ds4432_set_out1_source(&ds4432_, data); }

private:
    DS4432 ds4432_;
    struct Writer_
    {
        DS4432I2CWriter parent;
        HardwareI2C *wire_;
    } writer_;
};

#endif // DS4432_ARDUINO_H_

#endif // ARDUINO
