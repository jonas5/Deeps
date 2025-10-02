#ifndef __AS_MEMORY_H_INCLUDED__
#define __AS_MEMORY_H_INCLUDED__

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <Windows.h>
#include <vector>
#include <Psapi.h>

namespace Ashita
{
    namespace Memory
    {
        /**
         * Reads memory from the given address.
         *
         * @param {uintptr_t} address The address to read from.
         * @param {void*} buffer The buffer to read the memory into.
         * @param {uint32_t} size The size of the memory to read.
         * @returns {bool} True on success, false otherwise.
         */
        static bool Read(uintptr_t address, void* buffer, uint32_t size)
        {
            if (IsBadReadPtr((const void*)address, size))
                return false;
            memcpy(buffer, (const void*)address, size);
            return true;
        }

        /**
         * Writes memory to the given address.
         *
         * @param {uintptr_t} address The address to write to.
         * @param {void*} buffer The buffer to write to memory.
         * @param {uint32_t} size The size of the memory to write.
         * @returns {bool} True on success, false otherwise.
         */
        static bool Write(uintptr_t address, void* buffer, uint32_t size)
        {
            if (IsBadWritePtr((void*)address, size))
                return false;
            DWORD oldProt = 0;
            if (VirtualProtect((void*)address, size, PAGE_EXECUTE_READWRITE, &oldProt))
            {
                memcpy((void*)address, buffer, size);
                VirtualProtect((void*)address, size, oldProt, &oldProt);
                return true;
            }
            return false;
        }

        /**
         * Finds a pattern within the given memory range.
         *
         * @param {const char*} pattern The pattern to find.
         * @param {const char*} mask The mask of the pattern to use.
         * @param {uintptr_t} address The address to begin the search at.
         * @param {uint32_t} size The size of the memory to search.
         * @param {uint32_t} offset The offset from the found address to return.
         * @returns {uintptr_t} The address of the found pattern, 0 otherwise.
         */
        static uintptr_t FindPattern(const char* pattern, const char* mask, uintptr_t address, uint32_t size, uint32_t offset)
        {
            char* pData = (char*)address;
            char* pEnd = pData + size - strlen(mask);
            for (; pData < pEnd; ++pData)
            {
                bool bFound = true;
                for (size_t i = 0; i < strlen(mask) && bFound; ++i)
                {
                    bFound &= (mask[i] == '?' || pattern[i] == *(pData + i));
                }
                if (bFound)
                {
                    return (uintptr_t)pData + offset;
                }
            }
            return 0;
        }
    }; // namespace Memory
}; // namespace Ashita

#endif // __AS_MEMORY_H_INCLUDED__