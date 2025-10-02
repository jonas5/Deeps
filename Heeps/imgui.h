// dear imgui, v1.80 WIP
// (headers)

// See imgui.cpp file for documentation.
// See ImGui::ShowDemoWindow() in imgui_demo.cpp for demo code.
// Read a file named 'imgui.ini' in the same directory as your executable to save default window settings.

#pragma once

// Configuration file with commented out settings.
//#include "imconfig.h"

// Basic types
#include <float.h>          // FLT_MAX
#include <stdarg.h>         // va_list
#include <stddef.h>         // ptrdiff_t, size_t
#include <string.h>         // memset, memmove, memcpy, strlen, strchr, strcmp, strcpy

// Define assertion handler.
#ifndef IM_ASSERT
#include <assert.h>
#define IM_ASSERT(_EXPR)    assert(_EXPR)
#endif

// Define attributes of all API symbols declarations (e.g. for DLL under Windows)
// IMGUI_API is used for core imgui functions, IMGUI_IMPL_API is used for the default backends files (imgui_impl_xxx.h)
#ifndef IMGUI_API
#define IMGUI_API
#endif
#ifndef IMGUI_IMPL_API
#define IMGUI_IMPL_API      IMGUI_API
#endif

// Helper macros to build decent error messages
#define IM_ARRAYSIZE(_ARR)          ((int)(sizeof(_ARR)/sizeof(*_ARR)))
#define IM_STRINGIFY_HELPER(X)      #X
#define IM_STRINGIFY(X)             IM_STRINGIFY_HELPER(X)

//---- Forward declarations
struct ImDrawChannel;               // Temporary storage for outputting drawing commands out of order, used by ImDrawListSplitter and ImDrawList::ChannelsSplit()
struct ImDrawCmd;                   // A single drawing command. Stores render state, number of vertices, index offset.
struct ImDrawData;                  // All draw command lists required to render the frame + pos/size coordinates to use for the projection matrix.
struct ImDrawList;                  // A single draw command list (generally one per window, can be shared among multiple windows)
struct ImDrawListSharedData;        // Data shared among multiple draw lists (typically owned by parent ImGui context, but you may create one yourself)
struct ImDrawListSplitter;          // Helper to split a draw list into different layers which can be drawn into out of order
struct ImDrawVert;                  // A single vertex (pos + uv + col = 20 bytes by default. Override layout with IMGUI_OVERRIDE_DRAW_VERT_STRUCT_LAYOUT)
struct ImFont;                      // Runtime data for a single font within a parent ImFontAtlas
struct ImFontAtlas;                 // Runtime data for multiple fonts, bake multiple fonts into a single texture, TTF/OTF font loader
struct ImFontConfig;                // Configuration data when adding a font or merging fonts
struct ImFontGlyph;                 // A single font glyph (code point, advance, offsets, etc.)
struct ImFontGlyphRangesBuilder;    // Helper to build glyph ranges from text/string data
struct ImColor;                     // Helper functions to create a color that can be converted to either u32 or float4
struct ImGuiContext;                // Dear ImGui context (opaque structure, unless including imgui_internal.h)
struct ImGuiIO;                     // Main configuration and I/O between your application and ImGui
struct ImGuiInputTextCallbackData;  // Shared state of InputText() when using custom callbacks (advanced)
struct ImGuiListClipper;            // Helper to manually clip large list of items
struct ImGuiOnceUponAFrame;         // Helper for running a block of code not more than once a frame
struct ImGuiPayload;                // User data payload for drag and drop operations
struct ImGuiSizeCallbackData;       // Callback data when using SetNextWindowSizeConstraints() (advanced)
struct ImGuiStorage;                // Helper for key->value storage
struct ImGuiStyle;                  // Runtime data for styling/colors
struct ImGuiTableSortSpecs;         // Sorting specifications for a table (often handling sort specs for a single column, occasionally more)
struct ImGuiTableColumnSortSpecs;   // Sorting specification for one column of a table
struct ImGuiTextBuffer;             // Helper to hold and append into a text buffer (~string builder)
struct ImGuiTextFilter;             // Helper to parse and apply text filters (e.g. "aaaaa[,bbbbb][,ccccc]")

// Typedefs
typedef unsigned int ImGuiID;       // A unique ID used by widgets
typedef int ImGuiCol;               // A color identifier for styling
typedef int ImGuiCond;              // A condition identifier for SetWindow*** functions
typedef int ImGuiDataType;          // A primary data type identifier
typedef int ImGuiDir;               // A cardinal direction
typedef int ImGuiKey;               // A key identifier (ImGui-side enum)
typedef int ImGuiNavInput;          // An input identifier for navigation
typedef int ImGuiMouseButton;       // A mouse button identifier (0=left, 1=right, 2=middle)
typedef int ImGuiMouseCursor;       // A mouse cursor identifier
typedef int ImGuiSortDirection;     // A sorting direction (ascending or descending)
typedef int ImGuiStyleVar;          // A variable identifier for styling
typedef int ImGuiTableBgTarget;     // A target for specifying table background colors
typedef int ImGuiTableColumnFlags;  // Flags for defining table columns
typedef int ImGuiTableFlags;        // Flags for defining a table
typedef int ImGuiTableRowFlags;     // Flags for defining a table row
typedef int ImDrawFlags;            // Flags for ImDrawList functions
typedef int ImDrawCornerFlags;      // Flags for ImDrawList::AddRect(), AddRectFilled() etc.
typedef int ImFontAtlasFlags;       // Flags for ImFontAtlas build
typedef int ImGuiBackendFlags;      // Flags for backend capabilities
typedef int ImGuiButtonFlags;       // Flags for InvisibleButton()
typedef int ImGuiColorEditFlags;    // Flags for ColorEdit3(), ColorEdit4(), ColorPicker3(), ColorPicker4(), ColorButton()
typedef int ImGuiConfigFlags;       // Flags for ImGui::NewFrame()
typedef int ImGuiComboFlags;        // Flags for BeginCombo()
typedef int ImGuiDragDropFlags;     // Flags for BeginDragDropSource(), AcceptDragDropPayload()
typedef int ImGuiFocusedFlags;      // Flags for IsWindowFocused()
typedef int ImGuiHoveredFlags;      // Flags for IsItemHovered(), IsWindowHovered() etc.
typedef int ImGuiInputTextFlags;    // Flags for InputText(), InputTextMultiline()
typedef int ImGuiKeyModFlags;       // Flags for io.KeyMods (Ctrl/Shift/Alt/Super)
typedef int ImGuiPopupFlags;        // Flags for OpenPopup*(), BeginPopupContext*()
typedef int ImGuiSelectableFlags;   // Flags for Selectable()
typedef int ImGuiSliderFlags;       // Flags for DragFloat(), DragInt(), SliderFloat(), SliderInt() etc.
typedef int ImGuiTabBarFlags;       // Flags for BeginTabBar()
typedef int ImGuiTabItemFlags;      // Flags for BeginTabItem()
typedef int ImGuiTreeNodeFlags;     // Flags for TreeNode(), TreeNodeEx(), CollapsingHeader()
typedef int ImGuiWindowFlags;       // Flags for Begin(), BeginChild()
typedef int (*ImGuiInputTextCallback)(ImGuiInputTextCallbackData* data);
typedef void (*ImGuiSizeCallback)(ImGuiSizeCallbackData* data);

// Scalar data types
typedef unsigned short ImWchar16;   // A single character UTF-16
typedef unsigned int ImWchar32;     // A single character UTF-32
#ifdef IMGUI_USE_WCHAR32            // ImWchar [configurable type: override in imconfig.h with 'typedef unsigned int ImWchar;']
typedef ImWchar32 ImWchar;
#else
typedef ImWchar16 ImWchar;
#endif

//-----------------------------------------------------------------------------
// Helpers
//-----------------------------------------------------------------------------

// Helper: IM_NEW(), IM_DELETE(), IM_FREE()
// We call C++ constructor on own allocated memory via the placement "new" operator.
// Can be moved to imconfig.h
#ifndef IM_PLACEMENT_NEW
#define IM_PLACEMENT_NEW(_PTR)  new((void*)(_PTR))
#endif
#ifndef IM_NEW
#define IM_NEW(_TYPE)           new((void*)ImGui::MemAlloc(sizeof(_TYPE))) _TYPE
#endif
#ifndef IM_DELETE
#define IM_DELETE(_PTR)         do { if(_PTR) { (_PTR)->~decltype(*(_PTR))(); ImGui::MemFree(_PTR); } } while (0)
#endif

// Helper: ImVec2
// 2D vector, used for position, size, etc.
struct ImVec2
{
    float x, y;
    ImVec2() { x = y = 0.0f; }
    ImVec2(float _x, float _y) { x = _x; y = _y; }
    float  operator[] (size_t idx) const { IM_ASSERT(idx <= 1); return (&x)[idx]; }    // We very rarely use this [] operator, the assert overhead is fine.
    float& operator[] (size_t idx) { IM_ASSERT(idx <= 1); return (&x)[idx]; }    // We very rarely use this [] operator, the assert overhead is fine.
};

// Helper: ImVec4
// 4D vector, used for clipping rectangles, colors, etc.
struct ImVec4
{
    float x, y, z, w;
    ImVec4() { x = y = z = w = 0.0f; }
    ImVec4(float _x, float _y, float _z, float _w) { x = _x; y = _y; z = _z; w = _w; }
};

//-----------------------------------------------------------------------------
// ImGui::
// - You can use C++ user-defined + operator to do math on ImVec2 and ImVec4.
// - If you want to use the macros below, use them selectively to avoid overhead.
// - You can also freely use the structures operators, e.g. ImVec2(1,1) + ImVec2(2,2)
//-----------------------------------------------------------------------------

namespace ImGui
{
    // Main
    IMGUI_API ImGuiContext* CreateContext(ImFontAtlas* shared_font_atlas = NULL);
    IMGUI_API void          DestroyContext(ImGuiContext* ctx = NULL);   // NULL = current context
    IMGUI_API ImGuiContext* GetCurrentContext();
    IMGUI_API void          SetCurrentContext(ImGuiContext* ctx);
    IMGUI_API ImGuiIO&      GetIO();
    IMGUI_API ImGuiStyle&   GetStyle();
    IMGUI_API void          NewFrame();
    IMGUI_API void          EndFrame();
    IMGUI_API void          Render();
    IMGUI_API ImDrawData*   GetDrawData();

    // Demo, Debug, Information
    IMGUI_API void          ShowDemoWindow(bool* p_open = NULL);
    IMGUI_API void          ShowAboutWindow(bool* p_open = NULL);
    IMGUI_API void          ShowMetricsWindow(bool* p_open = NULL);
    IMGUI_API void          ShowStyleEditor(ImGuiStyle* ref = NULL);
    IMGUI_API bool          ShowStyleSelector(const char* label);
    IMGUI_API void          ShowFontSelector(const char* label);
    IMGUI_API void          ShowUserGuide();
    IMGUI_API const char*   GetVersion();

    // Styles
    IMGUI_API void          StyleColorsDark(ImGuiStyle* dst = NULL);
    IMGUI_API void          StyleColorsClassic(ImGuiStyle* dst = NULL);
    IMGUI_API void          StyleColorsLight(ImGuiStyle* dst = NULL);

    // Windows
    IMGUI_API bool          Begin(const char* name, bool* p_open = NULL, ImGuiWindowFlags flags = 0);
    IMGUI_API void          End();
    IMGUI_API bool          BeginChild(const char* str_id, const ImVec2& size = ImVec2(0,0), bool border = false, ImGuiWindowFlags flags = 0);
    IMGUI_API bool          BeginChild(ImGuiID id, const ImVec2& size = ImVec2(0,0), bool border = false, ImGuiWindowFlags flags = 0);
    IMGUI_API void          EndChild();

    // Windows Utilities
    IMGUI_API bool          IsWindowAppearing();
    IMGUI_API bool          IsWindowCollapsed();
    IMGUI_API bool          IsWindowFocused(ImGuiFocusedFlags flags=0); // is current window focused? or its root/child, depending on flags. see flags for options.
    IMGUI_API bool          IsWindowHovered(ImGuiHoveredFlags flags=0); // is current window hovered (and typically: not blocked by a popup/modal)? see flags for options.
    IMGUI_API ImDrawList*   GetWindowDrawList();                        // get draw list associated to the current window, to append your own drawing primitives
    IMGUI_API ImVec2        GetWindowPos();                             // get current window position in screen space (useful if you want to do your own drawing via the DrawList API)
    IMGUI_API ImVec2        GetWindowSize();                            // get current window size
    IMGUI_API float         GetWindowWidth();                           // get current window width (shortcut for GetWindowSize().x)
    IMGUI_API float         GetWindowHeight();                          // get current window height (shortcut for GetWindowSize().y)
    IMGUI_API ImVec2        GetContentRegionMax();                      // current content boundaries (typically window boundaries including scrolling, or current column boundaries), in windows coordinates
    IMGUI_API ImVec2        GetContentRegionAvail();                    // == GetContentRegionMax() - GetCursorPos()
    IMGUI_API ImVec2        GetWindowContentRegionMin();                // content boundaries min (roughly (0,0)-Scroll), in window coordinates
    IMGUI_API ImVec2        GetWindowContentRegionMax();                // content boundaries max (roughly (0,0)+Size-Scroll) where Size can be override with SetNextWindowContentSize(), in window coordinates
    IMGUI_API float         GetWindowContentRegionWidth();              //
    IMGUI_API void          SetNextWindowPos(const ImVec2& pos, ImGuiCond cond = 0, const ImVec2& pivot = ImVec2(0,0));
    IMGUI_API void          SetNextWindowSize(const ImVec2& size, ImGuiCond cond = 0);
    IMGUI_API void          SetNextWindowSizeConstraints(const ImVec2& size_min, const ImVec2& size_max, ImGuiSizeCallback custom_callback = NULL, void* custom_callback_data = NULL);
    IMGUI_API void          SetNextWindowContentSize(const ImVec2& size);
    IMGUI_API void          SetNextWindowCollapsed(bool collapsed, ImGuiCond cond = 0);
    IMGUI_API void          SetNextWindowFocus();
    IMGUI_API void          SetNextWindowBgAlpha(float alpha);
    IMGUI_API void          SetWindowPos(const ImVec2& pos, ImGuiCond cond = 0);
    IMGUI_API void          SetWindowSize(const ImVec2& size, ImGuiCond cond = 0);
    IMGUI_API void          SetWindowCollapsed(bool collapsed, ImGuiCond cond = 0);
    IMGUI_API void          SetWindowFocus();
    IMGUI_API void          SetWindowFontScale(float scale);
    IMGUI_API void          SetWindowPos(const char* name, const ImVec2& pos, ImGuiCond cond = 0);
    IMGUI_API void          SetWindowSize(const char* name, const ImVec2& size, ImGuiCond cond = 0);
    IMGUI_API void          SetWindowCollapsed(const char* name, bool collapsed, ImGuiCond cond = 0);
    IMGUI_API void          SetWindowFocus(const char* name);

    // Scrolling
    IMGUI_API float         GetScrollX();
    IMGUI_API float         GetScrollY();
    IMGUI_API float         GetScrollMaxX();
    IMGUI_API float         GetScrollMaxY();
    IMGUI_API void          SetScrollX(float scroll_x);
    IMGUI_API void          SetScrollY(float scroll_y);
    IMGUI_API void          SetScrollHereX(float center_x_ratio = 0.5f);
    IMGUI_API void          SetScrollHereY(float center_y_ratio = 0.5f);
    IMGUI_API void          SetScrollFromPosX(float local_x, float center_x_ratio = 0.5f);
    IMGUI_API void          SetScrollFromPosY(float local_y, float center_y_ratio = 0.5f);

    // Parameters stacks (shared)
    IMGUI_API void          PushFont(ImFont* font);
    IMGUI_API void          PopFont();
    IMGUI_API void          PushStyleColor(ImGuiCol idx, ImU32 col);
    IMGUI_API void          PushStyleColor(ImGuiCol idx, const ImVec4& col);
    IMGUI_API void          PopStyleColor(int count = 1);
    IMGUI_API void          PushStyleVar(ImGuiStyleVar idx, float val);
    IMGUI_API void          PushStyleVar(ImGuiStyleVar idx, const ImVec2& val);
    IMGUI_API void          PopStyleVar(int count = 1);
    IMGUI_API const ImVec4& GetStyleColorVec4(ImGuiCol idx);
    IMGUI_API ImFont*       GetFont();
    IMGUI_API float         GetFontSize();
    IMGUI_API ImVec2        GetFontTexUvWhitePixel();
    IMGUI_API ImU32         GetColorU32(ImGuiCol idx, float alpha_mul = 1.0f);
    IMGUI_API ImU32         GetColorU32(const ImVec4& col);
    IMGUI_API ImU32         GetColorU32(ImU32 col);

    // Parameters stacks (current window)
    IMGUI_API void          PushItemWidth(float item_width);
    IMGUI_API void          PopItemWidth();
    IMGUI_API void          SetNextItemWidth(float item_width);
    IMGUI_API float         CalcItemWidth();
    IMGUI_API void          PushTextWrapPos(float wrap_local_pos_x = 0.0f);
    IMGUI_API void          PopTextWrapPos();
    IMGUI_API void          PushAllowKeyboardFocus(bool allow_keyboard_focus);
    IMGUI_API void          PopAllowKeyboardFocus();
    IMGUI_API void          PushButtonRepeat(bool repeat);
    IMGUI_API void          PopButtonRepeat();

