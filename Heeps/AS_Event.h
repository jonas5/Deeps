#ifndef __AS_EVENT_H_INCLUDED__
#define __AS_EVENT_H_INCLUDED__

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <Windows.h>

namespace Ashita
{
    class CEvent
    {
    private:
        HANDLE m_hEvent;

    public:
        CEvent(BOOL bManualReset = FALSE, BOOL bInitialState = FALSE, const char* szName = nullptr)
        {
            this->m_hEvent = ::CreateEventA(nullptr, bManualReset, bInitialState, szName);
        }
        CEvent(BOOL bManualReset, BOOL bInitialState, const wchar_t* szName)
        {
            this->m_hEvent = ::CreateEventW(nullptr, bManualReset, bInitialState, szName);
        }
        ~CEvent()
        {
            if (this->m_hEvent != nullptr)
                ::CloseHandle(this->m_hEvent);
        }

    public:
        HANDLE GetEvent(void)
        {
            return this->m_hEvent;
        }

        void Wait(void)
        {
            if (this->m_hEvent == nullptr)
                return;
            ::WaitForSingleObject(this->m_hEvent, INFINITE);
        }

        bool Wait(uint32_t ms)
        {
            if (this->m_hEvent == nullptr)
                return false;
            return (::WaitForSingleObject(this->m_hEvent, ms) == WAIT_OBJECT_0);
        }

        void Set(void)
        {
            if (this->m_hEvent != nullptr)
                ::SetEvent(this->m_hEvent);
        }

        void Reset(void)
        {
            if (this->m_hEvent != nullptr)
                ::ResetEvent(this->m_hEvent);
        }

        void Pulse(void)
        {
            if (this->m_hEvent != nullptr)
                ::PulseEvent(this->m_hEvent);
        }
    };
}; // namespace Ashita

#endif // __AS_EVENT_H_INCLUDED__