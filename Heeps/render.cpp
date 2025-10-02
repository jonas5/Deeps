#include "Heeps.h"
//Global pointer for callback to use
Heeps* g_Heeps = nullptr;

/**
 * Global function to serve as mouse callback
 */
BOOL __stdcall g_OnClick(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (g_Heeps == nullptr)
        return false;
    return g_Heeps->OnClick(uMsg, wParam, lParam);
}

/**
 * @brief Direct3D release call to allow this plugin to cleanup any Direct3D objects.
 */
void Heeps::Direct3DRelease(void)
{
    m_AshitaCore->GetInputManager()->GetKeyboard()->RemoveCallback("heeps_click");

    if (m_Background != nullptr)
    {
        m_AshitaCore->GetConfigurationManager()->set_value("Heeps", "xpos", std::to_string(m_Background->GetPositionX()).c_str());
        m_AshitaCore->GetConfigurationManager()->set_value("Heeps", "ypos", std::to_string(m_Background->GetPositionY()).c_str());
        m_AshitaCore->GetFontManager()->Delete(m_Background->GetAlias());
        m_Background = nullptr;
    }
    m_AshitaCore->GetConfigurationManager()->set_value("Heeps", "tvmode", std::to_string(m_TVMode).c_str());
    m_AshitaCore->GetConfigurationManager()->Save("Heeps", "Heeps");

    while (!m_Bars.empty())
    {
        auto bar = m_Bars.back();
        if (bar != nullptr)
        {
            m_AshitaCore->GetFontManager()->Delete(bar->GetAlias());
        }
        m_Bars.pop_back();
    }
}


/**
 * @brief Direct3D initialize call to prepare this plugin for Direct3D calls.
 *
 * @param lpDevice              The Direct3D device currently wrapped by Ashita.
 *
 * @return True on success, false otherwise.
 *
 * @note    Plugins that do not return true on this call will not receive any other
 *          Direct3D calls listed below!
 */
bool Heeps::Direct3DInitialize(IDirect3DDevice8* device)
{
    this->m_Direct3DDevice = device;
    m_Drag                 = false;
    g_Heeps                = this;

    float xpos = m_AshitaCore->GetConfigurationManager()->get_float("Heeps", "xpos", 300.0f);
    float ypos = m_AshitaCore->GetConfigurationManager()->get_float("Heeps", "ypos", 300.0f);
    m_TVMode = m_AshitaCore->GetConfigurationManager()->get_bool("Heeps", "tvmode", false);
    m_GUIScale = m_AshitaCore->GetConfigurationManager()->get_bool("Heeps", "tvmode", false) ? 1.5f : 1.0f;

    m_Background = m_AshitaCore->GetFontManager()->Create("HeepsBackground");
    if (m_Background == nullptr) return false;
    m_Background->SetFontFamily("Arial");
    m_Background->SetFontHeight(static_cast<uint32_t>(TITLE_FONT_HEIGHT * m_GUIScale));
    m_Background->SetAutoResize(false);
    m_Background->GetBackground()->SetColor(D3DCOLOR_ARGB(0xCC, 0x00, 0x00, 0x00));
    m_Background->GetBackground()->SetVisibility(true);
    m_Background->GetBackground()->SetWidth(WINDOW_WIDTH * m_GUIScale);
    m_Background->GetBackground()->SetHeight(TITLEBAR_HEIGHT * m_GUIScale);
    m_Background->SetColor(D3DCOLOR_ARGB(0xFF, 0xFF, 0xFF, 0xFF));
    m_Background->SetBold(false);
    m_Background->SetText("");
    m_Background->SetPositionX(xpos);
    m_Background->SetPositionY(ypos);
    m_Background->SetVisibility(true);

    m_AshitaCore->GetInputManager()->GetKeyboard()->AddCallback("heeps_click", nullptr, nullptr, nullptr, (LPVOID)g_OnClick);

    return true;
}

