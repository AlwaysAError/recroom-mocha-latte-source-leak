#pragma once

#include "Dependencies/imgui/imgui.h"
#include "Dependencies/imgui/imgui_internal.h"

#include "Dependencies/imgui/imgui_impl_dx11.h"
#include "Dependencies/imgui/imgui_impl_win32.h"

#include "Dependencies/imgui/freetype/imgui_freetype.h"
#include "Dependencies/imgui/addons/imgui_addons.h"

#include <d3d9.h>
#include <vector>
#include <algorithm>

#include "CTextures.h"
#include "CNotification.h"

#include "Resources/Fonts/IconsFontAwesome6.h"
#include "Resources/Fonts/IconsFontAwesome6Brands.h"
#include "Resources/Fonts/MuseoSans.h"
#include "Resources/Fonts/Poppins_Medium.h"
#include "Resources/Fonts/Roboto_Regular.h"

struct renderPlayerData
{
    PlayerInfo& player;
    ImVec4 vec4Color;
    ImVec4 iconColor;
    ImTextureID tIcon;
};

enum eMenuPage_ : int
{
    // Player
    MenuPage_Combat,
    MenuPage_Movement,
    MenuPage_Misc,
    MenuPage_Visuals,

    // Network
    MenuPage_Exploits,
    MenuPage_Playerlist,
    MenuPage_AssetsSpawn,
    MenuPage_ItemsSpawn,

    // Settings
    MenuPage_Configs,
    MenuPage_Themes,

    // Developer
    MenuPage_TestMenu,
    MenuPage_AntiExploits,
    MenuPage_Api,

    MenuPage_COUNT

    /* old code here
    // Player
    MenuPage_ActualModules,
    MenuPage_ItemsSpawn,
    MenuPage_AssetSpawn,

    // Network
    MenuPage_Exploit,
    MenuPage_Anti,
    MenuPage_PlayerList,
    MenuPage_Api,

    // Settings
    MenuPage_Themes,
    MenuPage_Config,
    MenuPage_DevBeta,

    MenuPage_TestMenu,
    */
};

enum eThemes_ : int
{
    THEME_DARK_BLUE, // Github app
    THEME_DARK_PURPLE,
    THEME_DARK,
    THEME_MOCHA,
    THEME_RED,
};

int iTheme = THEME_MOCHA;

class CGui
{
public:
    CGui(CTextures* pTextures);
    ~CGui();

