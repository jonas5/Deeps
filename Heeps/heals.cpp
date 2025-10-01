#include "Heeps.h"
#include <sstream>
#include <iomanip>

/**
 * @brief Allows a plugin to attempt to handle an incoming packet.
 *
 * @param uiPacketId            The id of the packet.
 * @param uiPacketSize          The size of the packet.
 * @param lpRawData             The raw packet data.
 *
 * @return True on handled, false otherwise.
 *
 * @note    Returning true on this will block the packet from being handled! This can
 *          have undesired effects! Use with caution as this can get you banned!
 */
bool Heeps::HandleIncomingPacket(uint16_t id, uint32_t size, const uint8_t* data, uint8_t* modified, uint32_t sizeChunk, const uint8_t* dataChunk, bool injected, bool blocked)
{
    for (std::list<void*>::iterator it = m_Packets.begin(); it != m_Packets.end(); it++)
    {
        if (memcmp(data, (*it), size) == 0)
        {
            return false;
        }
    }

    void* packet = malloc(1024);
    memset(packet, 0, 1024);
    memcpy(packet, data, size);
    m_Packets.push_back(packet);
    while (m_Packets.size() > 200)
    {
        free(*m_Packets.begin());
        m_Packets.pop_front();
    }

    if (id == 0x28 || id == 0x20)
    {
        if (m_Debug)
        {
            std::stringstream ss;
            ss << "Heeps Debug: Packet 0x" << std::hex << std::uppercase << id << " received. Size: " << std::dec << size << ". Data: ";
            for (uint32_t i = 0; i < size; ++i)
            {
                ss << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]) << " ";
            }
            m_AshitaCore->GetChatManager()->Write(-3, false, ss.str().c_str());
            return false;
        }
    }

    if (id != 0x28)
    {
        return false;
    }

    uint8_t actionType = (uint8_t)Ashita::BinaryData::UnpackBitsBE(const_cast<uint8_t*>(data), 82, 4);
    if (!IsParsedActionType(actionType))
    {
        return false;
    }

    uint32_t startBit = 0;
    uint8_t targetCount = (uint8_t)Ashita::BinaryData::UnpackBitsBE(const_cast<uint8_t*>(data), startBit + 40, 4);

    for (uint8_t i = 0; i < targetCount; ++i)
    {
        uint32_t targetBit = startBit + 44 + (i * 240);
        uint32_t actorID = (uint32_t)Ashita::BinaryData::UnpackBitsBE(const_cast<uint8_t*>(data), targetBit, 32);

        if (actorID == 0)
            continue;

        uint16_t index = GetIndexFromId(actorID);
        if (index == 0)
            continue;

        entitysources_t* entityInfo = nullptr;
        auto it = m_Entities.find(actorID);
        if (it != m_Entities.end())
        {
            entityInfo = &it->second;
        }
        else
        {
            if (actorID > 0x1000000)
                continue;

            entitysources_t newInfo;
            auto name = m_AshitaCore->GetMemoryManager()->GetEntity()->GetName(index);
            newInfo.name = name != nullptr ? name : "(Unknown)";
            newInfo.color = RandomColors[rand() % RandomColors.size()];
            newInfo.id = actorID;
            newInfo.ownerid = NULL;
            entityInfo = &m_Entities.insert(std::make_pair(actorID, newInfo)).first->second;
        }

        if (entityInfo == nullptr)
            continue;

        bool isPet = (entityInfo->ownerid != NULL);
        uint16_t petIndex = m_AshitaCore->GetMemoryManager()->GetEntity()->GetPetTargetIndex(index);
        uint32_t petID = m_AshitaCore->GetMemoryManager()->GetEntity()->GetServerId(petIndex);
        if (petIndex > 0 && petID > 0)
        {
            auto petIt = m_Entities.find(petID);
            if (petIt == m_Entities.end())
            {
                entitysources_t newPetInfo;
                auto name = m_AshitaCore->GetMemoryManager()->GetEntity()->GetName(petIndex);
                newPetInfo.name = name != nullptr ? name : "(Unknown)";
                newPetInfo.color = RandomColors[rand() % RandomColors.size()];
                newPetInfo.id = petID;
                newPetInfo.ownerid = actorID;
                m_Entities.insert(std::make_pair(petID, newPetInfo));
            }
        }

        if (isPet)
        {
            auto petOwnerIndex = m_AshitaCore->GetMemoryManager()->GetEntity()->GetTrustOwnerTargetIndex(index);
            if (petOwnerIndex != 0)
            {
                entityInfo->ownerid = m_AshitaCore->GetMemoryManager()->GetEntity()->GetServerId(petOwnerIndex);
            }
            auto ownerIt = m_Entities.find(entityInfo->ownerid);
            if (ownerIt != m_Entities.end())
            {
                entityInfo = &ownerIt->second;
            }
            else
            {
                continue;
            }
        }

        uint16_t actionID = (uint16_t)Ashita::BinaryData::UnpackBitsBE(const_cast<uint8_t*>(data), 86, 10);
        source_t* source = GetHealSource(entityInfo, actionType, actionID, isPet);
        if (source == nullptr)
            continue;

        uint8_t actionCount = (uint8_t)Ashita::BinaryData::UnpackBitsBE(const_cast<uint8_t*>(data), targetBit + 64, 4);
        for (uint8_t j = 0; j < actionCount; ++j)
        {
            uint32_t actionBit = targetBit + 68 + (j * 192);

            // Main action block
            uint32_t mainAmount = (uint32_t)Ashita::BinaryData::UnpackBitsBE(const_cast<uint8_t*>(data), actionBit + 63, 17);
            uint16_t messageID = (uint16_t)Ashita::BinaryData::UnpackBitsBE(const_cast<uint8_t*>(data), actionBit + 80, 10);
            UpdateHealSource(source, messageID, mainAmount);

            // Additional effect block
            uint8_t hasAdditionalEffect = (uint8_t)Ashita::BinaryData::UnpackBitsBE(const_cast<uint8_t*>(data), actionBit + 128, 1);
            if (hasAdditionalEffect)
            {
                uint16_t addEffectAmount = (uint16_t)Ashita::BinaryData::UnpackBitsBE(const_cast<uint8_t*>(data), actionBit + 132, 16);
                uint16_t addMessageID = (uint16_t)Ashita::BinaryData::UnpackBitsBE(const_cast<uint8_t*>(data), actionBit + 149, 10);
                UpdateHealSource(source, addMessageID, addEffectAmount);
            }
        }
    }
    return false;
}


