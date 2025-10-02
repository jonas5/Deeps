#ifndef __AS_FFXI_PARTY_H_INCLUDED__
#define __AS_FFXI_PARTY_H_INCLUDED__

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

namespace Ashita {
    namespace FFXI {
#pragma pack(1)
        /**
        * FFXI Party Member Structure
        */
        typedef struct partymember_t {
            /* 0x000 */ uint8_t     Index;
            /* 0x001 */ uint8_t     Number;
            /* 0x002 */ uint8_t     Unknown002[2];
            /* 0x004 */ char        Name[0x18];
            /* 0x01C */ uint32_t    ServerId;
            /* 0x020 */ uint32_t    TargetIndex;
            /* 0x024 */ uint32_t    CurrentHP;
            /* 0x028 */ uint32_t    CurrentMP;
            /* 0x02C */ uint32_t    CurrentTP;
            /* 0x030 */ uint8_t     CurrentHPP;
            /* 0x031 */ uint8_t     CurrentMPP;
            /* 0x032 */ uint16_t    Zone;
            /* 0x034 */ uint32_t    FlagMask;
            /* 0x038 */ uint8_t     MainJob;
            /* 0x039 */ uint8_t     MainJobLevel;
            /* 0x03A */ uint8_t     SubJob;
            /* 0x03B */ uint8_t     SubJobLvl;
            /* 0x03C */ uint32_t    ServerId2;
            /* 0x040 */ uint8_t     CurrentHPP2;
            /* 0x041 */ uint8_t     CurrentMPP2;
            /* 0x042 */ uint8_t     Active;
            /* 0x043 */ uint8_t     Unknown043[1];
        } partymember_t;

        /**
        * FFXI Party Structure
        */
        typedef struct ffxi_party_t {
            /* 0x000 */ uint32_t    AllianceLeaderServerId;
            /* 0x004 */ uint32_t    AllianceParty0LeaderServerId;
            /* 0x008 */ uint32_t    AllianceParty1LeaderServerId;
            /* 0x00C */ uint32_t    AllianceParty2LeaderServerId;
            /* 0x010 */ int8_t      AllianceParty0Visible;
            /* 0x011 */ int8_t      AllianceParty1Visible;
            /* 0x012 */ int8_t      AllianceParty2Visible;
            /* 0x013 */ int8_t      AllianceParty0MemberCount;
            /* 0x014 */ int8_t      AllianceParty1MemberCount;
            /* 0x015 */ int8_t      AllianceParty2MemberCount;
            /* 0x016 */ int8_t      AllianceInvited;
            /* 0x017 */ uint8_t     Unknown017[1];
            /* 0x018 */ partymember_t PartyMember[18];
        } ffxi_party_t;
#pragma pack()
    }; // namespace FFXI
}; // namespace Ashita

#endif // __AS_FFXI_PARTY_H_INCLUDED__