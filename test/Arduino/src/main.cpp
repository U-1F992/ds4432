#include <ds4432/Arduino.h>

#include <Arduino.h>
#include <Wire.h>

#include <assert.h>
#include <errno.h>

static const pin_size_t PIN_I2C_SDA = 0;
static const pin_size_t PIN_I2C_SCL = 1;
static const pin_size_t PIN_OUT0 = 26;
static const pin_size_t PIN_OUT1 = 27;

static DS4432Wrapper ds4432(&Wire);

void setup()
{
    Serial.begin();

    pinMode(PIN_OUT0, INPUT);
    pinMode(PIN_OUT1, INPUT);

    Wire.setSDA(PIN_I2C_SDA);
    Wire.setSCL(PIN_I2C_SCL);
    Wire.begin();
}

void out0()
{
    Serial.println("===== OUT0 - Sink =====");
    for (size_t i = 0; i < 0b10000000; i++)
    {
        ds4432.setOut0Sink(0b1111111 - i);
        delay(1);
        Serial.println(analogRead(PIN_OUT0));

        delay(50);
    }

    Serial.println("===== OUT0 - Source =====");
    for (size_t i = 0; i < 0b10000000; i++)
    {
        ds4432.setOut0Source(i);
        delay(1);
        Serial.println(analogRead(PIN_OUT0));

        delay(50);
    }

    ds4432.setOut0Sink(0);
}

void out1()
{
    Serial.println("===== OUT1 - Sink =====");
    for (size_t i = 0; i < 0b10000000; i++)
    {
        ds4432.setOut1Sink(0b1111111 - i);
        delay(1);
        Serial.println(analogRead(PIN_OUT1));

        delay(50);
    }

    Serial.println("===== OUT1 - Source =====");
    for (size_t i = 0; i < 0b10000000; i++)
    {
        ds4432.setOut1Source(i);
        delay(1);
        Serial.println(analogRead(PIN_OUT1));

        delay(50);
    }

    ds4432.setOut1Sink(0);
}

void loop()
{
    out0();
    out1();

    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}