    bool Initialize(void* hWnd, ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
    void ApplyTheme();
    void Shutdown();

    // tabs here
    void AntiExploitsTab(ImGuiStyle& style);
    void ApiTab(ImGuiStyle& style);
    void AssetsSpawnTab(ImGuiStyle& style);
    void CombatTab(ImGuiStyle& style);
    void ConfigsTab(ImGuiStyle& style);
    void ExploitsTab(ImGuiStyle& style);
    void ItemsSpawnTab(ImGuiStyle& style);
    void MiscTab(ImGuiStyle& style);
    void MovementTab(ImGuiStyle& style);
    void PlayerListTab(ImGuiStyle& style);
    void TestTab(ImGuiStyle& style);
    void ThemesTab(ImGuiStyle& style);
    void VisualsTab(ImGuiStyle& style);

    void PlayerListGUI(ImGuiStyle& style);

    void PreRender();
    void Render();

    bool MsgProc(HWND, UINT, WPARAM, LPARAM);

    const char* GetTabName(int ID);
    const char* GetTabDescription(int ID);
    ImTextureID GetTabIconTexture(int ID, bool bFilled = false);

    struct {
        ImFont* MainFont;
        ImFont* BigFont;
    } m_Fonts;

    ImNotify notify;
    CTextures* m_pTextures;

private:
    int iSelectedPage;

    std::vector<renderPlayerData> renderPlayerlist;
};

#include "Tabs/include.h" // we use CGui definitions so i put this here, lazy, idc smd

// Define Gui pointers
CGui* pGui = 0;
CTextures* pTextures = 0;

CGui::CGui(CTextures* pTextures)
{
    m_pTextures = pTextures;
    iSelectedPage = 0;
    iTheme = THEME_MOCHA;
}

CGui::~CGui()
{
}

bool CGui::Initialize(void* hWnd, ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
    if (!pDevice)
        return false;

    bool result = true;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiStyle& style = ImGui::GetStyle();
    ImGuiIO& io = ImGui::GetIO();

    io.ConfigFlags &= ~ImGuiConfigFlags_NavEnableKeyboard;  // Turn off this piece of shit
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;    // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
    io.IniFilename = "init";
    io.LogFilename = "logs";
    GImGui->NavDisableHighlight = true;                     // Disable Highlighting

    style.TabRounding = 4;
    style.ScrollbarRounding = 9;
    style.WindowRounding = 7;
    style.GrabRounding = 3;
    style.FrameRounding = 3;
    style.PopupRounding = 4;
    style.ChildRounding = 4;

    ApplyTheme();

    // Setup Font
    ImFontConfig cfg;
    cfg.FontBuilderFlags |= ImGuiFreeTypeBuilderFlags::ImGuiFreeTypeBuilderFlags_ForceAutoHint;
    m_Fonts.MainFont = io.Fonts->AddFontFromMemoryCompressedTTF(Poppins_Medium_compressed_data, Poppins_Medium_compressed_size, 16, &cfg, io.Fonts->GetGlyphRangesDefault());
    //ImFont* mainFont = io.Fonts->AddFontFromMemoryCompressedTTF(uiMuseoSansData, uiMuseoSansSize, 14, &cfg, io.Fonts->GetGlyphRangesDefault());

    // merge in icons from Font Awesome
    static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
    static const ImWchar icons_ranges_brands[] = { ICON_MIN_FAB, ICON_MAX_16_FAB, 0 };

    ImFontConfig fa_config; fa_config.MergeMode = true; fa_config.PixelSnapH = true;
    fa_config.FontBuilderFlags |= ImGuiFreeTypeBuilderFlags::ImGuiFreeTypeBuilderFlags_ForceAutoHint;

    ImFont* fontAwesome = io.Fonts->AddFontFromMemoryCompressedTTF(fa6_solid_compressed_data, fa6_solid_compressed_size, 16, &fa_config, icons_ranges);
    ImFont* fontAwesomeBrands = io.Fonts->AddFontFromMemoryCompressedTTF(fa_brands_400_compressed_data, fa_brands_400_compressed_size, 16, &fa_config, icons_ranges_brands);

    m_Fonts.BigFont = io.Fonts->AddFontFromMemoryCompressedTTF(Poppins_Medium_compressed_data, Poppins_Medium_compressed_size, 18, &cfg, io.Fonts->GetGlyphRangesDefault());

    // Setup Platform/Renderer backends
    result &= ImGui_ImplWin32_Init(hWnd);
    result &= ImGui_ImplDX11_Init(pDevice, pContext);

    return result;
}

void CGui::ApplyTheme()
{
    ImGuiStyle& style = ImGui::GetStyle();

    switch (iTheme)
    {
    case THEME_DARK_BLUE:
        style.Colors[ImGuiCol_WindowBg] = ImAdd::HexToColorVec4(0x1D2125, 1.0f);
        style.Colors[ImGuiCol_PopupBg] = ImAdd::HexToColorVec4(0x24292E, 1.0f);
        style.Colors[ImGuiCol_ChildBg] = ImAdd::HexToColorVec4(0x2B3137, 1.0f);

        style.Colors[ImGuiCol_Text] = ImAdd::HexToColorVec4(0xFFFFFF, 1.0f);
        style.Colors[ImGuiCol_CheckMark] = style.Colors[ImGuiCol_Text];
        style.Colors[ImGuiCol_TextDisabled] = ImAdd::HexToColorVec4(0x959DA5, 1.0f);

        style.Colors[ImGuiCol_SliderGrab] = ImAdd::HexToColorVec4(0x99C8FF, 1.0f);
        style.Colors[ImGuiCol_SliderGrabActive] = ImAdd::HexToColorVec4(0x8AB2E1, 1.0f);

        style.Colors[ImGuiCol_ScrollbarGrab] = ImAdd::HexToColorVec4(0x2B3137, 1.0f);
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImAdd::HexToColorVec4(0x2B3137, 1.0f);
        style.Colors[ImGuiCol_ScrollbarGrabActive] = ImAdd::HexToColorVec4(0x2B3137, 1.0f);

        style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0, 0, 0, 0);

        style.Colors[ImGuiCol_TextSelectedBg] = style.Colors[ImGuiCol_SliderGrab];

        style.Colors[ImGuiCol_Border] = ImAdd::HexToColorVec4(0x24292E, 1.0f);
        style.Colors[ImGuiCol_Separator] = style.Colors[ImGuiCol_Border];

        style.Colors[ImGuiCol_Button] = ImAdd::HexToColorVec4(0x1D2125, 1.0f);
        style.Colors[ImGuiCol_ButtonHovered] = ImAdd::HexToColorVec4(0x1D2125, 0.7f);
        style.Colors[ImGuiCol_ButtonActive] = ImAdd::HexToColorVec4(0x1D2125, 0.5f);

        style.Colors[ImGuiCol_FrameBg] = ImAdd::HexToColorVec4(0x1D2125, 1.0f);
        style.Colors[ImGuiCol_FrameBgHovered] = ImAdd::HexToColorVec4(0x1D2125, 0.7f);
        style.Colors[ImGuiCol_FrameBgActive] = ImAdd::HexToColorVec4(0x1D2125, 0.5f);

        style.Colors[ImGuiCol_Header] = ImAdd::HexToColorVec4(0x2B3137, 1.0f);
        style.Colors[ImGuiCol_HeaderHovered] = ImAdd::HexToColorVec4(0x2B3137, 0.7f);
        style.Colors[ImGuiCol_HeaderActive] = ImAdd::HexToColorVec4(0x2B3137, 0.5f);
        break;
    case THEME_DARK_PURPLE:
        style.Colors[ImGuiCol_WindowBg] = ImAdd::HexToColorVec4(0x231D2B, 1.0f);
        style.Colors[ImGuiCol_PopupBg] = ImAdd::HexToColorVec4(0x2C2336, 1.0f);
        style.Colors[ImGuiCol_ChildBg] = ImAdd::HexToColorVec4(0x342B40, 1.0f);

        style.Colors[ImGuiCol_Text] = ImAdd::HexToColorVec4(0xFFFFFF, 1.0f);
        style.Colors[ImGuiCol_CheckMark] = style.Colors[ImGuiCol_Text];
        style.Colors[ImGuiCol_TextDisabled] = ImAdd::HexToColorVec4(0xA491AF, 1.0f);

        style.Colors[ImGuiCol_SliderGrab] = ImAdd::HexToColorVec4(0xB199FF, 1.0f);
        style.Colors[ImGuiCol_SliderGrabActive] = ImAdd::HexToColorVec4(0x9985DA, 1.0f);

        style.Colors[ImGuiCol_ScrollbarGrab] = ImAdd::HexToColorVec4(0x342B40, 1.0f);
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImAdd::HexToColorVec4(0x342B40, 1.0f);
        style.Colors[ImGuiCol_ScrollbarGrabActive] = ImAdd::HexToColorVec4(0x342B40, 1.0f);

        style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0, 0, 0, 0);

