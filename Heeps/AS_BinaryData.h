#ifndef __AS_BINARYDATA_H_INCLUDED__
#define __AS_BINARYDATA_H_INCLUDED__

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

namespace Ashita
{
    namespace BinaryData
    {
        /**
         * Unpacks bits from the given data buffer. (Little Endian)
         *
         * @param {uint8_t*} data - The data to unpack from.
         * @param {uint32_t} bit - The starting bit to read from.
         * @param {uint32_t} size - The number of bits to read.
         * @returns {uint64_t} The unpacked data from the buffer.
         */
        static uint64_t UnpackBitsLE(uint8_t* data, uint32_t bit, uint32_t size)
        {
            uint64_t temp = 0;
            memcpy(&temp, &data[bit / 8], 8);
            return (temp >> (bit % 8)) & ((1ULL << size) - 1);
        }

        /**
         * Unpacks bits from the given data buffer. (Big Endian)
         *
         * @param {uint8_t*} data - The data to unpack from.
         * @param {uint32_t} bit - The starting bit to read from.
         * @param {uint32_t} size - The number of bits to read.
         * @returns {uint64_t} The unpacked data from the buffer.
         */
        static uint64_t UnpackBitsBE(uint8_t* data, uint32_t bit, uint32_t size)
        {
            uint64_t temp = 0;
            uint8_t* p = (uint8_t*)&temp;
            uint8_t* d = &data[bit / 8];

            for (uint32_t x = 0; x < 8; ++x)
                p[x] = d[7 - x];

            return (temp >> (64 - (bit % 8) - size)) & ((1ULL << size) - 1);
        }

        /**
         * Packs bits into the given data buffer. (Little Endian)
         *
         * @param {uint8_t*} data - The data to pack into.
         * @param {uint32_t} bit - The starting bit to write to.
         * @param {uint32_t} size - The number of bits to write.
         * @param {uint64_t} value - The value to pack into the buffer.
         */
        static void PackBitsLE(uint8_t* data, uint32_t bit, uint32_t size, uint64_t value)
        {
            uint64_t temp = 0;
            memcpy(&temp, &data[bit / 8], 8);
            temp &= ~(((1ULL << size) - 1) << (bit % 8));
            temp |= (value & ((1ULL << size) - 1)) << (bit % 8);
            memcpy(&data[bit / 8], &temp, 8);
        }

        /**
         * Packs bits into the given data buffer. (Big Endian)
         *
         * @param {uint8_t*} data - The data to pack into.
         * @param {uint32_t} bit - The starting bit to write to.
         * @param {uint32_t} size - The number of bits to write.
         * @param {uint64_t} value - The value to pack into the buffer.
         */
        static void PackBitsBE(uint8_t* data, uint32_t bit, uint32_t size, uint64_t value)
        {
            uint64_t temp = 0;
            uint8_t* p = (uint8_t*)&temp;
            uint8_t* d = &data[bit / 8];

            for (uint32_t x = 0; x < 8; ++x)
                p[x] = d[7 - x];

            temp &= ~(((1ULL << size) - 1) << (64 - (bit % 8) - size));
            temp |= (value & ((1ULL << size) - 1)) << (64 - (bit % 8) - size);

            for (uint32_t x = 0; x < 8; ++x)
                d[x] = p[7 - x];
        }
    }; // namespace BinaryData
}; // namespace Ashita

#endif // __AS_BINARYDATA_H_INCLUDED__