//
// Created by zinjk on 09.10.2017.
//

#include "crc.h"


uint16_t crc::update_crc(uint16_t acc, const uint8_t input) {
    const int POLY = 0x1021;
    // Create the CRC "dividend" for polynomial arithmetic (binary arithmetic
    // with no carries)
    acc ^= (input << 8);

    // "Divide" the poly into the dividend using CRC XOR subtraction
    // CRC_acc holds the "remainder" of each divide
    // Only complete this division for 8 bits since input is 1 byte

    for (uint8_t i = 0; i < 8; i++) {
        // Check if the MSB is set (if MSB is 1, then the POLY can "divide"
        // into the "dividend")

        if ((acc & 0x8000) == 0x8000) {
            acc <<= 1;
            acc ^= POLY;
        } else {
            acc <<= 1;
        }
    }

    return acc;
}

uint16_t crc::calculate_crc(const uint8_t *data, const int32_t len) {
    const int SEED = 0xFFFF;
    uint16_t crc_out = SEED;

    for (int32_t i = 0; i < len; i++) {
        crc_out = update_crc(crc_out, data[i]);
    }

    return crc_out;
}