    // Cursor / Layout
    IMGUI_API void          Separator();
    IMGUI_API void          SameLine(float offset_from_start_x=0.0f, float spacing=-1.0f);
    IMGUI_API void          NewLine();
    IMGUI_API void          Spacing();
    IMGUI_API void          Dummy(const ImVec2& size);
    IMGUI_API void          Indent(float indent_w = 0.0f);
    IMGUI_API void          Unindent(float indent_w = 0.0f);
    IMGUI_API void          BeginGroup();
    IMGUI_API void          EndGroup();
    IMGUI_API ImVec2        GetCursorPos();
    IMGUI_API float         GetCursorPosX();
    IMGUI_API float         GetCursorPosY();
    IMGUI_API void          SetCursorPos(const ImVec2& local_pos);
    IMGUI_API void          SetCursorPosX(float local_x);
    IMGUI_API void          SetCursorPosY(float local_y);
    IMGUI_API ImVec2        GetCursorStartPos();
    IMGUI_API ImVec2        GetCursorScreenPos();
    IMGUI_API void          SetCursorScreenPos(const ImVec2& pos);
    IMGUI_API void          AlignTextToFramePadding();
    IMGUI_API float         GetTextLineHeight();
    IMGUI_API float         GetTextLineHeightWithSpacing();
    IMGUI_API float         GetFrameHeight();
    IMGUI_API float         GetFrameHeightWithSpacing();

    // ID stack/scopes
    IMGUI_API void          PushID(const char* str_id);
    IMGUI_API void          PushID(const char* str_id_begin, const char* str_id_end);
    IMGUI_API void          PushID(const void* ptr_id);
    IMGUI_API void          PushID(int int_id);
    IMGUI_API void          PopID();
    IMGUI_API ImGuiID       GetID(const char* str_id);
    IMGUI_API ImGuiID       GetID(const char* str_id_begin, const char* str_id_end);
    IMGUI_API ImGuiID       GetID(const void* ptr_id);

    // Widgets: Text
    IMGUI_API void          TextUnformatted(const char* text, const char* text_end = NULL);
    IMGUI_API void          Text(const char* fmt, ...) IM_FMTARGS(1);
    IMGUI_API void          TextV(const char* fmt, va_list args) IM_FMTLIST(1);
    IMGUI_API void          TextColored(const ImVec4& col, const char* fmt, ...) IM_FMTARGS(2);
    IMGUI_API void          TextColoredV(const ImVec4& col, const char* fmt, va_list args) IM_FMTLIST(2);
    IMGUI_API void          TextDisabled(const char* fmt, ...) IM_FMTARGS(1);
    IMGUI_API void          TextDisabledV(const char* fmt, va_list args) IM_FMTLIST(1);
    IMGUI_API void          TextWrapped(const char* fmt, ...) IM_FMTARGS(1);
    IMGUI_API void          TextWrappedV(const char* fmt, va_list args) IM_FMTLIST(1);
    IMGUI_API void          LabelText(const char* label, const char* fmt, ...) IM_FMTARGS(2);
    IMGUI_API void          LabelTextV(const char* label, const char* fmt, va_list args) IM_FMTLIST(2);
    IMGUI_API void          BulletText(const char* fmt, ...) IM_FMTARGS(1);
    IMGUI_API void          BulletTextV(const char* fmt, va_list args) IM_FMTLIST(1);

    // Widgets: Main
    IMGUI_API bool          Button(const char* label, const ImVec2& size = ImVec2(0,0));
    IMGUI_API bool          SmallButton(const char* label);
    IMGUI_API bool          InvisibleButton(const char* str_id, const ImVec2& size, ImGuiButtonFlags flags = 0);
    IMGUI_API void          Image(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0 = ImVec2(0,0), const ImVec2& uv1 = ImVec2(1,1), const ImVec4& tint_col = ImVec4(1,1,1,1), const ImVec4& border_col = ImVec4(0,0,0,0));
    IMGUI_API bool          ImageButton(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0 = ImVec2(0,0), const ImVec2& uv1 = ImVec2(1,1), int frame_padding = -1, const ImVec4& bg_col = ImVec4(0,0,0,0), const ImVec4& tint_col = ImVec4(1,1,1,1));
    IMGUI_API bool          Checkbox(const char* label, bool* v);
    IMGUI_API bool          CheckboxFlags(const char* label, int* flags, int flags_value);
    IMGUI_API bool          CheckboxFlags(const char* label, unsigned int* flags, unsigned int flags_value);
    IMGUI_API bool          RadioButton(const char* label, bool active);
    IMGUI_API bool          RadioButton(const char* label, int* v, int v_button);
    IMGUI_API void          ProgressBar(float fraction, const ImVec2& size_arg = ImVec2(-1,0), const char* overlay = NULL);
    IMGUI_API void          Bullet();

