/**
* Copyright (c) 2011-2014 - Ashita Development Team
*
* Ashita is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Ashita is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Ashita.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Heeps.h"

/**
 * @brief Constructor and Deconstructor
 */
Heeps::Heeps(void)
    : m_AshitaCore(nullptr)
    , m_PluginId(0)
    , m_Direct3DDevice(nullptr)
    , m_Debug(false)
    , m_JobColors(true)
    , m_MaxBars(15)
    , m_PartyOnly(false)
    , m_TVMode(false)
    , m_GUIScale(1.0f)
{ }
Heeps::~Heeps(void)
{ }

/**
* @brief Returns the information about the plugin.
*
* @return {plugininfo_t} The plugin information structure.
*/
plugininfo_t Heeps::GetPluginInfo(void)
{
    return plugininfo_t("Heeps", "Relliko, kjLotus", 1.07, 1, 0);
}

/**
 * @brief Initializes our plugin. This is the main call that happens when your plugin is loaded.
 *
 * @param ashitaCore        The main Ashita Core object interface to interact with Ashita.
 * @param scriptEngine      The main script engine object interface to interact with the script engine.
 * @param dwPluginId        The base address of your plugin. This is used as the ID.
 *
 * @return True on success, false otherwise.
 *
 * @note If your plugin returns false here, it will be unloaded immediately!
 */
bool Heeps::Initialize(IAshitaCore* core, ILogManager* log, uint32_t id)
{
	this->m_AshitaCore = core;
	this->m_PluginId = id;
	this->m_LogManager = log;
    this->m_LastRender = GetTickCount();
    srand(static_cast<unsigned int>(time(nullptr)));
    m_CharInfo = 0;
	m_AshitaCore->GetConfigurationManager()->Load("Heeps", "Heeps");

    return true;
}

/**
 * @brief Releases this plugin. This is called when your plugin is unloaded.
 *
 * @note Your plugin should cleanup all its data here before it unloads. Anything such as:
 *          - Font objects.
 *          - Gui objects.
 *          - Bindings to the script engine (if you extended it any).
 */
void Heeps::Release(void)
{
    this->Direct3DRelease();

	while (m_Packets.size() > 0)
	{
		free(*m_Packets.begin());
		m_Packets.pop_front();
	}
}

/**
 * @brief Allows a plugin to attempt to handle a game command.
 *
 * @param pszCommand            The command being processed.
 * @param nCommandType          The type of command being processed.
 *
 * @return True on handled, false otherwise.
 */