void Heeps::Direct3DRender(void)
{
    DWORD now = GetTickCount();
    if (!(now - m_LastRender > 100))
    {
        return;
    }

    if (m_Background == nullptr)
        return;

    // Making sure the background heights and widths are good for when the size toggle is switched
    m_Background->SetFontHeight(static_cast<uint32_t>(TITLE_FONT_HEIGHT * m_GUIScale));
    m_Background->GetBackground()->SetWidth(WINDOW_WIDTH * m_GUIScale);
    m_Background->GetBackground()->SetHeight(TITLEBAR_HEIGHT * m_GUIScale);

    if (m_CharInfo == 0)
    {
        m_Background->SetText(" Heeps - Healing Done");
        std::vector<entitysources_t> temp;
        uint64_t total = 0;
        for (auto iter = m_Entities.begin(); iter != m_Entities.end(); iter++)
        {
            if ((iter->second.total() != 0) && (temp.size() < static_cast<size_t>(m_MaxBars)) && (this->CheckPartySetting(iter->first)))
            {
                temp.push_back(iter->second);
                total += iter->second.total();
            }
        }
        std::sort(temp.begin(), temp.end(), [](entitysources_t a, entitysources_t b) { return a > b; });
        RepairBars(m_Background, static_cast<uint8_t>(temp.size()));

        size_t i        = 0;
        uint64_t max = 0;
        m_ClickMap.clear();
        for (auto iter = temp.begin(); iter != temp.end(); iter++)
        {
            IFontObject* bar = m_Bars[i];
            if (iter->total() > max)
                max = iter->total();
            bar->GetBackground()->SetWidth((BAR_WIDTH * m_GUIScale) * (total == 0 ? 1.0f : ((float)iter->total() / (float)max)));
            bar->GetBackground()->SetColor(this->CheckColorSetting(iter->id, iter->color));
            char string[256];
            sprintf_s(string, 256, " %zu. %-10.10s %6llu (%03.1f%%)\n",
                i + 1, iter->name.c_str(), iter->total(), total == 0 ? 0.0f : 100.0f * ((float)iter->total() / (float)total));
            bar->SetText(string);
            m_ClickMap.insert(std::pair<IFontObject*, std::string>(bar, iter->name));
            i++;
        }
    }
    else
    {
        auto it = m_Entities.find(m_CharInfo);
        if (it != m_Entities.end())
        {
            if (m_SourceInfo == "") // Updating top layer of the plugin
            {
                std::vector<source_t> temp;
                uint64_t total = 0;
                for (auto s : it->second.sources)
                {
                    if (s.second.total() != 0 && temp.size() < 15)
                    {
                        temp.push_back(s.second);
                        total += s.second.total();
                    }
                }
                std::sort(temp.begin(), temp.end(), [](source_t a, source_t b) { return a > b; });
                char string[256];
                sprintf_s(string, 256, " %s - Sources\n", it->second.name.c_str());
                m_Background->SetText(string);
                RepairBars(m_Background, static_cast<uint8_t>(temp.size()));
                size_t i        = 0;
                uint64_t max = 0;
                m_ClickMap.clear();
                for (auto s : temp)
                {
                    IFontObject* bar = m_Bars[i];
                    if (s.total() > max)
                        max = s.total();
                    bar->GetBackground()->SetWidth((BAR_WIDTH * m_GUIScale) * (total == 0 ? 1.0f : ((float)s.total() / (float)max)));
                    bar->GetBackground()->SetColor(this->CheckColorSetting(it->first, it->second.color));
                    char string[256];
                    sprintf_s(string, 256, " %zu. %-10.10s %6llu (%03.1f%%)\n",
                        i + 1, s.name.c_str(), s.total(), total == 0 ? 0.0f : 100.0f * ((float)s.total() / (float)total));
                    bar->SetText(string);
                    m_ClickMap.insert(std::pair<IFontObject*, std::string>(bar, s.name));
                    i++;
                }
            }
            else // This is when a player's bar has been clicked into for additional details about their healing
            {
                for (auto s : it->second.sources)
                {
                    if (s.second.name == m_SourceInfo)
                    {
                        std::vector<std::pair<std::string, amount_t>> temp;
                        uint32_t count = 0;
                        for (const auto& d : s.second.amount)
                        {
                            if (d.second.count != 0 && temp.size() < 15)
                            {
                                temp.push_back(d);
                                count += d.second.count;
                            }
                        }

                        std::sort(temp.begin(), temp.end(), [](std::pair<std::string, amount_t> a, std::pair<std::string, amount_t> b) { return a.second > b.second; });
                        char string[256];
                        sprintf_s(string, 256, " %s - %s\n", it->second.name.c_str(), s.second.name.c_str());
                        m_Background->SetText(string);
                        RepairBars(m_Background, static_cast<uint8_t>(temp.size()));

                        size_t i        = 0;
                        uint32_t max = 0;
                        for (auto s : temp)
                        {
                            IFontObject* bar = m_Bars[i];
                            if (s.second.count > max)
                                max = s.second.count;
                            bar->GetBackground()->SetWidth((BAR_WIDTH * m_GUIScale) * (count == 0 ? 1.0f : 1.0f * ((float)s.second.count / (float)max)));
                            bar->GetBackground()->SetColor(this->CheckColorSetting(it->first, it->second.color));
                            char string[256];
                            sprintf_s(string, 256, " %-5sCnt:%4d  Avg:%5d  Max:%5d (%3.1f%%)\n", s.first.c_str(), s.second.count, s.second.avg(), s.second.max, count == 0 ? 0.0f : 100.0f * ((float)s.second.count / (float)count));
                            bar->SetText(string);
                            i++;
                        }
                        break;
                    }
                }
            }
        }
    }
    m_Background->GetBackground()->SetHeight(static_cast<float>(m_Bars.size()) * (BAR_BACKGROUND_HEIGHT * m_GUIScale) + (TITLEBAR_HEIGHT * m_GUIScale));
    m_LastRender = GetTickCount();
}

