#include "main.h"
#include "includes.h"
#include "Dependencies/HWBP/hwbp.hpp"
#include "Dependencies/Veh/vampveh.h"

using namespace std;

void OnOverlay();

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // there's a bug here where this thread never ends, probably something in keirohook
    // when DEL keybind is active, it creates a "ghost menu" and blocks user input from rr
    if (uMsg == WM_KEYUP && wParam == VK_DELETE)
    // it's annoying when unloaded, but not priority to fix it. i tried and couldn't - breww
    {
        globals::Open ^= 1;
    }

    if (globals::Open)
    {
        ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
        return true;
    }

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

static bool Init = false;
static bool wasOpenLastFrame = false;

int Initialize();

enum class CursorLockMode
{
    None = 0,
    Locked = 1,
    Confined = 2,
};

static auto previousCursorLockState = CursorLockMode::None;

std::chrono::steady_clock::time_point lastExecutionTime250 = std::chrono::steady_clock::now();
constexpr std::chrono::milliseconds threshold250(120);

static bool RKeyDown = false;

HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{

    if (!Init)
    {
        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
        {
            pDevice->GetImmediateContext(&pContext);
            DXGI_SWAP_CHAIN_DESC sd;
            pSwapChain->GetDesc(&sd);
            window = sd.OutputWindow;
            ID3D11Texture2D* pBackBuffer;
            pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
            if (pBackBuffer != nullptr)
            {
                pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &mainRenderTargetView);
                pBackBuffer->Release();
                oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);

                pTextures = new CTextures();
                bool textures_result = pTextures->Initialize(pDevice);
                if (!textures_result)
                {
                    Log::error("Could not initialize Textures.");
                }

                if (textures_result)
                {
                    bool gui_result = false;

                    pGui = new CGui(pTextures);
                    gui_result = pGui->Initialize(window, pDevice, pContext);
                    if (!gui_result)
                    {
                        Log::error("Could not initialize Gui.");
                    }
                }

                Initialize();

                Init = true;
                Log::log("ImGui initialized.");
            }
            else
            {
                Log::error("ImGui pBackBuffer is NULL.");
            }
        }

        else
            return oPresent(pSwapChain, SyncInterval, Flags);
    }
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();

    ImGui::NewFrame();

    ImGui::GetIO().MouseDrawCursor = globals::Open;

    ThreadFix();

    if (GetAsyncKeyState(0x52) & 0x8000)
    {
        // 0x52 is the R key and 0x8000 is being pressed
        if (!RKeyDown)
        {
            RKeyDown = true;
            globals::fov::zoomState = true;
        }
    }
    else
    {
        globals::fov::zoomState = false;
        RKeyDown = false;
    }

    // update playerlist
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime250 = currentTime - lastExecutionTime250;

    if (elapsedTime250 > threshold250)
    {
        // only every 250ms
        if (!globals::updatePlayerlistOnUpdate && pHookManager->hookPriority == HookManager::HookType::INLINE)
        {
            PlayerlistUpdate();
            ForceMasterClient();
        }

        /*
        if (pHookManager->hookPriority == HookManager::HookType::PAGEGUARD)
        {
            ThreadFix();
            PlayerlistUpdate();
            ForceMasterClient();
            ShaderChamsLogic();
            CircuitsDisablerLogic();
            
            if (bool& iOnUpdate = globals::veh::onUpdate;
                !globals::onUpdate::callbackQueue.empty())
            {
                iOnUpdate = true;
                pHookManager->UpdateHooks();
                Log::debug("queue not empty updating!");
            }
        }
        */
        
        AutoVanish();
        Cloak();
        SkillGap();
        AutoGun();
        StaticFly();

        lastExecutionTime250 = currentTime;
    }
    //end

    // render overlays
    OnOverlay();

    // render gui

    using get_lockState_t = CursorLockMode(*)();
    auto get_lockState = (get_lockState_t)methods::UnityEngine::Cursor::get_lockState;

    using set_lockState_t = void(*)(CursorLockMode value);
    auto set_lockState = (set_lockState_t)methods::UnityEngine::Cursor::set_lockState;

    if (globals::Open)
    {
        if (!wasOpenLastFrame)
        {
            // unlock cursor
            previousCursorLockState = get_lockState();
            set_lockState(CursorLockMode::None);
            wasOpenLastFrame = true;
        }

#ifndef CHEAP
        PlayerlistLegacy();
        PlayerListWindow();
#endif
        pGui->PreRender();
        if (globals::PopOutPlayerlist)
        {
            ImGuiStyle& style = ImGui::GetStyle();
            pGui->PlayerListGUI(style);
        }
    }
    else if (wasOpenLastFrame)
    {
        // restore original cursor lock state
        if (previousCursorLockState != CursorLockMode::None)
            set_lockState(previousCursorLockState);
        wasOpenLastFrame = false;
    }

    ImGui::Render();
    pContext->OMSetRenderTargets(1, &mainRenderTargetView, nullptr);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    return oPresent(pSwapChain, SyncInterval, Flags);
}

