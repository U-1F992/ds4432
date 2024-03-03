#include <ds4432.h>
#include "internal.h"

DS4432ErrNo ds4432_init(DS4432 *ds4432, DS4432I2CWriter *writer)
{
    if (ds4432 == NULL ||
        writer == NULL)
    {
        return DS4432_EINVAL;
    }

    ds4432->writer = writer;

    return DS4432_OK;
}

DS4432ErrNo ds4432_set_out0_sink(DS4432 *ds4432, uint8_t data)
{
    return ds4432_internal_set(ds4432, DS4432_OUT0, DS4432_SINK, data);
}

DS4432ErrNo ds4432_set_out0_source(DS4432 *ds4432, uint8_t data)
{
    return ds4432_internal_set(ds4432, DS4432_OUT0, DS4432_SOURCE, data);
}

DS4432ErrNo ds4432_set_out1_sink(DS4432 *ds4432, uint8_t data)
{
    return ds4432_internal_set(ds4432, DS4432_OUT1, DS4432_SINK, data);
}

DS4432ErrNo ds4432_set_out1_source(DS4432 *ds4432, uint8_t data)
{
    return ds4432_internal_set(ds4432, DS4432_OUT1, DS4432_SOURCE, data);
}