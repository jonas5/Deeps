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
    // Basic packet duplication check..
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

    // We only care about action packets..
    if (id != 0x28)
        return false;

    if (m_Debug)
    {
        std::stringstream ss;
        ss << "Heeps Debug: Packet 0x28 received. Size: " << size << ". Data: ";
        for (uint32_t i = 0; i < size; ++i)
        {
            ss << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]) << " ";
        }
        m_AshitaCore->GetChatManager()->Write(-3, false, ss.str().c_str());
    }

    // Unpack the action packet data..
    uint8_t targetNum  = Read8(data, 0x09);
    uint8_t actionType = (uint8_t)(Ashita::BinaryData::UnpackBitsBE(const_cast<uint8_t*>(data), 82, 4));
    uint16_t actionID = (uint16_t)(Ashita::BinaryData::UnpackBitsBE(const_cast<uint8_t*>(data), 86, 10));
    uint8_t actionNum  = (uint8_t)(Ashita::BinaryData::UnpackBitsBE(const_cast<uint8_t*>(data), 182, 4));
    uint32_t userID   = Read32(data, 0x05);
    uint16_t startBit = 150;
    uint16_t index = GetIndexFromId(userID);

    if (m_Debug)
    {
        m_AshitaCore->GetChatManager()->Writef(-3, false, "Heeps Debug: Unpacked Header -> UserID: 0x%08X, ActionType: %u, ActionID: %u, TargetNum: %u, ActionNum: %u",
            userID, actionType, actionID, targetNum, actionNum);
    }

    if (userID == 0 || index == 0)
    {
        if (m_Debug) m_AshitaCore->GetChatManager()->Write(-3, false, "Heeps Debug: Invalid UserID or Index. Skipping.");
        return false;
    }

    // Get the entity that performed the action..
    entitysources_t* entityInfo = nullptr;
    auto it = m_Entities.find(userID);
    if (it != m_Entities.end())
    {
        entityInfo = &it->second;
        if (m_Debug) m_AshitaCore->GetChatManager()->Writef(-3, false, "Heeps Debug: Found existing entity for ActorID 0x%08X.", userID);
    }
    else
    {
        if (userID > 0x1000000)
            return false;

        entitysources_t newInfo;
        auto name = m_AshitaCore->GetMemoryManager()->GetEntity()->GetName(index);
        newInfo.name = name != nullptr ? name : "(Unknown)";
        newInfo.color = RandomColors[rand() % RandomColors.size()];
        newInfo.id = userID;
        newInfo.ownerid = NULL;
        entityInfo = &m_Entities.insert(std::make_pair(userID, newInfo)).first->second;
        if (m_Debug) m_AshitaCore->GetChatManager()->Writef(-3, false, "Heeps Debug: Created new entity for ActorID 0x%08X.", userID);
    }
    if (entityInfo == nullptr)
        return false;

    if (m_Debug) m_AshitaCore->GetChatManager()->Writef(-3, false, "Heeps Debug: Actor is '%s'.", entityInfo->name.c_str());

    // Handle pet ownership..
    bool isPet = (entityInfo->ownerid != NULL);
    uint16_t petIndex = m_AshitaCore->GetMemoryManager()->GetEntity()->GetPetTargetIndex(index);
    if (petIndex > 0)
    {
        uint32_t petID = m_AshitaCore->GetMemoryManager()->GetEntity()->GetServerId(petIndex);
        if (petID > 0)
        {
            auto petIt = m_Entities.find(petID);
            if (petIt == m_Entities.end())
            {
                entitysources_t newPetInfo;
                auto name = m_AshitaCore->GetMemoryManager()->GetEntity()->GetName(petIndex);
                newPetInfo.name = name != nullptr ? name : "(Unknown)";
                newPetInfo.color = RandomColors[rand() % RandomColors.size()];
                newPetInfo.id = petID;
                newPetInfo.ownerid = userID;
                m_Entities.insert(std::make_pair(petID, newPetInfo));
            }
        }
    }
    if (isPet)
    {
        auto petOwnerIndex = m_AshitaCore->GetMemoryManager()->GetEntity()->GetTrustOwnerTargetIndex(index);
        if (petOwnerIndex != 0)
            entityInfo->ownerid = m_AshitaCore->GetMemoryManager()->GetEntity()->GetServerId(petOwnerIndex);
        auto ownerIt = m_Entities.find(entityInfo->ownerid);
        if (ownerIt != m_Entities.end())
        {
            entityInfo = &ownerIt->second;
            if (m_Debug) m_AshitaCore->GetChatManager()->Writef(-3, false, "Heeps Debug: Actor is a pet. Attributing to owner '%s'.", entityInfo->name.c_str());
        }
        else
            return false;
    }

    // If this is a parsable action, get the source and loop through the actions..
    if (IsParsedActionType(actionType))
    {
        if (m_Debug) m_AshitaCore->GetChatManager()->Writef(-3, false, "Heeps Debug: ActionType %u is parsable. Getting source.", actionType);

        source_t* source = GetHealSource(entityInfo, actionType, actionID, isPet);
        if (source == nullptr)
            return false;

        if (m_Debug) m_AshitaCore->GetChatManager()->Writef(-3, false, "Heeps Debug: Source is '%s'. Looping targets/actions.", source->name.c_str());

        for (int i = 0; i < targetNum; i++)
        {
            for (int j = 0; j < actionNum; j++)
            {
                uint32_t mainAmount = (uint32_t)Ashita::BinaryData::UnpackBitsBE(const_cast<uint8_t*>(data), startBit + 63, 17);
                uint16_t messageID = (uint16_t)Ashita::BinaryData::UnpackBitsBE(const_cast<uint8_t*>(data), startBit + 80, 10);
                if (m_Debug) m_AshitaCore->GetChatManager()->Writef(-3, false, "Heeps Debug: [T%d A%d] Main Block -> Amount: %u, MessageID: 0x%04X", i, j, mainAmount, messageID);
                UpdateHealSource(source, messageID, mainAmount);

                uint8_t hasAdditionalEffect = Ashita::BinaryData::UnpackBitsBE(const_cast<uint8_t*>(data), startBit + 121, 1) & 0x1;
                if (hasAdditionalEffect)
                {
                    uint16_t addEffectAmount = (uint16_t)Ashita::BinaryData::UnpackBitsBE(const_cast<uint8_t*>(data), startBit + 132, 16);
                    uint16_t addMessageID = (uint16_t)Ashita::BinaryData::UnpackBitsBE(const_cast<uint8_t*>(data), startBit + 149, 10);
                    if (m_Debug) m_AshitaCore->GetChatManager()->Writef(-3, false, "Heeps Debug: [T%d A%d] AddEffect Block -> Amount: %u, MessageID: 0x%04X", i, j, addEffectAmount, addMessageID);
                    UpdateHealSource(source, addMessageID, addEffectAmount);
                    startBit += 37;
                }

                startBit += 1;
                uint8_t hasSpikesEffect = Ashita::BinaryData::UnpackBitsBE(const_cast<uint8_t*>(data), startBit + 121, 1) & 0x1;
                if (hasSpikesEffect)
                    startBit += 34;
                startBit += 86;
            }
            startBit += 36;
        }
    }
    else
    {
        if (m_Debug) m_AshitaCore->GetChatManager()->Writef(-3, false, "Heeps Debug: ActionType %u is not parsable. Skipping.", actionType);
    }
    return false;
}

