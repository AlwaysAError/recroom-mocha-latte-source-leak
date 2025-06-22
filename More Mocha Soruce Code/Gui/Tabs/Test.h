#pragma once
#include "../../Hooks/Inline/Small.h"

bool alreadyFoundOne = false;

void GetAllObjects();
void ClearObjects();

void testBtnPress()
{
    Log::debug("Button pressed!");
    GameObject* scrollbar = GameObject::Find(WriteIl2CppString("[WatchMenuRRUIRoot]"));
    Log::debug("Found object.");
    if (scrollbar != nullptr)
    {
        Log::debug("Object not null.");
        GameObject* routerObject = scrollbar->get_transform()->GetChild(0)->GetChild(1)->GetChild(0)->GetChild(0)->
                                              get_gameObject();
        Log::debug("got parent object.");
        Log::debug(ReadIl2CppString(routerObject->GetName()));
        Log::debug("Name printed?");

        int routerChildCount = routerObject->get_transform()->get_ChildCount();
        for (int i = 0; i < routerChildCount; i++)
        {
            if (i != 0)
            {
                routerObject->get_transform()->GetChild(i)->get_gameObject()->set_active(false);
            }
        }
    }
}

void nameChildren(Transform* main)
{
    for (int i = 0; i < main->get_ChildCount(); i++)
    {
        Transform* child = main->GetChild(i);
        Log::debug(
            ReadIl2CppString(child->GetName()) + std::string(" Layer: ") + std::to_string(
                child->get_gameObject()->get_layer()));
        if (child->GetChild(0) != nullptr)
            nameChildren(child);
    }
}

using toStringGuid_t = Il2CppString* (*)(void* guid);

static Il2CppString* toStringGuid(void* guid)
{
    auto func = static_cast<toStringGuid_t>(reinterpret_cast<void*>(methods::System::Guid::toString));
    return func(guid);
}

PhotonView* cachedOriginalPV = nullptr;

struct GiftManager;

using OnGiftPackageReceivedEvent_hook_t = void(*)(GiftManager* instance, Il2CppObject* args);

