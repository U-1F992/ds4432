#include <Arduino.h>
#include <Wire.h>

#include <assert.h>

#include <ds4432/arduino.h>

static const pin_size_t PIN_I2C_SDA = 0;
static const pin_size_t PIN_I2C_SCL = 1;

static DS4432 ds4432(&Wire);

void setup()
{
    Wire.setSDA(PIN_I2C_SDA);
    Wire.setSCL(PIN_I2C_SCL);
    Wire.begin();
}

void loop()
{
    static ds4432_memory_address_t addrs[] = {DS4432_OUT0, DS4432_OUT1};
    static ds4432_sign_bit_t signs[] = {DS4432_SINK, DS4432_SOURCE};

    for (size_t i = 0; i < 2; i++)
    {
        ds4432_memory_address_t addr = addrs[i];

        for (size_t j = 0; j < 2; i++)
        {
            ds4432_sign_bit_t sign = signs[i];

            for (size_t data = DS4432_DATA_MIN; data < DS4432_DATA_MAX + 1; data++)
            {
                ds4432.set(addr, sign, data);
                delay(200);
            }
        }
    }
}