bool Heeps::HandleCommand(const char* command, int32_t type)
{
    UNREFERENCED_PARAMETER(type);
    char buff[256], help[1024];
    sprintf_s(help, sizeof(help), "\tInvalid command. Available commands:\n\t/hps reset\n\t/hps report [s/p/l] [#]\n\t/hps test\n\t/hps jobcolors\n\t/hps partyonly\n\t/hps tvmode");

    std::vector<std::string> args;
    std::string T = command;
    size_t next = 0, last = 0;
    while ((next = T.find(" ", last)) != std::string::npos)
    {
        args.push_back(T.substr(last, next - last));
        last = next + 1;
    }
    args.push_back(T.substr(last));

    if (args[0] != "/heeps" && args[0] != "/hps")
        return false;

    if (args.size() < 2)
    {
        m_AshitaCore->GetChatManager()->Write(help);
        return true;
    }

    if (args[1] == "reset")
    {
        m_Entities.clear();
        m_SourceInfo.clear();
        m_CharInfo = 0;
    }
    else if (args[1] == "test")
    {
        m_Entities.clear();
        m_SourceInfo.clear();
        m_CharInfo = 0;

        // Create Test Healer 1
        entitysources_t healer1;
        healer1.name = "TestHealer1";
        healer1.id = 1;
        healer1.color = D3DCOLOR_ARGB(255, 255, 0, 0);

        source_t cure4;
        cure4.name = "Cure IV";
        cure4.amount["Heal"].total = 1500;
        cure4.amount["Heal"].count = 5;
        cure4.amount["Heal"].min = 280;
        cure4.amount["Heal"].max = 320;
        healer1.sources.insert(std::make_pair(123, cure4));

        source_t cure3;
        cure3.name = "Cure III";
        cure3.amount["Heal"].total = 800;
        cure3.amount["Heal"].count = 8;
        cure3.amount["Heal"].min = 90;
        cure3.amount["Heal"].max = 110;
        healer1.sources.insert(std::make_pair(456, cure3));

        m_Entities.insert(std::make_pair(healer1.id, healer1));

        // Create Test Healer 2
        entitysources_t healer2;
        healer2.name = "TestHealer2";
        healer2.id = 2;
        healer2.color = D3DCOLOR_ARGB(255, 0, 255, 0);

        source_t waltz;
        waltz.name = "Curing Waltz";
        waltz.amount["Heal"].total = 2500;
        waltz.amount["Heal"].count = 10;
        waltz.amount["Heal"].min = 240;
        waltz.amount["Heal"].max = 260;
        healer2.sources.insert(std::make_pair(789, waltz));

        m_Entities.insert(std::make_pair(healer2.id, healer2));

        m_AshitaCore->GetChatManager()->Write("Test data loaded.");
    }
    else if (args[1] == "report")
    {
        char mode = 0x00;
        int max = 3;
        if (args.size() > 2)
        {
            if (std::all_of(args[2].begin(), args[2].end(), ::isdigit))
            {
                max = atoi(args[2].c_str());
            }
            else
            {
                mode = args[2][0];
                if (args.size() > 3)
                {
                    if (std::all_of(args[3].begin(), args[3].end(), ::isdigit))
                    {
                        max = atoi(args[3].c_str());
                    }
                }
            }
        }
        std::thread([this, mode, max] { this->Report(mode, max); }).detach();
    }
    else if (args[1] == "debug")
    {
        m_Debug = !m_Debug;
        sprintf_s(buff, sizeof(buff), "Debug %s.", m_Debug ? "enabled" : "disabled");
        m_AshitaCore->GetChatManager()->Write(buff);
    }
    else if (args[1] == "jobcolors")
    {
        m_JobColors = !m_JobColors;
        sprintf_s(buff, sizeof(buff), "Job colors %s.", m_JobColors ? "enabled" : "disabled");
        m_AshitaCore->GetChatManager()->Write(buff);
    }
    else if (args[1] == "partyonly")
    {
        m_PartyOnly = !m_PartyOnly;
        sprintf_s(buff, sizeof(buff), "Party only %s.", m_PartyOnly ? "enabled" : "disabled");
        m_AshitaCore->GetChatManager()->Write(buff);
    }
    else if (args[1] == "tvmode")
    {
        m_TVMode = !m_TVMode;
        m_GUIScale = m_TVMode ? 1.5f : 1.0f;
        // Wipe heeps to re-render the bars correctly
        m_Entities.clear();
        m_SourceInfo.clear();
        m_CharInfo = 0;
        sprintf_s(buff, sizeof(buff), "TV mode %s.", m_TVMode ? "enabled" : "disabled");
        m_AshitaCore->GetChatManager()->Write(buff);
    }
    else
    {
        m_AshitaCore->GetChatManager()->Write(help);
    }

    return true;
}

void Heeps::Report(char mode, int max)
{
    if (m_Background)
    {
        char buff[256];
        if (mode != 0x00)
        {
            sprintf_s(buff, sizeof(buff), "/%c %s", mode, m_Background->GetText());
            m_AshitaCore->GetChatManager()->QueueCommand(buff, 1);
        }
        for (size_t i = 0; i < m_Bars.size(); i++)
        {
            if (i > static_cast<size_t>(max))
                break;
            std::this_thread::sleep_for(std::chrono::milliseconds(1100));

            IFontObject* bar = m_Bars[i];
            if ((bar != nullptr) && (mode != 0x00))
            {
                sprintf_s(buff, sizeof(buff), "/%c %s", mode, bar->GetText());
                m_AshitaCore->GetChatManager()->QueueCommand(buff, 1);
            }
        }
    }
}

/************************************************************************************************/
/* Ashita Plugin Exports                                                                        */
/************************************************************************************************/
IPlugin* g_Plugin = nullptr;

/**
* @brief Creates an instance of this plugin object.
*
* @note This is a required export, your plugin must implement this!
*/
extern "C" __declspec(dllexport) IPlugin* __stdcall CreatePlugin(void)
{
    if (g_Plugin != nullptr)
        return g_Plugin;
    g_Plugin = new Heeps();
    return g_Plugin;
}

/**
* @brief Returns the interface version this plugin was compiled with.
*
* @note This is a required export, your plugin must implement this!
*/
extern "C" __declspec(dllexport) double __stdcall GetInterfaceVersion(void)
{
    return ASHITA_INTERFACE_VERSION;
}

/**
* @brief Creates the plugin information header for this plugin.
*
* @param {plugininfo_t*} The plugin information structure to be filled.
* @note This is a required export, your plugin must implement this!
*/
extern "C" __declspec(dllexport) void __stdcall CreatePluginInfo(plugininfo_t* info)
{
    if (info == nullptr)
        return;
    if (g_Plugin == nullptr)
        g_Plugin = new Heeps();
    *info = g_Plugin->GetPluginInfo();
}