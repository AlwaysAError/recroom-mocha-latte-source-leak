#pragma once

#define WIN32_LEAN_AND_MEAN

#define IMGUI_DEFINE_MATH_OPERATORS

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)


bool clothingEnabled = false;

#include "socket.h"

#include <windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <algorithm>
#include <random>
#include <d3d11.h>
#include <dxgi.h>
#include <MinHook.h>
#include <typeinfo>
#include "Dependencies/json.hpp"
#include "Dependencies/toml.hpp"
#include "variant"
#include "ranges"

#include <mutex>
#include <future>
#include <filesystem>

#include "dumper.h"

/*
#include <polyhook2/Detour/x64Detour.hpp>
#include <polyhook2/ZydisDisassembler.hpp>
#include <polyhook2/Exceptions/HWBreakPointHook.hpp>
#include <polyhook2/Exceptions/AVehHook.hpp>
*/

//#define PROD
//#define CHEAP

#include "logger.h"
#include "Dependencies/RetSpoof/spoofcall.h"
#include "globals.h"
#include "scanner.h"
#include "il2cpp.h"



#include "methods.h"

#include "Dependencies/Veh/veh.h"
#include "Hooks/HookHandler.h"

#include "exceptions.h"
#include "Functions.h"
#include "Game/includes.h" // our definations for Unity and Il2Cpp objects

std::vector<int> playerIdBlacklist = {
    1852, 34641, 88815, 347497, 277089, 31469, 1126, 11675, 19517, 3560, 79211,
    439000, 68758, 10665, 16270, 620745, 78666, 366937, 159154, 515033, 638796,
    319444, 170583, 1312288, 272386, 14940, 546806, 2312859, 213838, 203474,
    481690, 316681, 715200, 2527663, 418933, 805144, 2539447, 372074, 1424966,
    733388, 1117791, 1110889, 1751132, 447263, 2172278, 5731079, 2395704,
    2881818, 659865, 156085, 493146, 534186, 4080515, 4530885, 1469774, 613951,
    487637, 68792, 3912774, 1479520, 1210785, 872257, 699089, 1686696, 276676,
    1023994, 2290395, 1457431, 835842, 310916, 1232317, 395439, 655687, 2049822,
    1832582, 7906190, 195175, 3976829, 1671309, 860253, 2859795, 329824, 3710329,
    311311, 9409892, 2135398, 1236914, 6078720, 314074, 791214, 582917, 3083253,
    678296, 622743, 6445187, 3254059, 2208153, 410754, 1155163, 1736331, 2393578,
    20011278, 6597567, 1773739, 2004491, 4412145, 1697550, 4710826, 913154,
    358788, 1195466, 2331343, 352738, 10874001, 6328685, 228577, 4213153, 570960,
    3179695, 39099, 9775057, 345800, 1861473, 1304945, 1230392, 1052288, 5326881,
    11291166, 4105018, 1416963, 527321, 48366317, 2057143, 882822, 45098274,
    8494666, 1467035, 1311378, 156228, 1268602, 15184888, 224166, 4121601,
    8628014, 3747531, 402301, 419974, 1634926, 555477, 1242268, 9526391, 132126,
    4168358, 8493879, 12805529, 144256, 8073816, 672036, 586891, 14138278, 9310239,
    287195, 2641274, 1990632, 686783, 551129, 3294426, 885181, 79245113, 14861915,
    4795658, 730691, 525133315, 11440809, 26875312, 56177294, 65151521, 35341784,
    2312978, 206193, 8406816, 1164707769, 1854809, 538365, 9916, 121916, 1142357,
    128016, 179907, 1717035, 1259740, 1563266, 85088, 489899, 22187222, 5220289,
    13100926, 1461494, 47520, 8618408, 30816030, 254959, 1888434, 3161996, 3946295,
    9942509, 6615476, 11065378, 389368, 14465533, 386806, 17698129, 27886495,
    31033344, 36810857, 32564489, 1276474, 42336157, 59750188, 70413484, 638716,
    2129166, 837406, 3038967, 334909, 5469781, 8359555, 13990274, 1925135981,
    611024799, 1714923, 485186, 6532522, 21409, 19890837, 37408764, 4468918, 786607,
    1690275, 1732198, 8886115, 4944419, 1835229688, 22385053, 198937, 1, 18530946,
    1649158, 2175882, 1819275, 4453911, 5208215, 64462359, 7245979, 21309981,
    1845925, 10527015, 12287016, 1172265, 489899, 556971, 1950380, 18565040,
    369715, 16216953, 71737020, 64753088, 10360396, 103888, 617298, 1142357,
    1977430, 12003416, 2908891, 6169820, 2052959, 1180899, 1814884, 6888038,
    9786604, 21457774, 1532281, 6569595, 2157695
};

