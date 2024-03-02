#include <ds4432/Arduino.h>

#include <Arduino.h>
#include <Wire.h>

#include <assert.h>
#include <errno.h>

static const pin_size_t PIN_I2C_SDA = 0;
static const pin_size_t PIN_I2C_SCL = 1;

static DS4432Wrapper ds4432(&Wire);

void setup()
{
    Wire.setSDA(PIN_I2C_SDA);
    Wire.setSCL(PIN_I2C_SCL);
    Wire.begin();
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}