void __fastcall OnGiftPackageReceivedEvent_hook(GiftManager* instance, Il2CppObject* args)
{
    auto func = static_cast<OnGiftPackageReceivedEvent_hook_t>(reinterpret_cast<void*>(GameAssembly + 0x0));


    Log::debug("precum");
    auto gift = GetField<void*>(args, 16);
    Log::debug("nigger2");

#ifdef testststts
	GetField<int64_t>(gift, 16); // nullable this is likely giftbox id
	GetField<int32_t>(gift, 32); // no idea this is new maybe recipient
	GetField<void*>(gift, 36); // nullable
	GetField<Il2CppString*>(gift, 48); // AvatarItemDescOrHairDyeDesc  ??
	GetField<testshit::AvatarItemType>(gift, 56); // nullable also AvatarItemType
	GetField<Il2CppString*>(gift, 64); // ConsumableItemDesc ??
	//GetField<void*>(gift, 72, nullptr); // MEMBER(System::Nullable<System::Guid>, JEBHHDJLFEH, 72); // probably avatar guid
	GetField<Il2CppString*>(gift, 96); // EquipmentPrefabName ??
	GetField<Il2CppString*>(gift, 104); // EquipmentModificationGuid ??
	GetField<testshit::CurrencyType>(gift, 112); // CurrencyType
	GetField<int32_t>(gift, 116); // Currency ??
	GetField<int32_t>(gift, 120); // XP ??
	GetField<testshit::GiftContext>(gift, 124); // GiftContext
	GetField<testshit::GiftRarity>(gift, 128); // GiftRarity
	GetField<Il2CppString*>(gift, 136); /// this is name of yelllow message this is custom message
	GetField<testshit::PlatformType>(gift, 144); // PlatformType
	GetField<testshit::PlatformMask>(gift, 148); // PlatformMask
	GetField<testshit::StorefrontBalanceType>(gift, 152); // StorefrontBalanceType nullable
	GetField<bool>(gift, 160); // Consumed
	GetField<bool>(gift, 161); // CanSpawnOnCurrentPlatform ??
	GetField<Il2CppString*>(gift, 168); // ErrorMessage ??
	GetField<bool>(gift, 176); // IsValid ??
	GetField<bool>(gift, 177); // IsGifted ??
#endif

    if (gift != nullptr)
    {
        auto guidStuff = GetField<void*>(gift, 72);

        Log::debug("Get Guid Field");

        std::string guidStr = "";

        if (guidStuff != nullptr)
        {
            Il2CppString* il2StrGuid = toStringGuid(guidStuff);
            Log::debug("not a nullptr");
            guidStr = ReadIl2CppString(il2StrGuid);
        }

        Log::debug("gift is good");

        Log::debug(std::string("16: ") + std::to_string(GetField<int64_t>(gift, 16)) + "\n"); // nullable
        Log::debug(std::string("32: ") + std::to_string(GetField<int32_t>(gift, 32)) + "\n");
        Log::debug(std::string("36: ") + std::to_string(GetField<int32_t>(gift, 36)) + "\n"); // nullable
        Log::debug(std::string("48: ") + ReadIl2CppString(GetField<Il2CppString*>(gift, 48)) + "\n");
        Log::debug(std::string("56: ") + std::to_string(GetField<int>(gift, 56)) + "\n"); // nullable
        Log::debug(std::string("64: ") + ReadIl2CppString(GetField<Il2CppString*>(gift, 64)) + "\n");
        Log::debug(std::string("72: ") + guidStr + "\n");
        Log::debug(std::string("96: ") + ReadIl2CppString(GetField<Il2CppString*>(gift, 96)) + "\n");
        Log::debug(std::string("104: ") + ReadIl2CppString(GetField<Il2CppString*>(gift, 104)) + "\n");
        Log::debug(std::string("112: ") + std::to_string(GetField<int>(gift, 112)) + "\n");
        Log::debug(std::string("116: ") + std::to_string(GetField<int32_t>(gift, 116)) + "\n");
        Log::debug(std::string("120: ") + std::to_string(GetField<int32_t>(gift, 120)) + "\n");
        Log::debug(std::string("124: ") + std::to_string(GetField<int>(gift, 124)) + "\n");
        Log::debug(std::string("128: ") + std::to_string(GetField<int>(gift, 128)) + "\n");
        Log::debug(std::string("136: ") + ReadIl2CppString(GetField<Il2CppString*>(gift, 136)) + "\n");
        Log::debug(std::string("144: ") + std::to_string(GetField<int>(gift, 144)) + "\n");
        Log::debug(std::string("148: ") + std::to_string(GetField<int>(gift, 148)) + "\n");
        Log::debug(std::string("152: ") + std::to_string(GetField<int>(gift, 152)) + "\n"); // nullable
        Log::debug(std::string("160: ") + std::to_string(GetField<bool>(gift, 160)) + "\n");
        Log::debug(std::string("161: ") + std::to_string(GetField<bool>(gift, 161)) + "\n");
        //Log::debug(std::string("168: ") + ReadIl2CppString(GetField<Il2CppString*>(gift, 168)) + "\n");
        Log::debug(std::string("176: ") + std::to_string(GetField<bool>(gift, 176)) + "\n");
        Log::debug(std::string("177: ") + std::to_string(GetField<bool>(gift, 177)) + "\n");
    }
    else
    {
        Log::debug("fuck gift");
    }

    return veh::CallOriginal<void>(func, instance, args);
}

void GetScreenSize(int& width, int& height)
{
    width = GetSystemMetrics(SM_CXSCREEN);
    height = GetSystemMetrics(SM_CYSCREEN);
}

// Our hook function
bool WINAPI HookedFunctionVictim(bool cuzzo)
{
    // Log the hook being called
    Log::debug("Hooked function_victim called!");

    // Modify the behavior (optional, in this case, we return true)
    return true; //TrueFunctionVictim(cuzzo); // or perform any other custom logic
}

bool function_victim(bool cuzzo)
{
    Log::debug("eepic shhit");

    return false;
}

