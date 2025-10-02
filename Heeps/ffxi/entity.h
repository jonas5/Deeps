#ifndef __AS_FFXI_ENTITY_H_INCLUDED__
#define __AS_FFXI_ENTITY_H_INCLUDED__

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

namespace Ashita {
    namespace FFXI {
        /**
         * FFXI Entity Structure
         */
#pragma pack(1)
        typedef struct ffxi_entity_t {
            /* 0x000 */ float       LocalPosition[3];
            /* 0x00C */ float       LocalRotation[3];
            /* 0x018 */ float       LastPosition[3];
            /* 0x024 */ float       LastRotation[3];
            /* 0x030 */ float       MovePosition[3];
            /* 0x03C */ uint32_t    TargetIndex;
            /* 0x040 */ uint32_t    ServerId;
            /* 0x044 */ char        Name[0x18];
            /* 0x05C */ float       Speed;
            /* 0x060 */ float       AnimationSpeed;
            /* 0x064 */ uint32_t    WarpPointer;
            /* 0x068 */ float       Distance;
            /* 0x06C */ float       Heading;
            /* 0x070 */ uint32_t    PetOwnerId;
            /* 0x074 */ uint8_t     HealthPercent;
            /* 0x075 */ uint8_t     ManaPercent;
            /* 0x076 */ uint8_t     EntityType;
            /* 0x077 */ uint8_t     Race;
            /* 0x078 */ uint16_t    ModelFade;
            /* 0x07A */ uint16_t    LookHair;
            /* 0x07C */ uint16_t    LookHead;
            /* 0x07E */ uint16_t    LookBody;
            /* 0x080 */ uint16_t    LookHands;
            /* 0x082 */ uint16_t    LookLegs;
            /* 0x084 */ uint16_t    LookFeet;
            /* 0x086 */ uint16_t    LookMain;
            /* 0x088 */ uint16_t    LookSub;
            /* 0x08A */ uint16_t    LookRanged;
            /* 0x08C */ uint16_t    ActionTimer1;
            /* 0x08E */ uint16_t    ActionTimer2;
            /* 0x090 */ uint32_t    RenderFlags0;
            /* 0x094 */ uint32_t    RenderFlags1;
            /* 0x098 */ uint32_t    RenderFlags2;
            /* 0x09C */ uint32_t    RenderFlags3;
            /* 0x0A0 */ uint32_t    RenderFlags4;
            /* 0x0A4 */ uint16_t    NpcSpeechLoop;
            /* 0x0A6 */ uint16_t    NpcSpeechFrame;
            /* 0x0A8 */ float       Speed2;
            /* 0x0AC */ uint16_t    NpcWalkPosition1;
            /* 0x0AE */ uint16_t    NpcWalkPosition2;
            /* 0x0B0 */ uint16_t    NpcWalkMode;
            /* 0x0B2 */ uint16_t    CostumeId;
            /* 0x0B4 */ uint32_t    Status;
            /* 0x0B8 */ uint32_t    StatusServer;
            /* 0x0BC */ uint32_t    StatusNpcChat;
            /* 0x0C0 */ uint32_t    ClaimServerId;
            /* 0x0C4 */ uint8_t     Animations[0x40];
            /* 0x104 */ uint16_t    AnimationTick;
            /* 0x106 */ uint16_t    AnimationStep;
            /* 0x108 */ uint8_t     AnimationPlay;
            /* 0x109 */ uint8_t     Unknown109[3];
            /* 0x10C */ uint16_t    EmoteTargetIndex;
            /* 0x10E */ uint16_t    EmoteId;
            /* 0x110 */ uint32_t    EmoteIdString;
            /* 0x114 */ uint32_t    EmoteTargetWarpPointer;
            /* 0x118 */ uint32_t    SpawnFlags;
            /* 0x11C */ uint32_t    LinkshellColor;
            /* 0x120 */ uint16_t    NameColor;
            /* 0x122 */ uint16_t    CampaignNameFlag;
            /* 0x124 */ uint16_t    FishingTimer;
            /* 0x126 */ uint16_t    FishingCastTimer;
            /* 0x128 */ uint32_t    FishingUnknown1;
            /* 0x12C */ uint32_t    FishingUnknown2;
            /* 0x130 */ uint16_t    FishingUnknown3;
            /* 0x132 */ uint16_t    TargetedIndex;
            /* 0x134 */ uint16_t    PetTargetIndex;
            /* 0x136 */ uint8_t     BallistaScoreFlag;
            /* 0x137 */ uint8_t     PankrationEnabled;
            /* 0x138 */ uint8_t     PankrationFlagFlip;
            /* 0x139 */ uint8_t     Unknown139[3];
            /* 0x13C */ float       ModelSize;
            /* 0x140 */ uint16_t    MonstrosityFlag;
            /* 0x142 */ uint16_t    MonstrosityNameId;
            /* 0x144 */ char        MonstrosityName[0x20];
            /* 0x164 */ uint8_t     Unknown164[0x98];
        } ffxi_entity_t;
#pragma pack()
    }; // namespace FFXI
}; // namespace Ashita

#endif // __AS_FFXI_ENTITY_H_INCLUDED__