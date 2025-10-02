#ifndef __AS_REGISTRY_H_INCLUDED__
#define __AS_REGISTRY_H_INCLUDED__

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <Windows.h>

namespace Ashita
{
    namespace Registry
    {
        /**
         * Reads a key from the given registry path.
         *
         * @param {HKEY} hKey The root key to read from.
         * @param {const char*} path The path of the key to read.
         * @param {const char*} name The name of the key to read.
         * @param {void*} buffer The buffer to read the key into.
         * @param {uint32_t*} size The size of the buffer.
         * @returns {bool} True on success, false otherwise.
         */
        static bool ReadKey(HKEY hKey, const char* path, const char* name, void* buffer, uint32_t* size)
        {
            HKEY hKeyRead = nullptr;
            if (RegOpenKeyExA(hKey, path, 0, KEY_READ, &hKeyRead) != ERROR_SUCCESS)
                return false;
            if (RegQueryValueExA(hKeyRead, name, 0, nullptr, (LPBYTE)buffer, (LPDWORD)size) != ERROR_SUCCESS)
            {
                RegCloseKey(hKeyRead);
                return false;
            }
            RegCloseKey(hKeyRead);
            return true;
        }

        /**
         * Writes a key to the given registry path.
         *
         * @param {HKEY} hKey The root key to write to.
         * @param {const char*} path The path of the key to write.
         * @param {const char*} name The name of the key to write.
         * @param {uint32_t} type The type of the key to write.
         * @param {void*} buffer The buffer to write from.
         * @param {uint32_t} size The size of the buffer.
         * @returns {bool} True on success, false otherwise.
         */
        static bool WriteKey(HKEY hKey, const char* path, const char* name, uint32_t type, void* buffer, uint32_t size)
        {
            HKEY hKeyWrite = nullptr;
            if (RegCreateKeyExA(hKey, path, 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_WRITE, nullptr, &hKeyWrite, nullptr) != ERROR_SUCCESS)
                return false;
            if (RegSetValueExA(hKeyWrite, name, 0, type, (const BYTE*)buffer, size) != ERROR_SUCCESS)
            {
                RegCloseKey(hKeyWrite);
                return false;
            }
            RegCloseKey(hKeyWrite);
            return true;
        }
    }; // namespace Registry
}; // namespace Ashita

#endif // __AS_REGISTRY_H_INCLUDED__