// Returns true if given actionType matches one of the ones we're parsing
bool Heeps::IsParsedActionType(uint8_t actionType)
{
    return ((actionType == ACTIONTYPE_CAST_FINISH) ||
            (actionType == ACTIONTYPE_ITEM_FINISH) ||
            (actionType == ACTIONTYPE_JA) ||
            (actionType == ACTIONTYPE_AVATAR_BP_FINISH) ||
            (actionType == ACTIONTYPE_JA_DNC) ||
            (actionType == ACTIONTYPE_JA_RUN));
}


uint16_t Heeps::GetIndexFromId(int id)
{
    auto entMgr = m_AshitaCore->GetMemoryManager()->GetEntity();
    for (int i = 0; i < 0x900; i++)
    {
        if (entMgr->GetServerId(i) == id)
            return i;
    }
    return 0;
}

source_t* Heeps::GetHealSource(entitysources_t* entityInfo, uint8_t actionType, uint16_t actionID, bool isPet)
{
    uint32_t key;
    if (isPet) // All pet attacks are going into a "Pet" healing source
    {
        key = 0xBADC0DE;
    }
    else
    {
        key = (actionID << 8) + actionType;
    }
    auto sourcesIt = entityInfo->sources.find(key);

    source_t* source;

    if (sourcesIt != entityInfo->sources.end())
    {
        source = &sourcesIt->second;
    }
    else
    {
        source_t newsource;

        sourcesIt = entityInfo->sources.insert(std::make_pair(key, newsource)).first;

        source = &sourcesIt->second;

        if (isPet)
        {
            source->name.append("Pet");
        }
        else
        {
            switch (actionType)
            {
                case ACTIONTYPE_CAST_FINISH:
                    source->name.append(m_AshitaCore->GetResourceManager()->GetSpellById(actionID)->Name[2]);
                    source->isMagic = true;
                    break;
                case ACTIONTYPE_ITEM_FINISH:
                    source->name.append(m_AshitaCore->GetResourceManager()->GetItemById(actionID)->Name[0]);
                    break;
                case ACTIONTYPE_JA:
                case ACTIONTYPE_JA_DNC:
                case ACTIONTYPE_JA_RUN:
                    source->name.append(m_AshitaCore->GetResourceManager()->GetAbilityById(actionID + 512)->Name[2]);
                    break;
                case ACTIONTYPE_AVATAR_BP_FINISH:
                     source->name.append(m_AshitaCore->GetResourceManager()->GetAbilityById(actionID)->Name[2]);
                     break;
                default:
                     source->name.append("Unknown");
                     break;
            }
        }
    }
    return source;
}

/**
 * @brief Updates the total, count, and min/max values for a healing source.
 *
 * @param source The source_t to update
 * @param message The message ID from an incoming action packet
 * @param amount The amount value from an incoming action packet
 */
void Heeps::UpdateHealSource(source_t* source, uint16_t message, uint32_t amount)
{
    amount_t* type = NULL;
    if (std::find(healMessages.begin(), healMessages.end(), message) != healMessages.end())
    {
        type = &source->amount["Heal"];
    }

    if (type == NULL || amount == 0)
    {
        return;
    }

    type->total += amount;
    type->count++;
    type->min = (amount < type->min ? amount : type->min);
    type->max = (amount > type->max ? amount : type->max);
}