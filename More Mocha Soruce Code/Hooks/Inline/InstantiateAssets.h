#pragma once
#include "Dependencies/HWBP/hwbp.hpp"

// Quaternion conjugate: (w, x, y, z) -> (w, -x, -y, -z)
Quaternion conjugate(const Quaternion& q) {
    Quaternion result;
    result.w = q.w;
    result.x = -q.x;
    result.y = -q.y;
    result.z = -q.z;
    return result;
}

// Quaternion multiplication: q1 * q2
Quaternion multiply(const Quaternion& q1, const Quaternion& q2) {
    Quaternion result;
    result.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
    result.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
    result.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
    result.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
    return result;
}

// Rotate a vector by a quaternion: q * v * q.conjugate()
Vector3 rotate_by_quaternion(const Quaternion& q, const Vector3& v) {
    // Convert vector to quaternion with w = 0
    Quaternion q_v = {0, v.x, v.y, v.z};
    Quaternion q_conj = conjugate(q);
    Quaternion result = multiply(multiply(q, q_v), q_conj);
    return {result.x, result.y, result.z};
}

float get_yaw(const Quaternion& q) {
    // Assuming Y-axis is up, compute yaw from quaternion
    float siny_cosp = 2 * (q.w * q.y + q.x * q.z);
    float cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
    return atan2(siny_cosp, cosy_cosp);
}

