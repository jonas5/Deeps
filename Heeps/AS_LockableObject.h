#ifndef __AS_LOCKABLEOBJECT_H_INCLUDED__
#define __AS_LOCKABLEOBJECT_H_INCLUDED__

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <Windows.h>

namespace Ashita
{
    /**
    * To be used with the CLockableObject class.
    * This will automatically handle the locking and unlocking of a critical section.
    */
    class CAutoLock
    {
    private:
        CRITICAL_SECTION* m_pLock;

    public:
        CAutoLock(CRITICAL_SECTION* pLock)
        {
            m_pLock = pLock;
            ::EnterCriticalSection(m_pLock);
        }
        ~CAutoLock()
        {
            ::LeaveCriticalSection(m_pLock);
        }
    };

    /**
    * A simple lockable object class that allows easy use of critical sections.
    */
    class CLockableObject
    {
    private:
        CRITICAL_SECTION m_Lock;

    public:
        CLockableObject(void)
        {
            ::InitializeCriticalSection(&m_Lock);
        }
        ~CLockableObject(void)
        {
            ::DeleteCriticalSection(&m_Lock);
        }

    public:
        void Lock(void)
        {
            ::EnterCriticalSection(&m_Lock);
        }
        void Unlock(void)
        {
            ::LeaveCriticalSection(&m_Lock);
        }
    };
}; // namespace Ashita

#endif // __AS_LOCKABLEOBJECT_H_INCLUDED__