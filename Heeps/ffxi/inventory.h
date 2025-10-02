#ifndef __AS_FFXI_INVENTORY_H_INCLUDED__
#define __AS_FFXI_INVENTORY_H_INCLUDED__

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

namespace Ashita {
    namespace FFXI {
#pragma pack(1)
        /**
         * FFXI Item Structure
         */
        typedef struct item_t {
            /* 0x000 */ uint16_t    Id;
            /* 0x002 */ uint16_t    Index;
            /* 0x004 */ uint32_t    Count;
            /* 0x008 */ uint32_t    Flags;
            /* 0x00C */ uint32_t    Price;
            /* 0x010 */ uint8_t     Unknown10[4];
            /* 0x014 */ uint8_t     Slot;
            /* 0x015 */ uint8_t     Container;
            /* 0x016 */ uint8_t     Unknown16[2];
            /* 0x018 */ uint32_t    Extra;
            /* 0x01C */ uint8_t     Unknown1C[4];
        } item_t;

        /**
         * FFXI Treasure Item Structure
         */
        typedef struct treasureitem_t {
            /* 0x000 */ uint16_t    ItemId;
            /* 0x002 */ uint16_t    Count;
            /* 0x004 */ uint8_t     Unknown04[4];
        } treasureitem_t;

        /**
         * FFXI Equipment Structure
         */
        typedef struct equipment_t {
            /* 0x000 */ uint8_t     Slot;
            /* 0x001 */ uint8_t     Container;
            /* 0x002 */ uint16_t    Index;
        } equipment_t;
#pragma pack()

        /**
         * FFXI Inventory Structure
         */
        typedef struct ffxi_inventory_t {
            /* 0x0000 */ item_t      Items[13][80];      // Inventory Bags (0-12)
            /* 0x2EE0 */ uint16_t    ContainerMax[13];   // Max items per container.
            /* 0x2EFA */ uint8_t     Unknown2EFA[0x196]; // Unknown..
            /* 0x3090 */ treasureitem_t Treasure[10];    // Treasure Pool Items
            /* 0x30F4 */ uint8_t     Unknown30F4[0x2C];  // Unknown..
            /* 0x3120 */ equipment_t Equipment[16];      // Equipment
            /* 0x31A0 */ uint32_t    CraftWait;          // Time until craft is finished.
        } ffxi_inventory_t;
    }; // namespace FFXI
}; // namespace Ashita

#endif // __AS_FFXI_INVENTORY_H_INCLUDED__