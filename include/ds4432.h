#ifndef DS4432_H_
#define DS4432_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>
#include <stdint.h>

#define DS4432_SLAVE_ADDRESS ((uint8_t)0x90)
#define DS4432_DATA_MAX ((uint8_t) /* 0b0111'1111*/ 0x7F)

    typedef int DS4432ErrNo;

#define DS4432_OK /*    */ ((DS4432ErrNo)0)
#define DS4432_EIO /*   */ ((DS4432ErrNo)5)
#define DS4432_EINVAL /**/ ((DS4432ErrNo)22)

    typedef struct DS4432I2CWriter
    {
        DS4432ErrNo (*write)(struct DS4432I2CWriter *writer, uint8_t data[], size_t size);
    } DS4432I2CWriter;

    typedef struct DS4432
    {
        DS4432I2CWriter *writer;
    } DS4432;

    DS4432ErrNo ds4432_init(DS4432 *ds4432, DS4432I2CWriter *writer);
    DS4432ErrNo ds4432_set_out0_sink(DS4432 *ds4432, uint8_t data);
    DS4432ErrNo ds4432_set_out0_source(DS4432 *ds4432, uint8_t data);
    DS4432ErrNo ds4432_set_out1_sink(DS4432 *ds4432, uint8_t data);
    DS4432ErrNo ds4432_set_out1_source(DS4432 *ds4432, uint8_t data);

#ifdef __cplusplus
}
#endif

#endif // DS4432_H_