        style.Colors[ImGuiCol_TextSelectedBg] = style.Colors[ImGuiCol_SliderGrab];

        style.Colors[ImGuiCol_Border] = ImAdd::HexToColorVec4(0x2C2336, 1.0f);
        style.Colors[ImGuiCol_Separator] = style.Colors[ImGuiCol_Border];

        style.Colors[ImGuiCol_Button] = ImAdd::HexToColorVec4(0x231D2B, 1.0f);
        style.Colors[ImGuiCol_ButtonHovered] = ImAdd::HexToColorVec4(0x231D2B, 0.7f);
        style.Colors[ImGuiCol_ButtonActive] = ImAdd::HexToColorVec4(0x231D2B, 0.5f);

        style.Colors[ImGuiCol_FrameBg] = ImAdd::HexToColorVec4(0x231D2B, 1.0f);
        style.Colors[ImGuiCol_FrameBgHovered] = ImAdd::HexToColorVec4(0x231D2B, 0.7f);
        style.Colors[ImGuiCol_FrameBgActive] = ImAdd::HexToColorVec4(0x231D2B, 0.5f);

        style.Colors[ImGuiCol_Header] = ImAdd::HexToColorVec4(0x342B40, 1.0f);
        style.Colors[ImGuiCol_HeaderHovered] = ImAdd::HexToColorVec4(0x342B40, 0.7f);
        style.Colors[ImGuiCol_HeaderActive] = ImAdd::HexToColorVec4(0x342B40, 0.5f);
        break;
    case THEME_DARK:
        style.Colors[ImGuiCol_WindowBg] = ImAdd::HexToColorVec4(0x1F1F1F, 1.0f);
        style.Colors[ImGuiCol_PopupBg] = ImAdd::HexToColorVec4(0x272727, 1.0f);
        style.Colors[ImGuiCol_ChildBg] = ImAdd::HexToColorVec4(0x2F2F2F, 1.0f);

        style.Colors[ImGuiCol_Text] = ImAdd::HexToColorVec4(0xFFFFFF, 1.0f);
        style.Colors[ImGuiCol_CheckMark] = style.Colors[ImGuiCol_Text];
        style.Colors[ImGuiCol_TextDisabled] = ImAdd::HexToColorVec4(0xA2A2A2, 1.0f);

        style.Colors[ImGuiCol_SliderGrab] = ImAdd::HexToColorVec4(0x99C8FF, 1.0f);
        style.Colors[ImGuiCol_SliderGrabActive] = ImAdd::HexToColorVec4(0x8AB2E1, 1.0f);

        style.Colors[ImGuiCol_ScrollbarGrab] = ImAdd::HexToColorVec4(0x2F2F2F, 1.0f);
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImAdd::HexToColorVec4(0x2F2F2F, 1.0f);
        style.Colors[ImGuiCol_ScrollbarGrabActive] = ImAdd::HexToColorVec4(0x2F2F2F, 1.0f);

