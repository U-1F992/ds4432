#ifndef DS4432_INTERNAL_H_
#define DS4432_INTERNAL_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <ds4432.h>

#include <assert.h>

    typedef enum DS4432MemoryAddress
    {
        DS4432_OUT0 = 0xF8,
        DS4432_OUT1 = 0xF9
    } DS4432MemoryAddress;

    typedef enum DS4432SignBit
    {
        DS4432_SINK = 0,
        DS4432_SOURCE = 1
    } DS4432SignBit;

    static inline DS4432ErrNo ds4432_internal_set(DS4432 *ds4432, DS4432MemoryAddress addr, DS4432SignBit sign, uint8_t data)
    {
        if (ds4432 == NULL ||
            (addr != DS4432_OUT0 && addr != DS4432_OUT1) ||
            (sign != DS4432_SINK && sign != DS4432_SOURCE) ||
            DS4432_DATA_MAX < data)
        {
            return DS4432_EINVAL;
        }
        assert(ds4432->writer != NULL);

        ds4432->writer->write(ds4432->writer,
                              (uint8_t[]){(uint8_t)addr,
                                          ((uint8_t)sign << 7) | data},
                              2);

        return DS4432_OK;
    }

#ifdef __cplusplus
}
#endif

#endif // DS4432_INTERNAL_H_