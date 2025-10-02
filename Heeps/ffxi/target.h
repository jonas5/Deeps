#ifndef __AS_FFXI_TARGET_H_INCLUDED__
#define __AS_FFXI_TARGET_H_INCLUDED__

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

namespace Ashita {
    namespace FFXI {
#pragma pack(1)
        /**
         * FFXI Target Structure
         */
        typedef struct ffxi_target_t {
            /* 0x000 */ char        Name[0x18];
            /* 0x018 */ uint32_t    HealthPercent;
            /* 0x01C */ uint32_t    TargetIndex;
            /* 0x020 */ uint32_t    ServerId;
            /* 0x024 */ uint32_t    EntityPointer;
            /* 0x028 */ uint32_t    WarpPointer;
            /* 0x02C */ uint8_t     TargetVisible;
            /* 0x02D */ uint8_t     Unknown02D[3];
            /* 0x030 */ uint16_t    Mask;
            /* 0x032 */ uint16_t    CalculatedId;
            /* 0x034 */ uint32_t    SubTargetIndex;
            /* 0x038 */ uint32_t    SubTargetServerId;
            /* 0x03C */ uint32_t    SubTargetEntityPointer;
            /* 0x040 */ uint32_t    SubTargetWarpPointer;
            /* 0x044 */ uint8_t     SubTargetVisible;
            /* 0x045 */ uint8_t     Unknown045[3];
            /* 0x048 */ uint16_t    SubTargetMask;
            /* 0x04A */ uint8_t     SubTargetActive;
            /* 0x04B */ uint8_t     TargetDeactivate;
            /* 0x04C */ uint8_t     IsLockedOn;
            /* 0x04D */ uint8_t     Unknown04D[3];
            /* 0x050 */ uint32_t    TargetSelectionMask;
            /* 0x054 */ uint8_t     IsMenuOpen;
            /* 0x055 */ uint8_t     Unknown055[0xBB];
        } ffxi_target_t;
#pragma pack()
    }; // namespace FFXI
}; // namespace Ashita

#endif // __AS_FFXI_TARGET_H_INCLUDED__