        style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0, 0, 0, 0);

        style.Colors[ImGuiCol_TextSelectedBg] = style.Colors[ImGuiCol_SliderGrab];

        style.Colors[ImGuiCol_Border] = ImAdd::HexToColorVec4(0x272727, 1.0f);
        style.Colors[ImGuiCol_Separator] = style.Colors[ImGuiCol_Border];

        style.Colors[ImGuiCol_Button] = ImAdd::HexToColorVec4(0x1F1F1F, 1.0f);
        style.Colors[ImGuiCol_ButtonHovered] = ImAdd::HexToColorVec4(0x1F1F1F, 0.7f);
        style.Colors[ImGuiCol_ButtonActive] = ImAdd::HexToColorVec4(0x1F1F1F, 0.5f);

        style.Colors[ImGuiCol_FrameBg] = ImAdd::HexToColorVec4(0x1F1F1F, 1.0f);
        style.Colors[ImGuiCol_FrameBgHovered] = ImAdd::HexToColorVec4(0x1F1F1F, 0.7f);
        style.Colors[ImGuiCol_FrameBgActive] = ImAdd::HexToColorVec4(0x1F1F1F, 0.5f);

        style.Colors[ImGuiCol_Header] = ImAdd::HexToColorVec4(0x2F2F2F, 1.0f);
        style.Colors[ImGuiCol_HeaderHovered] = ImAdd::HexToColorVec4(0x2F2F2F, 0.7f);
        style.Colors[ImGuiCol_HeaderActive] = ImAdd::HexToColorVec4(0x2F2F2F, 0.5f);
        break;
    case THEME_MOCHA:
        // Backgrounds
        style.Colors[ImGuiCol_WindowBg] = ImAdd::HexToColorVec4(0x1F1F1F, 1.0f);
        style.Colors[ImGuiCol_PopupBg] = ImAdd::HexToColorVec4(0x272727, 1.0f);
        style.Colors[ImGuiCol_ChildBg] = ImAdd::HexToColorVec4(0x2F2F2F, 1.0f);

        // Text
        style.Colors[ImGuiCol_Text] = ImAdd::HexToColorVec4(0xFFFFFF, 1.0f);
        style.Colors[ImGuiCol_TextDisabled] = ImAdd::HexToColorVec4(0xA2A2A2, 1.0f);
        style.Colors[ImGuiCol_TextSelectedBg] = ImAdd::HexToColorVec4(0xd8a1fc, 1.0f);  // Changed to pinkish-purple

        // CheckMark
        style.Colors[ImGuiCol_CheckMark] = ImAdd::HexToColorVec4(0xFFFFFF, 1.0f);

        // Sliders
        style.Colors[ImGuiCol_SliderGrab] = ImAdd::HexToColorVec4(0xd8a1fc, 1.0f);  // Changed to pinkish-purple
        style.Colors[ImGuiCol_SliderGrabActive] = ImAdd::HexToColorVec4(0xb67fdf, 1.0f);  // Slightly darker pinkish-purple


        // Scrollbars
        style.Colors[ImGuiCol_ScrollbarGrab] = ImAdd::HexToColorVec4(0x2F2F2F, 1.0f);
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImAdd::HexToColorVec4(0x2F2F2F, 1.0f);
        style.Colors[ImGuiCol_ScrollbarGrabActive] = ImAdd::HexToColorVec4(0x2F2F2F, 1.0f);
        style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0, 0, 0, 0);

        // Borders
        style.Colors[ImGuiCol_Border] = ImAdd::HexToColorVec4(0x272727, 1.0f);
        style.Colors[ImGuiCol_Separator] = ImAdd::HexToColorVec4(0x272727, 1.0f);

        // Buttons
        style.Colors[ImGuiCol_Button] = ImAdd::HexToColorVec4(0x1F1F1F, 1.0f);
        style.Colors[ImGuiCol_ButtonHovered] = ImAdd::HexToColorVec4(0x1F1F1F, 0.7f);
        style.Colors[ImGuiCol_ButtonActive] = ImAdd::HexToColorVec4(0x1F1F1F, 0.5f);

        // Frames
        style.Colors[ImGuiCol_FrameBg] = ImAdd::HexToColorVec4(0x1F1F1F, 1.0f);
        style.Colors[ImGuiCol_FrameBgHovered] = ImAdd::HexToColorVec4(0x1F1F1F, 0.7f);
        style.Colors[ImGuiCol_FrameBgActive] = ImAdd::HexToColorVec4(0x1F1F1F, 0.5f);

        // Headers
        style.Colors[ImGuiCol_Header] = ImAdd::HexToColorVec4(0x2F2F2F, 1.0f);
        style.Colors[ImGuiCol_HeaderHovered] = ImAdd::HexToColorVec4(0x2F2F2F, 0.7f);
        style.Colors[ImGuiCol_HeaderActive] = ImAdd::HexToColorVec4(0x2F2F2F, 0.5f);
        break;
    case THEME_RED:
        style.Colors[ImGuiCol_WindowBg] = ImAdd::HexToColorVec4(0x2B1D1D, 1.0f);
        style.Colors[ImGuiCol_PopupBg] = ImAdd::HexToColorVec4(0x362323, 1.0f);
        style.Colors[ImGuiCol_ChildBg] = ImAdd::HexToColorVec4(0x402B2B, 1.0f);

        style.Colors[ImGuiCol_Text] = ImAdd::HexToColorVec4(0xFFFFFF, 1.0f);
        style.Colors[ImGuiCol_CheckMark] = style.Colors[ImGuiCol_Text];
        style.Colors[ImGuiCol_TextDisabled] = ImAdd::HexToColorVec4(0xAF9191, 1.0f);

        style.Colors[ImGuiCol_SliderGrab] = ImAdd::HexToColorVec4(0xFF9999, 1.0f);
        style.Colors[ImGuiCol_SliderGrabActive] = ImAdd::HexToColorVec4(0xDA8585, 1.0f);

        style.Colors[ImGuiCol_ScrollbarGrab] = ImAdd::HexToColorVec4(0x402B2B, 1.0f);
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImAdd::HexToColorVec4(0x402B2B, 1.0f);
        style.Colors[ImGuiCol_ScrollbarGrabActive] = ImAdd::HexToColorVec4(0x402B2B, 1.0f);

        style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0, 0, 0, 0);

        style.Colors[ImGuiCol_TextSelectedBg] = style.Colors[ImGuiCol_SliderGrab];

        style.Colors[ImGuiCol_Border] = ImAdd::HexToColorVec4(0x362323, 1.0f);
        style.Colors[ImGuiCol_Separator] = style.Colors[ImGuiCol_Border];

        style.Colors[ImGuiCol_Button] = ImAdd::HexToColorVec4(0x2B1D1D, 1.0f);
        style.Colors[ImGuiCol_ButtonHovered] = ImAdd::HexToColorVec4(0x2B1D1D, 0.7f);
        style.Colors[ImGuiCol_ButtonActive] = ImAdd::HexToColorVec4(0x2B1D1D, 0.5f);

        style.Colors[ImGuiCol_FrameBg] = ImAdd::HexToColorVec4(0x2B1D1D, 1.0f);
        style.Colors[ImGuiCol_FrameBgHovered] = ImAdd::HexToColorVec4(0x2B1D1D, 0.7f);
        style.Colors[ImGuiCol_FrameBgActive] = ImAdd::HexToColorVec4(0x2B1D1D, 0.5f);

        style.Colors[ImGuiCol_Header] = ImAdd::HexToColorVec4(0x402B2B, 1.0f);
        style.Colors[ImGuiCol_HeaderHovered] = ImAdd::HexToColorVec4(0x402B2B, 0.7f);
        style.Colors[ImGuiCol_HeaderActive] = ImAdd::HexToColorVec4(0x402B2B, 0.5f);
        break;
    default:
        // Backgrounds
        style.Colors[ImGuiCol_WindowBg] = ImAdd::HexToColorVec4(0x1F1F1F, 1.0f);
        style.Colors[ImGuiCol_PopupBg] = ImAdd::HexToColorVec4(0x272727, 1.0f);
        style.Colors[ImGuiCol_ChildBg] = ImAdd::HexToColorVec4(0x2F2F2F, 1.0f);

        // Text
        style.Colors[ImGuiCol_Text] = ImAdd::HexToColorVec4(0xFFFFFF, 1.0f);
        style.Colors[ImGuiCol_TextDisabled] = ImAdd::HexToColorVec4(0xA2A2A2, 1.0f);
        style.Colors[ImGuiCol_TextSelectedBg] = ImAdd::HexToColorVec4(0xd8a1fc, 1.0f);  // Changed to pinkish-purple

        // CheckMark
        style.Colors[ImGuiCol_CheckMark] = ImAdd::HexToColorVec4(0xFFFFFF, 1.0f);

        // Sliders
        style.Colors[ImGuiCol_SliderGrab] = ImAdd::HexToColorVec4(0xd8a1fc, 1.0f);  // Changed to pinkish-purple
        style.Colors[ImGuiCol_SliderGrabActive] = ImAdd::HexToColorVec4(0xb67fdf, 1.0f);  // Slightly darker pinkish-purple


        // Scrollbars
        style.Colors[ImGuiCol_ScrollbarGrab] = ImAdd::HexToColorVec4(0x2F2F2F, 1.0f);
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImAdd::HexToColorVec4(0x2F2F2F, 1.0f);
        style.Colors[ImGuiCol_ScrollbarGrabActive] = ImAdd::HexToColorVec4(0x2F2F2F, 1.0f);
        style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0, 0, 0, 0);

        // Borders
        style.Colors[ImGuiCol_Border] = ImAdd::HexToColorVec4(0x272727, 1.0f);
        style.Colors[ImGuiCol_Separator] = ImAdd::HexToColorVec4(0x272727, 1.0f);

        // Buttons
        style.Colors[ImGuiCol_Button] = ImAdd::HexToColorVec4(0x1F1F1F, 1.0f);
        style.Colors[ImGuiCol_ButtonHovered] = ImAdd::HexToColorVec4(0x1F1F1F, 0.7f);
        style.Colors[ImGuiCol_ButtonActive] = ImAdd::HexToColorVec4(0x1F1F1F, 0.5f);

        // Frames
        style.Colors[ImGuiCol_FrameBg] = ImAdd::HexToColorVec4(0x1F1F1F, 1.0f);
        style.Colors[ImGuiCol_FrameBgHovered] = ImAdd::HexToColorVec4(0x1F1F1F, 0.7f);
        style.Colors[ImGuiCol_FrameBgActive] = ImAdd::HexToColorVec4(0x1F1F1F, 0.5f);

        // Headers
        style.Colors[ImGuiCol_Header] = ImAdd::HexToColorVec4(0x2F2F2F, 1.0f);
        style.Colors[ImGuiCol_HeaderHovered] = ImAdd::HexToColorVec4(0x2F2F2F, 0.7f);
        style.Colors[ImGuiCol_HeaderActive] = ImAdd::HexToColorVec4(0x2F2F2F, 0.5f);
        break;
    }
}

