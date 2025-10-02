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
bool Heeps::HandleIncomingPacket(uint16_t id, uint32_t size, void* data, void* modified, bool blocked)
{
    UNREFERENCED_PARAMETER(modified);
    UNREFERENCED_PARAMETER(blocked);
    const uint8_t* packet_data = static_cast<const uint8_t*>(data);

    // Basic packet duplication check..
    for (std::list<void*>::iterator it = m_Packets.begin(); it != m_Packets.end(); it++)
    {
        if (memcmp(packet_data, (*it), size) == 0)
        {
            return false;
        }
    }
    void* packet = malloc(1024);
    memset(packet, 0, 1024);
    memcpy(packet, packet_data, size);
    m_Packets.push_back(packet);
    while (m_Packets.size() > 200)
    {
        free(*m_Packets.begin());
        m_Packets.pop_front();
    }

    // We only care about action packets..
    if (id != 0x28)
        return false;

    // Unpack the action packet data..
    uint8_t targetNum  = Read8(packet_data, 0x09);
    uint8_t actionType = (uint8_t)(Ashita::BinaryData::UnpackBitsBE(const_cast<uint8_t*>(packet_data), 82, 4));
    uint16_t actionID = (uint16_t)(Ashita::BinaryData::UnpackBitsBE(const_cast<uint8_t*>(packet_data), 86, 10));
    uint8_t actionNum  = (uint8_t)(Ashita::BinaryData::UnpackBitsBE(const_cast<uint8_t*>(packet_data), 182, 4));
    uint32_t userID   = Read32(packet_data, 0x05);
    uint16_t startBit = 150;
    uint16_t index = GetIndexFromId(userID);

    if (m_Debug)
    {
        char buff[2048];
        std::stringstream ss;
        ss << "Heeps Debug: Packet 0x28 received. Size: " << size << ". Data: ";
        for (uint32_t i = 0; i < size; ++i)
        {
            ss << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(packet_data[i]) << " ";
        }
        m_AshitaCore->GetChatManager()->Write(ss.str().c_str());
        sprintf_s(buff, sizeof(buff), "Heeps Debug: Unpacked Header -> UserID: 0x%08X, ActionType: %u, ActionID: %u, TargetNum: %u, ActionNum: %u",
            userID, actionType, actionID, targetNum, actionNum);
        m_AshitaCore->GetChatManager()->Write(buff);
    }

    if (userID == 0 || index == 0)
    {
        if (m_Debug) m_AshitaCore->GetChatManager()->Write("Heeps Debug: Invalid UserID or Index. Skipping.");
        return false;
    }

    // Get the entity that performed the action..
    entitysources_t* entityInfo = nullptr;
    auto it = m_Entities.find(userID);
    if (it != m_Entities.end())
    {
        entityInfo = &it->second;
    }
    else
    {
        if (userID > 0x1000000)
            return false;

        entitysources_t newInfo;
        auto name = m_AshitaCore->GetDataManager()->GetEntity()->GetName(index);
        newInfo.name = name != nullptr ? name : "(Unknown)";
        newInfo.color = RandomColors[rand() % RandomColors.size()];
        newInfo.id = userID;
        newInfo.ownerid = NULL;
        entityInfo = &m_Entities.insert(std::make_pair(userID, newInfo)).first->second;
    }
    if (entityInfo == nullptr)
        return false;

    // Handle pet ownership..
    bool isPet = (entityInfo->ownerid != NULL);
    uint16_t petIndex = m_AshitaCore->GetDataManager()->GetEntity()->GetPetTargetIndex(index);
    if (petIndex > 0)
    {
        uint32_t petID = m_AshitaCore->GetDataManager()->GetEntity()->GetServerId(petIndex);
        if (petID > 0)
        {
            auto petIt = m_Entities.find(petID);
            if (petIt == m_Entities.end())
            {
                entitysources_t newPetInfo;
                auto name = m_AshitaCore->GetDataManager()->GetEntity()->GetName(petIndex);
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
        // This function does not exist in v3, so we can't update pet ownership this way.
        // auto petOwnerIndex = m_AshitaCore->GetDataManager()->GetEntity()->GetTrustOwnerTargetIndex(index);
        // if (petOwnerIndex != 0)
        //     entityInfo->ownerid = m_AshitaCore->GetDataManager()->GetEntity()->GetServerId(petOwnerIndex);
        auto ownerIt = m_Entities.find(entityInfo->ownerid);
        if (ownerIt != m_Entities.end())
            entityInfo = &ownerIt->second;
        else
            return false;
    }

    // If this is a parsable action, get the source and loop through the actions..
    if (IsParsedActionType(actionType))
    {
        source_t* source = GetHealSource(entityInfo, actionType, actionID, isPet);
        if (source == nullptr)
            return false;

        for (int i = 0; i < targetNum; i++)
        {
            for (int j = 0; j < actionNum; j++)
            {
                uint32_t mainAmount = (uint32_t)Ashita::BinaryData::UnpackBitsBE(const_cast<uint8_t*>(packet_data), startBit + 63, 17);
                uint16_t messageID = (uint16_t)Ashita::BinaryData::UnpackBitsBE(const_cast<uint8_t*>(packet_data), startBit + 80, 10);
                UpdateHealSource(source, messageID, mainAmount);

                uint8_t hasAdditionalEffect = Ashita::BinaryData::UnpackBitsBE(const_cast<uint8_t*>(packet_data), startBit + 121, 1) & 0x1;
                if (hasAdditionalEffect)
                {
                    uint16_t addEffectAmount = (uint16_t)Ashita::BinaryData::UnpackBitsBE(const_cast<uint8_t*>(packet_data), startBit + 132, 16);
                    uint16_t addMessageID = (uint16_t)Ashita::BinaryData::UnpackBitsBE(const_cast<uint8_t*>(packet_data), startBit + 149, 10);
                    UpdateHealSource(source, addMessageID, addEffectAmount);
                    startBit += 37;
                }

                startBit += 1;
                uint8_t hasSpikesEffect = Ashita::BinaryData::UnpackBitsBE(const_cast<uint8_t*>(packet_data), startBit + 121, 1) & 0x1;
                if (hasSpikesEffect)
                    startBit += 34;
                startBit += 86;
            }
            startBit += 36;
        }
    }
    return false;
}

// Returns true if given actionType matches one of the ones we're parsing
bool Heeps::IsParsedActionType(uint8_t actionType)
{
    if (m_Debug)
        return true;

    return ((actionType == ACTIONTYPE_MELEE) ||
            (actionType == ACTIONTYPE_RA_FINISH) ||
            (actionType == ACTIONTYPE_WS_FINISH) ||
            (actionType == ACTIONTYPE_CAST_FINISH) ||
            (actionType == ACTIONTYPE_ITEM_FINISH) ||
            (actionType == ACTIONTYPE_JA) ||
            (actionType == ACTIONTYPE_NPC_TP_FINISH) ||
            (actionType == ACTIONTYPE_AVATAR_BP_FINISH) ||
            (actionType == ACTIONTYPE_JA_DNC) ||
            (actionType == ACTIONTYPE_JA_RUN));
}

uint16_t Heeps::GetIndexFromId(int id)
{
    auto entMgr = m_AshitaCore->GetDataManager()->GetEntity();
    for (int i = 0; i < 0x900; i++)
    {
        if (entMgr->GetServerId(i) == id)
            return i;
    }
    return 0;
}

source_t* Heeps::GetHealSource(entitysources_t* entityInfo, uint8_t actionType, uint16_t actionID, bool isPet)
{
    if (m_Debug)
    {
        char buff[256];
        sprintf_s(buff, sizeof(buff), "Heeps Debug: GetHealSource called with ActionType: %u, ActionID: %u", actionType, actionID);
        m_AshitaCore->GetChatManager()->Write(buff);
    }

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
        if (m_Debug) m_AshitaCore->GetChatManager()->Write("Heeps Debug: GetHealSource -> Found existing source.");
        return &sourcesIt->second;
    }
    else
    {
        if (m_Debug) m_AshitaCore->GetChatManager()->Write("Heeps Debug: GetHealSource -> Creating new source.");
        source_t newsource;
        if (isPet)
        {
            if (m_Debug) m_AshitaCore->GetChatManager()->Write("Heeps Debug: GetHealSource -> Source is a Pet.");
            newsource.name.append("Pet");
        }
        else
        {
            switch (actionType)
            {
                case ACTIONTYPE_MELEE:
                    if (m_Debug) m_AshitaCore->GetChatManager()->Write("Heeps Debug: GetHealSource -> ACTIONTYPE_MELEE triggered.");
                    newsource.name.append("Attack");
                    break;
                case ACTIONTYPE_RA_FINISH:
                    if (m_Debug) m_AshitaCore->GetChatManager()->Write("Heeps Debug: GetHealSource -> ACTIONTYPE_RA_FINISH triggered.");
                    newsource.name.append("Ranged Attack");
                    break;
                case ACTIONTYPE_WS_FINISH:
                case ACTIONTYPE_NPC_TP_FINISH:
                    if (m_Debug) m_AshitaCore->GetChatManager()->Write("Heeps Debug: GetHealSource -> WEAPONSKILL/TP action triggered.");
                    newsource.name.append(m_AshitaCore->GetResourceManager()->GetAbilityById(actionID)->Name[2]);
                    break;
                case ACTIONTYPE_CAST_FINISH:
                    if (m_Debug) m_AshitaCore->GetChatManager()->Write("Heeps Debug: GetHealSource -> >>> ACTIONTYPE_CAST_FINISH triggered! <<<");
                    newsource.name.append(m_AshitaCore->GetResourceManager()->GetSpellById(actionID)->Name[2]);
                    newsource.isMagic = true;
                    break;
                case ACTIONTYPE_ITEM_FINISH:
                    if (m_Debug) m_AshitaCore->GetChatManager()->Write("Heeps Debug: GetHealSource -> ACTIONTYPE_ITEM_FINISH triggered.");
                    newsource.name.append(m_AshitaCore->GetResourceManager()->GetItemById(actionID)->Name[0]);
                    break;
                case ACTIONTYPE_JA:
                case ACTIONTYPE_JA_DNC:
                case ACTIONTYPE_JA_RUN:
                    if (m_Debug) m_AshitaCore->GetChatManager()->Write("Heeps Debug: GetHealSource -> ACTIONTYPE_JA triggered.");
                    newsource.name.append(m_AshitaCore->GetResourceManager()->GetAbilityById(actionID + 512)->Name[2]);
                    break;
                case ACTIONTYPE_AVATAR_BP_FINISH:
                     if (m_Debug) m_AshitaCore->GetChatManager()->Write("Heeps Debug: GetHealSource -> AVATAR action triggered.");
                     newsource.name.append(m_AshitaCore->GetResourceManager()->GetAbilityById(actionID)->Name[2]);
                     break;
                default:
                     if (m_Debug)
                     {
                         char buff[256];
                         sprintf_s(buff, sizeof(buff), "Heeps Debug: GetHealSource -> Unhandled ActionType: %u", actionType);
                         m_AshitaCore->GetChatManager()->Write(buff);
                     }
                     newsource.name.append("Unknown");
                     break;
            }
        }
        return &entityInfo->sources.insert(std::make_pair(key, newsource)).first->second;
    }
}

void Heeps::UpdateHealSource(source_t* source, uint16_t message, uint32_t amount)
{
    amount_t* type = nullptr;
    if ((std::find(healMessages.begin(), healMessages.end(), message) != healMessages.end()) || (message == 0 && amount > 0))
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