#ifndef __AS_EXCEPTION_H_INCLUDED__
#define __AS_EXCEPTION_H_INCLUDED__

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <Windows.h>
#include <exception>

namespace Ashita
{
    class CException : public std::exception
    {
    private:
        char        m_szMessage[1024];
        uint32_t    m_nCode;

    public:
        CException(const char* szMessage, uint32_t nCode)
        {
            strcpy_s(this->m_szMessage, 1024, szMessage);
            this->m_nCode = nCode;
        }
        CException(const CException& ex)
        {
            strcpy_s(this->m_szMessage, 1024, ex.m_szMessage);
            this->m_nCode = ex.m_nCode;
        }

    public:
        CException& operator = (const CException& ex)
        {
            strcpy_s(this->m_szMessage, 1024, ex.m_szMessage);
            this->m_nCode = ex.m_nCode;
            return *this;
        }

        const char* what(void) const
        {
            return this->m_szMessage;
        }

        uint32_t code(void) const
        {
            return this->m_nCode;
        }
    };
}; // namespace Ashita

#endif // __AS_EXCEPTION_H_INCLUDED__