void CGui::Shutdown()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void CGui::PreRender()
{
    if (globals::IsClosing)
        return;

    ApplyTheme();

    ImGuiStyle& style = ImGui::GetStyle();

    const float SideBarWidth = 144;

    {
        static ImVec2 MenuSize = ImVec2(570, 726);
        ImGui::SetNextWindowSize(MenuSize, ImGuiCond_Once);
        ImGui::SetNextWindowPos(ImGui::GetIO().DisplaySize / 2 - MenuSize / 2, ImGuiCond_Once);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::SetNextWindowSizeConstraints(MenuSize, {9999, 9999});
        ImGui::Begin("menu", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground);
        ImGui::PopStyleVar(2);

        // Renders
        {
            ImVec2 pos = ImGui::GetWindowPos();
            ImVec2 size = ImGui::GetWindowSize();
            ImDrawList* drawList = ImGui::GetWindowDrawList();

            drawList->AddRectFilled(pos, pos + ImVec2(SideBarWidth, size.y), ImGui::GetColorU32(ImGuiCol_WindowBg), style.WindowRounding, ImDrawFlags_RoundCornersLeft);
            drawList->AddRectFilled(pos + ImVec2(SideBarWidth, 0), pos + size, ImGui::GetColorU32(ImGuiCol_PopupBg), style.WindowRounding, ImDrawFlags_RoundCornersRight);
        }

        // Content
        {
            ImGui::BeginChild("SideBar", ImVec2(SideBarWidth, 0), ImGuiChildFlags_Border, ImGuiWindowFlags_NoBackground);
            {
                ImGui::PushStyleColor(ImGuiCol_Border, ImVec4());
                ImGui::BeginChild("LogoRect", ImVec2(0, ImGui::GetFontSize() + style.WindowPadding.y * 2), ImGuiChildFlags_Border);
                ImGui::PopStyleColor();
                {
                    ImGui::SetCursorPos({ ImGui::GetWindowWidth() / 2 - ImGui::CalcTextSize(std::string("Mocha " + std::string(TOSTRING(GIT_COMMIT_HASH))).c_str()).x / 2, style.WindowPadding.y });
                    ImGui::BeginGroup();
                    {
                        ImGui::Text("Mocha");
                        ImGui::SameLine(ImGui::CalcTextSize("Mocha").x);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 4);
                        ImGui::TextDisabled(std::string(" " + std::string(TOSTRING(GIT_COMMIT_HASH))).c_str());
                    }
                    ImGui::EndGroup();
                }
                ImGui::EndChild();

                ImVec2 radioSize = ImVec2(ImGui::GetWindowWidth() - style.WindowPadding.x * 2, 0);

                ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, style.ChildRounding);
                ImGui::PushStyleColor(ImGuiCol_FrameBg, style.Colors[ImGuiCol_PopupBg]);
                {
                    ImAdd::SeparatorText("PLAYER");
                    {
                        ImAdd::RadioFrameIcon(GetTabName(MenuPage_Combat), GetTabIconTexture(MenuPage_Combat, iSelectedPage == MenuPage_Combat), &iSelectedPage, MenuPage_Combat, radioSize);
                        ImAdd::RadioFrameIcon(GetTabName(MenuPage_Movement), GetTabIconTexture(MenuPage_Movement, iSelectedPage == MenuPage_Movement), &iSelectedPage, MenuPage_Movement, radioSize);
#ifndef CHEAP
                        ImAdd::RadioFrameIcon(GetTabName(MenuPage_Misc), GetTabIconTexture(MenuPage_Misc, iSelectedPage == MenuPage_Misc), &iSelectedPage, MenuPage_Misc, radioSize);
#endif
                        ImAdd::RadioFrameIcon(GetTabName(MenuPage_Visuals), GetTabIconTexture(MenuPage_Visuals, iSelectedPage == MenuPage_Visuals), &iSelectedPage, MenuPage_Visuals, radioSize);
                    }
                    ImAdd::SeparatorText("NETWORK");
                    {
                        ImAdd::RadioFrameIcon(GetTabName(MenuPage_AntiExploits), GetTabIconTexture(MenuPage_AntiExploits, iSelectedPage == MenuPage_AntiExploits), &iSelectedPage, MenuPage_AntiExploits, radioSize);
#ifndef CHEAP
                        ImAdd::RadioFrameIcon(GetTabName(MenuPage_Exploits), GetTabIconTexture(MenuPage_Exploits, iSelectedPage == MenuPage_Exploits), &iSelectedPage, MenuPage_Exploits, radioSize);
                        ImAdd::RadioFrameIcon(GetTabName(MenuPage_Playerlist), GetTabIconTexture(MenuPage_Playerlist, iSelectedPage == MenuPage_Playerlist), &iSelectedPage, MenuPage_Playerlist, radioSize);
#endif
                        ImAdd::RadioFrameIcon(GetTabName(MenuPage_AssetsSpawn), GetTabIconTexture(MenuPage_AssetsSpawn, iSelectedPage == MenuPage_AssetsSpawn), &iSelectedPage, MenuPage_AssetsSpawn, radioSize);
#ifndef CHEAP
                        ImAdd::RadioFrameIcon(GetTabName(MenuPage_ItemsSpawn), GetTabIconTexture(MenuPage_ItemsSpawn, iSelectedPage == MenuPage_ItemsSpawn), &iSelectedPage, MenuPage_ItemsSpawn, radioSize);
#endif
                    }
                    ImAdd::SeparatorText("SETTINGS");
                    {
                        ImAdd::RadioFrameIcon(GetTabName(MenuPage_Configs), GetTabIconTexture(MenuPage_Configs, iSelectedPage == MenuPage_Configs), &iSelectedPage, MenuPage_Configs, radioSize);
                        ImAdd::RadioFrameIcon(GetTabName(MenuPage_Themes), GetTabIconTexture(MenuPage_Themes, iSelectedPage == MenuPage_Themes), &iSelectedPage, MenuPage_Themes, radioSize);
                    }
#ifndef PROD
                    ImAdd::SeparatorText("DEVELOPER");
                    {
                        ImAdd::RadioFrameIcon(GetTabName(MenuPage_TestMenu), GetTabIconTexture(MenuPage_TestMenu, iSelectedPage == MenuPage_TestMenu), &iSelectedPage, MenuPage_TestMenu, radioSize);
                        ImAdd::RadioFrameIcon(GetTabName(MenuPage_Api), GetTabIconTexture(MenuPage_Api, iSelectedPage == MenuPage_Api), &iSelectedPage, MenuPage_Api, radioSize);
                    }
#endif
                }
                ImGui::PopStyleColor();
                ImGui::PopStyleVar();
            }

            ImGui::EndChild();
            ImGui::SameLine(SideBarWidth);
            ImGui::BeginChild("Content", ImVec2(0, 0), ImGuiChildFlags_Border, ImGuiWindowFlags_NoBackground);
            {
                ImGui::BeginChild("PageIcon", ImVec2(ImGui::GetFontSize() + m_Fonts.BigFont->FontSize + style.ItemInnerSpacing.y * 3, ImGui::GetFontSize() + m_Fonts.BigFont->FontSize + style.ItemInnerSpacing.y * 3));
                {
                    ImGui::SetCursorPos(ImGui::GetWindowSize() / 2 - ImVec2(ImGui::GetFontSize(), ImGui::GetFontSize()) / 2);
                    ImGui::Image(GetTabIconTexture(iSelectedPage, true), ImVec2(ImGui::GetFontSize(), ImGui::GetFontSize()), ImVec2(0, 0), ImVec2(1, 1), style.Colors[ImGuiCol_SliderGrab]);
                }
                ImGui::EndChild();
                ImGui::SameLine();
                ImGui::BeginGroup();
                {
                    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, style.ItemInnerSpacing);
                    {
                        ImGui::Spacing();
                        ImGui::PushFont(m_Fonts.BigFont);
                        {
                            ImGui::Text(GetTabName(iSelectedPage));
                        }
                        ImGui::PopFont();
                        ImGui::TextDisabled(GetTabDescription(iSelectedPage));
                    }
                    ImGui::PopStyleVar();
                }
                ImGui::EndGroup();

                switch (iSelectedPage)
                {
                case MenuPage_Combat:
                    CombatTab(style);
                    break;
                case MenuPage_Movement:
                    MovementTab(style);
                    break;
#ifndef CHEAP
                case MenuPage_Misc:
                    MiscTab(style);
                    break;
#endif
                case MenuPage_Visuals:
                    VisualsTab(style);
                    break;
#ifndef CHEAP
                case MenuPage_Exploits:
                    ExploitsTab(style);
                    break;
                case MenuPage_Playerlist:
                    PlayerListTab(style);
                    break;
#endif
                case MenuPage_AssetsSpawn:
                    AssetsSpawnTab(style);
                    break;
#ifndef CHEAP
                case MenuPage_ItemsSpawn:
                    ItemsSpawnTab(style);
                    break;
#endif
                case MenuPage_Configs:
                    ConfigsTab(style);
                    break;
                case MenuPage_Themes:
                    ThemesTab(style);
                    break;
                case MenuPage_AntiExploits:
                    AntiExploitsTab(style);
                    break;
#ifndef PROD
                case MenuPage_TestMenu:
                    TestTab(style);
                    break;
                case MenuPage_Api:
                    ApiTab(style);
                    break;
#endif
                default:
                    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, style.ItemInnerSpacing);
                    ImGui::PushFont(m_Fonts.BigFont);
                    {
                        ImGui::TextDisabled("Unknown Tab");
                    }
                    ImGui::PopFont();
                    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4());
                    ImGui::BeginChild("Unknown Tab", ImVec2(0, (ImGui::GetFontSize() * 2 + style.WindowPadding.y * 4 + style.ItemInnerSpacing.y) + (style.WindowPadding.y * 2 + ImGui::GetFontSize() * 6 + style.ItemInnerSpacing.y * 3) + (ImGui::GetFontSize() + style.WindowPadding.y * 2) * 10), ImGuiChildFlags_Border);
                    ImGui::PopStyleColor();
                    ImGui::PopStyleVar();
                    {
                        ImGui::SetCursorPos(ImGui::GetWindowSize() / 2 - ImGui::CalcTextSize("Unknow Content") / 2);
                        ImGui::TextDisabled("Unknow Content");
                    }
                    ImGui::EndChild();
                    break;
                }
            }
            ImGui::EndChild();
        }
        ImGui::End();
    }

}