/**
 * @brief Starts from the font base and creates or deletes bars as necessary.
 *
 * @param heepsBase The base font background
 * @param size The number of bars that should be displaying
 */
void Heeps::RepairBars(IFontObject* heepsBase, uint8_t size)
{
    size_t barCount = m_Bars.size();
    while (m_Bars.size() < static_cast<size_t>(size))
    {
        barCount = m_Bars.size();
        char buffer[256];
        sprintf_s(buffer, 256, "HeepsBar%zu", barCount);
        auto newBar = m_AshitaCore->GetFontManager()->Create(buffer);
        if (newBar == nullptr) continue;
        newBar->SetAutoResize(false);
        newBar->SetFontFamily("Arial");
        newBar->SetBold(m_TVMode);
        newBar->SetFontHeight(static_cast<uint32_t>(BAR_FONT_HEIGHT * m_GUIScale));
        newBar->GetBackground()->SetColor(D3DCOLOR_ARGB(0xFF, 0x00, 0x7C, 0x5C));
        newBar->GetBackground()->SetVisibility(true);
        char texturePath[MAX_PATH];
        sprintf_s(texturePath, sizeof(texturePath), "%s\\Resources\\Heeps\\bar.tga", m_AshitaCore->GetAshitaInstallPathA());
        newBar->GetBackground()->SetTextureFromFile(texturePath);
        newBar->GetBackground()->SetWidth(BAR_WIDTH * m_GUIScale);
        newBar->GetBackground()->SetHeight(BAR_HEIGHT * m_GUIScale);
        newBar->SetVisibility(true);
        if (barCount == 0)
        {
            newBar->SetParent(m_Background);
            newBar->SetPositionX(BAR_HORIZONTAL_PADDING * m_GUIScale);
            newBar->SetPositionY((TITLEBAR_HEIGHT * m_GUIScale) - (1.0f * m_GUIScale));
        }
        else
        {
            if (m_Bars[barCount - 1] != nullptr)
            {
                newBar->SetParent(m_Bars[barCount - 1]);
                newBar->SetAnchorParent((uint32_t)Ashita::FrameAnchor::BottomLeft);
                newBar->SetPositionX(0);
                newBar->SetPositionY(BETWEEN_BAR_PADDING * m_GUIScale);
            }
        }
        m_Bars.push_back(newBar);
    }

    while (m_Bars.size() > size)
    {
        auto bar = m_Bars.back();
        if (bar != nullptr)
        {
            bar->SetParent(nullptr);
            m_AshitaCore->GetFontManager()->Delete(bar->GetAlias());
        }
        m_Bars.pop_back();
    }
}

