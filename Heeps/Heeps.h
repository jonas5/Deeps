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

#ifndef __ASHITA_Heeps_H_INCLUDED__
#define __ASHITA_Heeps_H_INCLUDED__

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/**
 * @brief Required includes for an extension.
 */
#include "Ashita.h"
#include <algorithm>
#include <functional>
#include <list>
#include <map>
#include <stdint.h>
#include <thread>
#include <windowsx.h>
#include "Defines.h"

/**
 * @brief Our Main Plugin Class
 *
 * @note    The main class of your plugin MUST use PluginBase as a base class. This is the
 *          internal base class that Ashita uses to communicate with your plugin!
 */
class Heeps : IPlugin
{
    // Internal class variables
	IAshitaCore*          m_AshitaCore;
	ILogManager* 	      m_LogManager;
	DWORD                 m_PluginId;
	IDirect3DDevice8*     m_Direct3DDevice;

    // Configuration
    bool                  m_Debug;
    bool                  m_JobColors;
    int32_t               m_MaxBars;
    bool                  m_PartyOnly;
    bool                  m_TVMode;
    float                 m_GUIScale;

    // Packet Deduplication reference
	std::list<void*>	  m_Packets;

    // Display State
    IFontObject*                        m_Background;
    std::vector<IFontObject*>           m_Bars;
    uint32_t                            m_CharInfo;
    std::map<IFontObject*, std::string> m_ClickMap;
    std::unordered_map<uint32_t, entitysources_t> m_Entities;
    std::string                         m_SourceInfo;

    // Mouse Handler
    bool                  m_Drag;
    int32_t               m_LastX;
    int32_t               m_LastY;

    DWORD                 m_LastRender;

private:
    //heals.cpp
    uint16_t GetIndexFromId(int id);
    source_t* GetHealSource(entitysources_t* entityInfo, uint8_t actionType, uint16_t actionID, bool isPet);
    bool IsParsedActionType(uint8_t actionType);
    void UpdateHealSource(source_t* source, uint16_t message, uint32_t amount);

    //main.cpp
    void Report(char mode, int max);

    //render.cpp
    void Direct3DRelease(void);
    void RepairBars(IFontObject* heepsBase, uint8_t size);
    uint32_t CheckColorSetting(uint32_t id, uint32_t random);
    bool CheckPartySetting(uint32_t id);
    bool HitTestBar(IFontObject* bar, int32_t x, int32_t y);

public:
    //main.cpp
    Heeps(void);
    virtual ~Heeps(void);
	plugininfo_t GetPluginInfo(void) override;
    bool Initialize(IAshitaCore* core, ILogManager* log, uint32_t id) override;
    void Release(void) override;
    bool HandleCommand(const char* command, int32_t type) override;

    //heals.cpp
	bool HandleIncomingPacket(uint16_t id, uint32_t size, void* data, void* modified, bool blocked) override;

    //render.cpp
    bool Direct3DInitialize(IDirect3DDevice8* device) override;
	void Direct3DRelease(void) override;
    void Direct3DRender(void) override;
    bool OnClick(uint32_t uMsg, WPARAM wParam, LPARAM lParam, bool handled);
};

/**
 * @brief Required Plugin Exports
 */
extern "C" __declspec(dllexport) IPlugin* __stdcall CreatePlugin(void);
extern "C" __declspec(dllexport) double __stdcall GetInterfaceVersion(void);
extern "C" __declspec(dllexport) void __stdcall CreatePluginInfo(plugininfo_t* info);

#endif // __ASHITA_Heeps_H_INCLUDED__