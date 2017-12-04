//
// Created by zinjk on 09.10.2017.
//

#ifndef OVERWATER_FIRMWARE_CRC_H
#define OVERWATER_FIRMWARE_CRC_H
#include <stdint.h>

namespace crc {
    uint16_t update_crc(uint16_t acc, const uint8_t input);

    uint16_t calculate_crc(const uint8_t *data, const int32_t len);
};


#endif //OVERWATER_FIRMWARE_CRC_H