void OnOverlay()
{
#ifdef PROD
	if (clothingEnabled && localPlayerExists)
		clothingEnabled = false;
#endif

    ImGui::PushFont(pGui->m_Fonts.BigFont);
    {
        pGui->notify.Render();
    }
    ImGui::PopFont();

#ifndef PROD

    if (globals::CPPExplorer::open)
        StartExplorer();

#endif

    if (globals::watchMenuTest && (pHookManager->hookPriority == HookManager::HookType::PAGEGUARD))
        pWatchMenuHandler->Update();

    RenderParticles();
    WaterMark();
    ChangelogCreditsWindow();
    esp();
    Chams();
    RainbowSkin();
    HitboxExpander();
    
    {
        if (!localPlayerExists)
        {
            globals::jedi::prefabGameObject = nullptr;
            rapidFireWeaponComponent = nullptr;
            shareCameraPV = nullptr;
            assetsLoaded = false;
            cachedAudioPlayer = nullptr;
            cachedSeat = nullptr;
            cachedTargetHead = nullptr;
        }
    }

#ifndef CHEAP
    dial();
#endif
    aimbotCall(); /// fix this later
    packetfly(); // epic totally an overlay! :D
}

uintptr_t readUintptrFromFile(const char* filename)
{
    uintptr_t value = 0;
    std::ifstream file(filename, std::ios::in | std::ios::binary);
    if (file.is_open())
    {
        file.read(reinterpret_cast<char*>(&value), sizeof(uintptr_t));
        file.close();
    }
    else
    {
        Log::error("[AEAC] Unable to find pipe. Is AEAC/EAC-Patcher missing?");
    }
    return value;
}

void CreateAudioBat()
{
    /// hex of audio.bat script, we can't get a handle to the audio device (because of EAC)
    /// so we're forced to do it through winapi (.bat is easiest)
    const std::string data =
        "\x40\x65\x63\x68\x6F\x20\x6F\x66\x66\x0D\x0A\x70\x6F\x77\x65\x72\x73\x68\x65\x6C\x6C\x20\x2D\x63\x20\x28\x4E\x65\x77\x2D\x4F\x62\x6A\x65\x63\x74\x20\x4D\x65\x64\x69\x61\x2E\x53\x6F\x75\x6E\x64\x50\x6C\x61\x79\x65\x72\x20\x22\x4D\x6F\x63\x68\x61\x2F\x76\x6D\x6F\x64\x2E\x77\x61\x76\x22\x29\x2E\x50\x6C\x61\x79\x53\x79\x6E\x63\x28\x29\x3B\x0D\x0A";

    std::ofstream file("audio.bat", std::ios_base::out | std::ios_base::binary);

    if (file.is_open())
    {
        if (file.tellp() == 0) // Check if the file is empty
        {
            file.write(data.c_str(), data.size());
            file.close();
        }
        else
        {
            file.close();
            Log::debug("audio.bat found.");
        }
    }
    else
    {
        file.close();
        Log::error("Failed to create audio.bat!");
    }
}

void CreateWavFile()
{
    std::vector<unsigned char> data = audioWavData;
    std::string filePath = "Mocha/vmod.wav";

    if (std::filesystem::exists(filePath))
    {
        std::ifstream file(filePath, std::ios_base::binary | std::ios_base::ate);
        if (file.is_open())
        {
            if (file.tellg() > 0)
            {
                file.close();
                Log::debug("vmod.wav found.");
                return;
            }
            file.close();
        }
    }

    std::ofstream file(filePath, std::ios_base::out | std::ios_base::binary);
    if (file.is_open())
    {
        file.write(reinterpret_cast<const char*>(data.data()), data.size());
        file.close();
        if (!file)
        {
            Log::error("Failed writing to vmod.wav!");
        }
    }
    else
    {
        Log::error("Failed to create vmod.wav!");
    }
}

LONG WINAPI ExceptionFixVectoredExceptionHandler(EXCEPTION_POINTERS* ExceptionInfo)
{
    /// yes this works lmao

    return EXCEPTION_EXECUTE_HANDLER;
}