    // Widgets: Combo Box
    IMGUI_API bool          BeginCombo(const char* label, const char* preview_value, ImGuiComboFlags flags = 0);
    IMGUI_API void          EndCombo();
    IMGUI_API bool          Combo(const char* label, int* current_item, const char* const items[], int items_count, int popup_max_height_in_items = -1);
    IMGUI_API bool          Combo(const char* label, int* current_item, const char* items_separated_by_zeros, int popup_max_height_in_items = -1);
    IMGUI_API bool          Combo(const char* label, int* current_item, bool(*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int popup_max_height_in_items = -1);

    // Widgets: Drags
    IMGUI_API bool          DragFloat(const char* label, float* v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    IMGUI_API bool          DragFloat2(const char* label, float v[2], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    IMGUI_API bool          DragFloat3(const char* label, float v[3], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    IMGUI_API bool          DragFloat4(const char* label, float v[4], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    IMGUI_API bool          DragFloatRange2(const char* label, float* v_current_min, float* v_current_max, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", const char* format_max = NULL, ImGuiSliderFlags flags = 0);
    IMGUI_API bool          DragInt(const char* label, int* v, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);
    IMGUI_API bool          DragInt2(const char* label, int v[2], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);
    IMGUI_API bool          DragInt3(const char* label, int v[3], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);
    IMGUI_API bool          DragInt4(const char* label, int v[4], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);
    IMGUI_API bool          DragIntRange2(const char* label, int* v_current_min, int* v_current_max, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", const char* format_max = NULL, ImGuiSliderFlags flags = 0);
    IMGUI_API bool          DragScalar(const char* label, ImGuiDataType data_type, void* p_data, float v_speed, const void* p_min = NULL, const void* p_max = NULL, const char* format = NULL, ImGuiSliderFlags flags = 0);
    IMGUI_API bool          DragScalarN(const char* label, ImGuiDataType data_type, void* p_data, int components, float v_speed, const void* p_min = NULL, const void* p_max = NULL, const char* format = NULL, ImGuiSliderFlags flags = 0);

    // Widgets: Sliders
    IMGUI_API bool          SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    IMGUI_API bool          SliderFloat2(const char* label, float v[2], float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    IMGUI_API bool          SliderFloat3(const char* label, float v[3], float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    IMGUI_API bool          SliderFloat4(const char* label, float v[4], float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    IMGUI_API bool          SliderAngle(const char* label, float* v_rad, float v_degrees_min = -360.0f, float v_degrees_max = +360.0f, const char* format = "%.0f deg", ImGuiSliderFlags flags = 0);
    IMGUI_API bool          SliderInt(const char* label, int* v, int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
    IMGUI_API bool          SliderInt2(const char* label, int v[2], int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
    IMGUI_API bool          SliderInt3(const char* label, int v[3], int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
    IMGUI_API bool          SliderInt4(const char* label, int v[4], int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
    IMGUI_API bool          SliderScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format = NULL, ImGuiSliderFlags flags = 0);
    IMGUI_API bool          SliderScalarN(const char* label, ImGuiDataType data_type, void* p_data, int components, const void* p_min, const void* p_max, const char* format = NULL, ImGuiSliderFlags flags = 0);
    IMGUI_API bool          VSliderFloat(const char* label, const ImVec2& size, float* v, float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    IMGUI_API bool          VSliderInt(const char* label, const ImVec2& size, int* v, int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
    IMGUI_API bool          VSliderScalar(const char* label, const ImVec2& size, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format = NULL, ImGuiSliderFlags flags = 0);

    // Widgets: Input with Keyboard
    IMGUI_API bool          InputText(const char* label, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
    IMGUI_API bool          InputTextMultiline(const char* label, char* buf, size_t buf_size, const ImVec2& size = ImVec2(0,0), ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
    IMGUI_API bool          InputTextWithHint(const char* label, const char* hint, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
    IMGUI_API bool          InputFloat(const char* label, float* v, float step = 0.0f, float step_fast = 0.0f, const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
    IMGUI_API bool          InputFloat2(const char* label, float v[2], const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
    IMGUI_API bool          InputFloat3(const char* label, float v[3], const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
    IMGUI_API bool          InputFloat4(const char* label, float v[4], const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
    IMGUI_API bool          InputInt(const char* label, int* v, int step = 1, int step_fast = 100, ImGuiInputTextFlags flags = 0);
    IMGUI_API bool          InputInt2(const char* label, int v[2], ImGuiInputTextFlags flags = 0);
    IMGUI_API bool          InputInt3(const char* label, int v[3], ImGuiInputTextFlags flags = 0);
    IMGUI_API bool          InputInt4(const char* label, int v[4], ImGuiInputTextFlags flags = 0);
    IMGUI_API bool          InputDouble(const char* label, double* v, double step = 0.0, double step_fast = 0.0, const char* format = "%.6f", ImGuiInputTextFlags flags = 0);
    IMGUI_API bool          InputScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_step = NULL, const void* p_step_fast = NULL, const char* format = NULL, ImGuiInputTextFlags flags = 0);
    IMGUI_API bool          InputScalarN(const char* label, ImGuiDataType data_type, void* p_data, int components, const void* p_step = NULL, const void* p_step_fast = NULL, const char* format = NULL, ImGuiInputTextFlags flags = 0);

    // Widgets: Color Editor/Picker
    IMGUI_API bool          ColorEdit3(const char* label, float col[3], ImGuiColorEditFlags flags = 0);
    IMGUI_API bool          ColorEdit4(const char* label, float col[4], ImGuiColorEditFlags flags = 0);
    IMGUI_API bool          ColorPicker3(const char* label, float col[3], ImGuiColorEditFlags flags = 0);
    IMGUI_API bool          ColorPicker4(const char* label, float col[4], ImGuiColorEditFlags flags = 0, const float* ref_col = NULL);
    IMGUI_API bool          ColorButton(const char* desc_id, const ImVec4& col, ImGuiColorEditFlags flags = 0, ImVec2 size = ImVec2(0,0));
    IMGUI_API void          SetColorEditOptions(ImGuiColorEditFlags flags);

    // Widgets: Trees
    IMGUI_API bool          TreeNode(const char* label);
    IMGUI_API bool          TreeNode(const char* str_id, const char* fmt, ...) IM_FMTARGS(2);
    IMGUI_API bool          TreeNode(const void* ptr_id, const char* fmt, ...) IM_FMTARGS(2);
    IMGUI_API bool          TreeNodeV(const char* str_id, const char* fmt, va_list args) IM_FMTLIST(2);
    IMGUI_API bool          TreeNodeV(const void* ptr_id, const char* fmt, va_list args) IM_FMTLIST(2);
    IMGUI_API bool          TreeNodeEx(const char* label, ImGuiTreeNodeFlags flags = 0);
    IMGUI_API bool          TreeNodeEx(const char* str_id, ImGuiTreeNodeFlags flags, const char* fmt, ...) IM_FMTARGS(3);
    IMGUI_API bool          TreeNodeEx(const void* ptr_id, ImGuiTreeNodeFlags flags, const char* fmt, ...) IM_FMTARGS(3);
    IMGUI_API bool          TreeNodeExV(const char* str_id, ImGuiTreeNodeFlags flags, const char* fmt, va_list args) IM_FMTLIST(3);
    IMGUI_API bool          TreeNodeExV(const void* ptr_id, ImGuiTreeNodeFlags flags, const char* fmt, va_list args) IM_FMTLIST(3);
    IMGUI_API void          TreePush(const char* str_id);
    IMGUI_API void          TreePush(const void* ptr_id = NULL);
    IMGUI_API void          TreePop();
    IMGUI_API float         GetTreeNodeToLabelSpacing();
    IMGUI_API bool          CollapsingHeader(const char* label, ImGuiTreeNodeFlags flags = 0);
    IMGUI_API bool          CollapsingHeader(const char* label, bool* p_open, ImGuiTreeNodeFlags flags = 0);
    IMGUI_API void          SetNextItemOpen(bool is_open, ImGuiCond cond = 0);

    // Widgets: Selectables
    IMGUI_API bool          Selectable(const char* label, bool selected = false, ImGuiSelectableFlags flags = 0, const ImVec2& size = ImVec2(0,0));
    IMGUI_API bool          Selectable(const char* label, bool* p_selected, ImGuiSelectableFlags flags = 0, const ImVec2& size = ImVec2(0,0));

    // Widgets: List Boxes
    IMGUI_API bool          ListBox(const char* label, int* current_item, const char* const items[], int items_count, int height_in_items = -1);
    IMGUI_API bool          ListBox(const char* label, int* current_item, bool (*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int height_in_items = -1);
    IMGUI_API bool          ListBoxHeader(const char* label, const ImVec2& size = ImVec2(0,0));
    IMGUI_API bool          ListBoxHeader(const char* label, int items_count, int height_in_items = -1);
    IMGUI_API void          ListBoxFooter();

    // Widgets: Data Plotting
    IMGUI_API void          PlotLines(const char* label, const float* values, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0,0), int stride = sizeof(float));
    IMGUI_API void          PlotLines(const char* label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0,0));
    IMGUI_API void          PlotHistogram(const char* label, const float* values, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0,0), int stride = sizeof(float));
    IMGUI_API void          PlotHistogram(const char* label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0,0));

    // Widgets: Value() Helpers.
    IMGUI_API void          Value(const char* prefix, bool b);
    IMGUI_API void          Value(const char* prefix, int v);
    IMGUI_API void          Value(const char* prefix, unsigned int v);
    IMGUI_API void          Value(const char* prefix, float v, const char* float_format = NULL);

    // Widgets: Menus
    IMGUI_API bool          BeginMainMenuBar();
    IMGUI_API void          EndMainMenuBar();
    IMGUI_API bool          BeginMenuBar();
    IMGUI_API void          EndMenuBar();
    IMGUI_API bool          BeginMenu(const char* label, bool enabled = true);
    IMGUI_API void          EndMenu();
    IMGUI_API bool          MenuItem(const char* label, const char* shortcut = NULL, bool selected = false, bool enabled = true);
    IMGUI_API bool          MenuItem(const char* label, const char* shortcut, bool* p_selected, bool enabled = true);

    // Tooltips
    IMGUI_API void          BeginTooltip();
    IMGUI_API void          EndTooltip();
    IMGUI_API void          SetTooltip(const char* fmt, ...) IM_FMTARGS(1);
    IMGUI_API void          SetTooltipV(const char* fmt, va_list args) IM_FMTLIST(1);

    // Popups, Modals
    IMGUI_API void          OpenPopup(const char* str_id, ImGuiPopupFlags popup_flags = 0);
    IMGUI_API bool          BeginPopup(const char* str_id, ImGuiWindowFlags flags = 0);
    IMGUI_API bool          BeginPopupContextItem(const char* str_id = NULL, ImGuiPopupFlags popup_flags = 1);
    IMGUI_API bool          BeginPopupContextWindow(const char* str_id = NULL, ImGuiPopupFlags popup_flags = 1);
    IMGUI_API bool          BeginPopupContextVoid(const char* str_id = NULL, ImGuiPopupFlags popup_flags = 1);
    IMGUI_API bool          BeginPopupModal(const char* name, bool* p_open = NULL, ImGuiWindowFlags flags = 0);
    IMGUI_API void          EndPopup();
    IMGUI_API void          OpenPopupOnItemClick(const char* str_id = NULL, ImGuiPopupFlags popup_flags = 1);
    IMGUI_API bool          IsPopupOpen(const char* str_id, ImGuiPopupFlags flags = 0);
    IMGUI_API void          CloseCurrentPopup();

    // Tables
    IMGUI_API bool          BeginTable(const char* str_id, int column, ImGuiTableFlags flags = 0, const ImVec2& outer_size = ImVec2(0,0), float inner_width = 0.0f);
    IMGUI_API void          EndTable();
    IMGUI_API void          TableNextRow(ImGuiTableRowFlags row_flags = 0, float min_row_height = 0.0f);
    IMGUI_API bool          TableNextColumn();
    IMGUI_API bool          TableSetColumnIndex(int column_n);
    IMGUI_API void          TableSetupColumn(const char* label, ImGuiTableColumnFlags flags = 0, float init_width_or_weight = 0.0f, ImGuiID user_id = 0);
    IMGUI_API void          TableSetupScrollFreeze(int cols, int rows);
    IMGUI_API void          TableHeadersRow();
    IMGUI_API void          TableHeader(const char* label);
    IMGUI_API ImGuiTableSortSpecs*  TableGetSortSpecs();
    IMGUI_API int           TableGetColumnCount();
    IMGUI_API int           TableGetColumnIndex();
    IMGUI_API int           TableGetRowIndex();
    IMGUI_API const char*   TableGetColumnName(int column_n = -1);
    IMGUI_API ImGuiTableColumnFlags TableGetColumnFlags(int column_n = -1);
    IMGUI_API void          TableSetBgColor(ImGuiTableBgTarget target, ImU32 color, int column_n = -1);

    // Columns
    IMGUI_API void          Columns(int count = 1, const char* id = NULL, bool border = true);
    IMGUI_API void          NextColumn();
    IMGUI_API int           GetColumnIndex();
    IMGUI_API float         GetColumnWidth(int column_index = -1);
    IMGUI_API void          SetColumnWidth(int column_index, float width);
    IMGUI_API float         GetColumnOffset(int column_index = -1);
    IMGUI_API void          SetColumnOffset(int column_index, float offset_x);
    IMGUI_API int           GetColumnsCount();

    // Tab Bars, Tabs
    IMGUI_API bool          BeginTabBar(const char* str_id, ImGuiTabBarFlags flags = 0);
    IMGUI_API void          EndTabBar();
    IMGUI_API bool          BeginTabItem(const char* label, bool* p_open = NULL, ImGuiTabItemFlags flags = 0);
    IMGUI_API void          EndTabItem();
    IMGUI_API bool          TabItemButton(const char* label, ImGuiTabItemFlags flags = 0);
    IMGUI_API void          SetTabItemClosed(const char* tab_or_docked_window_label);

    // Drag and Drop
    IMGUI_API bool          BeginDragDropSource(ImGuiDragDropFlags flags = 0);
    IMGUI_API bool          SetDragDropPayload(const char* type, const void* data, size_t sz, ImGuiCond cond = 0);
    IMGUI_API void          EndDragDropSource();
    IMGUI_API bool          BeginDragDropTarget();
    IMGUI_API const ImGuiPayload* AcceptDragDropPayload(const char* type, ImGuiDragDropFlags flags = 0);
    IMGUI_API void          EndDragDropTarget();
    IMGUI_API const ImGuiPayload* GetDragDropPayload();

    // Clipping
    IMGUI_API void          PushClipRect(const ImVec2& clip_rect_min, const ImVec2& clip_rect_max, bool intersect_with_current_clip_rect);
    IMGUI_API void          PopClipRect();

    // Focus, Activation
    IMGUI_API void          SetItemDefaultFocus();
    IMGUI_API void          SetKeyboardFocusHere(int offset = 0);

    // Item/Widgets Utilities
    IMGUI_API bool          IsItemHovered(ImGuiHoveredFlags flags = 0);
    IMGUI_API bool          IsItemActive();
    IMGUI_API bool          IsItemFocused();
    IMGUI_API bool          IsItemClicked(ImGuiMouseButton mouse_button = 0);
    IMGUI_API bool          IsItemVisible();
    IMGUI_API bool          IsItemEdited();
    IMGUI_API bool          IsItemActivated();
    IMGUI_API bool          IsItemDeactivated();
    IMGUI_API bool          IsItemDeactivatedAfterEdit();
    IMGUI_API bool          IsAnyItemHovered();
    IMGUI_API bool          IsAnyItemActive();
    IMGUI_API bool          IsAnyItemFocused();
    IMGUI_API ImVec2        GetItemRectMin();
    IMGUI_API ImVec2        GetItemRectMax();
    IMGUI_API ImVec2        GetItemRectSize();
    IMGUI_API void          SetItemAllowOverlap();

    // Miscellaneous Utilities
    IMGUI_API bool          IsRectVisible(const ImVec2& size);
    IMGUI_API bool          IsRectVisible(const ImVec2& rect_min, const ImVec2& rect_max);
    IMGUI_API double        GetTime();
    IMGUI_API int           GetFrameCount();
    IMGUI_API ImDrawList*   GetBackgroundDrawList();
    IMGUI_API ImDrawList*   GetForegroundDrawList();
    IMGUI_API ImDrawListSharedData* GetDrawListSharedData();
    IMGUI_API const char*   GetStyleColorName(ImGuiCol idx);
    IMGUI_API void          SetStateStorage(ImGuiStorage* storage);
    IMGUI_API ImGuiStorage* GetStateStorage();
    IMGUI_API void          CalcListClipping(int items_count, float items_height, int* out_items_display_start, int* out_items_display_end);
    IMGUI_API bool          BeginChildFrame(ImGuiID id, const ImVec2& size, ImGuiWindowFlags flags = 0);
    IMGUI_API void          EndChildFrame();

    // Text Utilities
    IMGUI_API ImVec2        CalcTextSize(const char* text, const char* text_end = NULL, bool hide_text_after_double_hash = false, float wrap_width = -1.0f);

    // Color Utilities
    IMGUI_API ImVec4        ColorConvertU32ToFloat4(ImU32 in);
    IMGUI_API ImU32         ColorConvertFloat4ToU32(const ImVec4& in);
    IMGUI_API void          ColorConvertRGBtoHSV(float r, float g, float b, float& out_h, float& out_s, float& out_v);
    IMGUI_API void          ColorConvertHSVtoRGB(float h, float s, float v, float& out_r, float& out_g, float& out_b);

    // Inputs
    IMGUI_API int           GetKeyIndex(ImGuiKey imgui_key);
    IMGUI_API bool          IsKeyDown(int user_key_index);
    IMGUI_API bool          IsKeyPressed(int user_key_index, bool repeat = true);
    IMGUI_API bool          IsKeyReleased(int user_key_index);
    IMGUI_API int           GetKeyPressedAmount(int key_index, float repeat_delay, float rate);
    IMGUI_API bool          IsMouseDown(ImGuiMouseButton button);
    IMGUI_API bool          IsMouseClicked(ImGuiMouseButton button, bool repeat = false);
    IMGUI_API bool          IsMouseDoubleClicked(ImGuiMouseButton button);
    IMGUI_API bool          IsMouseReleased(ImGuiMouseButton button);
    IMGUI_API bool          IsMouseDragging(ImGuiMouseButton button, float lock_threshold = -1.0f);
    IMGUI_API bool          IsMouseHoveringRect(const ImVec2& r_min, const ImVec2& r_max, bool clip = true);
    IMGUI_API bool          IsMousePosValid(const ImVec2* mouse_pos = NULL);
    IMGUI_API ImVec2        GetMousePos();
    IMGUI_API ImVec2        GetMousePosOnOpeningCurrentPopup();
    IMGUI_API ImVec2        GetMouseDragDelta(ImGuiMouseButton button = 0, float lock_threshold = -1.0f);
    IMGUI_API void          ResetMouseDragDelta(ImGuiMouseButton button = 0);
    IMGUI_API ImGuiMouseCursor GetMouseCursor();
    IMGUI_API void          SetMouseCursor(ImGuiMouseCursor cursor_type);
    IMGUI_API void          CaptureKeyboardFromApp(bool want_capture_keyboard_value = true);
    IMGUI_API void          CaptureMouseFromApp(bool want_capture_mouse_value = true);

    // Clipboard Utilities
    IMGUI_API const char*   GetClipboardText();
    IMGUI_API void          SetClipboardText(const char* text);

    // Settings/.Ini Utilities
    IMGUI_API void          LoadIniSettingsFromDisk(const char* ini_filename);
    IMGUI_API void          LoadIniSettingsFromMemory(const char* ini_data, size_t ini_size = 0);
    IMGUI_API void          SaveIniSettingsToDisk(const char* ini_filename);
    IMGUI_API const char*   SaveIniSettingsToMemory(size_t* out_ini_size = NULL);

    // Memory Utilities
    // All those functions are not reliant on the current context.
    // If you reload the contents of imgui.cpp at runtime, you may need to call SetCurrentContext() + SetAllocatorFunctions() again.
    IMGUI_API void          SetAllocatorFunctions(void* (*alloc_func)(size_t sz, void* user_data), void (*free_func)(void* ptr, void* user_data), void* user_data = NULL);
    IMGUI_API void*         MemAlloc(size_t size);
    IMGUI_API void          MemFree(void* ptr);

} // namespace ImGui

//-----------------------------------------------------------------------------
// Flags enum
//-----------------------------------------------------------------------------

// Flags for ImGui::Begin()
enum ImGuiWindowFlags_
{
    ImGuiWindowFlags_None                   = 0,
    ImGuiWindowFlags_NoTitleBar             = 1 << 0,   // Disable title-bar
    ImGuiWindowFlags_NoResize               = 1 << 1,   // Disable user resizing with the lower-right grip
    ImGuiWindowFlags_NoMove                 = 1 << 2,   // Disable user moving the window
    ImGuiWindowFlags_NoScrollbar            = 1 << 3,   // Disable scrollbars (window can still scroll with mouse or programmatically)
    ImGuiWindowFlags_NoScrollWithMouse      = 1 << 4,   // Disable user vertically scrolling with mouse wheel. On child window, mouse wheel will be forwarded to the parent unless NoScrollbar is also set.
    ImGuiWindowFlags_NoCollapse             = 1 << 5,   // Disable user collapsing window by double-clicking on it
    ImGuiWindowFlags_AlwaysAutoResize       = 1 << 6,   // Resize every window to its content every frame
    ImGuiWindowFlags_NoBackground           = 1 << 7,   // Disable drawing background color (WindowBg, etc.) and outside border. Similar as using SetNextWindowBgAlpha(0.0f).
    ImGuiWindowFlags_NoSavedSettings        = 1 << 8,   // Never load/save settings in .ini file
    ImGuiWindowFlags_NoMouseInputs          = 1 << 9,   // Disable catching mouse, hovering test with pass through.
    ImGuiWindowFlags_MenuBar                = 1 << 10,  // Has a menu-bar
    ImGuiWindowFlags_HorizontalScrollbar    = 1 << 11,  // Allow horizontal scrollbar to appear (off by default). You may use SetNextWindowContentSize(ImVec2(width,0.0f)); prior to calling Begin() to specify width. Read code in imgui_demo in the "Horizontal Scrolling" section.
    ImGuiWindowFlags_NoFocusOnAppearing     = 1 << 12,  // Disable taking focus when transitioning from hidden to visible state
    ImGuiWindowFlags_NoBringToFrontOnFocus  = 1 << 13,  // Disable bringing window to front when taking focus (e.g. clicking on it or programmatically giving it focus)
    ImGuiWindowFlags_AlwaysVerticalScrollbar= 1 << 14,  // Always show vertical scrollbar (even if ContentSize.y < WindowSize.y)
    ImGuiWindowFlags_AlwaysHorizontalScrollbar=1 << 15, // Always show horizontal scrollbar (even if ContentSize.x < WindowSize.x)
    ImGuiWindowFlags_AlwaysUseWindowPadding = 1 << 16,  // Ensure child windows without border uses window padding (ignored by default for non-bordered child windows, because it makes more sense)
    ImGuiWindowFlags_NoNavInputs            = 1 << 18,  // No gamepad/keyboard navigation within the window
    ImGuiWindowFlags_NoNavFocus             = 1 << 19,  // No focusing toward this window with gamepad/keyboard navigation (e.g. skipped by CTRL+TAB)
    ImGuiWindowFlags_UnsavedDocument        = 1 << 20,  // Append '*' to title without affecting the ID, as a convenience to avoid using the ### operator. When used in a tab/docking context, tab is selected on closure and user gets a chance to save before closing.
    ImGuiWindowFlags_NoNav                  = ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus,
    ImGuiWindowFlags_NoDecoration           = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse,
    ImGuiWindowFlags_NoInputs               = ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus,

    // [Internal]
    ImGuiWindowFlags_NavFlattened           = 1 << 23,  // (for internal use only) flatten navigation/tabbing fields onto parent, will solve overlapping crises
    ImGuiWindowFlags_ChildWindow            = 1 << 24,  // (for internal use only) identify a window created by BeginChild()
    ImGuiWindowFlags_Tooltip                = 1 << 25,  // (for internal use only) identify a window created by BeginTooltip()
    ImGuiWindowFlags_Popup                  = 1 << 26,  // (for internal use only) identify a window created by BeginPopup()
    ImGuiWindowFlags_Modal                  = 1 << 27,  // (for internal use only) identify a window created by BeginPopupModal()
    ImGuiWindowFlags_ChildMenu              = 1 << 28   // (for internal use only) identify a menu child window
};

// Flags for ImGui::InputText()
enum ImGuiInputTextFlags_
{
    ImGuiInputTextFlags_None                = 0,
    ImGuiInputTextFlags_CharsDecimal        = 1 << 0,   // Allow 0123456789.+-
    ImGuiInputTextFlags_CharsHexadecimal    = 1 << 1,   // Allow 0123456789ABCDEFabcdef
    ImGuiInputTextFlags_CharsUppercase      = 1 << 2,   // Turn a..z into A..Z
    ImGuiInputTextFlags_CharsNoBlank        = 1 << 3,   // Filter out spaces, tabs
    ImGuiInputTextFlags_AutoSelectAll       = 1 << 4,   // Select entire text when first taking focus
    ImGuiInputTextFlags_EnterReturnsTrue    = 1 << 5,   // Return 'true' when Enter is pressed (as opposed to every time the value was modified). Consider looking at the IsItemDeactivatedAfterEdit() function.
    ImGuiInputTextFlags_CallbackCompletion  = 1 << 6,   // Callback on pressing TAB (for completion handling)
    ImGuiInputTextFlags_CallbackHistory     = 1 << 7,   // Callback on pressing Up/Down arrows (for history handling)
    ImGuiInputTextFlags_CallbackAlways      = 1 << 8,   // Callback on each iteration. User code may query cursor position, modify text buffer.
    ImGuiInputTextFlags_CallbackCharFilter  = 1 << 9,   // Callback on character inputs to replace or discard them. Modify 'EventChar' to replace characters.
    ImGuiInputTextFlags_AllowTabInput       = 1 << 10,  // Pressing TAB input a '\t' character into the text field
    ImGuiInputTextFlags_CtrlEnterForNewLine = 1 << 11,  // In multi-line mode, unfocus with Enter, add new line with Ctrl+Enter. Consume browser navigation shortcuts if pointing to an HTML canvas.
    ImGuiInputTextFlags_NoHorizontalScroll  = 1 << 12,  // Disable horizontal scrolling i.e. prevent a text with a single line from scrolling horizontally (for InputText).
    ImGuiInputTextFlags_AlwaysInsertMode    = 1 << 13,  // Insert mode
    ImGuiInputTextFlags_ReadOnly            = 1 << 14,  // Read-only
    ImGuiInputTextFlags_Password            = 1 << 15,  // Password mode, display all characters as '*'
    ImGuiInputTextFlags_NoUndoRedo          = 1 << 16,  // Disable undo/redo. Note that input text owns the text data while active, if you want to provide your own undo/redo stack you need e.g. to call ClearActiveID().
    ImGuiInputTextFlags_CharsScientific     = 1 << 17,  // Allow 0123456789.+-Ee
    ImGuiInputTextFlags_CallbackResize      = 1 << 18,  // Callback on buffer capacity changes request (beyond 'buf_size' parameter). Make sure read-only buffer are never resized.
    // [Internal]
    ImGuiInputTextFlags_Multiline           = 1 << 20,  // (for internal use only)
    ImGuiInputTextFlags_NoMarkEdited        = 1 << 21   // (for internal use only)
};

// Flags for ImGui::TreeNodeEx(), ImGui::CollapsingHeader()
enum ImGuiTreeNodeFlags_
{
    ImGuiTreeNodeFlags_None                 = 0,
    ImGuiTreeNodeFlags_Selected             = 1 << 0,   // Draw as selected
    ImGuiTreeNodeFlags_Framed               = 1 << 1,   // Full colored frame (e.g. for CollapsingHeader)
    ImGuiTreeNodeFlags_AllowItemOverlap     = 1 << 2,   // Hit testing to allow subsequent widgets to overlap this one
    ImGuiTreeNodeFlags_NoTreePushOnOpen     = 1 << 3,   // Don't do a TreePush() when open (e.g. for CollapsingHeader) = no extra indent nor pushing on ID stack
    ImGuiTreeNodeFlags_NoAutoOpenOnLog      = 1 << 4,   // Don't automatically open when logging is active (by default logging will open nodes recursively)
    ImGuiTreeNodeFlags_DefaultOpen          = 1 << 5,   // Default node to be open
    ImGuiTreeNodeFlags_OpenOnDoubleClick    = 1 << 6,   // Need double-click to open node
    ImGuiTreeNodeFlags_OpenOnArrow          = 1 << 7,   // Only open when clicking on the arrow part. If ImGuiTreeNodeFlags_OpenOnDoubleClick is also set, single-click arrow or double-click all box to open.
    ImGuiTreeNodeFlags_Leaf                 = 1 << 8,   // No collapsing, no arrow (use as a convenience for leaf nodes).
    ImGuiTreeNodeFlags_Bullet               = 1 << 9,   // Display a bullet instead of arrow
    ImGuiTreeNodeFlags_FramePadding         = 1 << 10,  // Use FramePadding (even for an unframed text node) to vertically align text baseline to regular widget height. Equivalent to calling AlignTextToFramePadding().
    ImGuiTreeNodeFlags_SpanAvailWidth       = 1 << 11,  // Extend hit box to the right-most edge, even if not framed. This is not the default in order to allow adding other items on the same line. In the future we may refactor the hit system to be front-to-back, allowing natural overlaps and then this can become the default.
    ImGuiTreeNodeFlags_SpanFullWidth        = 1 << 12,  // Extend hit box to the left-most and right-most edges (bypass the indented area).
    ImGuiTreeNodeFlags_NavLeftJumpsBackHere = 1 << 13,  // (WIP) Nav: left direction may move to this TreeNode() from any of its child (items submitted between TreeNode and TreePop)
    //ImGuITreeNodeFlags_NoScrollOnOpen     = 1 << 14,  // FIXME: TODO: Disable automatic scrolling when opening a tree node
    ImGuiTreeNodeFlags_CollapsingHeader     = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_NoAutoOpenOnLog
};

// Flags for ImGui::Selectable()
enum ImGuiSelectableFlags_
{
    ImGuiSelectableFlags_None               = 0,
    ImGuiSelectableFlags_DontClosePopups    = 1 << 0,   // Clicking this don't close parent popup window
    ImGuiSelectableFlags_SpanAllColumns     = 1 << 1,   // Selectable frame can span all columns (text will still fit in current column)
    ImGuiSelectableFlags_AllowDoubleClick   = 1 << 2,   // Generate press events on double clicks too
    ImGuiSelectableFlags_Disabled           = 1 << 3,   // Cannot be selected, display greyed out text
    ImGuiSelectableFlags_AllowItemOverlap   = 1 << 4    // (WIP) Hit testing to allow subsequent widgets to overlap this one
};

// Flags for ImGui::BeginCombo()
enum ImGuiComboFlags_
{
    ImGuiComboFlags_None                    = 0,
    ImGuiComboFlags_PopupAlignLeft          = 1 << 0,   // Align the popup toward the left by default
    ImGuiComboFlags_HeightSmall             = 1 << 1,   // Max ~4 items visible. Tip: If you want your combo popup to be a specific size you can use SetNextWindowSizeConstraints() prior to calling BeginCombo()
    ImGuiComboFlags_HeightRegular           = 1 << 2,   // Max ~8 items visible (default)
    ImGuiComboFlags_HeightLarge             = 1 << 3,   // Max ~20 items visible
    ImGuiComboFlags_HeightLargest           = 1 << 4,   // As many fitting items as possible
    ImGuiComboFlags_NoArrowButton           = 1 << 5,   // Display on the preview box without the square arrow button
    ImGuiComboFlags_NoPreview               = 1 << 6,   // Display only a square arrow button
    ImGuiComboFlags_HeightMask_             = ImGuiComboFlags_HeightSmall | ImGuiComboFlags_HeightRegular | ImGuiComboFlags_HeightLarge | ImGuiComboFlags_HeightLargest
};

// Flags for ImGui::BeginTabBar()
enum ImGuiTabBarFlags_
{
    ImGuiTabBarFlags_None                           = 0,
    ImGuiTabBarFlags_Reorderable                    = 1 << 0,   // Allow manually reordering tabs (use CTRL+SHIFT+TAB to cycle through tabs)
    ImGuiTabBarFlags_AutoSelectNewTabs              = 1 << 1,   // Automatically select new tabs when they appear
    ImGuiTabBarFlags_TabListPopupButton             = 1 << 2,   // Disable hitting TAB to namescope window contents to the tab bar
    ImGuiTabBarFlags_NoCloseWithMiddleMouseButton   = 1 << 3,   // Disable behavior of closing tabs (that are submitted with p_open != NULL) with middle mouse button. You can still repro this behavior on user's side with IsItemHovered() + IsMouseClicked(2).
    ImGuiTabBarFlags_NoTabListScrollingButtons      = 1 << 4,   // Disable scrolling buttons (apply when fitting policy is ImGuiTabBarFlags_FittingPolicyScroll)
    ImGuiTabBarFlags_NoTooltip                      = 1 << 5,   // Disable tooltips when hovering a tab
    ImGuiTabBarFlags_FittingPolicyResizeDown        = 1 << 6,   // Resize tabs when they don't fit
    ImGuiTabBarFlags_FittingPolicyScroll            = 1 << 7,   // Add scroll buttons when tabs don't fit
    ImGuiTabBarFlags_FittingPolicyMask_             = ImGuiTabBarFlags_FittingPolicyResizeDown | ImGuiTabBarFlags_FittingPolicyScroll,
    ImGuiTabBarFlags_FittingPolicyDefault_          = ImGuiTabBarFlags_FittingPolicyResizeDown
};

// Flags for ImGui::BeginTabItem()
enum ImGuiTabItemFlags_
{
    ImGuiTabItemFlags_None                          = 0,
    ImGuiTabItemFlags_UnsavedDocument               = 1 << 0,   // Append '*' to tab label, e.g. "MyFile.txt*". Also appends GImGuiTabItemFlags_UnsavedDocument to the parent tab bar.
    ImGuiTabItemFlags_SetSelected                   = 1 << 1,   // Trigger flag to programmatically make the tab selected when calling BeginTabItem()
    ImGuiTabItemFlags_NoCloseWithMiddleMouseButton  = 1 << 2,   // Disable behavior of closing tabs (that are submitted with p_open != NULL) with middle mouse button. You can still repro this behavior on user's side with IsItemHovered() + IsMouseClicked(2).
    ImGuiTabItemFlags_NoPushId                      = 1 << 3    // Don't push an ID based on the tab's label. This is default behavior and need to be turned off if you want to use visible label as ID.
};

// Flags for ImGui::Focused()
enum ImGuiFocusedFlags_
{
    ImGuiFocusedFlags_None                          = 0,
    ImGuiFocusedFlags_ChildWindows                  = 1 << 0,   // IsWindowFocused(): Return true if any children of the window is focused
    ImGuiFocusedFlags_RootWindow                    = 1 << 1,   // IsWindowFocused(): Test from root window (top most parent of the current hierarchy)
    ImGuiFocusedFlags_AnyWindow                     = 1 << 2,   // IsWindowFocused(): Return true if any window is focused
    ImGuiFocusedFlags_RootAndChildWindows           = ImGuiFocusedFlags_RootWindow | ImGuiFocusedFlags_ChildWindows
};

// Flags for ImGui::Hovered()
enum ImGuiHoveredFlags_
{
    ImGuiHoveredFlags_None                          = 0,
    ImGuiHoveredFlags_ChildWindows                  = 1 << 0,   // IsWindowHovered() only: Return true if any children of the window is hovered
    ImGuiHoveredFlags_RootWindow                    = 1 << 1,   // IsWindowHovered() only: Test from root window (top most parent of the current hierarchy)
    ImGuiHoveredFlags_AnyWindow                     = 1 << 2,   // IsWindowHovered() only: Return true if any window is hovered
    ImGuiHoveredFlags_AllowWhenBlockedByPopup       = 1 << 3,   // Return true even if a popup window is normally blocking access to this item/window
    //ImGuiHoveredFlags_AllowWhenBlockedByModal     = 1 << 4,   // Return true even if a modal popup window is normally blocking access to this item/window. FIXME-TODO: Currently requires ImGuiHoveredFlags_AllowWhenBlockedByPopup as well.
    ImGuiHoveredFlags_AllowWhenBlockedByActiveItem  = 1 << 5,   // Return true even if an active item is blocking access to this item/window. Useful for Drag and Drop patterns.
    ImGuiHoveredFlags_AllowWhenOverlapped           = 1 << 6,   // Return true even if the position is obstructed or overlapped by another window
    ImGuiHoveredFlags_AllowWhenDisabled             = 1 << 7,   // Return true even if the item is disabled
    ImGuiHoveredFlags_RectOnly                      = ImGuiHoveredFlags_AllowWhenBlockedByPopup | ImGuiHoveredFlags_AllowWhenBlockedByActiveItem | ImGuiHoveredFlags_AllowWhenOverlapped,
    ImGuiHoveredFlags_RootAndChildWindows           = ImGuiHoveredFlags_RootWindow | ImGuiHoveredFlags_ChildWindows
};

// Flags for ImGui::BeginDragDropSource(), ImGui::AcceptDragDropPayload()
enum ImGuiDragDropFlags_
{
    ImGuiDragDropFlags_None                         = 0,
    // BeginDragDropSource() flags
    ImGuiDragDropFlags_SourceNoPreviewTooltip       = 1 << 0,   // By default, a successful call to BeginDragDropSource opens a tooltip so you can display a preview or description of the source contents. This flag disable this behavior.
    ImGuiDragDropFlags_SourceNoDisableHover         = 1 << 1,   // By default, when dragging we clear data so that IsItemHovered() will return false, to avoid subsequent user code submitting tooltips. This flag disable this behavior so you can still call IsItemHovered() on the source item.
    ImGuiDragDropFlags_SourceNoHoldToOpenOthers     = 1 << 2,   // Disable the behavior that allows to open tree nodes and collapsing header by holding over them while dragging a source item.
    ImGuiDragDropFlags_SourceAllowNullID            = 1 << 3,   // Allow items such as Text(), Image() that have no unique identifier to be used as drag source, by manufacturing a temporary identifier based on their window-relative position. This is a shortcut for PushID()/PopID() in this situation.
    ImGuiDragDropFlags_SourceExtern                 = 1 << 4,   // External source (from outside of imgui), won't attempt to read current item's state.
    ImGuiDragDropFlags_SourceAutoExpirePayload      = 1 << 5,   // Automatically expire the payload if the source functions returns false (e.g. Stop dragging + release mouse button).
    // AcceptDragDropPayload() flags
    ImGuiDragDropFlags_AcceptBeforeDelivery         = 1 << 10,  // AcceptDragDropPayload() will returns true even before a call to SetDragDropPayload() between BeginDragDropSource() and EndDragDropSource().
    ImGuiDragDropFlags_AcceptNoDrawDefaultRect      = 1 << 11,  // Do not draw the default highlight rectangle when hovering over target.
    ImGuiDragDropFlags_AcceptNoPreviewTooltip       = 1 << 12,  // Request hiding the BeginDragDropSource tooltip from the BeginDragDropTarget site.
    ImGuiDragDropFlags_AcceptPeekOnly               = ImGuiDragDropFlags_AcceptBeforeDelivery | ImGuiDragDropFlags_AcceptNoDrawDefaultRect // For peeking ahead and inspecting the payload before delivery.
};

// Standard Drag and Drop payload types. You can define you own payload types using short strings. Types starting with '_' are defined by Dear ImGui.
#define IMGUI_PAYLOAD_TYPE_COLOR_3F     "_COL3F"    // float[3]
#define IMGUI_PAYLOAD_TYPE_COLOR_4F     "_COL4F"    // float[4]

//- enum
enum ImGuiDataType_
{
    ImGuiDataType_S8,       // signed char / char (with sensible compilers)
    ImGuiDataType_U8,       // unsigned char
    ImGuiDataType_S16,      // signed short
    ImGuiDataType_U16,      // unsigned short
    ImGuiDataType_S32,      // signed int
    ImGuiDataType_U32,      // unsigned int
    ImGuiDataType_S64,      // signed long long
    ImGuiDataType_U64,      // unsigned long long
    ImGuiDataType_Float,    // float
    ImGuiDataType_Double,   // double
    ImGuiDataType_COUNT
};

//- enum
enum ImGuiDir_
{
    ImGuiDir_None    = -1,
    ImGuiDir_Left    = 0,
    ImGuiDir_Right   = 1,
    ImGuiDir_Up      = 2,
    ImGuiDir_Down    = 3,
    ImGuiDir_COUNT
};

// A sorting direction
enum ImGuiSortDirection_
{
    ImGuiSortDirection_None         = 0,
    ImGuiSortDirection_Ascending    = 1,    // e.g. A->Z, 0->9
    ImGuiSortDirection_Descending   = 2     // e.g. Z->A, 9->0
};

//- enum
// MACOS: F1..F12 seems to be key-equivalent to Sound Up/Down/Mute, Brightness Up/Down, etc.
// We should perhaps not use those default mappings.
enum ImGuiKey_
{
    ImGuiKey_Tab,
    ImGuiKey_LeftArrow,
    ImGuiKey_RightArrow,
    ImGuiKey_UpArrow,
    ImGuiKey_DownArrow,
    ImGuiKey_PageUp,
    ImGuiKey_PageDown,
    ImGuiKey_Home,
    ImGuiKey_End,
    ImGuiKey_Insert,
    ImGuiKey_Delete,
    ImGuiKey_Backspace,
    ImGuiKey_Space,
    ImGuiKey_Enter,
    ImGuiKey_Escape,
    ImGuiKey_KeyPadEnter,
    ImGuiKey_A,         // for text edit CTRL+A: select all
    ImGuiKey_C,         // for text edit CTRL+C: copy
    ImGuiKey_V,         // for text edit CTRL+V: paste
    ImGuiKey_X,         // for text edit CTRL+X: cut
    ImGuiKey_Y,         // for text edit CTRL+Y: redo
    ImGuiKey_Z,         // for text edit CTRL+Z: undo
    ImGuiKey_COUNT
};

// To test io.KeyMods (which is a combination of individual flags)
enum ImGuiKeyModFlags_
{
    ImGuiKeyModFlags_None       = 0,
    ImGuiKeyModFlags_Ctrl       = 1 << 0,
    ImGuiKeyModFlags_Shift      = 1 << 1,
    ImGuiKeyModFlags_Alt        = 1 << 2,
    ImGuiKeyModFlags_Super      = 1 << 3
};

//- enum
enum ImGuiNavInput_
{
    // Gamepad Mapping
    ImGuiNavInput_Activate,      // activate / open / toggle / tweak value       (e.g. Cross  (PS4), A (Xbox), A (Switch))
    ImGuiNavInput_Cancel,        // cancel / close / exit                        (e.g. Circle (PS4), B (Xbox), B (Switch))
    ImGuiNavInput_Input,         // text input / on-screen keyboard              (e.g. Square (PS4), X (Xbox), Y (Switch))
    ImGuiNavInput_Menu,          // tap: toggle menu / hold: focus, move, resize (e.g. Option (PS4), Start (Xbox), + (Switch))
    ImGuiNavInput_DpadLeft,      // move left                                    (e.g. D-Pad Left)
    ImGuiNavInput_DpadRight,     // move right                                   (e.g. D-Pad Right)
    ImGuiNavInput_DpadUp,        // move up                                      (e.g. D-Pad Up)
    ImGuiNavInput_DpadDown,      // move down                                    (e.g. D-Pad Down)
    ImGuiNavInput_LStickLeft,    // scroll / move window (w/Menu)                (e.g. Left Analog Stick Left)
    ImGuiNavInput_LStickRight,   // scroll / move window (w/Menu)                (e.g. Left Analog Stick Right)
    ImGuiNavInput_LStickUp,      // scroll / move window (w/Menu)                (e.g. Left Analog Stick Up)
    ImGuiNavInput_LStickDown,    // scroll / move window (w/Menu)                (e.g. Left Analog Stick Down)
    ImGuiNavInput_FocusPrev,     // next window (w/L1)                           (e.g. L1 or L bumper)
    ImGuiNavInput_FocusNext,     // prev window (w/R1)                           (e.g. R1 or R bumper)
    ImGuiNavInput_TweakSlow,     // slower tweaks                                (e.g. L2 or L trigger)
    ImGuiNavInput_TweakFast,     // faster tweaks                                (e.g. R2 or R trigger)

    // [Internal] For internal use by ImGui
    ImGuiNavInput_KeyMenu_,      // toggle menu
    ImGuiNavInput_KeyLeft_,      // move left
    ImGuiNavInput_KeyRight_,     // move right
    ImGuiNavInput_KeyUp_,        // move up
    ImGuiNavInput_KeyDown_,      // move down
    ImGuiNavInput_COUNT,
    ImGuiNavInput_InternalStart_ = ImGuiNavInput_KeyMenu_
};

// Flags for ImGui::NewFrame()
enum ImGuiConfigFlags_
{
    ImGuiConfigFlags_None                   = 0,
    ImGuiConfigFlags_NavEnableKeyboard      = 1 << 0,   // Master keyboard navigation enable flag. NewFrame() will automatically fill io.NavInputs[] based on io.KeysDown[].
    ImGuiConfigFlags_NavEnableGamepad       = 1 << 1,   // Master gamepad navigation enable flag. This is mostly to instruct backend to fill io.NavInputs[]. Backend also needs to set ImGuiBackendFlags_HasGamepad.
    ImGuiConfigFlags_NavEnableSetMousePos   = 1 << 2,   // Navigate with keyboard: set mouse position hardware cursor to focused item (used by some backends).
    ImGuiConfigFlags_NavNoCaptureKeyboard   = 1 << 3,   // Navigate with keyboard: consume keyboard inputs (io.WantCaptureKeyboard will be set).
    ImGuiConfigFlags_NoMouse                = 1 << 4,   // Master mouse disable flag. Private backend rendering for multi-viewport nests may still need mouse initialisation.
    ImGuiConfigFlags_NoMouseCursorChange    = 1 << 5,   // Request backend to not alter mouse cursor shape and visibility. Use if the backend cursor changes are interfering with yours and you don't want to use SetMouseCursor() to change mouse cursor. You may want to honor requests from imgui by reading GetMouseCursor() yourself instead.

    // User storage data via io.BackendFlags
    ImGuiConfigFlags_IsSRGB                 = 1 << 20,  // Application is SRGB-aware.
    ImGuiConfigFlags_IsTouchScreen          = 1 << 21   // Application is using a touch screen instead of a mouse.
};

// Backend capabilities flags stored in io.BackendFlags. Set by imgui_impl_xxx files.
enum ImGuiBackendFlags_
{
    ImGuiBackendFlags_None                  = 0,
    ImGuiBackendFlags_HasGamepad            = 1 << 0,   // Backend Platform supports gamepad and currently has one connected.
    ImGuiBackendFlags_HasMouseCursors       = 1 << 1,   // Backend Platform supports honoring GetMouseCursor() value to change the OS cursor shape.
    ImGuiBackendFlags_HasSetMousePos        = 1 << 2,   // Backend Platform supports io.WantSetMousePos requests to reposition the OS mouse position (only used if ImGuiConfigFlags_NavEnableSetMousePos is set).
    ImGuiBackendFlags_RendererHasVtxOffset  = 1 << 3    // Backend Renderer supports ImDrawCmd::VtxOffset. This enables output of large meshes (64K+ vertices) while still using 16-bit indices.
};

// Enumeration for PushStyleColor() / PopStyleColor()
enum ImGuiCol_
{
    ImGuiCol_Text,
    ImGuiCol_TextDisabled,
    ImGuiCol_WindowBg,              // Background of normal windows
    ImGuiCol_ChildBg,               // Background of child windows
    ImGuiCol_PopupBg,               // Background of popups, menus, tooltips windows
    ImGuiCol_Border,
    ImGuiCol_BorderShadow,
    ImGuiCol_FrameBg,               // Background of checkbox, radio button, plot, slider, text input
    ImGuiCol_FrameBgHovered,
    ImGuiCol_FrameBgActive,
    ImGuiCol_TitleBg,
    ImGuiCol_TitleBgActive,
    ImGuiCol_TitleBgCollapsed,
    ImGuiCol_MenuBarBg,
    ImGuiCol_ScrollbarBg,
    ImGuiCol_ScrollbarGrip,
    ImGuiCol_ScrollbarGripHovered,
    ImGuiCol_ScrollbarGripActive,
    ImGuiCol_CheckMark,
    ImGuiCol_SliderGrip,
    ImGuiCol_SliderGripActive,
    ImGuiCol_Button,
    ImGuiCol_ButtonHovered,
    ImGuiCol_ButtonActive,
    ImGuiCol_Header,
    ImGuiCol_HeaderHovered,
    ImGuiCol_HeaderActive,
    ImGuiCol_Separator,
    ImGuiCol_SeparatorHovered,
    ImGuiCol_SeparatorActive,
    ImGuiCol_ResizeGrip,
    ImGuiCol_ResizeGripHovered,
    ImGuiCol_ResizeGripActive,
    ImGuiCol_Tab,
    ImGuiCol_TabHovered,
    ImGuiCol_TabActive,
    ImGuiCol_TabUnfocused,
    ImGuiCol_TabUnfocusedActive,
    ImGuiCol_PlotLines,
    ImGuiCol_PlotLinesHovered,
    ImGuiCol_PlotHistogram,
    ImGuiCol_PlotHistogramHovered,
    ImGuiCol_TableBorderStrong,     // Table outer and header borders
    ImGuiCol_TableBorderLight,      // Table inner borders
    ImGuiCol_TableHeaderBg,         // Table header background
    ImGuiCol_TableRowBg,            // Table row background (even rows)
    ImGuiCol_TableRowBgAlt,         // Table row background (odd rows)
    ImGuiCol_TextSelectedBg,
    ImGuiCol_DragDropTarget,
    ImGuiCol_NavHighlight,          // Gamepad/keyboard: navigation highlight color
    ImGuiCol_NavWindowingHighlight, // Gamepad/keyboard: navigation windowing highlight color
    ImGuiCol_NavWindowingDimBg,     // Gamepad/keyboard: darker background color when frame is hovered by navigation
    ImGuiCol_ModalWindowDimBg,      // Darken entire screen behind a modal window, when one is active
    ImGuiCol_COUNT
};

// Enumeration for PushStyleVar() / PopStyleVar() to temporarily modify the ImGuiStyle structure.
// NB: the enum only refers to fields of ImGuiStyle which makes sense to be pushed/popped inside UI code.
// During initialization or between frames, feel free to just poke into ImGuiStyle directly.
// NB: if you create a new ImGuiStyleVar constant, you need to add a corresponding case in PushStyleVar() and PopStyleVar()!
// NB: if you want to change the default value of a style variable, you can access the ImGuiStyle structure instances from the IO object.
enum ImGuiStyleVar_
{
    // Enum name --------------------- // Member in ImGuiStyle structure (see ImGuiStyle for descriptions)
    ImGuiStyleVar_Alpha,               // float     Alpha
    ImGuiStyleVar_WindowPadding,       // ImVec2    WindowPadding
    ImGuiStyleVar_WindowRounding,      // float     WindowRounding
    ImGuiStyleVar_WindowBorderSize,    // float     WindowBorderSize
    ImGuiStyleVar_WindowMinSize,       // ImVec2    WindowMinSize
    ImGuiStyleVar_WindowTitleAlign,    // ImVec2    WindowTitleAlign
    ImGuiStyleVar_ChildRounding,       // float     ChildRounding
    ImGuiStyleVar_ChildBorderSize,     // float     ChildBorderSize
    ImGuiStyleVar_PopupRounding,       // float     PopupRounding
    ImGuiStyleVar_PopupBorderSize,     // float     PopupBorderSize
    ImGuiStyleVar_FramePadding,        // ImVec2    FramePadding
    ImGuiStyleVar_FrameRounding,       // float     FrameRounding
    ImGuiStyleVar_FrameBorderSize,     // float     FrameBorderSize
    ImGuiStyleVar_ItemSpacing,         // ImVec2    ItemSpacing
    ImGuiStyleVar_ItemInnerSpacing,    // ImVec2    ItemInnerSpacing
    ImGuiStyleVar_IndentSpacing,       // float     IndentSpacing
    ImGuiStyleVar_CellPadding,         // ImVec2    CellPadding
    ImGuiStyleVar_ScrollbarSize,       // float     ScrollbarSize
    ImGuiStyleVar_ScrollbarRounding,   // float     ScrollbarRounding
    ImGuiStyleVar_GrabMinSize,         // float     GrabMinSize
    ImGuiStyleVar_GrabRounding,        // float     GrabRounding
    ImGuiStyleVar_TabRounding,         // float     TabRounding
    ImGuiStyleVar_ButtonTextAlign,     // ImVec2    ButtonTextAlign
    ImGuiStyleVar_SelectableTextAlign, // ImVec2    SelectableTextAlign
    ImGuiStyleVar_COUNT
};

// Flags for ColorEdit3() / ColorEdit4() / ColorPicker3() / ColorPicker4() / ColorButton()
enum ImGuiColorEditFlags_
{
    ImGuiColorEditFlags_None            = 0,
    ImGuiColorEditFlags_NoAlpha         = 1 << 1,   //              // ColorEdit, ColorPicker, ColorButton: ignore Alpha component (read 3 components from the input pointer).
    ImGuiColorEditFlags_NoPicker        = 1 << 2,   //              // ColorEdit: disable picker when clicking on color square.
    ImGuiColorEditFlags_NoOptions       = 1 << 3,   //              // ColorEdit: disable toggling options menu when right-clicking on inputs/small preview.
    ImGuiColorEditFlags_NoSmallPreview  = 1 << 4,   //              // ColorEdit, ColorPicker: disable color square preview next to the inputs.
    ImGuiColorEditFlags_NoInputs        = 1 << 5,   //              // ColorEdit, ColorPicker: disable inputs sliders/text widgets (e.g. to show only the small preview color square).
    ImGuiColorEditFlags_NoTooltip       = 1 << 6,   //              // ColorEdit, ColorPicker, ColorButton: disable tooltip when hovering the preview.
    ImGuiColorEditFlags_NoLabel         = 1 << 7,   //              // ColorEdit, ColorPicker: disable display of inline text label (the label is still forwarded to the tooltip and picker).
    ImGuiColorEditFlags_NoSidePreview   = 1 << 8,   //              // ColorPicker: disable bigger color preview on right side of the picker, beside the hue bar.
    ImGuiColorEditFlags_NoDragDrop      = 1 << 9,   //              // ColorEdit: disable drag and drop target. ColorButton: disable drag and drop source.
    ImGuiColorEditFlags_AlphaBar        = 1 << 16,  //              // ColorPicker: show vertical alpha bar/gradient in picker.
    ImGuiColorEditFlags_AlphaPreview    = 1 << 17,  //              // ColorEdit, ColorPicker, ColorButton: display preview as a transparent color over a checkerboard, instead of opaque.
    ImGuiColorEditFlags_AlphaPreviewHalf= 1 << 18,  //              // ColorEdit, ColorPicker, ColorButton: display half opaque / half checkerboard, instead of opaque.
    ImGuiColorEditFlags_HDR             = 1 << 19,  //              // (WIP) ColorEdit: Currently only disable 0.0f..1.0f limits in RGBA edition (note: you probably want to use ImGuiColorEditFlags_Float flag as well).
    ImGuiColorEditFlags_DisplayRGB      = 1 << 20,  // [Inputs]     // ColorEdit: override display mode to RGB. ColorPicker: select RGB display mode default.
    ImGuiColorEditFlags_DisplayHSV      = 1 << 21,  // [Inputs]     // ColorEdit: override display mode to HSV. ColorPicker: select HSV display mode default.
    ImGuiColorEditFlags_DisplayHex      = 1 << 22,  // [Inputs]     // ColorEdit: override display mode to Hex. ColorPicker: select Hex display mode default.
    ImGuiColorEditFlags_Uint8           = 1 << 23,  // [DataType]   // ColorEdit, ColorPicker, ColorButton: _display_ values formatted as 0..255.
    ImGuiColorEditFlags_Float           = 1 << 24,  // [DataType]   // ColorEdit, ColorPicker, ColorButton: _display_ values formatted as 0.0f..1.0f floats instead of 0..255 integers. No round-trip of value via integers.
    ImGuiColorEditFlags_PickerHueBar    = 1 << 25,  // [Picker]     // ColorPicker: bar for Hue, rectangle for Sat/Value.
    ImGuiColorEditFlags_PickerHueWheel  = 1 << 26,  // [Picker]     // ColorPicker: wheel for Hue, triangle for Sat/Value.
    ImGuiColorEditFlags_InputRGB        = 1 << 27,  // [Input]      // ColorEdit, ColorPicker: input and output data in RGB format.
    ImGuiColorEditFlags_InputHSV        = 1 << 28,  // [Input]      // ColorEdit, ColorPicker: input and output data in HSV format.

    // Defaults Options
    ImGuiColorEditFlags__OptionsDefault = ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_PickerHueBar,

    // Masks
    ImGuiColorEditFlags__DisplayMask    = ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_DisplayHSV | ImGuiColorEditFlags_DisplayHex,
    ImGuiColorEditFlags__DataTypeMask   = ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_Float,
    ImGuiColorEditFlags__PickerMask     = ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_PickerHueBar,
    ImGuiColorEditFlags__InputMask      = ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_InputHSV
};

//- enum
enum ImGuiMouseButton_
{
    ImGuiMouseButton_Left = 0,
    ImGuiMouseButton_Right = 1,
    ImGuiMouseButton_Middle = 2,
    ImGuiMouseButton_COUNT = 5
};

// Enumeration for GetMouseCursor()
// User code may request backend to display given cursor by calling SetMouseCursor(), which is why we have some cursors that are marked unused here
enum ImGuiMouseCursor_
{
    ImGuiMouseCursor_None = -1,
    ImGuiMouseCursor_Arrow = 0,
    ImGuiMouseCursor_TextInput,         // When hovering over InputText, etc.
    ImGuiMouseCursor_ResizeAll,         // (Unused by imgui functions)
    ImGuiMouseCursor_ResizeNS,          // When hovering over an horizontal border
    ImGuiMouseCursor_ResizeEW,          // When hovering over a vertical border or a column
    ImGuiMouseCursor_ResizeNESW,        // When hovering over the bottom-left corner of a window
    ImGuiMouseCursor_ResizeNWSE,        // When hovering over the bottom-right corner of a window
    ImGuiMouseCursor_Hand,              // (Unused by imgui functions. Use for e.g. hyperlinks)
    ImGuiMouseCursor_NotAllowed,        // (Unused by imgui functions. Use for e.g. dragging over an invalid drop target)
    ImGuiMouseCursor_COUNT
};

// Condition for SetWindow***(), SetNextWindow***(), SetNextTreeNode***() functions
// All those functions treat 0 as a synonym to ImGuiCond_Always.
enum ImGuiCond_
{
    ImGuiCond_None          = 0,        // No condition (always set the variable), same as ImGuiCond_Always
    ImGuiCond_Always        = 1 << 0,   // Set the variable
    ImGuiCond_Once          = 1 << 1,   // Set the variable once per runtime session (only the first call with succeed)
    ImGuiCond_FirstUseEver  = 1 << 2,   // Set the variable if the window has no saved data (if doesn't exist in the .ini file)
    ImGuiCond_Appearing     = 1 << 3    // Set the variable if the window is appearing after being hidden/inactive (or the first time)
};

//-----------------------------------------------------------------------------
// ImGuiStyle
// You may modify the ImGui::GetStyle() main instance during initialization and before NewFrame().
// During the frame, use ImGui::PushStyleVar(ImGuiStyleVar_XXXX, value) to vary the style on a per-widget basis.
//-----------------------------------------------------------------------------
struct ImGuiStyle
{
    float       Alpha;                      // Global alpha applies to everything in ImGui.
    ImVec2      WindowPadding;              // Padding within a window
    float       WindowRounding;             // Radius of window corners rounding. Set to 0.0f to have rectangular windows.
    float       WindowBorderSize;           // Thickness of border around windows. Generally set to 1.0f or 0.0f. (Other values are not well tested and more CPU/GPU costly).
    ImVec2      WindowMinSize;              // Minimum window size. This is a global setting. If you want to constraint individual windows, use SetNextWindowSizeConstraints().
    ImVec2      WindowTitleAlign;           // Alignment for title bar text. Defaults to (0.0f,0.5f) for left-aligned,vertically centered.
    float       ChildRounding;              // Radius of child window corners rounding. Set to 0.0f to have rectangular child windows.
    float       ChildBorderSize;            // Thickness of border around child windows. Generally set to 1.0f or 0.0f. (Other values are not well tested and more CPU/GPU costly).
    float       PopupRounding;              // Radius of popup window corners rounding. (Note that tooltip windows use WindowRounding)
    float       PopupBorderSize;            // Thickness of border around popup/tooltip windows. Generally set to 1.0f or 0.0f. (Other values are not well tested and more CPU/GPU costly).
    ImVec2      FramePadding;               // Padding within a framed rectangle (used by most widgets)
    float       FrameRounding;              // Radius of frame corners rounding. Set to 0.0f to have rectangular frames (used by most widgets).
    float       FrameBorderSize;            // Thickness of border around frames. Generally set to 1.0f or 0.0f. (Other values are not well tested and more CPU/GPU costly).
    ImVec2      ItemSpacing;                // Horizontal and vertical spacing between widgets/lines
    ImVec2      ItemInnerSpacing;           // Horizontal and vertical spacing between within elements of a composed widget (e.g. a slider and its label)
    ImVec2      CellPadding;                // Padding within a table cell
    float       IndentSpacing;              // Indentation width
    float       ScrollbarSize;              // Scrollbar width
    float       ScrollbarRounding;          // Radius of grab corners rounding for scrollbar
    float       GrabMinSize;                // Minimum width/height of a grab box for slider/scrollbar
    float       GrabRounding;               // Radius of grabs corners rounding. Set to 0.0f to have rectangular slider grabs.
    float       TabRounding;                // Radius of upper corners of a tab. Set to 0.0f to have rectangular tabs.
    ImVec2      ButtonTextAlign;            // Alignment of button text when button is larger than text. Defaults to (0.5, 0.5) (centered)
    ImVec2      SelectableTextAlign;        // Alignment of selectable text when selectable is larger than text. Defaults to (0.0, 0.0) (top-left aligned).
    ImVec4      Colors[ImGuiCol_COUNT];

    IMGUI_API ImGuiStyle();
};

//-----------------------------------------------------------------------------
// ImGuiIO
// Communicate most settings and inputs/outputs to Dear ImGui using this structure.
// Access via ImGui::GetIO().
// Read 'Programmer guide' section in .cpp file for general usage.
//-----------------------------------------------------------------------------
struct ImGuiIO
{
    //------------------------------------------------------------------
    // Configuration (fill once)
    //------------------------------------------------------------------

    ImGuiConfigFlags ConfigFlags;           // = 0              // See ImGuiConfigFlags_ enum. Set by user/application. Gamepad/keyboard navigation options, etc.
    ImGuiBackendFlags BackendFlags;         // = 0              // See ImGuiBackendFlags_ enum. Set by backend (imgui_impl_xxx files or custom backend) to communicate features supported by the backend.
    ImVec2        DisplaySize;              // <unset>          // Main display size, in pixels (generally == GetMainViewport()->Size)
    float         DeltaTime;                // = 1.0f/60.0f     // Time elapsed since last frame, in seconds.
    float         IniSavingRate;            // = 5.0f           // Minimum time between saving positions/sizes to .ini file, in seconds.
    const char*   IniFilename;              // = "imgui.ini"    // Path to .ini file. Set NULL to disable automatic .ini loading/saving, if e.g. you want to manually load/save from memory.
    const char*   LogFilename;              // = "imgui_log.txt"// Path to .log file (default parameter to ImGui::LogToFile).
    float         MouseDoubleClickTime;     // = 0.30f          // Time for a double-click, in seconds.
    float         MouseDoubleClickMaxDist;  // = 6.0f           // Distance threshold to stay in to validate a double-click, in pixels.
    float         MouseDragThreshold;       // = 6.0f           // Distance threshold before considering we are dragging
    int           KeyMap[ImGuiKey_COUNT];   // <unset>          // Map of indices into the KeysDown[512] entries array which represent your "native" keyboard state.
    float         KeyRepeatDelay;           // = 0.250f         // When holding a key/button, time before it starts repeating, in seconds (for buttons in Repeat mode, etc.).
    float         KeyRepeatRate;            // = 0.050f         // When holding a key/button, rate at which it repeats, in seconds.
    void*         UserData;                 // = NULL           // Store your own user data for retrieval by callbacks.

    ImFontAtlas*  Fonts;                    // <auto>           // Font atlas: load, rasterize and pack one or more fonts into a single texture.
    float         FontGlobalScale;          // = 1.0f           // Global scale all fonts
    bool          FontAllowUserScaling;     // = false          // Allow user scaling text of individual window with CTRL+Wheel.
    ImFont*       FontDefault;              // = NULL           // Font to use on NewFrame(). Use NULL to uses Fonts->Fonts[0].
    ImVec2        DisplayFramebufferScale;  // = (1, 1)         // For retina display or other situations where window coordinates are different from framebuffer coordinates. This generally ends up in ImDrawData::FramebufferScale.

    //------------------------------------------------------------------
    // Miscellaneous options
    //------------------------------------------------------------------

    bool          MouseDrawCursor;          // = false          // Request ImGui to draw a mouse cursor for you (if you are on a platform without a mouse cursor).
    bool          ConfigMacOSXBehaviors;    // = defined(__APPLE__) // OS X style: Text editing cursor movement using Alt instead of Ctrl, Shortcuts using Cmd/Super instead of Ctrl, Line/Text Start and End using Cmd+Arrows instead of Home/End, Double click selects by word instead of selecting whole text, Multi-selection in lists uses Cmd/Super instead of Ctrl.
    bool          ConfigInputTextCursorBlink; // = true         // Set to false to disable blinking cursor, for users who consider it distracting.
    bool          ConfigWindowsResizeFromEdges; // = true       // Enable resizing of windows from their edges and from the lower-left corner.
    bool          ConfigWindowsMoveFromTitleBarOnly; // = false // [BETA] Set to true to only allow moving windows when clicking on their title bar. Does not apply to windows without a title bar.
    float         ConfigWindowsMemoryCompactTimer; // = 60.0f   // Timer (in seconds) to free transient windows memory buffers when unused. Set to -1.0f to disable.

    //------------------------------------------------------------------
    // Platform Functions
    // (the imgui_impl_xxxx files are tasked with writing to these fields)
    //------------------------------------------------------------------

    const char* (*GetClipboardTextFn)(void* user_data);
    void        (*SetClipboardTextFn)(void* user_data, const char* text);
    void*       ClipboardUserData;

    //------------------------------------------------------------------
    // Input - Fill before calling NewFrame()
    //------------------------------------------------------------------

    ImVec2        MousePos;                   // Mouse position, in pixels. Set to ImVec2(-FLT_MAX, -FLT_MAX) if mouse is unavailable (on another screen, etc.)
    bool          MouseDown[5];               // Mouse buttons: 0=left, 1=right, 2=middle + extras (ImGuiMouseButton_COUNT == 5). Dear ImGui mostly uses left and right buttons. Others buttons allows us to track if the mouse is being used by five-buttons mice.
    float         MouseWheel;                 // Mouse wheel Vertical: 1 unit scrolls about 5 lines text.
    float         MouseWheelH;                // Mouse wheel Horizontal. Most users don't have a mouse with an horizontal wheel, may not be filled by all backends.
    bool          KeyCtrl;                    // Keyboard modifier down: Control
    bool          KeyShift;                   // Keyboard modifier down: Shift
    bool          KeyAlt;                     // Keyboard modifier down: Alt
    bool          KeySuper;                   // Keyboard modifier down: Cmd/Super/Windows
    bool          KeysDown[512];              // Keyboard keys that are pressed (ideally left in the "native" order your engine has access to)
    float         NavInputs[ImGuiNavInput_COUNT]; // Gamepad inputs. Cleared back to zero by NewFrame(). Keyboard keys will be auto-mapped and written here by NewFrame().

    // Functions
    IMGUI_API void  AddInputCharacter(unsigned int c);                        // Add new character into InputCharacters[]
    IMGUI_API void  AddInputCharacterUTF16(ImWchar16 c);                      // Add new character into InputCharacters[] from an UTF-16 source
    IMGUI_API void  AddInputCharactersUTF8(const char* str);                  // Add new characters into InputCharacters[] from an UTF-8 string
    IMGUI_API void  ClearInputCharacters();                                   // Clear the text input buffer manually

    //------------------------------------------------------------------
    // Output - Retrieve after calling NewFrame()
    //------------------------------------------------------------------

    bool          WantCaptureMouse;           // Set when Dear ImGui will use mouse inputs, in this case do not dispatch them to your main game/application (either way, always pass on mouse inputs to imgui). (e.g. when hovering over windows, see ImGuiConfigFlags_NoMouse)
    bool          WantCaptureKeyboard;        // Set when Dear ImGui will use keyboard inputs, in this case do not dispatch them to your main game/application (either way, always pass keyboard inputs to imgui). (e.g. when typing in a text input, see ImGuiConfigFlags_NoKeyboard)
    bool          WantTextInput;              // Mobile users: when set, you may display an on-screen keyboard. This is set by Dear ImGui when it wants textual keyboard input to happen (e.g. when a InputText widget is active).
    bool          WantSetMousePos;            // Mouse position has been altered, backend should reposition mouse on next frame. Rarely used! Set only when ImGuiConfigFlags_NavEnableSetMousePos flag is set.
    bool          WantSaveIniSettings;        // When manual .ini saving is active (io.IniFilename == NULL), this will be set to notify your application that you can call SaveIniSettingsToMemory() and save yourself. IMPORTANT: You need to clear io.WantSaveIniSettings yourself.
    int           Framerate;                  // Application framerate estimation, in frame per second. Solely for convenience. Rolling average estimation based on io.DeltaTime over 120 frames.
    int           MetricsRenderVertices;      // Vertices output during last call to Render()
    int           MetricsRenderIndices;       // Indices output during last call to Render() = number of triangles * 3
    int           MetricsRenderWindows;       // Number of visible windows
    int           MetricsActiveWindows;       // Number of active windows
    int           MetricsActiveAllocations;   // Number of active allocations, updated by MemAlloc/MemFree based on current context. May be off if you have multiple contexts running.
    ImVec2        MouseDelta;                 // Mouse delta. Note that this is zero if either current or previous position are invalid (-FLT_MAX,-FLT_MAX), so a disappearing mouse won't cause a huge delta.

    //------------------------------------------------------------------
    // [Internal] ImGui will maintain those fields. Forward compatibility not guaranteed.
    //------------------------------------------------------------------

    ImGuiKeyModFlags KeyMods;                   // Key mods flags (any of ImGuiKeyModFlags_Ctrl/Shift/Alt/Super flags).
    ImVec2        MousePosPrev;               // Previous mouse position (note that MouseDelta is not necessary == MousePos-MousePosPrev, in case either position is invalid)
    ImVec2        MouseClickedPos[5];         // Position at time of clicking
    double        MouseClickedTime[5];        // Time of last click (used to figure out double-click)
    bool          MouseClicked[5];            // Mouse button went from !Down to Down
    bool          MouseDoubleClicked[5];      // Has mouse button been double-clicked?
    bool          MouseReleased[5];           // Mouse button went from Down to !Down
    bool          MouseDownOwned[5];          // Track if button was clicked inside a window. We don't request mouse capture from the application if click started outside hovered window.
    float         MouseDownDuration[5];       // Duration the mouse button has been held for.
    float         MouseDownDurationPrev[5];   // Previous time the mouse button has been held for.
    ImVec2        MouseDragMaxDistanceAbs[5]; // Maximum distance, absolute, on each axis, of how much mouse has been dragged from the clicking point
    float         MouseDragMaxDistanceSqr[5]; // Squared maximum distance of how much mouse has been dragged from the clicking point
    float         KeysDownDuration[512];      // Duration the keyboard key has been held for
    float         KeysDownDurationPrev[512];  // Previous duration the key has been held for
    float         NavInputsDownDuration[ImGuiNavInput_COUNT];
    float         NavInputsDownDurationPrev[ImGuiNavInput_COUNT];
    ImWchar16*    InputCharacters;            // Text input buffer, cleared each frame.
    int           InputCharactersCount;       // Number of characters in InputCharacters.

    IMGUI_API   ImGuiIO();
};

//-----------------------------------------------------------------------------
// Misc data structures
//-----------------------------------------------------------------------------

// A single vertex (20 bytes by default, override layout with IMGUI_OVERRIDE_DRAW_VERT_STRUCT_LAYOUT)
struct ImDrawVert
{
    ImVec2  pos;
    ImVec2  uv;
    ImU32   col;
};

// A single draw command
struct ImDrawCmd
{
    unsigned int    ElemCount;              // Number of indices (multiple of 3) to be rendered as triangles. Vertices are stored in the callee ImDrawList's vtx_buffer[] array, indices in idx_buffer[].
    ImVec4          ClipRect;               // Clipping rectangle (x1, y1, x2, y2)
    ImTextureID     TextureId;              // User-provided texture ID. Set by user in ImfontAtlas::SetTexID() for fonts or passed to Image*() functions. Ignore if never using images or multiple textures.
    unsigned int    VtxOffset;              // For retina display or other situations where window coordinates are different from framebuffer coordinates. This generally ends up in ImDrawData::FramebufferScale.
    unsigned int    IdxOffset;              //
    void*           UserCallback;           // If != NULL, call the function instead of rendering the vertices. clip_rect and texture_id will be set normally.
    void*           UserCallbackData;       // The data for the user callback.

    ImDrawCmd() { ElemCount = 0; ClipRect.x = ClipRect.y = ClipRect.z = ClipRect.w = 0.0f; TextureId = (ImTextureID)NULL; VtxOffset = IdxOffset = 0; UserCallback = NULL; UserCallbackData = NULL; }
};

// For rendering. Flags for ImDrawList.
enum ImDrawFlags_
{
    ImDrawFlags_None                        = 0,
    ImDrawFlags_Closed                      = 1 << 0, // PathStroke(), AddPolyline(): specify that shape should be closed (Important: this is always == 1 for legacy reason)
    ImDrawFlags_RoundCornersTopLeft         = 1 << 4, // AddRect(), AddRectFilled(), PathRect(): enable rounding top-left corner.
    ImDrawFlags_RoundCornersTopRight        = 1 << 5, // AddRect(), AddRectFilled(), PathRect(): enable rounding top-right corner.
    ImDrawFlags_RoundCornersBottomLeft      = 1 << 6, // AddRect(), AddRectFilled(), PathRect(): enable rounding bottom-left corner.
    ImDrawFlags_RoundCornersBottomRight     = 1 << 7, // AddRect(), AddRectFilled(), PathRect(): enable rounding bottom-right corner.
    ImDrawFlags_RoundCornersNone            = 1 << 8, // AddRect(), AddRectFilled(), PathRect(): disable rounding on all corners.
    ImDrawFlags_RoundCornersTop             = ImDrawFlags_RoundCornersTopLeft | ImDrawFlags_RoundCornersTopRight,
    ImDrawFlags_RoundCornersBottom          = ImDrawFlags_RoundCornersBottomLeft | ImDrawFlags_RoundCornersBottomRight,
    ImDrawFlags_RoundCornersLeft            = ImDrawFlags_RoundCornersTopLeft | ImDrawFlags_RoundCornersBottomLeft,
    ImDrawFlags_RoundCornersRight           = ImDrawFlags_RoundCornersTopRight | ImDrawFlags_RoundCornersBottomRight,
    ImDrawFlags_RoundCornersAll             = ImDrawFlags_RoundCornersTopLeft | ImDrawFlags_RoundCornersTopRight | ImDrawFlags_RoundCornersBottomLeft | ImDrawFlags_RoundCornersBottomRight,
    ImDrawFlags_RoundCornersDefault_        = ImDrawFlags_RoundCornersAll, // Default to rounding all corners if ImDrawCornerFlags_RoundCornersNone is not set.
    ImDrawFlags_RoundCornersMask_           = ImDrawFlags_RoundCornersAll | ImDrawFlags_RoundCornersNone
};

// Draw channels are used by the ImDrawListSplitter to split drawing calls into different layers.
// For general help on what this is, please refer to the FAQ in imgui.cpp.
struct ImDrawChannel
{
    ImVector<ImDrawCmd>     _CmdBuffer;
    ImVector<ImWchar>       _IdxBuffer;
};

// ImDrawListSplitter is a helper for splitting a draw list into different layers.
// For general help on what this is, please refer to the FAQ in imgui.cpp.
struct ImDrawListSplitter
{
    int                     _Current;
    int                     _Count;
    ImVector<ImDrawChannel> _Channels;

    IMGUI_API ImDrawListSplitter()  { _Current = 0; _Count = 1; }
    IMGUI_API ~ImDrawListSplitter() { Clear(); }
    IMGUI_API void Clear() { _Current = 0; _Count = 1; _Channels.clear(); }
    IMGUI_API void ClearFreeMemory() { _Current = 0; _Count = 1; _Channels.clear_destruct(); }
    IMGUI_API void Split(ImDrawList* draw_list, int count);
    IMGUI_API void Merge(ImDrawList* draw_list);
    IMGUI_API void SetCurrentChannel(ImDrawList* draw_list, int channel_idx);
};

// Draw command list
// This is the low-level list of polygons that ImGui functions are filling. At the end of the frame,
// all command lists are passed to your render function for rendering.
// Each ImGui window contains its own ImDrawList. You can use ImGui::GetWindowDrawList() to
// access the current window draw list and draw custom primitives.
// You can interleave normal ImGui calls and adding primitives to the current draw list.
// All positions are in screen coordinates.
struct ImDrawList
{
    // This is what you have to render
    ImVector<ImDrawCmd>     CmdBuffer;          // Commands. Typically 1 command = 1 draw call.
    ImVector<ImWchar>       IdxBuffer;          // Index buffer. Each command consume ImDrawCmd::ElemCount of those
    ImVector<ImDrawVert>    VtxBuffer;          // Vertex buffer.
    ImDrawFlags             Flags;              // Flags, you may poke into these to adjust anti-aliasing settings per-primitive.

    // [Internal, used while building lists]
    const ImDrawListSharedData* _Data;          // Pointer to shared data (for font, shader values, etc.)
    const char*             _OwnerName;         // Pointer to owner window's name for debugging
    unsigned int            _VtxCurrentOffset;  // [Internal] For retina display or other situations where window coordinates are different from framebuffer coordinates. This correctly translates to VtxCurrentOffset in the draw command.
    unsigned int            _VtxCurrentIdx;     // [Internal] point to current vertex in buffer
    ImDrawVert*             _VtxWritePtr;       // [Internal] point to current vertex in buffer
    ImWchar*                _IdxWritePtr;       // [Internal] point to current index in buffer
    ImVector<ImVec4>        _ClipRectStack;     // [Internal]
    ImVector<ImTextureID>   _TextureIdStack;    // [Internal]
    ImVector<ImVec2>        _Path;              // [Internal] current path in screen space
    int                     _ChannelsCurrent;   // [Internal] current channel number (0)
    int                     _ChannelsCount;     // [Internal] number of active channels (1+)
    ImVector<ImDrawChannel> _Channels;          // [Internal] draw channels for columns API (not strictly necessary but it simplifies columns implementation)

    IMGUI_API ImDrawList(const ImDrawListSharedData* shared_data) { _Data = shared_data; Flags = ImDrawFlags_RoundCornersDefault_; }
    IMGUI_API ~ImDrawList() { _ClearFreeMemory(); }
    IMGUI_API void  PushClipRect(ImVec2 clip_rect_min, ImVec2 clip_rect_max, bool intersect_with_current_clip_rect = false);  // Render-level scissoring. This is passed down to your render function but not used for CPU-side coarse clipping. Prefer using higher-level ImGui::PushClipRect() to affect logic (hit-testing and widget culling)
    IMGUI_API void  PushClipRectFullScreen();
    IMGUI_API void  PopClipRect();
    IMGUI_API void  PushTextureID(ImTextureID texture_id);
    IMGUI_API void  PopTextureID();
    inline ImVec2   GetClipRectMin() const { const ImVec4& cr = _ClipRectStack.back(); return ImVec2(cr.x, cr.y); }
    inline ImVec2   GetClipRectMax() const { const ImVec4& cr = _ClipRectStack.back(); return ImVec2(cr.z, cr.w); }

    // Primitives
    IMGUI_API void  AddLine(const ImVec2& p1, const ImVec2& p2, ImU32 col, float thickness = 1.0f);
    IMGUI_API void  AddRect(const ImVec2& p_min, const ImVec2& p_max, ImU32 col, float rounding = 0.0f, ImDrawFlags rounding_corners = ImDrawFlags_RoundCornersAll, float thickness = 1.0f);
    IMGUI_API void  AddRectFilled(const ImVec2& p_min, const ImVec2& p_max, ImU32 col, float rounding = 0.0f, ImDrawFlags rounding_corners = ImDrawFlags_RoundCornersAll);
    IMGUI_API void  AddRectFilledMultiColor(const ImVec2& p_min, const ImVec2& p_max, ImU32 col_upr_left, ImU32 col_upr_right, ImU32 col_bot_right, ImU32 col_bot_left);
    IMGUI_API void  AddQuad(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col, float thickness = 1.0f);
    IMGUI_API void  AddQuadFilled(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col);
    IMGUI_API void  AddTriangle(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, ImU32 col, float thickness = 1.0f);
    IMGUI_API void  AddTriangleFilled(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, ImU32 col);
    IMGUI_API void  AddCircle(const ImVec2& center, float radius, ImU32 col, int num_segments = 12, float thickness = 1.0f);
    IMGUI_API void  AddCircleFilled(const ImVec2& center, float radius, ImU32 col, int num_segments = 12);
    IMGUI_API void  AddNgon(const ImVec2& center, float radius, ImU32 col, int num_segments, float thickness = 1.0f);
    IMGUI_API void  AddNgonFilled(const ImVec2& center, float radius, ImU32 col, int num_segments);
    IMGUI_API void  AddText(const ImVec2& pos, ImU32 col, const char* text_begin, const char* text_end = NULL);
    IMGUI_API void  AddText(const ImFont* font, float font_size, const ImVec2& pos, ImU32 col, const char* text_begin, const char* text_end = NULL, float wrap_width = 0.0f, const ImVec4* cpu_fine_clip_rect = NULL);
    IMGUI_API void  AddPolyline(const ImVec2* points, int num_points, ImU32 col, ImDrawFlags flags, float thickness);
    IMGUI_API void  AddConvexPolyFilled(const ImVec2* points, int num_points, ImU32 col);
    IMGUI_API void  AddBezierCubic(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col, float thickness, int num_segments = 0);
    IMGUI_API void  AddBezierQuadratic(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, ImU32 col, float thickness, int num_segments = 0);

    // Image primitives
    IMGUI_API void  AddImage(ImTextureID user_texture_id, const ImVec2& p_min, const ImVec2& p_max, const ImVec2& uv_min = ImVec2(0, 0), const ImVec2& uv_max = ImVec2(1, 1), ImU32 col = 0xFFFFFFFF);
    IMGUI_API void  AddImageQuad(ImTextureID user_texture_id, const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, const ImVec2& uv1 = ImVec2(0, 0), const ImVec2& uv2 = ImVec2(1, 0), const ImVec2& uv3 = ImVec2(1, 1), const ImVec2& uv4 = ImVec2(0, 1), ImU32 col = 0xFFFFFFFF);
    IMGUI_API void  AddImageRounded(ImTextureID user_texture_id, const ImVec2& p_min, const ImVec2& p_max, const ImVec2& uv_min, const ImVec2& uv_max, ImU32 col, float rounding, ImDrawFlags rounding_corners = ImDrawFlags_RoundCornersAll);

    // Stateful path API, add points then finish with PathFillConvex() or PathStroke()
    inline    void  PathClear() { _Path.Size = 0; }
    inline    void  PathLineTo(const ImVec2& pos) { _Path.push_back(pos); }
    inline    void  PathLineToMergeDuplicate(const ImVec2& pos) { if (_Path.Size == 0 || _Path.back().x != pos.x || _Path.back().y != pos.y) _Path.push_back(pos); }
    inline    void  PathFillConvex(ImU32 col) { AddConvexPolyFilled(_Path.Data, _Path.Size, col); PathClear(); }
    inline    void  PathStroke(ImU32 col, ImDrawFlags flags = 0, float thickness = 1.0f) { AddPolyline(_Path.Data, _Path.Size, col, flags, thickness); PathClear(); }
    IMGUI_API void  PathArcTo(const ImVec2& center, float radius, float a_min, float a_max, int num_segments = 10);
    IMGUI_API void  PathArcToFast(const ImVec2& center, float radius, int a_min_of_12, int a_max_of_12);
    IMGUI_API void  PathBezierCubicCurveTo(const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, int num_segments = 0);
    IMGUI_API void  PathBezierQuadraticCurveTo(const ImVec2& p2, const ImVec2& p3, int num_segments = 0);
    IMGUI_API void  PathRect(const ImVec2& rect_min, const ImVec2& rect_max, float rounding = 0.0f, ImDrawFlags rounding_corners = ImDrawFlags_RoundCornersAll);

    // Channels
    IMGUI_API void  ChannelsSplit(int count);
    IMGUI_API void  ChannelsMerge();
    IMGUI_API void  ChannelsSetCurrent(int n);

    // Advanced
    IMGUI_API void  AddCallback(void* callback, void* callback_data); // Your rendering function must check for UserCallback in ImDrawCmd and call the function instead of rendering triangles.
    IMGUI_API void  AddDrawCmd();                                   // This is useful if you need to forcefully create a new draw call (to allow for dependent rendered texture).

    // Internal helpers
    IMGUI_API void  Clear();
    IMGUI_API void  _ClearFreeMemory();
    IMGUI_API void  PrimReserve(int idx_count, int vtx_count);
    IMGUI_API void  PrimRect(const ImVec2& a, const ImVec2& b, ImU32 col); // Axis aligned rectangle (composed of two triangles)
    IMGUI_API void  PrimRectUV(const ImVec2& a, const ImVec2& b, const ImVec2& uv_a, const ImVec2& uv_b, ImU32 col);
    IMGUI_API void  PrimQuadUV(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& d, const ImVec2& uv_a, const ImVec2& uv_b, const ImVec2& uv_c, const ImVec2& uv_d, ImU32 col);
    inline    void  PrimVtx(const ImVec2& pos, const ImVec2& uv, ImU32 col) { _VtxWritePtr->pos = pos; _VtxWritePtr->uv = uv; _VtxWritePtr->col = col; _VtxWritePtr++; _VtxCurrentIdx++; }
    inline    void  PrimWriteVtx(const ImVec2& pos, const ImVec2& uv, ImU32 col) { _VtxWritePtr->pos = pos; _VtxWritePtr->uv = uv; _VtxWritePtr->col = col; _VtxWritePtr++; }
    inline    void  PrimWriteIdx(ImWchar idx) { *_IdxWritePtr = idx; _IdxWritePtr++; }
    inline    void  PrimUnreserve(int idx_count, int vtx_count) { _VtxWritePtr -= vtx_count; _IdxWritePtr -= idx_count; }
    IMGUI_API void  UpdateClipRect();
    IMGUI_API void  UpdateTextureID();
};

// All draw data to render an ImGui frame
struct ImDrawData
{
    bool            Valid;                  // Only valid after Render() is called and before NewFrame() is called.
    ImDrawList**    CmdLists;
    int             CmdListsCount;
    int             TotalIdxCount;          // For convenience, sum of all cmd_lists idx_buffer.Size
    int             TotalVtxCount;          // For convenience, sum of all cmd_lists vtx_buffer.Size
    ImVec2          DisplayPos;             // Upper-left position of the viewport to render (generally (0,0))
    ImVec2          DisplaySize;            // Size of the viewport to render (generally io.DisplaySize)
    ImVec2          FramebufferScale;       // Amount of pixels for each unit of DisplaySize. Based on io.DisplayFramebufferScale. Generally (1,1).

    ImDrawData() { Valid = false; CmdLists = NULL; CmdListsCount = TotalIdxCount = TotalVtxCount = 0; }
    IMGUI_API void  DeIndexAllBuffers();    // For backward compatibility or convenience: convert all buffers from indexed to de-indexed, in case you cannot render indexed. Note: this is slow and most likely a waste of resources. Always prefer using your own indexed rendering function.
    IMGUI_API void  ScaleClipRects(const ImVec2& fb_scale);  // Helper to scale the ClipRect field of each ImDrawCmd. Use if your final output buffer is at a different scale than Dear ImGui expects, or if there is a difference between your window resolution and framebuffer resolution.
};

//-----------------------------------------------------------------------------
// Font API (ImFont, ImFontAtlas)
//-----------------------------------------------------------------------------

struct ImFontConfig
{
    void*           FontData;               //          // TTF/OTF data
    int             FontDataSize;           //          // TTF/OTF data size
    bool            FontDataOwnedByAtlas;   // true     // True if FontData is owned by the atlas (and should be freed by it).
    int             FontNo;                 // 0        // Index of font within TTF/OTF file
    float           SizePixels;             //          // Size in pixels for rasterizer.
    int             OversampleH;            // 3        // Rasterize at higher quality for sub-pixel positioning. We don't use sub-pixel positions on the Y axis.
    int             OversampleV;            // 1        // Rasterize at higher quality for sub-pixel positioning. We don't use sub-pixel positions on the Y axis.
    bool            PixelSnapH;             // false    // Align every glyph to pixel boundary. Useful for fonts which are not anti-aliased.
    ImVec2          GlyphExtraSpacing;      // 0, 0     // Extra spacing (in pixels) between glyphs.
    ImVec2          GlyphOffset;            // 0, 0     // Offset all glyphs from this font input.
    const ImWchar*  GlyphRanges;            // NULL     // Pointer to a user-provided list of Unicode range (2 value per range, values are inclusive, zero-terminated list). THE ARRAY DATA NEEDS TO PERSIST AS LONG AS THE FONT IS ALIVE.
    float           GlyphMinAdvanceX;       // 0        // Minimum AdvanceX for glyphs, set Min to align font icons, set Max to clamp ussages.
    float           GlyphMaxAdvanceX;       // FLT_MAX  // Maximum AdvanceX for glyphs
    bool            MergeMode;              // false    // Merge into previous ImFont, so you can combine multiple inputs font into one ImFont (e.g. ASCII font + icons + Japanese font). You may want to use GlyphOffset.y when merging fonts.
    unsigned int    RasterizerFlags;        // 0x00     // Settings for custom font rasterizer (e.g. ImGuiFreeType). Leave as 0 for the default font rasterizer.
    float           RasterizerMultiply;     // 1.0f     // Brighten (>1.0f) or darken (<1.0f) font output. Used by FreeType and default rasterizer.

    IMGUI_API ImFontConfig();
};

struct ImFontGlyph
{
    unsigned int    Codepoint;          // 0x0000..0xFFFF
    unsigned int    Visible;            // Flag to indicate glyph is visible
    float           AdvanceX;           // Distance to next character
    float           X0, Y0, X1, Y1;     // Glyph corners
    float           U0, V0, U1, V1;     // Texture coordinates
};

// See ImGuiFreeType::RasterizerFlags
enum ImGuiFreeTypeBuilderFlags
{
    ImGuiFreeTypeBuilderFlags_NoHinting         = 1 << 0,   // Disable hinting. This generally generates 'blurrier' bitmap fonts when the glyph are rendered in any size that doesn't correspond to the font native size.
    ImGuiFreeTypeBuilderFlags_NoAutoHint        = 1 << 1,   // Disable auto-hinter.
    ImGuiFreeTypeBuilderFlags_ForceAutoHint     = 1 << 2,   // Indicates that the auto-hinter is preferred over the font's native hinter.
    ImGuiFreeTypeBuilderFlags_LightHinting      = 1 << 3,   // A lighter hinting algorithm for gray-level rendered fonts.
    ImGuiFreeTypeBuilderFlags_MonoHinting       = 1 << 4,   // Strong hinting algorithm that should only be used for monochrome output.
    ImGuiFreeTypeBuilderFlags_Bold              = 1 << 5,   // Styling: Should we artificially embolden the font?
    ImGuiFreeTypeBuilderFlags_Oblique           = 1 << 6,   // Styling: Should we slant the font, emulating an italic style?
    ImGuiFreeTypeBuilderFlags_LoadColor         = 1 << 7    // Enable loading color images from font specified in CPAL+COLR tables.
};

// 'ImFont' is a runtime representation of a single font.
// 'ImFontAtlas' contains a list of all fonts used by the application, holds the font texture, and builds everything.
struct ImFont
{
    // Members: Hot ~62/78 bytes
    float                       FontSize;           // <user set>      // Height of characters, set during loading (don't change after loading)
    float                       Scale;              // = 1.f           // Base font scale, multiplied by the per-window font scale which you can adjust with SetWindowFontScale()
    ImVec2                      DisplayOffset;      // = (0,0)         // Offset font rendering by xx pixels
    ImFontAtlas*                ContainerAtlas;     //                  // What we has been loaded into
    ImFontConfig                ConfigData;         //                  // Pointer to the config used to create this font.
    short                       ConfigDataCount;    //                  // Number of config used to create this font.
    ImWchar                     FallbackChar;       // = '?'           // Replacement character if a glyph isn't found. Only set on font loading, perhaps should be a constant?
    float                       FallbackAdvanceX;   //                  // Base advance_x for fallback character.
    float                       Ascent, Descent;    //                  // Ascent: distance from top to bottom of e.g. 'A' [0..FontSize]
    bool                        DirtyLookupTables;
    ImVector<ImFontGlyph>       Glyphs;
    const ImFontGlyph*          FallbackGlyph;      //
    ImVector<float>             IndexAdvanceX;
    ImVector<ImWchar>           IndexLookup;

    IMGUI_API ImFont();
    IMGUI_API ~ImFont();
    IMGUI_API const ImFontGlyph*FindGlyph(ImWchar c) const;
    IMGUI_API const ImFontGlyph*FindGlyphNoFallback(ImWchar c) const;
    IMGUI_API float             GetCharAdvance(ImWchar c) const { return ((int)c < IndexAdvanceX.Size) ? IndexAdvanceX[(int)c] : FallbackAdvanceX; }
    IMGUI_API bool              IsLoaded() const { return ContainerAtlas != NULL; }
    IMGUI_API const char*       GetDebugName() const { return ConfigData ? ConfigData.Name : "<unknown>"; }
    IMGUI_API ImVec2            CalcTextSizeA(float size, float max_width, float wrap_width, const char* text_begin, const char* text_end = NULL, const char** remaining = NULL) const;
    IMGUI_API const char*       CalcWordWrapPositionA(float scale, const char* text, const char* text_end, float wrap_width) const;
    IMGUI_API void              RenderChar(ImDrawList* draw_list, float size, ImVec2 pos, ImU32 col, ImWchar c) const;
    IMGUI_API void              RenderText(ImDrawList* draw_list, float size, ImVec2 pos, ImU32 col, const ImVec4& clip_rect, const char* text_begin, const char* text_end, float wrap_width = 0.0f, bool cpu_fine_clip = false) const;
    IMGUI_API void              BuildLookupTable();
    IMGUI_API void              ClearOutputData();
    IMGUI_API void              GrowIndex(int new_size);
    IMGUI_API void              AddGlyph(ImWchar c, float x0, float y0, float x1, float y1, float u0, float v0, float u1, float v1, float advance_x);
    IMGUI_API void              AddRemapChar(ImWchar dst, ImWchar src, bool overwrite_dst = true);
    IMGUI_API void              SetGlyphVisible(ImWchar c, bool visible);
};

// Flags for ImFontAtlas build
enum ImFontAtlasFlags_
{
    ImFontAtlasFlags_None               = 0,
    ImFontAtlasFlags_NoPowerOfTwoHeight = 1 << 0,   // Don't round the height to next power of two
    ImFontAtlasFlags_NoMouseCursors     = 1 << 1,   // Don't build software mouse cursors into the atlas
    ImFontAtlasFlags_NoBakedLines       = 1 << 2    // Don't build thick line textures into the atlas
};

struct ImFontAtlas
{
    IMGUI_API ImFontAtlas();
    IMGUI_API ~ImFontAtlas();
    IMGUI_API ImFont*           AddFont(const ImFontConfig* font_cfg);
    IMGUI_API ImFont*           AddFontDefault(const ImFontConfig* font_cfg = NULL);
    IMGUI_API ImFont*           AddFontFromFileTTF(const char* filename, float size_pixels, const ImFontConfig* font_cfg = NULL, const ImWchar* glyph_ranges = NULL);
    IMGUI_API ImFont*           AddFontFromMemoryTTF(void* font_data, int font_size, float size_pixels, const ImFontConfig* font_cfg = NULL, const ImWchar* glyph_ranges = NULL);
    IMGUI_API ImFont*           AddFontFromMemoryCompressedTTF(const void* compressed_font_data, int compressed_font_size, float size_pixels, const ImFontConfig* font_cfg = NULL, const ImWchar* glyph_ranges = NULL);
    IMGUI_API ImFont*           AddFontFromMemoryCompressedBase85TTF(const char* compressed_font_data_base85, float size_pixels, const ImFontConfig* font_cfg = NULL, const ImWchar* glyph_ranges = NULL);
    IMGUI_API void              ClearInputData();
    IMGUI_API void              ClearTexData();
    IMGUI_API void              ClearFonts();
    IMGUI_API void              Clear();
    IMGUI_API bool              Build();
    IMGUI_API void              GetTexDataAsAlpha8(unsigned char** out_pixels, int* out_width, int* out_height, int* out_bytes_per_pixel = NULL);
    IMGUI_API void              GetTexDataAsRGBA32(unsigned char** out_pixels, int* out_width, int* out_height, int* out_bytes_per_pixel = NULL);
    IMGUI_API bool              IsBuilt() { return Fonts.Size > 0 && (TexPixelsAlpha8 != NULL || TexPixelsRGBA32 != NULL); }
    IMGUI_API void              SetTexID(ImTextureID id) { TexID = id; }
    IMGUI_API const ImWchar*    GetGlyphRangesDefault();
    IMGUI_API const ImWchar*    GetGlyphRangesKorean();
    IMGUI_API const ImWchar*    GetGlyphRangesJapanese();
    IMGUI_API const ImWchar*    GetGlyphRangesChineseFull();
    IMGUI_API const ImWchar*    GetGlyphRangesChineseSimplifiedCommon();
    IMGUI_API const ImWchar*    GetGlyphRangesCyrillic();
    IMGUI_API const ImWchar*    GetGlyphRangesThai();
    IMGUI_API const ImWchar*    GetGlyphRangesVietnamese();

    // [Internal]
    IMGUI_API void              CalcCustomRectUV(const struct ImFontAtlasCustomRect* rect, ImVec2* out_uv_min, ImVec2* out_uv_max);
    IMGUI_API bool              GetMouseCursorTexData(ImGuiMouseCursor cursor, ImVec2* out_offset, ImVec2* out_size, ImVec2 out_uv_border[2], ImVec2 out_uv_fill[2]);

    ImVector<ImFont*>           Fonts;
    ImVector<ImFontAtlasCustomRect> CustomRects;
    ImVector<ImFontConfig>      ConfigData;
    ImVec4                      TexUvWhitePixel;
    ImTextureID                 TexID;
    int                         TexDesiredWidth;
    int                         TexGlyphPadding;
    unsigned char*              TexPixelsAlpha8;
    unsigned int*               TexPixelsRGBA32;
    int                         TexWidth;
    int                         TexHeight;
    ImFontAtlasFlags            Flags;

    // [Private]
    bool                        Locked;
    IMGUI_API void              AddCustomRectRegular(int id, int w, int h);
    IMGUI_API void              AddCustomRectFontGlyph(ImFont* font, ImWchar id, int w, int h, float advance_x, const ImVec2& offset = ImVec2(0, 0));
    IMGUI_API struct ImFontAtlasCustomRect* GetCustomRectByIndex(int index);
    IMGUI_API void              _ClearTexData();
};

// A single custom rectangle stored in the font atlas.
struct ImFontAtlasCustomRect
{
    unsigned short  Width, Height;  // Input    // Desired rectangle dimension
    unsigned short  X, Y;           // Output   // Packed position in Atlas
    unsigned int    GlyphID;        // Input    // For custom font glyphs only (ID < 0x10000)
    float           GlyphAdvanceX;  // Input    // For custom font glyphs only: glyph xadvance
    ImVec2          GlyphOffset;    // Input    // For custom font glyphs only: glyph display offset
    ImFont*         Font;           // Input    // For custom font glyphs only: target font
    ImFontAtlasCustomRect() { Width = Height = 0; X = Y = 0xFFFF; GlyphID = 0; GlyphAdvanceX = 0.0f; GlyphOffset = ImVec2(0, 0); Font = NULL; }
    bool IsPacked() const { return X != 0xFFFF; }
};

//-----------------------------------------------------------------------------
// Renderer API
// (Implmented by back-ends)
//-----------------------------------------------------------------------------

// Provided by user application, called by ImGui::Render()
// ImDrawData is generally valid for a single frame, if you want to build your own rendering queue out of ImDrawData, you need to copy ImDrawList* and all their contents.
// (see ImDrawData::DeIndexAllBuffers() for a convenient way of converting render data into a de-indexed format, if your renderer prefer that)
extern "C" void ImGui_ImplAsm_RenderDrawLists(ImDrawData* draw_data);

//-----------------------------------------------------------------------------
// Obsolete functions
//-----------------------------------------------------------------------------

// Those are obsolete functions, available for backward compatibility and will be removed in a future version.
// (Will trigger a warning if IMGUI_DISABLE_OBSOLETE_FUNCTIONS is not defined)
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
namespace ImGui
{
    // OBSOLETED in 1.79 (from July 2020)
    static inline bool  IsAnyWindowFocused(ImGuiFocusedFlags flags = 0) { return IsWindowFocused(flags | ImGuiFocusedFlags_AnyWindow); }
    // OBSOLETED in 1.78 (from June 2020)
    static inline bool  IsAnyWindowHovered(ImGuiHoveredFlags flags = 0) { return IsWindowHovered(flags | ImGuiHoveredFlags_AnyWindow); }
    static inline ImVec2 GetContentRegionAvailScreen()                 { return GetContentRegionAvail(); } // Wrong name, had to be retrieved from window.
    // OBSOLETED in 1.77 (from April 2020)
    static inline ImDrawList* GetOverlayDrawList()                      { return GetForegroundDrawList(); }
    // OBSOLETED in 1.76 (from Jan 2020)
    static inline void  SetScrollHere(float center_ratio = 0.5f)        { SetScrollHereY(center_ratio); }
    // OBSOLETED in 1.72 (from April 2019)
    static inline bool  IsItemDeactivatedAfterChange()                  { return IsItemDeactivatedAfterEdit(); }
    // OBSOLETED in 1.71 (from March 2019)
    static inline void  SetNextTreeNodeOpen(bool open, ImGuiCond c=0)   { SetNextItemOpen(open, c); }
    // OBSOLETED in 1.68 (from October 2018)
    static inline void  PushItemFlag(int, bool) {}
    static inline void  PopItemFlag() {}
    // OBSOLETED in 1.67 (from September 2018)
    static inline void  SetNextWindowContentWidth(float w)              { SetNextWindowContentSize(ImVec2(w, 0.0f)); }
    // OBSOLETED in 1.66 (from July 2018)
    static inline bool  IsRectVisible(const ImVec2&, const ImVec2&)     { return true; }
    static inline bool  IsPosHoveringAnyWindow(const ImVec2&)            { return false; }
    // OBSOLETED in 1.64 (from March 2018)
    static inline bool  IsMouseHoveringWindow()                         { return IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup | ImGuiHoveredFlags_AllowWhenBlockedByActiveItem); }
    // OBSOLETED in 1.63 (from February 2018)
    static inline bool  GetWindowIsFocused(ImGuiFocusedFlags flags = 0) { return IsWindowFocused(flags); }
    static inline bool  GetWindowIsHovered(ImGuiHoveredFlags flags = 0) { return IsWindowHovered(flags); }
    // OBSOLETED in 1.61 (from October 2017)
    IMGUI_API void      ShowTestWindow(bool* p_open = NULL);
    // OBSOLETED in 1.60 (from August 2017)
    static inline void  PushClipRect(const ImVec2& clip_rect_min, const ImVec2& clip_rect_max, bool intersect_with_current_clip_rect) { GetWindowDrawList()->PushClipRect(clip_rect_min, clip_rect_max, intersect_with_current_clip_rect); }
    static inline void  PopClipRect()                                   { GetWindowDrawList()->PopClipRect(); }
    // OBSOLETED in 1.53 (between Oct 2016 and Jan 2017)
    static inline void  SetNextWindowPosCenter(ImGuiCond c = 0)         { ImGuiIO& io = GetIO(); SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), c, ImVec2(0.5f, 0.5f)); }
    // OBSOLETED in 1.52 (from September 2016)
    static inline bool  IsRootWindowFocused()                           { return IsWindowFocused(ImGuiFocusedFlags_RootWindow); }
    static inline bool  IsRootWindowOrAnyChildFocused()                 { return IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows); }
    static inline void  SetNextWindowMainViewport()                     {}
    // OBSOLETED in 1.51 (from June 2016)
    static inline bool  IsMouseHoveringAnyWindow()                      { return IsAnyWindowHovered(); }
    static inline bool  IsMouseHoveringRect(const ImVec2& r_min, const ImVec2& r_max, bool clip = true) { return IsMouseHoveringRect(r_min, r_max, clip); }
    // OBSOLETED in 1.50 (from April 2016)
    static inline bool  IsAnyWindowFocused()                            { return IsWindowFocused(ImGuiFocusedFlags_AnyWindow); }
    // OBSOLETED in 1.48 (from November 2015)
    static inline void  ShowCheckeredAppsBackground(bool)               {}
    // OBSOLETED in 1.47 (from October 2015)
    static inline void  BeginDockspace()                                {}
    static inline void  EndDockspace()                                  {}
    static inline void  SetDockspaceSize(float, float)                  {}
}
#endif

//-----------------------------------------------------------------------------
// Helpers functions to create a color that can be converted to either u32 or float4
//-----------------------------------------------------------------------------

struct ImColor
{
    ImVec4              Value;

    ImColor()                                           { Value.x = Value.y = Value.z = Value.w = 0.0f; }
    ImColor(int r, int g, int b, int a = 255)           { float sc = 1.0f/255.0f; Value.x = (float)r * sc; Value.y = (float)g * sc; Value.z = (float)b * sc; Value.w = (float)a * sc; }
    ImColor(ImU32 rgba)                                 { float sc = 1.0f/255.0f; Value.x = (float)((rgba>>0)&0xFF) * sc; Value.y = (float)((rgba>>8)&0xFF) * sc; Value.z = (float)((rgba>>16)&0xFF) * sc; Value.w = (float)(rgba >> 24) * sc; }
    ImColor(float r, float g, float b, float a = 1.0f)  { Value.x = r; Value.y = g; Value.z = b; Value.w = a; }
    ImColor(const ImVec4& col)                          { Value = col; }
    inline operator ImU32() const                       { return ImGui::ColorConvertFloat4ToU32(Value); }
    inline operator ImVec4() const                      { return Value; }

    // FIXME-OBSOLETE: May be removed!
    inline void    SetHSV(float h, float s, float v, float a = 1.0f){ ImGui::ColorConvertHSVtoRGB(h, s, v, Value.x, Value.y, Value.z); Value.w = a; }
    static ImColor HSV(float h, float s, float v, float a = 1.0f)   { float r,g,b; ImGui::ColorConvertHSVtoRGB(h, s, v, r, g, b); return ImColor(r,g,b,a); }
};

//-----------------------------------------------------------------------------
// ImVector<>
// Lightweight std::vector like class.
//-----------------------------------------------------------------------------

template<typename T>
struct ImVector
{
    int                 Size;
    int                 Capacity;
    T*                  Data;

    typedef T                   value_type;
    typedef value_type*         iterator;
    typedef const value_type*   const_iterator;

    ImVector()                  { Size = Capacity = 0; Data = NULL; }
    ~ImVector()                 { if (Data) ImGui::MemFree(Data); }

    inline bool         empty() const                   { return Size == 0; }
    inline int          size() const                    { return Size; }
    inline int          capacity() const                { return Capacity; }
    inline T&           operator[](int i)               { IM_ASSERT(i < Size); return Data[i]; }
    inline const T&     operator[](int i) const         { IM_ASSERT(i < Size); return Data[i]; }

    inline void         clear()                         { Size = 0; }
    inline iterator     begin()                         { return Data; }
    inline const_iterator begin() const                 { return Data; }
    inline iterator     end()                           { return Data + Size; }
    inline const_iterator end() const                   { return Data + Size; }
    inline T&           front()                         { IM_ASSERT(Size > 0); return Data[0]; }
    inline const T&     front() const                   { IM_ASSERT(Size > 0); return Data[0]; }
    inline T&           back()                          { IM_ASSERT(Size > 0); return Data[Size-1]; }
    inline const T&     back() const                    { IM_ASSERT(Size > 0); return Data[Size-1]; }
    inline void         swap(ImVector<T>& rhs)          { int rhs_size = rhs.Size; rhs.Size = Size; Size = rhs_size; int rhs_cap = rhs.Capacity; rhs.Capacity = Capacity; Capacity = rhs_cap; T* rhs_data = rhs.Data; rhs.Data = Data; Data = rhs_data; }

    inline int          _grow_capacity(int sz) const    { int new_capacity = Capacity ? (Capacity + Capacity/2) : 8; return new_capacity > sz ? new_capacity : sz; }
    inline void         resize(int new_size)            { if (new_size > Capacity) reserve(_grow_capacity(new_size)); Size = new_size; }
    inline void         reserve(int new_capacity)
    {
        if (new_capacity <= Capacity) return;
        T* new_data = (T*)ImGui::MemAlloc((size_t)new_capacity * sizeof(T));
        if (Data) { memcpy(new_data, Data, (size_t)Size * sizeof(T)); ImGui::MemFree(Data); }
        Data = new_data;
        Capacity = new_capacity;
    }

    inline void         push_back(const T& v)           { if (Size == Capacity) reserve(_grow_capacity(Size+1)); memcpy(&Data[Size], &v, sizeof(v)); Size++; }
    inline void         pop_back()                      { IM_ASSERT(Size > 0); Size--; }
    inline iterator     erase(const_iterator it)        { IM_ASSERT(it >= Data && it < Data+Size); const ptrdiff_t off = it - Data; memmove(Data + off, Data + off + 1, ((size_t)Size - (size_t)off - 1) * sizeof(T)); Size--; return Data + off; }
    inline iterator     insert(const_iterator it, const T& v) { IM_ASSERT(it >= Data && it <= Data+Size); const ptrdiff_t off = it - Data; if (Size == Capacity) reserve(_grow_capacity(Size+1)); if (off < Size) memmove(Data + off + 1, Data + off, ((size_t)Size - (size_t)off) * sizeof(T)); memcpy(&Data[off], &v, sizeof(v)); Size++; return Data + off; }
};

//-----------------------------------------------------------------------------
// ImGuiTextFilter
// Helper: Parse and apply text filters. In format "aaaaa[,bbbbb][,ccccc]"
//-----------------------------------------------------------------------------
struct ImGuiTextFilter
{
    struct TextRange
    {
        const char* b;
        const char* e;

        TextRange() { b = e = NULL; }
        TextRange(const char* _b, const char* _e) { b = _b; e = _e; }
        const char* begin() const { return b; }
        const char* end() const { return e; }
        bool empty() const { return b == e; }
        char front() const { return *b; }
        void split(char separator, ImVector<TextRange>& out) const;
    };

    char                InputBuf[256];
    ImVector<TextRange> Filters;
    int                 CountGrep;

    IMGUI_API           ImGuiTextFilter(const char* default_filter = "");
    IMGUI_API bool      Draw(const char* label = "Filter (inc,-exc)", float width = 0.0f);    // Helper calling InputText+Build
    IMGUI_API bool      PassFilter(const char* text, const char* text_end = NULL) const;
    IMGUI_API void      Build();
    void                Clear() { InputBuf[0] = 0; Build(); }
    bool                IsActive() const { return !Filters.empty(); }
};

//-----------------------------------------------------------------------------
// ImGuiTextBuffer
// Helper: Simple text buffer for logging/accumulating text
//-----------------------------------------------------------------------------
struct ImGuiTextBuffer
{
    ImVector<char>      Buf;
    IMGUI_API ImGuiTextBuffer() { }
    inline char         operator[](int i) { return Buf[i]; }
    const char*         begin() const { return Buf.begin(); }
    const char*         end() const { return Buf.end(); }
    int                 size() const { return Buf.Size; }
    bool                empty() { return Buf.empty(); }
    void                clear() { Buf.clear(); }
    void                reserve(int capacity) { Buf.reserve(capacity); }
    const char*         c_str() const { return Buf.Data ? Buf.Data : ""; }
    IMGUI_API void      append(const char* fmt, ...) IM_FMTARGS(2);
    IMGUI_API void      appendv(const char* fmt, va_list args) IM_FMTLIST(2);
};

//-----------------------------------------------------------------------------
// ImGuiStorage
// Helper: Key->value storage
//-----------------------------------------------------------------------------

struct ImGuiStorage
{
    struct Pair
    {
        ImGuiID key;
        union { int val_i; float val_f; void* val_p; };
        Pair(ImGuiID _key, int _val_i)   { key = _key; val_i = _val_i; }
        Pair(ImGuiID _key, float _val_f) { key = _key; val_f = _val_f; }
        Pair(ImGuiID _key, void* _val_p) { key = _key; val_p = _val_p; }
    };
    ImVector<Pair>      Data;

    // - Get***() functions find pair, never add/allocate. Pairs are sorted so a query is O(log N)
    // - Set***() functions find pair, add/allocate if missing.
    // - Get***Ref() functions find pair, add/allocate if missing, return pointer to value.
    IMGUI_API void      Clear();
    IMGUI_API int       GetInt(ImGuiID key, int default_val = 0) const;
    IMGUI_API void      SetInt(ImGuiID key, int val);
    IMGUI_API bool      GetBool(ImGuiID key, bool default_val = false) const;
    IMGUI_API void      SetBool(ImGuiID key, bool val);
    IMGUI_API float     GetFloat(ImGuiID key, float default_val = 0.0f) const;
    IMGUI_API void      SetFloat(ImGuiID key, float val);
    IMGUI_API void*     GetVoidPtr(ImGuiID key) const;
    IMGUI_API void      SetVoidPtr(ImGuiID key, void* val);

    // - Get***Ref() functions find pair, add/allocate if missing, return pointer to value.
    IMGUI_API int*      GetIntRef(ImGuiID key, int default_val = 0);
    IMGUI_API bool*     GetBoolRef(ImGuiID key, bool default_val = false);
    IMGUI_API float*    GetFloatRef(ImGuiID key, float default_val = 0.0f);
    IMGUI_API void**    GetVoidPtrRef(ImGuiID key, void* default_val = NULL);

    // Use on your own storage if you know only integer are being stored (open/close states, collapsing nodes)
    IMGUI_API void      SetAllInt(int val);

    // For quicker full rebuild of a storage (instead of an incremental one), you can use BuildSortByKey().
    // It will be much faster but you need to verify that your keys are stricly unique among the pairs.
    IMGUI_API void      BuildSortByKey();
};

//-----------------------------------------------------------------------------
// ImGuiListClipper
// Helper to clip large list of items easily.
//-----------------------------------------------------------------------------
struct ImGuiListClipper
{
    float   StartPosY;
    float   ItemsHeight;
    int     ItemsCount, StepNo, DisplayStart, DisplayEnd;

    // NB: Begin() function also calls Step() once!
    IMGUI_API ImGuiListClipper(int items_count = -1, float items_height = -1.0f);
    IMGUI_API ~ImGuiListClipper();
    IMGUI_API bool  Step();
    IMGUI_API void  Begin(int items_count, float items_height = -1.0f);
    IMGUI_API void  End();
};

//-----------------------------------------------------------------------------
// ImGuiOnceUponAFrame
// Helper for running a block of code not more than once a frame.
//-----------------------------------------------------------------------------
struct ImGuiOnceUponAFrame
{
    ImGuiOnceUponAFrame() { RefFrame = -1; }
    int RefFrame;
    operator bool() { int current_frame = ImGui::GetFrameCount(); if (RefFrame == current_frame) return false; RefFrame = current_frame; return true; }
};

//-----------------------------------------------------------------------------
// IMGUI_IMPL_API
//-----------------------------------------------------------------------------

// ImDrawData are passed to the renderer function every frame.
// You can use your own drawing function based on the ImDrawData structure.
// If you are not using a standard binding method, you can use this function to get the draw data and dispatch it to your renderer.
// You can call this function after ImGui::Render() and before ImGui::NewFrame().
// This function is defined in imgui.cpp.
IMGUI_IMPL_API ImDrawData* ImGui_GetDrawData();

// This is the main rendering function that you have to implement and provide to ImGui (via setting up 'RenderDrawListsFn' in your ImGuiIO structure)
// If you are using a standard binding method, this will be called automatically for you.
// See the examples applications for the implementation of this function.
IMGUI_IMPL_API void ImGui_RenderDrawLists(ImDrawData* data);

//-----------------------------------------------------------------------------
// Obsolete symbols
//-----------------------------------------------------------------------------

#if defined(IMGUI_DISABLE_OBSOLETE_FUNCTIONS) && !defined(IMGUI_DISABLE_OBSOLETE_KEYIO)
#define IMGUI_DISABLE_OBSOLETE_KEYIO
#endif

// Allow using original legacy names if IMGUI_DISABLE_OBSOLETE_FUNCTIONS is not defined.
#if !defined(IMGUI_DISABLE_OBSOLETE_FUNCTIONS)
typedef ImDrawList      ImDrawList;
typedef ImDrawData      ImDrawData;
typedef ImDrawCmd       ImDrawCmd;
typedef ImDrawVert      ImDrawVert;
typedef ImFont          ImFont;
typedef ImFontAtlas     ImFontAtlas;
typedef ImGuiIO         ImGuiIO;
typedef ImGuiStyle      ImGuiStyle;
typedef ImGuiContext    ImGuiContext;
typedef ImVec2          ImVec2;
typedef ImVec4          ImVec4;
typedef ImGuiListClipper ImGuiListClipper;
typedef ImColor         ImColor;
typedef ImGuiTextFilter ImGuiTextFilter;
typedef ImGuiTextBuffer ImGuiTextBuffer;
typedef ImGuiStorage    ImGuiStorage;
#endif // !defined(IMGUI_DISABLE_OBSOLETE_FUNCTIONS)

#if defined(__cplusplus)
}
#endif