#ifndef __AS_OBJECTS_H_INCLUDED__
#define __AS_OBJECTS_H_INCLUDED__

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <Windows.h>

namespace Ashita
{
    /**
     * Simple rect object used with various features of Ashita.
     */
    struct asrect_t
    {
        uint32_t Top;
        uint32_t Right;
        uint32_t Bottom;
        uint32_t Left;
    };

    /**
     * Simple window information object used with Ashita.
     */
    struct aswindowinfo_t
    {
        HWND        Handle;
        RECT        Rect;
        int32_t     Width;
        int32_t     Height;
        int32_t     ClientWidth;
        int32_t     ClientHeight;
        uint32_t    Style;
        uint32_t    ExtendedStyle;
        WNDPROC     WindowProc;
    };
}; // namespace Ashita

#endif // __AS_OBJECTS_H_INCLUDED__