void CGui::TestTab(ImGuiStyle& style)
{
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, style.ItemInnerSpacing);
    ImGui::PushFont(m_Fonts.BigFont);
    {
        ImGui::TextDisabled("Test Menu");
    }
    ImGui::PopFont();
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4());
    ImGui::BeginChild("Test Menu", ImVec2(0, (ImGui::GetFontSize() * 2 + style.WindowPadding.y * 4 + style.ItemInnerSpacing.y) + (style.WindowPadding.y * 2 + ImGui::GetFontSize() * 6 + style.ItemInnerSpacing.y * 3) + (ImGui::GetFontSize() + style.WindowPadding.y * 2) * 60), ImGuiChildFlags_Border);
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
    {
        ImGuiColorEditFlags misc_flags = ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_AlphaPreviewHalf | ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_NoOptions;
        
        if (ImGui::Button("Type Shit"))
        {
            EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::TypeShit);
        }

        if (ImGui::Button("hook RpcPlaySample_o"))
        {
            veh::Hook(RpcPlaySample_o, &RpcPlaySample_Ihook);
        }

        if (ImGui::Button("unhook RpcPlaySample_o"))
        {
            veh::Unhook(RpcPlaySample_o);
        }
        
        if (ImGui::Button("Type Shit22222"))
        {
            EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::CuntTest);
        }
        
        if (ImGui::Button("Camera Test"))
        {
            EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::TestCamera);
        }

        if (ImGui::Button("Sigma Digma test Button"))
        {
            DumpDLL("GameAssembly.dll", "ga_dump.bin");
            DumpDLL("UnityPlayer.dll", "up_dump.bin");
        }

        if (ImGui::Button("Disable EACManager"))
        {
            EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::DisableEACManager);
        }

        ImGui::InputTextWithHint("##9021", "Put Room Id Here", &globals::roomIdBuffer);

        ImAdd::ToggleButtonClassic("Watch Menu Test", &globals::watchMenuTest);
        ImAdd::ToggleButtonClassic("RaiseCircuitTick60Hz", &globals::Ihooks::RaiseCircuitTick60Hz);
        ImGui::InputFloat("time scale type shit", &globals::timeScale);

        if (ImGui::Button("Authentication Values"))
        {
            AuthenticationValues* authVals = AuthenticationValues::get_AuthenticationValues();
            if (authVals != nullptr)
            {
                Log::debug("Auth Values NOT nullptr");
                Il2CppString* authValString = authVals->toString();
                Log::debug(ReadIl2CppString(authValString));
                Il2CppString* tokenString = authVals->get_RandomOne();
                Log::debug(ReadIl2CppString(tokenString));
                Il2CppString* tokenString2 = authVals->get_RandomTwo();
                Log::debug(ReadIl2CppString(tokenString2));
                Il2CppString* tokenString3 = authVals->get_RandomThree();
                Log::debug(ReadIl2CppString(tokenString3));
            }
        }

        if (ImGui::Button("Get Values"))
        {
            Il2CppArray* objects = GameObject::FindObjectsOfType("UnityEngine.GameObject");
            for (int i = 0; i < objects->max_length; i++)
            {
                GameObject* object = il2cpp_array_get(objects, GameObject*, i);
                if (object->GetComponent("Photon.Realtime.ConnectionHandler") != nullptr)
                {
                    Log::debug(ReadIl2CppString(object->GetName()));
                    std::string objectName = ReadIl2CppString(object->GetName());
                    if (objectName.find("PhotonMono") != std::string::npos)
                    {
                        auto connectionHandler = static_cast<ConnectionHandler*>(object->GetComponent(
                            "Photon.Realtime.ConnectionHandler"));
                        if (connectionHandler != nullptr)
                        {
                            Log::debug("ConnectionHandler NOT a nullptr");
                            LoadBalancingClient* loadBalancingClient = connectionHandler->get_Client();
                            if (loadBalancingClient != nullptr)
                            {
                                Log::debug("loadBalancingClient NOT a nullptr");
                                AuthenticationValues* authValues = loadBalancingClient->get_authenticationValues();
                                if (authValues != nullptr)
                                {
                                    Log::debug("authValues NOT a nullptr");
                                    auto authParams = GetField<Il2CppString*>(authValues, 24);
                                    if (authParams != nullptr)
                                    {
                                        Log::debug("authParams NOT a nullptr");
                                        Log::debug("Auth params: " + std::string(ReadIl2CppString(authParams)));
                                    }
                                    auto stringToken = GetField<Il2CppString*>(authValues, 40);
                                    if (stringToken != nullptr)
                                    {
                                        Log::debug("stringToken NOT a nullptr");
                                        Log::debug("Token: " + std::string(ReadIl2CppString(stringToken)));
                                    }
                                    auto stringUserId = GetField<Il2CppString*>(authValues, 48);
                                    if (stringUserId != nullptr)
                                    {
                                        Log::debug("stringUserId NOT a nullptr");
                                        Log::debug("User Id: " + std::string(ReadIl2CppString(stringUserId)));
                                    }
                                }
                                Il2CppString* appIdString = loadBalancingClient->get_appId();
                                if (appIdString != nullptr)
                                {
                                    Log::debug("appIdString NOT a nullptr");
                                    Log::debug("App Id: " + std::string(ReadIl2CppString(appIdString)));
                                }
                                Il2CppString* appVersion = loadBalancingClient->get_appVersion();
                                if (appVersion != nullptr)
                                {
                                    Log::debug("appVersion NOT a nullptr");
                                    Log::debug("AppVersion: " + std::string(ReadIl2CppString(appVersion)));
                                }
                                auto masterServerAddressString = GetField<Il2CppString*>(loadBalancingClient, 104);
                                Log::debug(ReadIl2CppString(masterServerAddressString));
                                int encryptionModeString = GetField<int>(loadBalancingClient, 52);
                                Log::debug(std::to_string(encryptionModeString));
                            }
                        }
                    }
                }
            }
            Log::debug("Practicalation 1");
            ServerSettings* serverSettings = ServerSettings::get_serverSettings();
            if (serverSettings != nullptr)
            {
                Log::debug("Server settings is NOT nullptr");
                auto appSettings = GetField<AppSettings*>(serverSettings, 24);
                auto devRegion = GetField<Il2CppString*>(serverSettings, 32);
                Log::debug("Dev Region: " + std::string(ReadIl2CppString(devRegion)));
                if (appSettings != nullptr)
                {
                    Log::debug("App settings is NOT nullptr");
                    auto realtimeAppId = GetField<Il2CppString*>(appSettings, 16);
                    auto chatAppId = GetField<Il2CppString*>(appSettings, 24);
                    auto voiceAppId = GetField<Il2CppString*>(appSettings, 32);
                    auto appVersion = GetField<Il2CppString*>(appSettings, 40);
                    auto serverAddr = GetField<Il2CppString*>(appSettings, 72);
                    int portNum = GetField<int>(appSettings, 80);
                    int protocol = GetField<int>(appSettings, 96);
                    Log::debug(ReadIl2CppString(realtimeAppId));
                    Log::debug(ReadIl2CppString(chatAppId));
                    Log::debug(ReadIl2CppString(voiceAppId));
                    Log::debug(ReadIl2CppString(appVersion));
                    Log::debug(ReadIl2CppString(serverAddr));
                    Log::debug(std::to_string(portNum));
                    Log::debug(std::to_string(protocol));
                }
            }
        }

        if (ImGui::Button("Find RRURL"))
        {
            Il2CppArray* objects = GameObject::FindObjectsOfType("UnityEngine.GameObject");
            for (int i = 0; i < objects->max_length; i++)
            {
                GameObject* object = il2cpp_array_get(objects, GameObject*, i);
                if (object->GetComponent("OBJLMCEEACJ") != nullptr)
                {
                    Log::debug("Shut up nigger.");
                }
            }
        }


        if (ImGui::Button("Get Dissonance Rooms"))
        {
            Il2CppArray* allGameObjects = GameObject::FindObjectsOfType("UnityEngine.GameObject");
            for (int i = 0; i < allGameObjects->max_length; i++)
            {
                GameObject* obj = il2cpp_array_get(allGameObjects, GameObject*, i);
                if (obj->GetComponent("Dissonance.DissonanceComms"))
                {
                    auto dissonanceComms = (DissonanceComms*)obj->GetComponent("Dissonance.DissonanceComms");
                }
                if (obj->GetComponent("Dissonance.RoomName"))
                {
                    Log::debug(ReadIl2CppString(obj->GetName()));
                    auto roomName = (RoomName*)obj->GetComponent("Dissonance.RoomName");
                    Il2CppString* actualRoomName = roomName->get_RoomName();
                    Log::debug(ReadIl2CppString(actualRoomName));
                }
            }
        }

        //ImAdd::ToggleButtonClassic("Dial Rewrite test", &globals::dialRewrite::toggle);

        ImGui::Checkbox("Object Explorer", &globals::CPPExplorer::open);
        if (ImGui::Button("Refresh Objects"))
        {
            GetAllObjects();
        }
        ImGui::SameLine();
        if (ImGui::Button("Clear Objects"))
        {
            ClearObjects();
        }

        if (ImGui::Button("hashtable test lol"))
        {
            Il2CppClass* punmanagerclass = FindClass("PUNNetworkManager");

            if (punmanagerclass != nullptr)
            {
                auto ht = GetStaticField<Hashtable*>(punmanagerclass, "PhotonRoomPropertiesBugWorkaround");

                Log::debug(ReadIl2CppString(ht->ToString()));
            }
        }

        if (ImGui::Button("Print GO"))
        {
            ThreadFix();

            Il2CppArray* objects = UObject::FindObjectsOfType("UnityEngine.GameObject");

            for (int i = 0; i < objects->max_length; i++)
            {
                GameObject* gameObject = il2cpp_array_get(objects, GameObject*, i);

                if (gameObject != nullptr)
                {
                    Log::debug("----------");
                    std::string objname = ReadIl2CppString(gameObject->ToString());

                    Log::debug(objname);

                    Log::debug("----------");

                    /*
                    if (objname.find("Seat") != std::string::npos) {

                        //Il2CppType* componentType = Type::getType(WriteIl2CppString("UnityEngine.Component"));

                        Il2CppArray* components = gameObject->GetComponents("UnityEngine.Component");
                        Log::debug("----------");
                        for (int i = 0; i < components->max_length; i++) {
                            Component* component = il2cpp_array_get(components, Component*, i);

                            Log::debug(ReadIl2CppString(component->GetName()));

                            Type* componentType = (Type*)Type::GetType(component);

                            Log::debug(ReadIl2CppString(componentType->ToString()));

                        }
                        Log::debug("----------");
                    }
                    */
                }
            }
        }

        ImGui::InputInt("Slave Actor-T", &globals::slaveID);

        if (ImGui::Button("Kill All CV2"))
        {
            EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded,
                            Callbacks::killCv2);
        }

        if (ImGui::Button("Join Room"))
        {
            joinRoom();
        }

        if (ImGui::Button("Initialize IHooks"))
        {
            pHookManager->InitializeInlineHooks();
        }

        if (ImGui::Button("cache self pv"))
        {
            cachedOriginalPV = localPlayer.photonView;
        }

        if (ImGui::Button("transfer ownership self pv"))
        {
            cachedOriginalPV->TransferOwnership(localPlayer.photonPlayer);
        }

        ImGui::Separator();

        ImAdd::ToggleButtonClassic("Ihook get_ActiveCameraScale", &globals::Ihooks::get_ActiveCameraScale);
        ImAdd::ToggleButtonClassic("Ihook CreationObjectInventions", &globals::Ihooks::CreationObjectInventions);
        ImAdd::ToggleButtonClassic("Ihook RpcLocalGoToRoom", &globals::Ihooks::RpcLocalGoToRoom);
        ImAdd::ToggleButtonClassic("Ihook CV2GoToRoom", &globals::Ihooks::CV2GoToRoom);
        ImAdd::ToggleButtonClassic("Ihook RpcPlaySample", &globals::Ihooks::RpcPlaySample);
        ImAdd::ToggleButtonClassic("Ihook OnUpdate", &globals::Ihooks::OnUpdate);
        ImAdd::ToggleButtonClassic("Ihook Instantiate ", &globals::Ihooks::Instantiate);
        ImAdd::ToggleButtonClassic("Ihook InstantiateAssets ", &globals::Ihooks::InstantiateAssets);
        ImAdd::ToggleButtonClassic("Ihook get_IsFlyingEnabled ", &globals::Ihooks::get_IsFlyingEnabled);
        ImAdd::ToggleButtonClassic("Ihook get_Health ", &globals::Ihooks::get_Health);
        ImAdd::ToggleButtonClassic("Ihook OpRaiseEvent ", &globals::Ihooks::OpRaiseEvent);
        ImAdd::ToggleButtonClassic("Ihook set_FieldOfView ", &globals::Ihooks::set_FieldOfView);
        ImAdd::ToggleButtonClassic("Ihook OnEvent ", &globals::Ihooks::OnEvent);
        ImAdd::ToggleButtonClassic("Ihook get_deviceUniqueIdentifier ", &globals::Ihooks::get_deviceUniqueIdentifier);
        ImAdd::ToggleButtonClassic("Ihook setMasterClient ", &globals::Ihooks::setMasterClient);
        ImAdd::ToggleButtonClassic("Ihook joinOrCreateRoom ", &globals::Ihooks::joinOrCreateRoom);
        ImAdd::ToggleButtonClassic("Ihook onJoinRoomFailed ", &globals::Ihooks::onJoinRoomFailed);
        ImAdd::ToggleButtonClassic("Ihook OpJoinRoom ", &globals::Ihooks::OpJoinRoom);
        ImAdd::ToggleButtonClassic("Ihook OpSetPropertiesOfRoom ", &globals::Ihooks::OpSetPropertiesOfRoom);
        ImAdd::ToggleButtonClassic("Ihook GenerateRequestSignature ", &globals::Ihooks::GenerateRequestSignature);

        ImGui::Separator();

        ImAdd::ToggleButtonClassic("sHook AddFlyEnabled", &globals::veh::fly);
        ImAdd::ToggleButtonClassic("sHook Instantiate", &globals::veh::itemspawn);
        ImAdd::ToggleButtonClassic("sHook InstantiateAssets", &globals::veh::assetspawn);
        ImAdd::ToggleButtonClassic("sHook OnUpdate", &globals::veh::onUpdate);
        ImAdd::ToggleButtonClassic("sHook OpRaiseEvent", &globals::veh::opRaiseEvent);
        ImAdd::ToggleButtonClassic("sHook GetNextGameplayRoomIndex", &globals::veh::questskip);
        ImAdd::ToggleButtonClassic("sHook IsValid", &globals::veh::chai);
        ImAdd::ToggleButtonClassic("sHook FatalApplicationQuit", &globals::veh::chai);

        if (ImGui::Button("Notification Test"))
        {
            notify.PushNotification<ImVec4(1, 0, 0, 1), 3.0f>(m_pTextures->tExplosion,
                                                              "Hello, I'm a notification! suck ya mum");
        }

        if (ImGui::Button("VMOD ALERT"))
        {
            STARTUPINFO si;
            PROCESS_INFORMATION pi;

            ZeroMemory(&si, sizeof(si));
            si.cb = sizeof(si);
            ZeroMemory(&pi, sizeof(pi));

            if (CreateProcess(nullptr, LPSTR("cmd /c audio.bat"), nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si,
                              &pi))
            {
                CloseHandle(pi.hProcess);
                CloseHandle(pi.hThread);
            }
        }

        if (ImGui::Button("get bearer token"))
        {
            Log::debug("1");
            //void* token = (void*)AccessToken::GetAccessToken();

            Log::debug("13");

            FieldInfo* testinfo = il2cpp_class_get_field_from_name_spoof(FindClass("IEFBLAAHMGC"), "CGGPFBPLCNO");
            Log::debug("132");
            void* value = nullptr;
            if (testinfo != nullptr)
                value = il2cpp_field_get_value_object_spoof(testinfo, AccessToken::GetAccessToken());
            Log::debug("133");
            Log::debug(std::to_string((uintptr_t)value));
        }

        if (ImGui::Button("gift render (tokens)"))
        {
            Il2CppArray* objects = UObject::FindObjectsOfType("UnityEngine.GameObject");

            GiftManager* GiftManagerInstance = nullptr;

            for (int i = 0; i < objects->max_length; i++)
            {
                GameObject* gameObject = il2cpp_array_get(objects, GameObject*, i);

                if (gameObject != nullptr)
                {
                    auto GiftManagerComponent = static_cast<GiftManager*>(gameObject->GetComponent("GiftManager"));

                    if (GiftManagerComponent != nullptr)
                    {
                        ThreadFix();

                        Log::debug("Found GiftManager!");

                        GiftManagerInstance = GiftManagerComponent;
                        Log::debug("epic1");
                        void* gift = GiftPackage::ctor();
                        Log::debug("epic2");
                        if (gift != nullptr)
                        {
                            std::cout << "lp id is : " << (localPlayer.playerID) << std::endl;

                            SetField<int64_t>(gift, 16, 1); // nullable this is likely giftbox id
                            SetField<int32_t>(gift, 32, 1417725497); // no idea this is new maybe recipient
                            SetField<int32_t>(gift, 36, 1); // nullable
                            SetField<Il2CppString*>(gift, 48, il2cpp_string_new_spoof(""));
                            /// should be prefab // AvatarItemDescOrHairDyeDesc  ?? // frOMH6WxDEG1fBqC4_83vg
                            //SetField<void*>(gift, 56, nullptr); // nullable also AvatarItemType
                            SetField<AvatarItemType>(gift, 56, AvatarItemType::Outfit); // nullable also AvatarItemType
                            SetField<Il2CppString*>(gift, 64, il2cpp_string_new_spoof("")); // ConsumableItemDesc ??
                            SetField<void*>(gift, 72, nullptr);
                            // MEMBER(System::Nullable<System::Guid>, JEBHHDJLFEH, 72); // probably avatar guid
                            SetField<Il2CppString*>(gift, 96, il2cpp_string_new_spoof("")); // EquipmentPrefabName ??
                            SetField<Il2CppString*>(gift, 104, il2cpp_string_new_spoof(""));
                            // EquipmentModificationGuid ??
                            SetField<CurrencyType>(gift, 112, CurrencyType::RecCenterTokens); // CurrencyType
                            SetField<int32_t>(gift, 116, 9999999); // Amount Currency
                            SetField<int32_t>(gift, 120, 1); // Amount XP
                            SetField<GiftContext>(gift, 124, GiftContext::NUX_TokensAndDressUp); // GiftContext
                            SetField<GiftRarity>(gift, 128, GiftRarity::Legendary); // GiftRarity
                            SetField<Il2CppString*>(
                                gift, 136, il2cpp_string_new_spoof("'Have fun in one week.' -Supremium 02/2024"));
                            /// this is name of yelllow message this is custom message
                            SetField<PlatformType>(gift, 144, PlatformType::All); // PlatformType
                            SetField<PlatformMask>(gift, 148, PlatformMask::All); // PlatformMask
                            SetField<StorefrontBalanceType>(gift, 152, StorefrontBalanceType::SteamPurchased);
                            // StorefrontBalanceType nullable
                            SetField<bool>(gift, 160, false); // Consumed
                            SetField<bool>(gift, 161, true); // CanSpawnOnCurrentPlatform ??
                            SetField<Il2CppString*>(gift, 168, il2cpp_string_new_spoof("")); // ErrorMessage ??
                            SetField<bool>(gift, 176, true); // IsValid ??
                            SetField<bool>(gift, 177, true); // IsGifted ??

                            GiftManager::GiftPackageReceivedArgs giftargs = {gift, true, true};
                            GiftManagerInstance->OnGiftPackageReceivedEvent(giftargs);
                        }

                        break;
                    }
                }
            }
        }

        if (ImGui::Button("gift unity (whitehat)"))
        {
            EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::Giftbox);
        }

        ImGui::TextDisabled("Unknow content");
    }
    ImGui::EndChild();
}