bool Heeps::OnClick(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int32_t xpos = GET_X_LPARAM(lParam);
    int32_t ypos = GET_Y_LPARAM(lParam);

    if (m_Background == nullptr)
        return false;

    if (m_Drag)
    {
        auto newX = m_Background->GetPositionX() + (xpos - m_LastX);
        auto newY = m_Background->GetPositionY() + (ypos - m_LastY);
        m_Background->SetPositionX(newX);
        m_Background->SetPositionY(newY);
        m_LastX = xpos;
        m_LastY = ypos;
        if ((uMsg == 514) || ((GetKeyState(VK_SHIFT) & 0x8000) == 0))
        {
            m_Drag = false;
            return true;
        }
    }

    //Left click down..
    if (uMsg == 513)
    {
        if ((GetKeyState(VK_SHIFT) & 0x8000) && (m_Background->GetBackground()->HitTest(xpos, ypos)))
        {
            m_Drag = true;
            m_LastX = xpos;
            m_LastY = ypos;
        }
    }

    // Don't block input if it didn't fall into the heeps object
    if (!m_Background->GetBackground()->HitTest(xpos, ypos))
        return false;

    // Left click release handler checks for bars to focus..
    if (uMsg == 514)
    {
        for (auto iter = m_Bars.begin(); iter != m_Bars.end(); iter++)
        {
            if (HitTestBar(*iter, xpos, ypos))
            {
                if (m_CharInfo == 0)
                {
                    auto name = m_ClickMap.find(*iter);
                    if (name != m_ClickMap.end())
                    {
                        for (auto& entity : m_Entities)
                        {
                            if (entity.second.name == name->second)
                            {
                                m_CharInfo = entity.first;
                                break;
                            }
                        }
                    }
                }
                else if (m_SourceInfo == "")
                {
                    auto name = m_ClickMap.find(*iter);
                    if (name != m_ClickMap.end())
                        m_SourceInfo.assign(name->second);
                }
                return true;
            }
        }
    }

    // Right click release handler cancels focused bar
    if (uMsg == 517)
    {
        if (m_SourceInfo != "")
        {
            m_SourceInfo = "";
        }
        else
        {
            m_CharInfo = 0;
        }
        return true;
    }

    // Block left and right click down as well.
    return ((uMsg == 513) || (uMsg == 516));
}

bool Heeps::HitTestBar(IFontObject* bar, int32_t x, int32_t y)
{
    if (bar == nullptr)
        return false;

    auto bg = bar->GetBackground();
    if (bg == nullptr) return false;
    auto min = bg->GetPositionY();
    auto max = min + bg->GetHeight();
    return ((y >= min) && (y < max));
}

uint32_t Heeps::CheckColorSetting(uint32_t id, uint32_t randomColor)
{
    if (this->m_JobColors == false)
        return randomColor;

    // Check if we have an available job for the player (Job can be 0 if person is anon!!)
    IParty* party = m_AshitaCore->GetDataManager()->GetParty();
    if (party == nullptr) return randomColor;
    for (int i = 0; i < 18; i++)
    {
        if (party->GetMemberServerId(i) == id)
        {
            auto job = party->GetMemberMainJob(i);
            if (job >= 0 && job < (sizeof(JobColors)/sizeof(JobColors[0])))
                return JobColors[job];
            break;
        }
    }
    return randomColor;
}

bool Heeps::CheckPartySetting(uint32_t id)
{
    if (this->m_PartyOnly == false)
        return true;

    IParty* party = m_AshitaCore->GetDataManager()->GetParty();
    if (party == nullptr) return false;
    for (int i = 0; i < 18; i++)
    {
        if (party->GetMemberServerId(i) == id)
        {
            return true;
        }
    }

    return false;
}