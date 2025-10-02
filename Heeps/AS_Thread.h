#ifndef __AS_THREAD_H_INCLUDED__
#define __AS_THREAD_H_INCLUDED__

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <Windows.h>

namespace Ashita
{
    class CThread
    {
    private:
        HANDLE      m_hThread;
        uint32_t    m_nThreadId;

    public:
        CThread(void)
        {
            this->m_hThread     = nullptr;
            this->m_nThreadId   = 0;
        }
        ~CThread(void)
        {
            if (this->m_hThread != nullptr)
                ::CloseHandle(this->m_hThread);
        }

    public:
        bool Create(LPTHREAD_START_ROUTINE lpStartAddress, void* pArgs = nullptr)
        {
            if (this->m_hThread != nullptr)
                return false;
            this->m_hThread = ::CreateThread(nullptr, 0, lpStartAddress, pArgs, 0, (LPDWORD)&this->m_nThreadId);
            return (this->m_hThread != nullptr);
        }

        bool Terminate(uint32_t nExitCode = 0)
        {
            if (this->m_hThread == nullptr)
                return false;

            BOOL bResult = ::TerminateThread(this->m_hThread, nExitCode);

            ::CloseHandle(this->m_hThread);
            this->m_hThread     = nullptr;
            this->m_nThreadId   = 0;

            return (bResult == TRUE);
        }

        void Wait(uint32_t nTimeout = INFINITE)
        {
            if (this->m_hThread == nullptr)
                return;
            ::WaitForSingleObject(this->m_hThread, nTimeout);
        }

        bool IsRunning(void)
        {
            if (this->m_hThread == nullptr)
                return false;

            DWORD nExitCode = 0;
            ::GetExitCodeThread(this->m_hThread, &nExitCode);

            return (nExitCode == STILL_ACTIVE);
        }

        void Suspend(void)
        {
            if (this->m_hThread == nullptr)
                return;
            ::SuspendThread(this->m_hThread);
        }

        void Resume(void)
        {
            if (this->m_hThread == nullptr)
                return;
            ::ResumeThread(this->m_hThread);
        }

        void SetPriority(int nPriority)
        {
            if (this->m_hThread == nullptr)
                return;
            ::SetThreadPriority(this->m_hThread, nPriority);
        }

        int GetPriority(void)
        {
            if (this->m_hThread == nullptr)
                return THREAD_PRIORITY_ERROR_RETURN;
            return ::GetThreadPriority(this->m_hThread);
        }

        uint32_t GetThreadId(void)
        {
            return this->m_nThreadId;
        }

        HANDLE GetThreadHandle(void)
        {
            return this->m_hThread;
        }
    };
}; // namespace Ashita

#endif // __AS_THREAD_H_INCLUDED__