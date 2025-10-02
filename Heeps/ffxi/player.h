#ifndef __AS_FFXI_PLAYER_H_INCLUDED__
#define __AS_FFXI_PLAYER_H_INCLUDED__

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

namespace Ashita {
    namespace FFXI {
#pragma pack(1)
        /**
        * FFXI Combat Skill Structure
        */
        typedef struct combatskill_t {
            /* 0x000 */ uint16_t    Level;
            /* 0x002 */ uint16_t    Current;
            /* 0x004 */ uint16_t    Capped;
            /* 0x006 */ uint8_t     Unknown006[2];
        } combatskill_t;

        /**
        * FFXI Craft Skill Structure
        */
        typedef struct craftskill_t {
            /* 0x000 */ uint8_t     Rank;
            /* 0x001 */ uint8_t     Unknown001[3];
            /* 0x004 */ float       Current;
            /* 0x008 */ float       Capped;
        } craftskill_t;

        /**
        * FFXI Player Structure
        */
        typedef struct ffxi_player_t {
            /* 0x0000 */ uint32_t    HealthMax;
            /* 0x0004 */ uint32_t    ManaMax;
            /* 0x0008 */ uint8_t     MainJob;
            /* 0x0009 */ uint8_t     MainJobLevel;
            /* 0x000A */ uint8_t     SubJob;
            /* 0x000B */ uint8_t     SubJobLevel;
            /* 0x000C */ uint16_t    ExpCurrent;
            /* 0x000E */ uint16_t    ExpNeeded;
            /* 0x0010 */ int16_t     Stats[8];
            /* 0x0020 */ int16_t     StatsModifiers[8];
            /* 0x0030 */ int16_t     Attack;
            /* 0x0032 */ int16_t     Defense;
            /* 0x0034 */ int16_t     Resist[8];
            /* 0x0044 */ uint16_t    Title;
            /* 0x0046 */ uint16_t    Rank;
            /* 0x0048 */ uint16_t    RankPoints;
            /* 0x004A */ uint16_t    Homepoint;
            /* 0x004C */ uint8_t     Nation;
            /* 0x004D */ uint8_t     Residence;
            /* 0x004E */ uint16_t    SuLevel;
            /* 0x0050 */ uint8_t     HighestItemLevel;
            /* 0x0051 */ uint8_t     ItemLevel;
            /* 0x0052 */ uint8_t     MainHandItemLevel;
            /* 0x0053 */ uint8_t     Unknown053;
            /* 0x0054 */ uint32_t    UnityFaction;
            /* 0x0058 */ uint32_t    UnityPoints;
            /* 0x005C */ uint16_t    UnityPartialPersonalEvalutionPoints;
            /* 0x005E */ uint16_t    UnityPersonalEvaluationPoints;
            /* 0x0060 */ uint32_t    UnityChatColorFlag;
            /* 0x0064 */ uint8_t     MasteryJob;
            /* 0x0065 */ uint8_t     MasteryJobLevel;
            /* 0x0066 */ uint8_t     MasteryFlags;
            /* 0x0067 */ uint8_t     MasteryUnknown;
            /* 0x0068 */ uint32_t    MasteryExp;
            /* 0x006C */ uint32_t    MasteryExpNeeded;
            /* 0x0070 */ combatskill_t CombatSkills[57];
            /* 0x02D8 */ craftskill_t CraftSkills[8];
            /* 0x0318 */ uint16_t    AbilityRecast[20];
            /* 0x0340 */ uint16_t    AbilityRecastTimerId[20];
            /* 0x0368 */ uint32_t    MountRecast;
            /* 0x036C */ uint32_t    MountRecastTimerId;
            /* 0x0370 */ uint8_t     DataLoadedFlags;
            /* 0x0371 */ uint8_t     Unknown371[3];
            /* 0x0374 */ uint16_t    LimitPoints;
            /* 0x0376 */ uint8_t     MeritPoints;
            /* 0x0377 */ uint8_t     LimitMode;
            /* 0x0378 */ uint32_t    MeritPointsMax;
            /* 0x037C */ uint8_t     Unknown37C[0x74];
            /* 0x03F0 */ uint8_t     HomepointMasks[0x40];
            /* 0x0430 */ uint32_t    IsZoning;
            /* 0x0434 */ uint8_t     Unknown434[0x27C];
            /* 0x06B0 */ uint16_t    CapacityPoints[23];
            /* 0x06DC */ uint16_t    JobPoints[23];
            /* 0x0708 */ uint16_t    JobPointsSpent[23];
            /* 0x0734 */ int16_t     StatusIcons[32];
            /* 0x0774 */ uint8_t     Unknown774[0x550];
            /* 0x0CC4 */ int32_t     StatusTimers[32];
            /* 0x0D44 */ int16_t     Buffs[256];
            /* 0x0F44 */ uint8_t     UnknownF44[0x2D7C];
            /* 0x3CC0 */ uint32_t    PetTP;
            /* 0x3CC4 */ uint32_t    PetMP;
            /* 0x3CC8 */ uint8_t     Unknown3CC8[0x20];
        } ffxi_player_t;
#pragma pack()
    }; // namespace FFXI
}; // namespace Ashita

#endif // __AS_FFXI_PLAYER_H_INCLUDED__