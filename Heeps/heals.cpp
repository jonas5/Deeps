#include "Heeps.h"

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
    if (id != 0x28)
        return false;

    // Use the SDK's ActionPacket to parse the data..
    Ashita::Packets::ActionPacket* action = (Ashita::Packets::ActionPacket*)data;

    // Get the actor of this action packet..
    uint16_t actorIndex = this->GetIndexFromId(action->GetActorId());
    if (actorIndex == 0)
        return false;

    entitysources_t* entityInfo = nullptr;
    auto it = m_Entities.find(action->GetActorId());
    if (it != m_Entities.end())
    {
        entityInfo = &it->second;
    }
    else
    {
        if (action->GetActorId() > 0x1000000)
            return false;

        entitysources_t newInfo;
        auto name = m_AshitaCore->GetMemoryManager()->GetEntity()->GetName(actorIndex);
        newInfo.name = name != nullptr ? name : "(Unknown)";
        newInfo.color = RandomColors[rand() % RandomColors.size()];
        newInfo.id = action->GetActorId();
        newInfo.ownerid = NULL;
        entityInfo = &m_Entities.insert(std::make_pair(action->GetActorId(), newInfo)).first->second;
    }

    if (entityInfo == nullptr)
        return false;

    // Handle pet attribution..
    bool isPet = (entityInfo->ownerid != NULL);
    uint16_t petIndex = m_AshitaCore->GetMemoryManager()->GetEntity()->GetPetTargetIndex(actorIndex);
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
            newPetInfo.ownerid = action->GetActorId();
            m_Entities.insert(std::make_pair(petID, newPetInfo));
        }
    }

    if (isPet)
    {
        auto petOwnerIndex = m_AshitaCore->GetMemoryManager()->GetEntity()->GetTrustOwnerTargetIndex(actorIndex);
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
            return false;
        }
    }

    // Get the source of the heal..
    source_t* source = GetHealSource(entityInfo, (uint8_t)action->GetCategory(), action->GetParameter(), isPet);
    if (source == nullptr)
        return false;

    // Loop through the actions and targets..
    for (uint32_t i = 0; i < action->GetTargetCount(); i++)
    {
        Ashita::Packets::ActionPacketTarget* target = action->GetTarget(i);
        if (target == nullptr)
            continue;

        for (uint32_t x = 0; x < target->GetActionCount(); x++)
        {
            Ashita::Packets::ActionPacketTargetAction* act = target->GetAction(x);
            if (act == nullptr)
                continue;

            UpdateHealSource(source, act->MessageId, act->Param);

            for (uint32_t y = 0; y < act->GetEffectCount(); y++)
            {
                Ashita::Packets::ActionPacketTargetActionEffect* effect = act->GetEffect(y);
                if (effect == nullptr)
                    continue;

                UpdateHealSource(source, effect->MessageId, effect->Param);
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