typedef void* (*InstantiateAssets_t)(Il2CppString*, Vector3, Quaternion, Vector3, uint8_t, Il2CppArray*, bool, bool, void*);
InstantiateAssets_t InstantiateAssets_o = nullptr;
static void* __fastcall InstantiateAssets_Ihook(Il2CppString* prefabName, Vector3 position, Quaternion rotation, Vector3 scale, uint8_t group, Il2CppArray* data, bool destroyOnLeave, bool idk, void* methodInfo) {
        
        if (auto& internalGB_enableDataSwap = globals::photon::giftbox::enableDataSwap;
            internalGB_enableDataSwap && (prefabName != nullptr) && std::string(ReadIl2CppString(prefabName)).find("(GiftBox)") != std::string::npos)
        {
            Il2CppArray*& objectArray = data;

            if (auto* dictionaryObject = il2cpp_array_get(objectArray, System::Collections::Generic::Dictionary_2*, 1); // object[Int32, Dictionary`2] ... index 1 is dictionary
                dictionaryObject != nullptr)
            {
                auto& internalGB_targetActorID = globals::photon::giftbox::targetActorID;

                PlayerInfo& targetPlayerInfo = localPlayer;
                
                if (internalGB_targetActorID > 0 && actorMap.contains(static_cast<uint32_t>(internalGB_targetActorID)))
                {
                    PhotonPlayer* targetPP = actorMap[internalGB_targetActorID];
                    if (cachedPlayerlist.contains(targetPP))
                    {
                        targetPlayerInfo = cachedPlayerlist[targetPP];
                    }
                }
                                            
                auto*& _entries = (Array*&)dictionaryObject->_entries2();

                for (int j = 0; j < _entries->max_length; j++) {

                    if (auto* dictionaryEntry = (System::Collections::Generic::Dictionary_2_Entry<uintptr_t, Il2CppObject*>*)_entries->GetValue(j);
                        dictionaryEntry != nullptr) {

                        if ((void*)dictionaryEntry->key == nullptr) continue;
                        if ((void*)dictionaryEntry->value == nullptr) continue;

                        if (dictionaryEntry->key == 28) // key 28 is giftbox recipient's photon actor number
                        {
                            int32_t* pTargetActorID = &targetPlayerInfo.photonActorID;

                            Il2CppObject* targetActorIDObject = il2cpp_value_box_spoof(FindClass("System.Int32"), pTargetActorID);
                            dictionaryEntry->value = targetActorIDObject;

                            _entries->SetValue(dictionaryEntry, j);
                            continue;
                        }

                        if (dictionaryEntry->key == 34) // key 34 is the giftbox json payload
                        {
                            auto valueString = std::string(ReadIl2CppString((Il2CppString*)dictionaryEntry->value));
                        
                            //Log::debug("value va: " + valueString);

                            if (valueString.find("PlayerId") != std::string::npos) // todo: find a better way to check if this is actually payload string
                            {
                                // Xxstoner4lifexX -> 31124221
                                //Log::debug("found data: " + std::string(ReadIl2CppString((Il2CppString*)dictionaryEntry->value)));

                                auto& internalGB_giftType = globals::photon::giftbox::giftType;
                                auto& internalGB_clothingBuffer = globals::photon::giftbox::clothingBuffer;
                                auto& internalGB_messageBuffer = globals::photon::giftbox::messageBuffer;
                                auto& internalGB_tokenAmount = globals::photon::giftbox::tokenAmount;
                                auto& internalGB_giftContext = globals::photon::giftbox::giftContext;

                                switch (internalGB_giftType)
                                {
                                case (globals::photon::giftbox::GiftType::Clothes):
                                    {
                                        dictionaryEntry->value = (Il2CppObject*)WriteIl2CppString(std::string(R"({"Id":0,"PlayerId":)" + std::string(targetPlayerInfo.playerID) + R"(,"FromPlayerId":)" + std::string(targetPlayerInfo.playerID) + R"(,"ConsumableItemDesc":"","AvatarItemType":0,"AvatarItemDesc":")" + std::string(internalGB_clothingBuffer) + R"(","CustomAvatarItemId":null,"EquipmentPrefabName":"","EquipmentModificationGuid":"","CurrencyType":0,"Currency":0,"Xp":0,"GiftContext":)" + std::to_string(internalGB_giftContext) + R"(,"GiftRarity":50,"Message":")" +  std::string(internalGB_messageBuffer) + R"(","Platform":-1,"PlatformsToSpawnOn":-1,"BalanceType":null})").c_str());

                                        break;
                                    }
                                default: // token
                                    dictionaryEntry->value = (Il2CppObject*)WriteIl2CppString(std::string(R"({"Id":0,"PlayerId":)" + std::string(targetPlayerInfo.playerID) + R"(,"FromPlayerId":)" + std::string(targetPlayerInfo.playerID) + R"(,"ConsumableItemDesc":"","AvatarItemType":null,"AvatarItemDesc":"","CustomAvatarItemId":null,"EquipmentPrefabName":"","EquipmentModificationGuid":"","CurrencyType":2,"Currency":)" + std::to_string(internalGB_tokenAmount) + R"(,"Xp":1,"GiftContext":)" + std::to_string(internalGB_giftContext) + R"(,"GiftRarity":50,"Message":")" +  std::string(internalGB_messageBuffer) + R"(","Platform":-1,"PlatformsToSpawnOn":-1,"BalanceType":null})").c_str());

                                    break;
                                }
                                
                                // white hat
                                //dictionaryEntry->value = (Il2CppObject*)WriteIl2CppString(std::string(R"({"Id":0,"PlayerId":)" + targetPlayerID + R"(,"FromPlayerId":)" + localPlayer.playerID + R"(,"ConsumableItemDesc":"","AvatarItemType":0,"AvatarItemDesc":"76369aef-aeda-46d2-996a-cd00594d0543,8XajS2adOEOqzqnLy6-zcQ,P12CUkIg8EuFihGQsvPlxg","CustomAvatarItemId":null,"EquipmentPrefabName":"","EquipmentModificationGuid":"","CurrencyType":0,"Currency":0,"Xp":0,"GiftContext":502,"GiftRarity":50,"Message":"'We are always one step ahead of our hackers.' -Shawn 22/08/2019","Platform":-1,"PlatformsToSpawnOn":-1,"BalanceType":null})").c_str());

                                // tokens
                                //dictionaryEntry->value = (Il2CppObject*)WriteIl2CppString(std::string(R"({"Id":0,"PlayerId":)" + std::string(targetPlayerInfo.playerID) + R"(,"FromPlayerId":)" + std::string(targetPlayerInfo.playerID) + R"(,"ConsumableItemDesc":"","AvatarItemType":null,"AvatarItemDesc":"","CustomAvatarItemId":null,"EquipmentPrefabName":"","EquipmentModificationGuid":"","CurrencyType":2,"Currency":999999999,"Xp":1,"GiftContext":501,"GiftRarity":50,"Message":")" + targetPlayerInfo.DisplayName + R"( <3 - MrBeast6000","Platform":-1,"PlatformsToSpawnOn":-1,"BalanceType":null})").c_str());

                                //Log::debug("swapped data: " + std::string(ReadIl2CppString((Il2CppString*)dictionaryEntry->value)));

                                _entries->SetValue(dictionaryEntry, j);
                            }
                        }
                    }
                }

                if (!targetPlayerInfo.isLocalPlayer && targetPlayerInfo.loadingStage >= LoadingStage::LOADED)
                {
                    auto* playerPlayer = RecRoomPlayer::GetFromActorNumber(targetPlayerInfo.photonActorID);

                    Vector3 playerBody_position = playerPlayer->get_CurrentBodyPosition();
                    Quaternion playerBody_rotation = playerPlayer->GetRotation();

                    float yaw = get_yaw(playerBody_rotation);
                    float yawRad = yaw * 3.1415926535f / 180.0f;  // Convert to radians

                    Quaternion yawRotation;
                    yawRotation.w = cos(yawRad / 2);
                    yawRotation.x = 0;
                    yawRotation.y = sin(yawRad / 2);
                    yawRotation.z = 0;

                    Vector3 forward = {0, 0, 1};
                    Vector3 horizontalForward = rotate_by_quaternion(yawRotation, forward);

                    float d = 1.84f;
                    Vector3 spawnOffset;
                    spawnOffset.x = horizontalForward.x * 1.5 * d;
                    spawnOffset.y = 0;
                    spawnOffset.z = horizontalForward.z * 1.5 * d;

                    position.x = playerBody_position.x + spawnOffset.x;
                    position.y = playerBody_position.y - 0.8f;
                    position.z = playerBody_position.z + spawnOffset.z;

                    rotation = playerBody_rotation;
                }
                
                //auto* giftbox = (GameObject*)InstantiateAssets_o(prefabName, position, rotation, scale, 0, data, destroyOnLeave, idk, methodInfo);
                auto* giftbox = (GameObject*)hook_manager::get()["spawn"]->call<void*>(prefabName, position, rotation, scale, 0, data, destroyOnLeave, idk, methodInfo);

                if (giftbox == nullptr) return giftbox;
                
                if (!targetPlayerInfo.isLocalPlayer)
                {
                    if (auto* giftboxPhotonView = (PhotonView*)giftbox->GetComponent("PhotonView");
                        giftboxPhotonView != nullptr)
                    {
                        giftboxPhotonView->TransferOwnership(targetPlayerInfo.photonPlayer);
                    }
                }
                
                internalGB_enableDataSwap = false;

                return giftbox;
            }
        }
    
    if (!globals::Ihooks::InstantiateAssets)
        return hook_manager::get()["spawn"]->call<void*>(prefabName, position, rotation, scale, group, data, destroyOnLeave, idk, methodInfo);
        //return InstantiateAssets_o(prefabName, position, rotation, scale, group, data, destroyOnLeave, idk, methodInfo);

    bool& debugToggle = globals::instantiateAssets::debugToggle;
    bool& internalVectorsToggle = globals::instantiateAssets::vectorsToggle;
    bool& internalPrefabTypeToggle = globals::instantiateAssets::prefabTypeToggle;
    bool& internalInfinityToggle = globals::instantiateAssets::infinityToggle;
    bool& internalInfinityScaleToggle = globals::instantiateAssets::infinityScaleToggle;
    bool& internalInfinityScaleType = globals::instantiateAssets::infinityScaleType;
    bool& internalReturnTypeFixToggle = globals::instantiateAssets::returnTypeFixToggle;
    bool& internalReturnTypeNULLToggle = globals::instantiateAssets::returnTypeNULLToggle;
    bool& internalAdvancedConfigToggle = globals::instantiateAssets::advancedConfigToggle;
    bool& internalBlackFlashToggle = globals::instantiateAssets::blackFlashToggle;
    bool& internalDespawnToggle = globals::instantiateAssets::despawnToggle;
    int& internalCount = globals::instantiateAssets::Count;

    Il2CppString* internalPrefab = internalPrefabTypeToggle ? WriteIl2CppString(globals::instantiateAssets::prefab.c_str()) : prefabName;

    Vector3 internalScale = globals::instantiateAssets::scale;

    if (debugToggle) {
        const char* debugPrefabName = ReadIl2CppString(prefabName);
        const char* debugSpoofedPrefabName = internalPrefabTypeToggle ? ReadIl2CppString(internalPrefab) : debugPrefabName;
        std::cout
            << "|=---------------------------------------------=|\n"
            << "|             Item Spawn Data Block             |\n"
            << "|=---------------------------------------------=|\n"
            << "[/] Real Prefab: " << debugPrefabName
            << "\n[/] Spoofed Prefab: " << debugSpoofedPrefabName
            << "\n[/] Position: " << position
            << "\n[/] Rotation: " << rotation
            << "\n[/] Scale: " << (globals::instantiateAssets::randomScaleToggle ? internalScale : scale)
            << "\n[/] destroyOnLeave: " << destroyOnLeave
            << "\n[/] Bool: " << idk
            << "\n|=---------------------------------------------=|\n";
    }
    else {
        Log::debug("Item spawned.");
    }

    bool whitelistActive = globals::instantiateAssets::playerSpawnWhitelistToggle || globals::instantiateAssets::polaroidWhitelistToggle;
    bool isWhitelisted = false;
    if (whitelistActive) {
        const char* prefabNameStr = ReadIl2CppString(prefabName);
        isWhitelisted = (globals::instantiateAssets::playerSpawnWhitelistToggle && strcmp(prefabNameStr, "[StandaloneShapeContainer]") == 0) ||
            (globals::instantiateAssets::polaroidWhitelistToggle && strcmp(prefabNameStr, "[Polaroid]") == 0);
        if (!isWhitelisted) {
            internalCount = 0;
        }
    }

    Il2CppString* chosenPrefab = (internalPrefabTypeToggle && (!whitelistActive || isWhitelisted)) ? internalPrefab : prefabName;
    Vector3 chosenPosition = internalVectorsToggle && isWhitelisted ? globals::instantiateAssets::position : position;
    Quaternion chosenRotation = internalVectorsToggle && isWhitelisted ? globals::instantiateAssets::rotation : rotation;
    Vector3 chosenScale = (!globals::instantiateAssets::randomScaleToggle || isWhitelisted) ? internalScale : scale;

    float maxx = 99999993215964691371151521984339247104.000f;
    float minn = -99999993215964691371151521984339247104.000f;

    if (internalInfinityToggle) {

        chosenPosition = { maxx, maxx, minn };
        chosenRotation = { maxx, minn, maxx, minn };

        if (internalInfinityScaleToggle)
            chosenScale = internalInfinityScaleType ? Vector3{ maxx, maxx, maxx } : Vector3{ minn, minn, minn };
    }

    if (internalBlackFlashToggle) {
        chosenPosition = { maxx, maxx, minn };
        chosenRotation = { maxx, minn, maxx, minn };

        chosenPrefab = il2cpp_string_new_spoof("[sandbox_ladder_hook]");

        Il2CppString* returnPrefab = il2cpp_string_new_spoof("[Dart]");

        chosenScale = Vector3{ minn, minn, minn };

        for (int i = 0; i < 8; i++) {
            //InstantiateAssets_o(chosenPrefab, chosenPosition, chosenRotation, chosenScale, 0, nullptr, false, idk, methodInfo);
            hook_manager::get()["spawn"]->call<void*>(chosenPrefab, chosenPosition, chosenRotation, chosenScale, 0, nullptr, false, idk, methodInfo);
        }

        globals::instantiateAssets::blackFlashToggle = false;

        //return InstantiateAssets_o(returnPrefab, position, rotation, Vector3{ 3, 3, 3 }, group, data, destroyOnLeave, idk, methodInfo);
        return hook_manager::get()["spawn"]->call<void*>(returnPrefab, position, rotation, Vector3{ 3, 3, 3 }, group, data, destroyOnLeave, idk, methodInfo);
    }
    
    if (internalAdvancedConfigToggle) {
        const char* internalPrefabName = ReadIl2CppString(prefabName); // yes ik this code can be better but fuck off it's good enough
        if (strcmp(internalPrefabName, "[ShareCamera]") == 0) {
            internalReturnTypeNULLToggle = false;
            internalReturnTypeFixToggle = false;
            internalScale = globals::instantiateAssets::scaleShareCamera; // internal scale cause ??? c++ is dogshit sometimes
            chosenPrefab = WriteIl2CppString(globals::instantiateAssets::prefabShareCamera);
        }

        if (strcmp(internalPrefabName, "[FeedbackTool]") == 0) {
            internalReturnTypeNULLToggle = false;
            internalReturnTypeFixToggle = false;
            internalScale = globals::instantiateAssets::scaleFeedbackTool;
            chosenPrefab = WriteIl2CppString(globals::instantiateAssets::prefabFeedbackTool);
        }

        if (strcmp(internalPrefabName, "[HandheldStreamerCamera]") == 0) {
            internalReturnTypeNULLToggle = false;
            internalReturnTypeFixToggle = true;
            internalScale = globals::instantiateAssets::scaleStreamerCam;
            chosenPrefab = WriteIl2CppString(globals::instantiateAssets::prefabStreamerCam);
        }
    }

    for (int i = 0; i < internalCount; ++i) {

        if (globals::instantiateAssets::randomScaleToggle) {
            internalScale.x = getRandomScale(globals::instantiateAssets::randomScaleX);
            internalScale.y = getRandomScale(globals::instantiateAssets::randomScaleY);
            internalScale.z = getRandomScale(globals::instantiateAssets::randomScaleZ);
        }
        //InstantiateAssets_o(chosenPrefab, chosenPosition, chosenRotation, chosenScale, 0, nullptr, internalDespawnToggle, idk, methodInfo);
        hook_manager::get()["spawn"]->call<void*>(chosenPrefab, chosenPosition, chosenRotation, chosenScale, 0, nullptr, internalDespawnToggle, idk, methodInfo);
    }

    if (internalReturnTypeFixToggle) {
        chosenPrefab = prefabName;
        chosenPosition = position;
        chosenRotation = rotation;
        chosenScale = scale;
    }

    if (internalReturnTypeNULLToggle) {
        chosenPrefab = WriteIl2CppString("");
    }

    //return InstantiateAssets_o(chosenPrefab, chosenPosition, chosenRotation, chosenScale, group, data, destroyOnLeave, idk, methodInfo);
    return hook_manager::get()["spawn"]->call<void*>(chosenPrefab, chosenPosition, chosenRotation, chosenScale, group, data, destroyOnLeave, idk, methodInfo);
}