bool IsBlacklistedPlayerID(std::vector<int>& vec, int value)
{
    std::sort(vec.begin(), vec.end()); // O(n log n)
    return std::binary_search(vec.begin(), vec.end(), value); // O(log n)
}

std::timed_mutex playerlistMutex;
PlayerInfo localPlayer;
bool localPlayerExists;
std::vector<PhotonPlayer*> photonPlayerlist;
std::unordered_map<PhotonPlayer*, PlayerInfo> livePlayerlist = {};
std::unordered_map<PhotonPlayer*, PlayerInfo> cachedPlayerlist = {};
// the compiler is very picky and wants this here and not in player.h
std::unordered_map<int32_t, PhotonPlayer*> actorMap;
std::vector<int32_t> blockedActorIds;

#include "playerlist.h"

namespace OpRaiseEventCache
{
    void* instance = nullptr;
    BYTE eventCode = NULL;
    Il2CppObject* payload = nullptr;
    void* eventOptions = nullptr;
    void* sendOptions = nullptr;
    static bool eventCached = false;
}

#include "Modules/Callbacks/includes.h"

enum class EventCodes : BYTE
{
    BulkDestroy = 2,
    BulkInstantiate = 1,
    CloseConnection = 203,
    Destroy = 204, // also used for creation???? braindead devs
    DestroyPlayer = 207,
    EACMessage = 3,
    Instantiation = 202, // also Voice
    OMSendChunk = 4,
    OwnershipRequest = 209,
    OwnershipTransfer = 210,
    OwnershipUpdate = 212,
    RemoveCachedRPCs = 205,
    RPC = 200,
    RRBufferedRoomEvent = 22,
    RRClearBufferedRoomEvent = 23,
    RRRoomRequestEvent = 20,
    RRRoomRequestFailedResponseEvent = 21,
    RR_CreationOp = 24,
    RR_CreationOpResponse = 25,
    RR_CreationOp_Unchecked = 26,
    SendSerialize = 201, // aka movement
    SendSerializeReliable = 206,
    VacantViewIds = 211,
};

bool initialDone = false;
void* roomOptionsSaved = nullptr;
void* typedLobbySaved = nullptr;

using joinRoom_t = bool(*)(Il2CppString*, void*, void*, void*);

bool joinRoom()
{
    auto func = static_cast<joinRoom_t>(reinterpret_cast<void*>(GameAssembly + 0x0));
    Il2CppString* newRoom = WriteIl2CppString(globals::roomIdBuffer.c_str());
    return func(newRoom, roomOptionsSaved, typedLobbySaved, nullptr);
}

static RangedWeapon* rapidFireWeaponComponent = nullptr;

#include "playerlistFunctions.h"
#include "Dependencies/imgui/imgui.h"
#include "Dependencies/imgui/imgui_impl_dx11.h"
#include "Dependencies/imgui/imgui_impl_win32.h"
#include "Dependencies/imgui/addons/imgui_stdlib.h"
#include "Dependencies/kiero/kiero.h"
#include "version.h"

static void HelpMarker(const char* desc)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::BeginItemTooltip())
    {
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

#include "Gui/CTextures.h"
#include "Gui/CGui.h"

#include "Gui/Watch/Button.h"
#include "Gui/Watch/ToggleButton.h"
#include "Gui/Watch/Text.h"
#include "Gui/Watch/Handler.h"
#include "Gui/Watch/Callbacks/includes.h"
#include "Gui/Watch/Menu.h"

#include "Hooks/includes.h"
#include "Gui/include.h"
#include "Modules/includes.h"
#include "Overlays/include.h"
#include "Resources/vmodwav.h"
#include "main.h"