void InitializeHooks()
{
    OnUpdate_o = (OnUpdate_t)methods::RecRoomSystems::InputManager::OnUpdate;
    Instantiate_o = (Instantiate_t)methods::obfuscated::photon::photonInstantiate;
    InstantiateAssets_o = (InstantiateAssets_t)methods::obfuscated::photon::photonInstantiateAssets;
    get_IsFlyingEnabled_o = (get_IsFlyingEnabled_t)methods::RecRoomCoreLocomotion::PlayerMovement::get_IsFlyingEnabled;
    get_Health_o = (get_Health_t)methods::obfuscated::get_Health;
    get_Health2_o = (get_Health_t)methods::obfuscated::get_Health2;
    get_Health3_o = (get_Health_t)methods::obfuscated::get_Health3;
    get_Health4_o = (get_Health_t)methods::obfuscated::get_Health4;
    get_Health5_o = (get_Health_t)methods::obfuscated::get_Health5;
    get_Health6_o = (get_Health_t)methods::obfuscated::get_Health6;
    OpRaiseEvent_o = (OpRaiseEvent_t)methods::obfuscated::photon::OpRaiseEvent;
    set_FieldOfView_o = (set_FieldOfView_t)methods::UnityEngine::Camera::set_fieldOfView;
    OnEvent_o = (OnEvent_t)methods::obfuscated::photon::OnEvent;
    UnityHWID_o = (UnityHWID_t)methods::UnityEngine::SystemInfo::get_deviceUniqueIdentifier;
    SetMasterClient_o = (SetMasterClient_t)methods::obfuscated::photon::setMasterClient;
    OnMasterClientSwitched_o = (OnMasterClientSwitched_t)(GameAssembly + 0x0); // PUNNetworkManager
    AddFlyEnabled_o = (AddFlyEnabled_t)methods::RecRoomCoreLocomotion::PlayerMovement::AddFlyEnabled;
    GetNextGameplayRoomIndex_o = (GetNextGameplayRoomIndex_t)(GameAssembly + 0x1652AB0);
    // obfuscated, one below GetCurrentGameplayRoomIndex()

    /// chai
    CreateUri_o = (CreateUri_t)methods::System::Uri::CreateUri;
    FatalApplicationQuit_o = (FatalApplicationQuit_t)methods::chai::FatalApplicationQuit;
    IsValid_o = (IsValid_t)methods::obfuscated::IsValid;

    /// test hook trampolines
    RequestDropBeacon_o = (RequestDropBeacon_t)(GameAssembly + 0x223ADD0); //! update this shit
    //RaiseCircuitTick60Hz_o = (RaiseCircuitTick60Hz_t)(GameAssembly + 0x82597F0); //! update this shit

    //JoinOrCreateRoom_o = (JoinOrCreateRoom_t)(GameAssembly + 0x0);
    //OnJoinRoomFailed_o = (OnJoinRoomFailed_t)(GameAssembly + 0x0);
    //OpJoinRoom_o = (OpJoinRoom_t)(GameAssembly + 0x0/*0x6349C40 <- from LoadBalancingPeer*/);
    //OpSetPropertiesOfRoom_o = (OpSetPropertiesOfRoom_t)(GameAssembly + 0x0);
    
    GenerateRequestSignature_o = (GenerateRequestSignature_t)(GameAssembly + 0x0); // search term inside RecNet.Runtime NoNamespace -> "(System.String, System.Byte[], System.Int32)"
    
    RpcPlaySample_o = (RpcPlaySample_t)(GameAssembly + 0x1B91830);
    RpcLocalGoToRoom_o = (RpcLocalGoToRoom_t)(GameAssembly + 0x0);
    
    get_InventionPermission_o = (get_InventionPermission_t)(GameAssembly + 0x0);
    get_CanSaveIntoInventions_o = (get_CanSaveIntoInventions_t)(GameAssembly + 0x0);
    get_CanPublishInInventions_o = (get_CanPublishInInventions_t)(GameAssembly + 0x0);

    get_IsOnCooldown_o = (get_IsOnCooldown_t)(GameAssembly + 0x0);
    DoesLocalPlayerOwnKey1_o = (DoesLocalPlayerOwnKey1_t)(GameAssembly + 0x0);
    DoesLocalPlayerOwnKey2_o = (DoesLocalPlayerOwnKey2_t)(GameAssembly + 0x0);

    get_IsDeveloper_o = (get_IsDeveloper_t)(GameAssembly + 0x0);
    get_LocalAccountIsDeveloper_o = (get_LocalAccountIsDeveloper_t)(GameAssembly + 0x0);
    get_HasActiveRRPlusSubscription_o = (get_HasActiveRRPlusSubscription_t)(GameAssembly + 0x0);
    get_LocalAccountIsModerator_o = (get_LocalAccountIsModerator_t)(GameAssembly + 0x0);

    /// toxmod

    CanInitializeToxMod_o = (CanInitializeToxMod_t)(GameAssembly + 0x0);
    PhotonVoiceCreated_o = (PhotonVoiceCreated_t)(GameAssembly + 0x0);
    Start_o = (Start_t)(GameAssembly + 0x0);
    OnFloatAudioFrame_o = (OnFloatAudioFrame_t)(GameAssembly + 0x0);
    //get_ActiveCameraScale_o = (get_ActiveCameraScale_t)(GameAssembly + 0x139EB60);
    
    //pHookManager->AddInlineHook("OnUpdate", globals::Ihooks::OnUpdate, &(PVOID&)OnUpdate_o, OnUpdate_Ihook);
    //pHookManager->AddInlineHook("OnUpdate", globals::Ihooks::OnUpdate, &(PVOID&)OnUpdate_o, OnUpdate_Ihook);
    /*
    pHookManager->AddInlineHook("Instantiate", globals::Ihooks::Instantiate, &(PVOID&)Instantiate_o, Instantiate_Ihook);
    pHookManager->AddInlineHook("InstantiateAssets", globals::Ihooks::InstantiateAssets, &(PVOID&)InstantiateAssets_o, InstantiateAssets_Ihook);
    pHookManager->AddInlineHook("IsFlyingEnabled", globals::Ihooks::get_IsFlyingEnabled, &(PVOID&)get_IsFlyingEnabled_o, get_IsFlyingEnabled_Ihook);

    pHookManager->AddInlineHook("Health", globals::Ihooks::get_Health, &(PVOID&)get_Health_o, get_Health_Ihook);
    pHookManager->AddInlineHook("Health2", globals::Ihooks::get_Health, &(PVOID&)get_Health2_o, get_Health2_Ihook);
    pHookManager->AddInlineHook("Health3", globals::Ihooks::get_Health, &(PVOID&)get_Health3_o, get_Health3_Ihook);
    pHookManager->AddInlineHook("Health4", globals::Ihooks::get_Health, &(PVOID&)get_Health4_o, get_Health4_Ihook);
    pHookManager->AddInlineHook("Health5", globals::Ihooks::get_Health, &(PVOID&)get_Health5_o, get_Health5_Ihook);
    pHookManager->AddInlineHook("Health6", globals::Ihooks::get_Health, &(PVOID&)get_Health6_o, get_Health6_Ihook);
    pHookManager->AddInlineHook("OpRaiseEvent", globals::Ihooks::OpRaiseEvent, &(PVOID&)OpRaiseEvent_o, OpRaiseEvent_Ihook);
    */
    //pHookManager->AddInlineHook("FieldOfView", globals::Ihooks::set_FieldOfView, &(PVOID&)set_FieldOfView_o, set_FieldOfView_Ihook);
    //pHookManager->AddInlineHook("OnEvent", globals::Ihooks::OnEvent, &(PVOID&)OnEvent_o, OnEvent_Ihook);

    //pHookManager->AddInlineHook("UnityHWID", globals::Ihooks::get_deviceUniqueIdentifier, &(PVOID&)UnityHWID_o, UnityHWID_Ihook);
    //pHookManager->AddInlineHook("SetMasterClient", globals::Ihooks::setMasterClient, &(PVOID&)SetMasterClient_o, SetMasterClient_Ihook);
    //pHookManager->AddInlineHook("OnMasterClientSwitched", globals::Ihooks::OnMasterClientSwitched, &(PVOID&)OnMasterClientSwitched_o, OnMasterClientSwitched_Ihook);

    //pHookManager->AddInlineHook("AddFlyEnabled", globals::Ihooks::AddFlyEnabled, &(PVOID&)AddFlyEnabled_o, AddFlyEnabled_Ihook);

    //pHookManager->AddInlineHook("GetNextGameplayRoomIndex", globals::Ihooks::GetNextGameplayRoomIndex, &(PVOID&)GetNextGameplayRoomIndex_o, GetNextGameplayRoomIndex_Ihook);

#ifndef PROD
    /// chai
    //pHookManager->AddInlineHook("chai", globals::Ihooks::chai, &(PVOID&)CreateUri_o, CreateUri_Ihook);
    //pHookManager->AddInlineHook("chai", globals::Ihooks::chai, &(PVOID&)FatalApplicationQuit_o, FatalApplicationQuit_Ihook);
    //pHookManager->AddInlineHook("chai", globals::Ihooks::chai, &(PVOID&)IsValid_o, IsValid_Ihook);
#endif
#ifdef PROD
	pHookManager->AddInlineHook("clothing", globals::Ihooks::chai, &(PVOID&)CreateUri_o, CreateUri_Ihook_PROD);
	pHookManager->AddInlineHook("clothing", globals::Ihooks::chai, &(PVOID&)FatalApplicationQuit_o, FatalApplicationQuit_Ihook);
	pHookManager->AddInlineHook("clothing", globals::Ihooks::chai, &(PVOID&)IsValid_o, IsValid_Ihook);
#endif

    /// test hooks
    //pHookManager->AddInlineHook("RequestDropBeacon", globals::Ihooks::RequestDropBeacon, &(PVOID&)RequestDropBeacon_o, RequestDropBeacon_Ihook);
    //pHookManager->AddInlineHook("RpcPlaySample", globals::Ihooks::RpcPlaySample, &(PVOID&)RpcPlaySample_o, RpcPlaySample_Ihook);

    //pHookManager->AddInlineHook("CV2GoToRoom", globals::Ihooks::CV2GoToRoom, &(PVOID&)CV2GoToRoom_o, CV2GoToRoom_Ihook);
    //pHookManager->AddInlineHook("RpcLocalGoToRoom", globals::Ihooks::RpcLocalGoToRoom, &(PVOID&)RpcLocalGoToRoom_o, RpcLocalGoToRoom_Ihook);

    //pHookManager->AddInlineHook("Inventions", globals::Ihooks::CreationObjectInventions, &(PVOID&)get_InventionPermission_o, get_InventionPermission_Ihook);
    //pHookManager->AddInlineHook("Inventions", globals::Ihooks::CreationObjectInventions, &(PVOID&)get_CanSaveIntoInventions_o, get_CanSaveIntoInventions_Ihook);
    //pHookManager->AddInlineHook("Inventions", globals::Ihooks::CreationObjectInventions, &(PVOID&)get_CanPublishInInventions_o, get_CanPublishInInventions_Ihook);

    /// gun shit
    ///
    /*    
    pHookManager->AddInlineHook("get_IsOnCooldown", globals::Ihooks::get_IsOnCooldown, &(PVOID&)get_IsOnCooldown_o, get_IsOnCooldown_Ihook);

    pHookManager->AddInlineHook("DoesLocalPlayerOwnKey", globals::Ihooks::DoesLocalPlayerOwnKey, &(PVOID&)DoesLocalPlayerOwnKey1_o, DoesLocalPlayerOwnKey1_Ihook);
    pHookManager->AddInlineHook("DoesLocalPlayerOwnKey", globals::Ihooks::DoesLocalPlayerOwnKey, &(PVOID&)DoesLocalPlayerOwnKey2_o, DoesLocalPlayerOwnKey2_Ihook);

    pHookManager->AddInlineHook("get_IsDeveloper", globals::Ihooks::get_IsDeveloper, &(PVOID&)get_IsDeveloper_o, get_IsDeveloper_Ihook);
    pHookManager->AddInlineHook("get_IsDeveloper", globals::Ihooks::get_IsDeveloper, &(PVOID&)get_LocalAccountIsDeveloper_o, get_LocalAccountIsDeveloper_Ihook);
    pHookManager->AddInlineHook("get_HasActiveRRPlusSubscription", globals::Ihooks::get_HasActiveRRPlusSubscription, &(PVOID&)get_HasActiveRRPlusSubscription_o, get_HasActiveRRPlusSubscription_Ihook);
    pHookManager->AddInlineHook("get_LocalAccountIsModerator", globals::Ihooks::get_LocalAccountIsModerator, &(PVOID&)get_LocalAccountIsModerator_o, get_LocalAccountIsModerator_Ihook);

    /// toxmod
    pHookManager->AddInlineHook("DisableToxMod", globals::Ihooks::DisableToxMod, &(PVOID&)CanInitializeToxMod_o, CanInitializeToxMod_Ihook);
    pHookManager->AddInlineHook("DisableToxMod", globals::Ihooks::DisableToxMod, &(PVOID&)PhotonVoiceCreated_o, PhotonVoiceCreated_Ihook);
    pHookManager->AddInlineHook("DisableToxMod", globals::Ihooks::DisableToxMod, &(PVOID&)Start_o, Start_Ihook);
    pHookManager->AddInlineHook("DisableToxMod", globals::Ihooks::DisableToxMod, &(PVOID&)OnFloatAudioFrame_o, OnFloatAudioFrame_Ihook);
    //pHookManager->AddInlineHook("get_ActiveCameraScale", globals::Ihooks::get_ActiveCameraScale, &(PVOID&)get_ActiveCameraScale_o, get_ActiveCameraScale_Ihook);
    */
    //pHookManager->AddInlineHook("shareScreenPerms", globals::Ihooks::shareScreenPerms, &(PVOID&)shareScreenPerms1_o, shareScreenPerms1_Ihook);
    //pHookManager->AddInlineHook("shareScreenPerms", globals::Ihooks::shareScreenPerms, &(PVOID&)shareScreenPerms2_o, shareScreenPerms2_Ihook);
    //pHookManager->AddInlineHook("shareScreenPerms", globals::Ihooks::shareScreenPerms, &(PVOID&)shareScreenPerms3_o, shareScreenPerms3_Ihook);
    //pHookManager->AddInlineHook("shareScreenPerms", globals::Ihooks::shareScreenPerms, &(PVOID&)shareScreenPerms4_o, shareScreenPerms4_Ihook);
    //pHookManager->AddInlineHook("shareScreenPerms", globals::Ihooks::shareScreenPerms, &(PVOID&)shareScreenPerms5_o, shareScreenPerms5_Ihook);

    //pHookManager->AddInlineHook("RaiseCircuitTick60Hz", globals::Ihooks::RaiseCircuitTick60Hz, &(PVOID&)RaiseCircuitTick60Hz_o, RaiseCircuitTick60Hz_Ihook);
    //pHookManager->AddInlineHook("JoinOrCreateRoom", globals::Ihooks::joinOrCreateRoom, &(PVOID&)JoinOrCreateRoom_o, JoinOrCreateRoom_Ihook);
    //pHookManager->AddInlineHook("OnJoinRoomFailed", globals::Ihooks::onJoinRoomFailed, &(PVOID&)OnJoinRoomFailed_o, OnJoinRoomFailed_Ihook);
    //pHookManager->AddInlineHook("OpJoinRoom", globals::Ihooks::OpJoinRoom, &(PVOID&)OpJoinRoom_o, OpJoinRoom_Ihook);
    //pHookManager->AddInlineHook("OpSetPropertiesOfRoom", globals::Ihooks::OpSetPropertiesOfRoom, &(PVOID&)OpSetPropertiesOfRoom_o, OpSetPropertiesOfRoom_Ihook);
    #ifndef PROD
    //pHookManager->AddInlineHook("GenerateRequestSignature", globals::Ihooks::GenerateRequestSignature, &(PVOID&)GenerateRequestSignature_o, GenerateRequestSignature_Ihook);
    #endif
    //pHookManager->AddInlineHook("SetAccessToken", globals::Ihooks::SetAccessToken, &(PVOID&)SetAccessToken_o, SetAccessToken_Ihook);

    //pHookManager->AddPageGuardHook("AddFlyEnabled", globals::veh::fly, (void*)methods::RecRoomCoreLocomotion::PlayerMovement::AddFlyEnabled, &AddFlyEnabled_hook);
    //pHookManager->AddPageGuardHook("Instantiate", globals::veh::itemspawn, (void*)methods::obfuscated::photon::photonInstantiate, &instantiate_hook);
    //pHookManager->AddPageGuardHook("InstantiateAssets", globals::veh::assetspawn, (void*)methods::obfuscated::photon::photonInstantiateAssets, &instantiateAssets_hook);
    //pHookManager->AddPageGuardHook("OnUpdate", globals::veh::onUpdate, (void*)methods::RecRoomSystems::InputManager::OnUpdate, &OnUpdate_hook);
    //pHookManager->AddPageGuardHook("OpRaiseEvent", globals::veh::opRaiseEvent, (void*)methods::obfuscated::photon::OpRaiseEvent, &OpRaiseEvent_hook);
    //pHookManager->AddPageGuardHook("GetNextGameplayRoomIndex", globals::veh::questskip, (void*)(GameAssembly + 0x144F0A0), &GetNextGameplayRoomIndex_hook);
#ifndef PROD
    //pHookManager->AddPageGuardHook("chai", globals::veh::chai, (void*)methods::obfuscated::IsValid, &uTrue_hook);
    //pHookManager->AddPageGuardHook("chai", globals::veh::chai, (void*)methods::chai::FatalApplicationQuit, &uTrue_hook);
#endif

    //pHookManager->UpdateHooks();
    
    //pHookManager->InitializeInlineHooks();
}