// Returns true if given actionType matches one of the ones we're parsing
bool Heeps::IsParsedActionType(uint8_t actionType)
{
    return ((actionType == ACTIONTYPE_RA_FINISH) ||
            (actionType == ACTIONTYPE_CAST_FINISH) ||
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
    if (isPet)
    {
        key = 0xBADC0DE;
    }
    else
    {
        key = (actionID << 8) + actionType;
    }
    auto sourcesIt = entityInfo->sources.find(key);

    if (sourcesIt != entityInfo->sources.end())
    {
        return &sourcesIt->second;
    }
    else
    {
        source_t newsource;
        if (isPet)
        {
            newsource.name.append("Pet");
        }
        else
        {
            switch (actionType)
            {
                case ACTIONTYPE_CAST_FINISH:
                case ACTIONTYPE_RA_FINISH: // Re-using for self-targeted spells
                    newsource.name.append(m_AshitaCore->GetResourceManager()->GetSpellById(actionID)->Name[2]);
                    newsource.isMagic = true;
                    break;
                case ACTIONTYPE_ITEM_FINISH:
                    newsource.name.append(m_AshitaCore->GetResourceManager()->GetItemById(actionID)->Name[0]);
                    break;
                case ACTIONTYPE_JA:
                case ACTIONTYPE_JA_DNC:
                case ACTIONTYPE_JA_RUN:
                    newsource.name.append(m_AshitaCore->GetResourceManager()->GetAbilityById(actionID + 512)->Name[2]);
                    break;
                case ACTIONTYPE_AVATAR_BP_FINISH:
                     newsource.name.append(m_AshitaCore->GetResourceManager()->GetAbilityById(actionID)->Name[2]);
                     break;
                default:
                     newsource.name.append("Unknown");
                     break;
            }
        }
        return &entityInfo->sources.insert(std::make_pair(key, newsource)).first->second;
    }
}

void Heeps::UpdateHealSource(source_t* source, uint16_t message, uint32_t amount)
{
    if (m_Debug) m_AshitaCore->GetChatManager()->Writef(-3, false, "Heeps Debug: UpdateHealSource called with MessageID: 0x%04X, Amount: %u", message, amount);

    amount_t* type = nullptr;
    if ((std::find(healMessages.begin(), healMessages.end(), message) != healMessages.end()) || (message == 0 && amount > 0))
    {
        if (m_Debug) m_AshitaCore->GetChatManager()->Write(-3, false, "Heeps Debug: MessageID is a healing message.");
        type = &source->amount["Heal"];
    }

    if (type == NULL || amount == 0)
    {
        if (m_Debug) m_AshitaCore->GetChatManager()->Writef(-3, false, "Heeps Debug: UpdateHealSource - Skipping. Type is %s, Amount is %u.", (type == NULL ? "NULL" : "Valid"), amount);
        return;
    }

    if (m_Debug) m_AshitaCore->GetChatManager()->Writef(-3, false, "Heeps Debug: UpdateHealSource - RECORDING HEAL for source '%s'. Amount: %u", source->name.c_str(), amount);

    type->total += amount;
    type->count++;
    type->min = (amount < type->min ? amount : type->min);
    type->max = (amount > type->max ? amount : type->max);
}