void CGui::Render() {
    ImGui::Render();

    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

const char* CGui::GetTabName(int ID) {
    switch (ID)
    {
    case MenuPage_Combat:
        return "Combat";
        break;
    case MenuPage_Movement:
        return "Movement";
        break;
    case MenuPage_Misc:
        return "Misc";
        break;
    case MenuPage_Visuals:
        return "Visuals";
        break;
    case MenuPage_Exploits:
        return "Exploits";
        break;
    case MenuPage_Playerlist:
        return "Player List";
        break;
    case MenuPage_AssetsSpawn:
        return "Assets Spawn";
        break;
    case MenuPage_ItemsSpawn:
        return "Items Spawn";
        break;
    case MenuPage_Configs:
        return "Configs";
        break;
    case MenuPage_Themes:
        return "Themes";
        break;
    case MenuPage_TestMenu:
        return "Test Menu";
        break;
    case MenuPage_AntiExploits:
        return "Anti-Exploits";
        break;
    case MenuPage_Api:
        return "Api";
        break;
    default:
        return "*UNKNOW*";
        break;
    }
}

const char* CGui::GetTabDescription(int ID) {
    switch (ID)
    {
    case MenuPage_Combat:
        return "\"Ion trust no man without no blicky\" - Latto";
        break;
    case MenuPage_Movement:
        return "Billions must fly!";
        break;
    case MenuPage_Misc:
        return "Collection of various uncategorizable modules.";
        break;
    case MenuPage_Visuals:
        return "Shooting at red boxes since 1999.";
        break;
    case MenuPage_Exploits:
        return "Supremium watching his bonus fly away.";
        break;
    case MenuPage_Playerlist:
        return "List of victims, I mean, players. :)";
        break;
    case MenuPage_AssetsSpawn:
        return "Spawn various prefabs.";
        break;
    case MenuPage_ItemsSpawn:
        return "Spawn various prefabs. Royalty Required!";
        break;
    case MenuPage_Configs:
        return "Save or load configs. Located in /Mocha folder.";
        break;
    case MenuPage_Themes:
        return "Choose your client theme.";
        break;
    case MenuPage_TestMenu:
        return "\"Skliggas OnTop\" - Advait 2020";
        break;
    case MenuPage_AntiExploits:
        return "Doing Supremium's job right here.";
        break;
    case MenuPage_Api:
        return "Chai rewrite when? 10 years.";
        break;
    default:
        return "*UNKNOW* Description Here ...";
        break;
    }
}

ImTextureID CGui::GetTabIconTexture(int ID, bool bFilled) {

    switch (ID)
    {
    case MenuPage_Combat:
        return bFilled ? m_pTextures->tGunFilled : m_pTextures->tGun;
        break;
    case MenuPage_Movement:
        return bFilled ? m_pTextures->tWingFilled : m_pTextures->tWing;
        break;
    case MenuPage_Misc:
        return bFilled ? m_pTextures->tCubeFilled : m_pTextures->tCube;
        break;
    case MenuPage_Visuals:
        return bFilled ? m_pTextures->tPencilFilled : m_pTextures->tPencil;
        break;
    case MenuPage_Exploits:
        return bFilled ? m_pTextures->tWarnFilled : m_pTextures->tWarnOutlines;
        break;
    case MenuPage_Playerlist:
        return bFilled ? m_pTextures->tUsersFilled : m_pTextures->tUsersOutlines;
        break;
    case MenuPage_AssetsSpawn:
        return bFilled ? m_pTextures->tMedkitFilled : m_pTextures->tMedkitOutlines;
        break;
    case MenuPage_ItemsSpawn:
        return bFilled ? m_pTextures->tItemsFilled : m_pTextures->tItemsOutlines;
        break;
    case MenuPage_Configs:
        return bFilled ? m_pTextures->tGearFilled : m_pTextures->tGearOutlines;
        break;
    case MenuPage_Themes:
        return bFilled ? m_pTextures->tUiFilled : m_pTextures->tUiOutlines;
        break;
    case MenuPage_TestMenu:
        return bFilled ? m_pTextures->tTestFilled : m_pTextures->tTest;
        break;
    case MenuPage_AntiExploits:
        return bFilled ? m_pTextures->tToolsFilled : m_pTextures->tToolsOutlines;
        break;
    case MenuPage_Api:
        return bFilled ? m_pTextures->tApiFilled : m_pTextures->tApiOutlines;
        break;
    default:
        return m_pTextures->tList;
        break;
    }
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
bool CGui::MsgProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
    return ImGui_ImplWin32_WndProcHandler(hwnd, umsg, wparam, lparam);
}