int Initialize()
{
    // this exists and is called after gui init to prevent BSOD when crashing here.
    
    AddVectoredExceptionHandler(2, ExceptionFixVectoredExceptionHandler);

    returnSpoofAddress = PatternScan<uint64_t*>("FF 23", BaseAddressUP, SizeOfImageUP);

    IL2CPPAPI::Init();
    IL2CPPAPI::Scan();

    Il2CppDomain* pDomain = il2cpp_domain_get_clean();

    std::stringstream spDomain;
    spDomain << std::uppercase << std::hex << (uintptr_t)pDomain;

    Log::log("pDomain: [0x" + spDomain.str() + "]");

    if (!pDomain)
    {
        Log::error("pDomain = nullptr!");
        Sleep(15000);
        return -1;
    }

    Il2CppThread* pAttachedThread = il2cpp_thread_attach_clean(il2cpp_domain_get_clean());

    std::stringstream spAttachedThread;
    spAttachedThread << std::uppercase << std::hex << (uintptr_t)pAttachedThread;

    Log::log("pAttachedThread: [0x" + spAttachedThread.str() + "]");
    
    if (!methods::initialize())
    {
        Log::error("Failed to initialize methods!");
        return -1;
    } // set method pointers

    pHookManager = new HookManager;


    // 48 89 5C 24 ?? 48 89 6C 24 ?? 48 89 74 24 ?? 57 41 54 41 56 48 83 EC ?? 41 8B E8


    RtlpAddVectoredHandler_o = (RtlpAddVectoredHandler_t)PatternScan<uint64_t*>("48 89 5C 24 ?? 48 89 6C 24 ?? 48 89 74 24 ?? 57 41 54 41 56 48 83 EC ?? 41 8B E8", BaseAddressNtDLL, SizeOfImageNtDLL);
    
    if (RtlpAddVectoredHandler_o != nullptr)
    {
        Log::debug("handler good");
    }

    //Log::debug("shit good");
    
    //veh::Setup();
   // Log::debug("shit good2");
    InitializeHooks();

    
   // Log::debug("TestThread2111");


    //veh::Setup();
    //Log::debug("TestThread211212122111");

    /*
    auto connection = lattedriver::connect();

    if (connection != NULL)
    {
        const uint16_t NtProtectVirtualMemory_restore[] = { /// this can cause issues but idgaf, works for me works for thee
            0x4C, 0x8B, 0xD1, 0xB8, 0x50, 0x00, 0x00, 0x00, 0xF6, 0x04, 0x25, 0x08, 0x03, 0xFE, 0x7F, 0x01
        };

        uint16_t NtProtectVirtualMemory_hooked[16];
        uint32_t current_pid = GetCurrentProcessId();

        /// restore original NtProtectVirtualMemory function (remove supremium's hook)
        lattedriver::read_memory(connection, current_pid, NtProtectVirtualMemory_addr, (uintptr_t)NtProtectVirtualMemory_hooked, sizeof(NtProtectVirtualMemory_hooked));
        lattedriver::protect_memory(connection, current_pid, NtProtectVirtualMemory_addr, sizeof(NtProtectVirtualMemory_restore), PAGE_EXECUTE_READWRITE);
        lattedriver::write(connection, current_pid, NtProtectVirtualMemory_addr, NtProtectVirtualMemory_restore);
        lattedriver::protect_memory(connection, current_pid, NtProtectVirtualMemory_addr, sizeof(NtProtectVirtualMemory_restore), PAGE_EXECUTE_READ);

        lattedriver::disconnect(connection);
        
        Sleep(500); /// must sleep or crash/fail to set hooks
    } else
    {
        lattedriver::disconnect(connection);
    }
    */
     
    //Log::debug("TestThread21123233");
    
    //bool status = veh::Hook((void*)(GameAssembly + 0xD0D280), &OnUpdate_hook);

    //PreformMainLoop_o = (PreformMainLoop_t)PatternScan<uint64_t*>("48 83 EC ? 80 3D ? ? ? ? ? 0F 85 ? ? ? ? 48 89 5C 24", BaseAddressUP, SizeOfImageUP);

    //OnUpdate_o(nullptr, nullptr);
    
    auto& mgr = hook_manager::get();

    //Log::debug("TestThread21112");

    veh::Setup(); // this will init mgr
    
   //mgr.init();

    //Log::debug("TestThread21113");
    
    //void* OnUpdate_otttt = (void*)PatternScan<uint64_t*>("48 83 EC ? 80 3D ? ? ? ? ? 0F 85 ? ? ? ? 48 89 5C 24", BaseAddressUP, SizeOfImageUP);

    //OnUpdate_o = (OnUpdate_t)OnUpdate_otttt;
    
    //Log::debug("TestThread21114");


    // hwbp hooks in order of priority
    // hook 3/4 may be always be applied to the thread
    
    mgr["Sleep"]->hook((void*)OnUpdate_o, (void*)OnUpdate_Ihook);
    mgr["onevent"]->hook((void*)OnEvent_o, (void*)OnEvent_Ihook);
    mgr["opraise"]->hook((void*)OpRaiseEvent_o, (void*)OpRaiseEvent_Ihook);
#ifndef PROD
    mgr["chai2"]->hook((void*)CreateUri_o, (void*)CreateUri_Ihook); // &(PVOID&)CreateUri_o, CreateUri_Ihook);
#endif
    //mgr["chai"]->hook(FatalApplicationQuit_o, uTrue_hook); // (void*)methods::chai::FatalApplicationQuit, &uTrue_hook
    //mgr["fov"]->hook(set_FieldOfView_o, set_FieldOfView_Ihook);
    //mgr["chai3"]->hook(IsValid_o, IsValid_Ihook); // &(PVOID&)CreateUri_o, CreateUri_Ihook); //  &(PVOID&)IsValid_o, IsValid_Ihook);
    //mgr["play"]->hook(RpcPlaySample_o, RpcPlaySample_Ihook);
    //mgr["spawn"]->hook(InstantiateAssets_o, InstantiateAssets_Ihook); // pHookManager->AddInlineHook("InstantiateAssets", globals::Ihooks::InstantiateAssets, &(PVOID&)InstantiateAssets_o, InstantiateAssets_Ihook);

    Log::debug("TestThread2");

    {
        //bool status = veh::Hook((void*)methods::RecRoomCoreLocomotion::PlayerMovement::get_IsFlyingEnabled, &uTrue_hook);
        //bool status = veh::Hook(PreformMainLoop_o, &PreformMainLoop_hook);
        
        veh::Hook((void*)RequestDropBeacon_o, (void*)uNop_hook);

#ifndef PROD
        veh::Hook((void*)FatalApplicationQuit_o, (void*)uTrue_hook); // probably redundant
        // must be pageguard cuz hwbp doesn't apply fast enough on some async calls
        veh::Hook((void*)IsValid_o, (void*)uTrue_hook);
        //veh::Hook((void*)(GameAssembly+0x21367D0), (void*)uFalse_hook);
        //veh::Hook((void*)get_IsFlyingEnabled_o, (void*)uTrue_hook);
#endif
    }

    //OnUpdate_o(nullptr, nullptr);
    

    /// Dial Stuff - WHY??????????????????
#ifndef CHEAP
    buttonNames.at(FREEZE) = "GAS";
    buttonNames.at(DESPAWN) = "Despawn";
    buttonNames.at(SPAWN) = "Spawn";
    buttonNames.at(TELEPORT) = "Teleport";
    buttonNames.at(GRAB) = "Grab";
    buttonNames.at(DROPTOOLS) = "Drop Tools";
    buttonNames.at(BULLETCRASH) = "RAM Crash";
    buttonNames.at(BULLETCRASH) = "RAM Crash";
    buttonNames.at(FLING) = "Fling";
#endif

    cachedObjectType = Type::getType(il2cpp_string_new_spoof("System.Object"));
    cachedPlayerlist = {};

    threadAddr = readUintptrFromFile("temp.txt");

    if (!Configs::Load::LoadConfigs()) { Log::error("Failed to apply auto configs!"); }
    if (!pHookManager->UpdateHooks())
        Log::error("rehook failed!");

    CreateWavFile();
    CreateAudioBat();

    pWatchMenuHandler = new WatchMenuHandler();
    InitializeWatchMenuUI();

#ifdef PROD
	//newThread(&SocketThread, nullptr);
#endif
    
    return 0;
}

int Main()
{
    Log::init();
    Log::log("Logger initialized.");

    static bool Done = false;

    while (!Done)
    {
        if (init(kiero::RenderType::D3D11) == kiero::Status::Success)
        {
            kiero::bind(8, (void**)&oPresent, (void*)hkPresent);
            Log::log("Present Hooked.");
            Done = true;
        }
    }

    return 0;
}
