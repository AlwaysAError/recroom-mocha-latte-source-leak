#pragma once
#include "../../globals.h"

typedef bool(*OpRaiseEvent_t)(void*, BYTE, Il2CppObject*, Il2CppObject*, Il2CppObject*, void*);
OpRaiseEvent_t OpRaiseEvent_o = nullptr;

void processEvent(
    Vector3 positionv,
    Vector3 scale,
    int count,
    Il2CppString* prefab,
    void* instance,
    BYTE eventCode,
    Il2CppObject* payload,
    Il2CppObject* raiseEventOptions,
    Il2CppObject* sendOptions,
    void* methodInfo,
    Hashtable* payloadHashtable,
    const globals::opRaiseEventEdit::EditInfo& editInfo

) {
    if (prefab != nullptr && prefab->length > 0) { // Ignore empty strings
        payloadHashtable->set_Item(0, (UObject*)prefab); // Update prefab

        std::string hashtableString = ReadIl2CppString(payloadHashtable->ToString());

        Vector3 position = positionv;
        if (hashtableString.find("(System.Byte)1=(UnityEngine.Vector3)") != std::string::npos) { // Update position
            payloadHashtable->set_Item(1, (UObject*)il2cpp_value_box_spoof(FindClass("UnityEngine.Vector3"), &position));
        }
        else {
            payloadHashtable->Add(1, (UObject*)il2cpp_value_box_spoof(FindClass("UnityEngine.Vector3"), &position));
        }


        Vector3 scaleCopy = scale;
        if (hashtableString.find("(System.Byte)9=(UnityEngine.Vector3)") != std::string::npos) { // Update scale
            payloadHashtable->set_Item(9, (UObject*)il2cpp_value_box_spoof(FindClass("UnityEngine.Vector3"), &scaleCopy));
        }
        else {
            payloadHashtable->Add(9, (UObject*)il2cpp_value_box_spoof(FindClass("UnityEngine.Vector3"), &scaleCopy));
        }

        Type* intType = (Type*)Type::getType(il2cpp_string_new_spoof("System.Int32"));
        int32_t arraySize = editInfo.targetActorIDs.size();
        Il2CppArray* targetActorsArray = Array::createInstance((Il2CppType*)intType, arraySize);

        for (int i = 0; i < targetActorsArray->max_length; i++) {
            il2cpp_array_set(targetActorsArray, int32_t, i, editInfo.targetActorIDs[i]);
        }

        SetField<Il2CppArray*>(raiseEventOptions, 24, targetActorsArray);

        for (int i = 0; i < count; i++) {

            int32_t allocatedPhotonViewID = PhotonNetwork::AllocateViewID(0, false);

            if (hashtableString.find("(System.Byte)7=(System.Int32)") != std::string::npos) { // Allocate photonviewid
                payloadHashtable->set_Item(7, (UObject*)il2cpp_value_box_spoof(FindClass("System.Int32"), &allocatedPhotonViewID));
            }
            else {
                payloadHashtable->Add(7, (UObject*)il2cpp_value_box_spoof(FindClass("System.Int32"), &allocatedPhotonViewID));
            }

            //OpRaiseEvent_o(instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo);
            hook_manager::get()["opraise"]->call<bool>(instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo);
        }
    }
}

bool __fastcall OpRaiseEvent_Ihook(void* instance, BYTE eventCode, Il2CppObject* payload, Il2CppObject* raiseEventOptions, Il2CppObject* sendOptions, void* methodInfo) {

    if (!globals::Ihooks::OpRaiseEvent)
        return hook_manager::get()["opraise"]->call<bool>(instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo);
        //return OpRaiseEvent_o(instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo);

    using namespace globals::photon::antis::outbound;

    bool transferOwnership = false;
    int32_t targetPhotonViewID = 0;
    int32_t ownershipActorNumber = 0;
    
    if (payload != nullptr) {

        auto prettyHashtableString = [](const std::string& text) {
            std::string result;
            for (char c : text) {
                result += c;
                if (c == ',') {
                    result += '\n';
                }
            }
            return result;
            };

        if (blockAllToggle) {
            bool shouldBlock = true;

            if (!blockAntiCheatToggle && eventCode == 3)
                shouldBlock = false;

            if (shouldBlock)
                return false;
        }

        if (eventCode == 200) { // rpc event
            OpRaiseEventCache::instance = instance;
            OpRaiseEventCache::eventCode = eventCode;
            OpRaiseEventCache::payload = payload;
            OpRaiseEventCache::eventOptions = raiseEventOptions;
            OpRaiseEventCache::sendOptions = sendOptions;
            OpRaiseEventCache::eventCached = true;
            globals::opRaiseEventCached = true;
        }

        if (eventCode == 202) {

            if (globals::photon::antis::outbound::squishPlayer) {

                Type* payloadType = (Type*)Type::GetType(payload);
                std::string payloadTypeString = ReadIl2CppString(payloadType->ToString());

                if (payloadTypeString == "Type: Hashtable") {

                    Hashtable* payloadHashtable = (Hashtable*)payload;

                    std::string hashtableString = ReadIl2CppString(payloadHashtable->ToString());

                    if (hashtableString.find("(System.Byte)0=(System.String)") != std::string::npos) {


                        Il2CppString* prefabString = (Il2CppString*)payloadHashtable->get_Item(0);

                        std::string prefabStringString = ReadIl2CppString(prefabString);

                        if (prefabStringString.find("[Player]") != std::string::npos) {

                            Log::debug("Squishing player pre");

                            Vector3 scale = globals::photon::antis::outbound::playerScale;

                            if (hashtableString.find("(System.Byte)9=(UnityEngine.Vector3)") != std::string::npos) { // update scale
                                payloadHashtable->set_Item(9, (UObject*)il2cpp_value_box_spoof(FindClass("UnityEngine.Vector3"), &scale));
                            }
                            else {
                                payloadHashtable->Add(9, (UObject*)il2cpp_value_box_spoof(FindClass("UnityEngine.Vector3"), &scale));
                            }

                            EnqueueCallback(std::chrono::milliseconds(500), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::SetLocalPlayerScale);

                            Log::debug("Squishing player post");

                        }
                    }
                }
            }


            if (auto& internalGB_enableDataSwap = globals::photon::giftbox::enableDataSwap;
                internalGB_enableDataSwap) {
                ///
                ///
                ///

                Type* payloadType = (Type*)Type::GetType(payload);
                std::string payloadTypeString = ReadIl2CppString(payloadType->ToString());

                if (payloadTypeString == "Type: Hashtable")
                {
                    Hashtable* payloadHashtable = (Hashtable*)payload;

                    std::string hashtableString = ReadIl2CppString(payloadHashtable->ToString());
                
                    if (internalGB_enableDataSwap && hashtableString.find("(GiftBox)") != std::string::npos && hashtableString.find("(System.Byte)7=(System.Int32)") != std::string::npos)
                    {

                        if (hashtableString.find("(System.Byte)5=(System.Object[])System.Object[]") != std::string::npos)
                        {
                            Il2CppArray* objectArray = (Il2CppArray*)payloadHashtable->get_Item(5); // byte 5 is object[] data

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

                                Vector3 position{0, 0, 0};
                                Quaternion rotation{0, 0, 0, 0};
                                
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
                                
                                if (hashtableString.find("(System.Byte)1=(UnityEngine.Vector3)") != std::string::npos) { // Update position
                                    payloadHashtable->set_Item(1, (UObject*)il2cpp_value_box_spoof(FindClass("UnityEngine.Vector3"), &position));
                                }

                                auto& iGBPhotonViewId = globals::photon::giftbox::GBPhotonViewId;

                                    if (Il2CppObject* boxedPvid = payloadHashtable->get_Item(7)) // requested photonViewId Int32
                                    {
                                        // key 1 is position

                                        const int32_t* ppvid = static_cast<int32_t*>(il2cpp_object_unbox_spoof(boxedPvid));
                                        iGBPhotonViewId = *ppvid;
                                    }

                                //Log::debug("debug1111");
                                //auto* giftbox = (GameObject*)InstantiateAssets_o(prefabName, position, rotation, scale, 0, data, destroyOnLeave, idk, methodInfo);
                                bool status = hook_manager::get()["opraise"]->call<bool>(instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo);
                                //Log::debug("debug11112");
                                PhotonView* giftBoxPV = PhotonView::findPhotonView(iGBPhotonViewId);
                                //Log::debug("debug11113");
                                if (giftBoxPV != nullptr)
                                {
                                    if (GameObject* giftboxGo = giftBoxPV->get_gameObject();
                                        giftboxGo != nullptr)
                                    {
                                        //Log::debug("debug11114");
                                        if (!targetPlayerInfo.isLocalPlayer)
                                        {
                                            //Log::debug("debug11115");
                                            if (auto* giftboxPhotonView = giftBoxPV; //(PhotonView*)giftboxGo->GetComponent("PhotonView");
                                                giftboxPhotonView != nullptr)
                                            {
                                                //Log::debug("debug11116");
                                                Transform* giftboxTransform = giftboxGo->get_transform();
                                                giftboxTransform->set_rotation(rotation);
                                                giftboxPhotonView->TransferOwnership(targetPlayerInfo.photonPlayer);

                                                // position is de-synced here cuz PUN 1
                                                // so we must set position client side
                                                //giftboxTransform->set_position(position);
                                            }
                                        }
                        
                                        internalGB_enableDataSwap = false;
                                    }
                                }
                                //Log::debug("debug1111777");
                                return status;
                            }
                        }
                    }
                }
                ///
                ///
                ///
            }
            
            if (!globals::opRaiseEventEdit::opRaiseEventEditQueue.empty() && !globals::opRaiseEventEdit::inExecution) { //! using localPlayer ActorID will crash if prefabs mismatch!!!!

                Type* payloadType = (Type*)Type::GetType(payload);
                std::string payloadTypeString = ReadIl2CppString(payloadType->ToString());

                if (payloadTypeString == "Type: Hashtable") {

                    Hashtable* payloadHashtable = (Hashtable*)payload;

                    std::string hashtableString = ReadIl2CppString(payloadHashtable->ToString());

                    if (hashtableString.find("(System.Byte)0=(System.String)") != std::string::npos) { /// if byte 0 is not string this is not an instantiate event

                        globals::opRaiseEventEdit::inExecution = true;

                        Il2CppArray* cachedActorsArray = GetField<Il2CppArray*>(raiseEventOptions, 24); //! raiseEventOptions get reused for some dumb reason so we must revert all changes to this object

                        for (const auto& editInfo : globals::opRaiseEventEdit::opRaiseEventEditQueue) {

                            switch (editInfo.customType) {
                            case (globals::opRaiseEventEdit::EditInfo::CustomType::Die): {

                                Il2CppString* prefabString = (Il2CppString*)payloadHashtable->get_Item(0);

                                if (ReadIl2CppString(prefabString) == globals::opRaiseEventEdit::magicPrefab) {


                                    using namespace globals::crashes::death;

                                    float maxx = 99999993215964691371151521984339247104.000f;
                                    float minn = -99999993215964691371151521984339247104.000f;

                                    int& numDirections = numberOfDirections;   // Number of directions in the circle
                                    int& steps = stepz;         // Number of steps outward
                                    int& count = countz;         // Number of steps outward
                                    float& minY = minYz;  // Minimum y-coordinate
                                    float& maxY = maxYz;   // Maximum y-coordinate (can be adjusted as needed)
                                    float& minScale = minScalez;  // Minimum scale value
                                    float& maxScale = maxScalez;  // Maximum scale value
                                    bool& extras = extraz;

                                    // Parameters for the decay curve
                                    float& decayFactor = decayFactorz;  // The rate at which steps decrease as they go outward

                                    const float PI = 3.14159265358979323846f;

                                    // Step increment for the range
                                    float stepIncrement = (maxx - minn) / steps;

                                    std::vector<std::string> prefabNames = {
                                        //"[Player]",
                                        "[Sandbox_Mirror]",
                                        "[Quest_Scifi_JumbotronBossEnemy]",
                                        "[Quest_Dracula1_DraculaBoss]",
                                        "[sandbox_ladder_hook]",
                                    };
                                    srand(time(0));  // Initialize random seed

                                    // Iterate through directions in a circle
                                    for (int dir = 0; dir < numDirections; dir++) {
                                        // Calculate angle in radians for the current direction
                                        float angle = dir * (2.0f * PI / numDirections);

                                        // Iterate through steps outward
                                        for (int step = 0; step <= steps; step++) {
                                            // Use an exponential decay for the current step value
                                            float currentStep = minn + step * exp(-decayFactor * step);

                                            // Calculate position based on angle and step
                                            Vector3 position;
                                            position.x = currentStep * cos(angle);
                                            position.z = currentStep * sin(angle);

                                            // Generate a random Y position within the range
                                            float randomYPos = minY + static_cast<float>(rand()) / RAND_MAX * (maxY - minY);
                                            position.y = randomYPos;

                                            // Generate random scale values
                                            float randomX = minScale + static_cast<float>(rand()) / RAND_MAX * (maxScale - minScale);
                                            float randomY = minScale + static_cast<float>(rand()) / RAND_MAX * (maxScale - minScale);
                                            float randomZ = minScale + static_cast<float>(rand()) / RAND_MAX * (maxScale - minScale);

                                            Vector3 scale = { randomX, randomY, randomZ };

                                            // Randomly choose a prefab name
                                            int randomIndex = rand() % prefabNames.size();

                                            // Example prefab, adjust as necessary
                                            Il2CppString* prefab = WriteIl2CppString(prefabNames[randomIndex].c_str());

                                            // Call the processEvent lambda
                                            processEvent(position, scale, count, prefab, instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo, payloadHashtable, editInfo);
                                        }
                                        if (extras) {
                                            /*
                                            processEvent({ maxx, -1000, minn }, { 1, 1, 1 }, 10, WriteIl2CppString("[Player]"), instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo, payloadHashtable, editInfo);
                                            processEvent({ minn, -1000, maxx }, { 10, 10, 10 }, 10, WriteIl2CppString("[Player]"), instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo, payloadHashtable, editInfo);
                                            processEvent({ maxx, -1000, maxx }, { 100, 100, 100 }, 10, WriteIl2CppString("[Player]"), instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo, payloadHashtable, editInfo);
                                            processEvent({ minn, -1000, minn }, { 1000, 1000, 1000 }, 10, WriteIl2CppString("[Player]"), instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo, payloadHashtable, editInfo);
                                            processEvent({ 1, -50, 0 }, { maxx, maxx, maxx }, 5, WriteIl2CppString("[Player]"), instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo, payloadHashtable, editInfo);
                                            processEvent({ 1, -50, 0 }, { 1, 1, 1 }, 100, WriteIl2CppString("[Player]"), instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo, payloadHashtable, editInfo);
                                            */
                                            
                                            processEvent({ maxx, -1000, minn }, { 1, 1, 1 }, 10, WriteIl2CppString("[Sandbox_Mirror]"), instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo, payloadHashtable, editInfo);
                                            processEvent({ minn, -1000, maxx }, { 10, 10, 10 }, 10, WriteIl2CppString("[Sandbox_Mirror]"), instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo, payloadHashtable, editInfo);
                                            processEvent({ maxx, -1000, maxx }, { 100, 100, 100 }, 10, WriteIl2CppString("[Sandbox_Mirror]"), instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo, payloadHashtable, editInfo);
                                            processEvent({ minn, -1000, minn }, { 1000, 1000, 1000 }, 10, WriteIl2CppString("[Sandbox_Mirror]"), instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo, payloadHashtable, editInfo);
                                            processEvent({ 0, -50, 1 }, { maxx, maxx, maxx }, 5, WriteIl2CppString("[Sandbox_Mirror]"), instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo, payloadHashtable, editInfo);
                                            processEvent({ 0, -50, 1 }, { 1, 1, 1 }, 100, WriteIl2CppString("[Sandbox_Mirror]"), instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo, payloadHashtable, editInfo);

                                            processEvent({ maxx, -1000, minn }, { 1, 1, 1 }, 10, WriteIl2CppString("[Quest_Scifi_JumbotronBossEnemy]"), instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo, payloadHashtable, editInfo);
                                            processEvent({ minn, -1000, maxx }, { 10, 10, 10 }, 10, WriteIl2CppString("[Quest_Scifi_JumbotronBossEnemy]"), instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo, payloadHashtable, editInfo);
                                            processEvent({ maxx, -1000, maxx }, { 100, 100, 100 }, 10, WriteIl2CppString("[Quest_Scifi_JumbotronBossEnemy]"), instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo, payloadHashtable, editInfo);
                                            processEvent({ minn, -1000, minn }, { 1000, 1000, 1000 }, 10, WriteIl2CppString("[Quest_Scifi_JumbotronBossEnemy]"), instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo, payloadHashtable, editInfo);
                                            processEvent({ 0, -50, 0 }, { maxx, maxx, maxx }, 5, WriteIl2CppString("[Quest_Scifi_JumbotronBossEnemy]"), instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo, payloadHashtable, editInfo);
                                            processEvent({ 0, -50, 0 }, { 1, 1, 1 }, 100, WriteIl2CppString("[Quest_Scifi_JumbotronBossEnemy]"), instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo, payloadHashtable, editInfo);

                                            processEvent({ maxx, -1000, minn }, { 1, 1, 1 }, 10, WriteIl2CppString("[Quest_Dracula1_DraculaBoss]"), instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo, payloadHashtable, editInfo);
                                            processEvent({ minn, -1000, maxx }, { 10, 10, 10 }, 10, WriteIl2CppString("[Quest_Dracula1_DraculaBoss]"), instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo, payloadHashtable, editInfo);
                                            processEvent({ maxx, -1000, maxx }, { 100, 100, 100 }, 10, WriteIl2CppString("[Quest_Dracula1_DraculaBoss]"), instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo, payloadHashtable, editInfo);
                                            processEvent({ minn, -1000, minn }, { 1000, 1000, 1000 }, 10, WriteIl2CppString("[Quest_Dracula1_DraculaBoss]"), instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo, payloadHashtable, editInfo);
                                            processEvent({ 0, -50, 0 }, { maxx, maxx, maxx }, 5, WriteIl2CppString("[Quest_Dracula1_DraculaBoss]"), instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo, payloadHashtable, editInfo);
                                            processEvent({ 0, -50, 0 }, { 1, 1, 1 }, 100, WriteIl2CppString("[Quest_Dracula1_DraculaBoss]"), instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo, payloadHashtable, editInfo);

                                            processEvent({ maxx, -1000, minn }, { 1, 1, 1 }, 10, WriteIl2CppString("[sandbox_ladder_hook]"), instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo, payloadHashtable, editInfo);
                                            processEvent({ minn, -1000, maxx }, { 10, 10, 10 }, 10, WriteIl2CppString("[sandbox_ladder_hook]"), instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo, payloadHashtable, editInfo);
                                            processEvent({ maxx, -1000, maxx }, { 100, 100, 100 }, 10, WriteIl2CppString("[sandbox_ladder_hook]"), instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo, payloadHashtable, editInfo);
                                            processEvent({ minn, -1000, minn }, { 1000, 1000, 1000 }, 10, WriteIl2CppString("[sandbox_ladder_hook]"), instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo, payloadHashtable, editInfo);
                                            processEvent({ 1, -50, 1 }, { maxx, maxx, maxx }, 5, WriteIl2CppString("[sandbox_ladder_hook]"), instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo, payloadHashtable, editInfo);
                                            processEvent({ 1, -50, 1 }, { 1, 1, 1 }, 100, WriteIl2CppString("[sandbox_ladder_hook]"), instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo, payloadHashtable, editInfo);
                                        }
                                    }


                                    std::string playerDiplayName = "DISPLAY NAME NOT FOUND";

                                    {
                                        RecRoomPlayer* playerPlayer = RecRoomPlayer::GetFromActorNumber(editInfo.targetActorIDs[0]);
                                        if (playerPlayer != nullptr) {

                                            PhotonPlayer* playerPlayerPP = playerPlayer->get_PhotonPlayer();

                                            if (playerPlayerPP != nullptr) {

                                                Il2CppString* playerPlayerDisplayName = playerPlayerPP->toStringUsername();

                                                if (playerPlayerDisplayName != nullptr && playerPlayerDisplayName->length > 0) {

                                                    playerDiplayName = ReadIl2CppString(playerPlayerDisplayName);
                                                }
                                            }
                                        }
                                    }

                                    std::string notifString = ("[Death] Killed: [" + std::to_string(editInfo.targetActorIDs[0]) + "] " + playerDiplayName + ".");

                                    pGui->notify.PushNotification<ImVec4(0.639, 0.631, 0.855, 1), 3.0f>(pGui->m_pTextures->tGunFilled, notifString);
                                }

                                break;
                            }
                            default: {
                                Il2CppString* prefabString = (Il2CppString*)payloadHashtable->get_Item(0);

                                if (prefabString != nullptr && prefabString->length > 0) { // ignore empty strings

                                    if (ReadIl2CppString(prefabString) == globals::opRaiseEventEdit::magicPrefab) {
                                        payloadHashtable->set_Item(0, (UObject*)WriteIl2CppString(editInfo.prefabToSwap.c_str())); // update prefab

                                        if (hashtableString.find("(System.Byte)1=(UnityEngine.Vector3)") != std::string::npos) { // update position
                                            Vector3 position = editInfo.position;
                                            payloadHashtable->set_Item(1, (UObject*)il2cpp_value_box_spoof(FindClass("UnityEngine.Vector3"), &position));
                                        }
                                        else {
                                            Vector3 position = editInfo.position;
                                            payloadHashtable->Add(1, (UObject*)il2cpp_value_box_spoof(FindClass("UnityEngine.Vector3"), &position));
                                        }

                                        if (hashtableString.find("(System.Byte)9=(UnityEngine.Vector3)") != std::string::npos) { // update scale
                                            Vector3 scale = editInfo.scale;
                                            payloadHashtable->set_Item(9, (UObject*)il2cpp_value_box_spoof(FindClass("UnityEngine.Vector3"), &scale));
                                        }
                                        else {
                                            Vector3 scale = editInfo.scale;
                                            payloadHashtable->Add(9, (UObject*)il2cpp_value_box_spoof(FindClass("UnityEngine.Vector3"), &scale));
                                        }

                                        Type* intType = (Type*)Type::getType(il2cpp_string_new_spoof("System.Int32"));
                                        int32_t arraySize = editInfo.targetActorIDs.size();
                                        Il2CppArray* targetActorsArray = Array::createInstance((Il2CppType*)intType, arraySize);

                                        for (int i = 0; i < targetActorsArray->max_length; i++) {

                                            //Log::debug("adding to array: " + std::to_string(actorID) + ", from i =: " + std::to_string(i));

                                            il2cpp_array_set(targetActorsArray, int32_t, i, editInfo.targetActorIDs[i]);
                                        }

                                        SetField<Il2CppArray*>(raiseEventOptions, 24, targetActorsArray);

                                        for (int i = 0; i < editInfo.count; i++) {
                                            hook_manager::get()["opraise"]->call<bool>(instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo);
                                            //OpRaiseEvent_o(instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo);
                                        }
                                    }
                                }
                                break;
                            }
                            }
                        }

                        SetField<Il2CppArray*>(raiseEventOptions, 24, cachedActorsArray); //! raiseEventOptions get reused for some dumb reason so we must revert all changes to this object

                        globals::opRaiseEventEdit::opRaiseEventEditQueue.clear();
                        globals::opRaiseEventEdit::inExecution = false;
                        return false; /// drop the dummy event or we will probably spawn some fucked shit
                    }
                }
            }

            
            
        }
        
#ifdef testshit
        if (eventCode == 202) {
            Type* payloadType = (Type*)Type::GetType(payload);
            std::string payloadTypeString = ReadIl2CppString(payloadType->ToString());

            if (payloadTypeString == "Type: Hashtable") {

                Hashtable* payloadHashtable = (Hashtable*)payload;

                std::string hashtableString = ReadIl2CppString(payloadHashtable->ToString());

                if (hashtableString.find(globals::opRaiseEventEdit::magicPrefab) != std::string::npos) {

                    Log::debug(hashtableString);

                    Log::debug("\"[ARENA_pIsToL]\" found!");

                    Vector3 scale = { 2, 2, 2 };

                    Il2CppString* prefabString = WriteIl2CppString("[Arena_Pistol]");

                    payloadHashtable->set_Item(0, (UObject*)prefabString); // update prefab
                    payloadHashtable->Add(9, (UObject*)il2cpp_value_box_spoof(FindClass("UnityEngine.Vector3"), &scale));


                    Log::debug("added byte 9");

                    Il2CppArray* targetActors = GetField<Il2CppArray*>(raiseEventOptions, 24);

                    if (targetActors != nullptr) {

                        Log::debug("actors array max: " + std::to_string(targetActors->max_length));

                        for (int i = 0; i < targetActors->max_length; i++) {
                            int32_t actorID = il2cpp_array_get(targetActors, int32_t, i);
                            Log::debug("target Actor: " + std::to_string(actorID));
                        }
                    }
                    else {
                        Log::debug("target actors is nullptr");
                        Type* intType = (Type*)Type::getType(il2cpp_string_new_spoof("System.Int32"));
                        Il2CppArray* targetActorsArray = Array::createInstance((Il2CppType*)intType, 1);
                        il2cpp_array_set(targetActorsArray, int32_t, 0, localPlayer.photonActorID);
                        SetField<Il2CppArray*>(raiseEventOptions, 24, targetActorsArray);
                        Log::debug("set actor to localPlayer");
                    }
                    

                }
            }


        }
#endif

#ifdef nvm
        if (eventCode == 24) { // RR_CreationOp\

            Type* payloadType = (Type*)Type::GetType(payload);
            std::string payloadTypeString = ReadIl2CppString(payloadType->ToString());

            if (payloadTypeString == "Type: Hashtable") {
                Hashtable* payloadHashtable = (Hashtable*)payload;

                OpRaiseEventCache::Ev24::CreationOp = payloadHashtable->get_Item(2);
                OpRaiseEventCache::Ev24::guid = payloadHashtable->get_Item(3);
                OpRaiseEventCache::Ev24::byteArray = payloadHashtable->get_Item(4);
                Log::debug("Ev24 data cached");
            }
        }
#endif

        if (blockMovementToggle) {
            if (eventCode == 201) { // movement event is 201
                return false;
            }
        }
        
        bool shouldDebug = true;

        if (!debugAntiCheatToggle && eventCode == 3)
            shouldDebug = false;

        if (blockPlayerInstantiation || (debugToggle && shouldDebug)) {

            Type* payloadType = (Type*)Type::GetType(payload);
            std::string payloadTypeString = ReadIl2CppString(payloadType->ToString());

            if (payloadTypeString == "Type: Hashtable") {

                Hashtable* payloadHashtable = (Hashtable*)payload;

                std::string hashtableString = ReadIl2CppString(payloadHashtable->ToString());

                if (debugToggle && shouldDebug) {
                    Log::debug("-----------------------------------------------------------------------------------");
                    Log::debug("Event Code: " + std::to_string(eventCode));
                    Log::debug("Payload " + payloadTypeString);
                    Log::debug("Hashtable Data: \n " + prettyHashtableString(hashtableString));

                    if (eventCode == 200) {
                        if (hashtableString.find("(System.Byte)5=(System.Int16)nigger") != std::string::npos) {
                            Il2CppArray* objectArray = (Il2CppArray*)payloadHashtable->get_Item(4); // key 4 is Object[]


                            Log::debug("shitshit");

                            int32_t* pTargetPhotonViewID1 = reinterpret_cast<int32_t*>(il2cpp_object_unbox_spoof(payloadHashtable->get_Item(0))); // rpc pvid
                            if (auto* pv = PhotonView::findPhotonView(*pTargetPhotonViewID1);
                                pv != nullptr)
                            {
                                auto* pvGO = pv->get_gameObject();

                                if (pvGO != nullptr)
                                {
                                    Log::debug(ReadIl2CppString(pvGO->GetName()));

                                    int testtargetpvid = *pTargetPhotonViewID1;
                                    
                                    for (const auto& player : cachedPlayerlist)
                                    {
                                        if (!player.second.isLocalPlayer && player.second.loadingStage >= LoadingStage::LOADED)
                                        {

                                            auto* playerPlayer = RecRoomPlayer::GetFromActorNumber(player.second.photonActorID);

                                            if (playerPlayer == nullptr)
                                                continue;
                                            if (!playerPlayer->get_IsInitialLoadFinished())
                                                continue;

                                            Component* targetComponent = GetField<Component*>(playerPlayer, 432);

                                            if (targetComponent == nullptr)
                                                continue;
                                            
                                            auto* targetGOO = targetComponent->get_gameObject();

                                            if (targetGOO == nullptr)
                                                continue;
                                            
                                            auto* targetPVV = (PhotonView*)targetGOO->GetComponent("PhotonView");

                                            if (targetPVV == nullptr)
                                                continue;
                                            
                                            testtargetpvid = targetPVV->get_ViewID();

                                            Log::debug("swap success");
                                            break;
                                        }
                                    }
                                    
                                    auto* targetpvid = (UObject*)il2cpp_value_box_spoof(FindClass("System.Int32"), &testtargetpvid);
                                    
                                    payloadHashtable->set_Item(0, targetpvid);
                                }
                            }
                            
                            Log::debug("object array max: " + std::to_string(objectArray->max_length));

                            for (int i = 0; i < objectArray->max_length; i++) {

                                Array* actualArray = (Array*)objectArray;
                                
                                Il2CppObject* object = actualArray->GetValue(i);

                                if (object != nullptr) {

                                    Type* objectType = (Type*)Type::GetType(object);

                                    std::string objectTypeString = ReadIl2CppString(objectType->ToString());
                                    Log::debug("object type: \n " + objectTypeString);
                                    if (objectTypeString.find("Type: String") != std::string::npos)
                                    {
                                        Il2CppArray* cachedActorsArray = GetField<Il2CppArray*>(raiseEventOptions, 24); //! raiseEventOptions get reused for some dumb reason so we must revert all changes to this object
                                        
                                        Log::debug("test shi");
                                        Log::debug(ReadIl2CppString((Il2CppString*)object));
                                        actualArray->SetValue((Il2CppObject*)WriteIl2CppString("<rotate=\"45\">nigga</rotate> test <sprite index=0> <sprite index=1>"), i);
                                        Log::debug(ReadIl2CppString((Il2CppString*)actualArray->GetValue(i)));

                                        std::vector<int32_t> targetActors;

                                        for (const auto& player : cachedPlayerlist)
                                        {
                                            targetActors.push_back(player.second.photonActorID);
                                        }
                                        
                                        Type* intType = (Type*)Type::getType(il2cpp_string_new_spoof("System.Int32"));
                                        int32_t arraySize = targetActors.size();
                                        Il2CppArray* targetActorsArray = Array::createInstance((Il2CppType*)intType, arraySize);

                                        for (int i = 0; i < targetActorsArray->max_length; i++) {

                                            //Log::debug("adding to array: " + std::to_string(actorID) + ", from i =: " + std::to_string(i));

                                            il2cpp_array_set(targetActorsArray, int32_t, i, targetActors[i]);
                                        }

                                        SetField<Il2CppArray*>(raiseEventOptions, 24, targetActorsArray);
                                        
                                        //SetField<Il2CppArray*>(raiseEventOptions, 24, nullptr); // nullptr = everybody
                                        
                                        auto result = hook_manager::get()["opraise"]->call<bool>(instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo);
                                        
                                        SetField<Il2CppArray*>(raiseEventOptions, 24, cachedActorsArray); //! raiseEventOptions get reused for some dumb reason so we must revert all changes to this object

                                        return result;
                                    }
                                    
                                    if (objectTypeString.find("Int32") != std::string::npos)
                                    {
                                        int32_t* pTargetPhotonViewID = reinterpret_cast<int32_t*>(il2cpp_object_unbox_spoof(object));
                                        std::string targetPhotonViewIDString = std::to_string(*pTargetPhotonViewID);
                                        Log::debug("int val:" + targetPhotonViewIDString);
                                    }
                                }
                            }
                        }
                    }
                    if (eventCode == 202) {
                        if (hashtableString.find("(System.Byte)5=(System.Object[])System.Object[]") != std::string::npos) {
                            Il2CppArray* objectArray = (Il2CppArray*)payloadHashtable->get_Item(5); // key 5 is Object[]

                            Log::debug("object array max: " + std::to_string(objectArray->max_length));

                            for (int i = 0; i < objectArray->max_length; i++) {
                                Il2CppObject* object = il2cpp_array_get(objectArray, Hashtable*, i);

                                if (object != nullptr) {

                                    Type* objectType = (Type*)Type::GetType(object);

                                    std::string objectTypeString = ReadIl2CppString(objectType->ToString());
                                    Log::debug("object type: \n " + objectTypeString);
                                }
                            }
//#ifdef serializetest

                            if ((hashtableString.find("Polaroid") != std::string::npos)) {

                                if (hashtableString.find("(System.Byte)4=(System.Int32[])System.Int32[]") != std::string::npos)
                                {
                                    Array* objectArray = (Array*)payloadHashtable->get_Item(4); // key 5 is Object[]

                                    Log::debug("============= ARRAY BYTE 4");
                                    Log::debug("object array max: " + std::to_string(objectArray->max_length));

                                    for (int i = 0; i < objectArray->max_length; i++) {

                                        Log::debug("array 1");
                                        
                                        Il2CppObject* object = objectArray->GetValue(i);

                                        if (object != nullptr) {

                                            Type* objectType = (Type*)Type::GetType(object);

                                            std::string objectTypeString = ReadIl2CppString(objectType->ToString());
                                            Log::debug("object type: \n " + objectTypeString);

                                            if (objectTypeString.find("Int32") != std::string::npos)
                                            {
                                                int* pTargetPhotonViewID = reinterpret_cast<int*>(il2cpp_object_unbox_spoof(object));
                                                std::string targetPhotonViewIDString = std::to_string(*pTargetPhotonViewID);
                                                Log::debug("int val:" + targetPhotonViewIDString);
                                            }
                                        }
                                    }
                                }
                                
                                //#ifdef jsontest
                                
                                Log::debug("json mid");

                                Il2CppString* stringy2 = NativeJson::SerializeObject(objectArray);

                                Log::debug(ReadIl2CppString(stringy2));

                                Log::debug("json end");

                                Il2CppObject* object = il2cpp_array_get(objectArray, Hashtable*, 1);

                                if (object != nullptr)
                                {
                                    auto* dobject = (System::Collections::Generic::Dictionary_2*)object;
                                    
                                    Log::debug("cunt 1");

                                    Array*& entries = (Array*&)dobject->_entries2();

                                    Log::debug("cunt 2");

                                    Type* entryObjType11 = (Type*)Type::GetType((Il2CppObject*)entries);
                                    Log::debug("inside entry3");
                                    std::string objectTypeString111 = ReadIl2CppString(entryObjType11->ToString());
                                    Log::debug("inside entry4");
                                    Log::debug("object type11: \n " + objectTypeString111);

                                    Log::debug("count: " + std::to_string(entries->max_length));

                                    for (int j = 0; j < entries->max_length; j++) {
                                        //System::Collections::Generic::Dictionary_2_Entry<Il2CppObject*, Il2CppObject*>* entryObj = (System::Collections::Generic::Dictionary_2_Entry<Il2CppObject*, Il2CppObject*>*)il2cpp_array_get(entries, Il2CppObject*, 0);
                                        auto* entryObj = (System::Collections::Generic::Dictionary_2_Entry<Il2CppObject*, Il2CppObject*>*)entries->GetValue(j);

                                        Log::debug("inside entry");
                                            
                                        if (entryObj != nullptr) {
                                            Log::debug("inside entry2");
                                            Log::debug("inside entry211");
                                            Log::debug("object type11: \n " + std::to_string((uintptr_t)entryObj));
                                            Log::debug("inside entry2");
                                            Log::debug("inside entry2");
                                            
                                            /*
                                            Type* entryObjType = (Type*)Type::GetType((Il2CppObject*)entryObj);
                                            Log::debug("inside entry3");
                                            std::string objectTypeString1 = ReadIl2CppString(entryObjType->ToString());
                                            Log::debug("inside entry4");
                                            Log::debug("object type11: \n " + objectTypeString1);
                                            */
                                            
                                            
                                            if (entryObj->key != nullptr)
                                            {
                                                Log::debug("inside entry211");
                                                Log::debug("key: " + std::to_string((uintptr_t)entryObj->key));
                                                Log::debug("inside entry2222");
                                                //Log::debug("key va: " + std::string(ReadIl2CppString((Il2CppString*)entryObj->key)));
                                            }
                                            
                                            if (entryObj->value != nullptr)
                                            {
                                                Log::debug("inside entry2333");
                                                Log::debug("value: " + std::to_string((uintptr_t)entryObj->value));
                                                Log::debug("inside entry2444");

                                               // auto valueString = std::string(ReadIl2CppString((Il2CppString*)entryObj->value));
                                                
                                                //Log::debug("value va: " + valueString);

                                                
                                                Type* entryObjType22 = (Type*)Type::GetType((Il2CppObject*)entryObj->value);
                                                Log::debug("inside entry31111");
                                                std::string objectTypeString122 = ReadIl2CppString(entryObjType22->ToString());
                                                Log::debug("inside entry4111111");
                                                Log::debug("object type1111111: \n " + objectTypeString122);
                                                
                                                /*
                                                if (valueString.find("PlayerId") != std::string::npos)
                                                {
                                                    // Xxstoner4lifexX -> 31124221
                                                    entryObj->value = (Il2CppObject*)WriteIl2CppString(R"({"Id":0,"PlayerId":31124221,"FromPlayerId":1,"ConsumableItemDesc":"","AvatarItemType":null,"AvatarItemDesc":"","CustomAvatarItemId":null,"EquipmentPrefabName":"","EquipmentModificationGuid":"","CurrencyType":2,"Currency":80085,"Xp":1,"GiftContext":30,"GiftRarity":50,"Message":"TEST MESSAGE","Platform":-1,"PlatformsToSpawnOn":-1,"BalanceType":null})");
                                                    Log::debug("replaced va: " + std::string(ReadIl2CppString((Il2CppString*)entryObj->value)));

                                                    Log::debug("inside entry3");

                                                    entries->SetValue(entryObj, j);
                                                    
                                                    Log::debug("inside entry4");
                                                }
                                                */
                                                
                                            }
                                        }
                                    }
                                }

                                /*
                                Il2CppType* dicttype = Type::getType(WriteIl2CppString("System.Collections.Generic.Dictionary`2"));

                                if (dicttype != nullptr) {

                                    Il2CppType* jsonconverttype = Type::getType(WriteIl2CppString("Newtonsoft.Json.JsonConverter"));

                                    Il2CppArray* okarray = Array::createInstance(jsonconverttype, 0);

                                    Log::debug("dict good type");


                                    Type* dicttypew2 = (Type*)dicttype;

                                    Log::debug(ReadIl2CppString(dicttypew2->ToString()));

                                    Log::debug("almost good now");

                                    //Il2CppString* cuhhh = WriteIl2CppString(R"("Owner":1,"GiftJSON":"{\"Id\":0,\"PlayerId\":1417725497,\"FromPlayerId\":0,\"ConsumableItemDesc\":\"\",\"AvatarItemType\":null,\"AvatarItemDesc\":\"\",\"CustomAvatarItemId\":null,\"EquipmentPrefabName\":\"\",\"EquipmentModificationGuid\":\"\",\"CurrencyType\":2,\"Currency\":9999999,\"Xp\":1,\"GiftContext\":30,\"GiftRarity\":50,\"Message\":\"'Have fun in one week.' -Supremium 02/2024\",\"Platform\":-1,\"PlatformsToSpawnOn\":-1,\"BalanceType\":null}")");

                                    
                                    

                                    Log::debug("almost good now1");
                                    Il2CppObject* obj = NativeJson::DeserializeObject(cuhhh, dicttype, okarray);

                                    if (obj != nullptr)
                                        Log::debug("objecty good!~");

                                    Log::debug("post derserial");

                                    Il2CppString* stringy21 = NativeJson::SerializeObject(obj);

                                    Log::debug(ReadIl2CppString(stringy21));

                                }
                                */
                                //#endif
                            }
//#endif
                        }
                    }

                    if (eventCode == 1) // bulk instantiate
                    {
                        Il2CppArray* hashtableArray = (Il2CppArray*)payloadHashtable->get_Item(1);

                        Log::debug("hastable array max: " + std::to_string(hashtableArray->max_length));

                        for (int i = 0; i < hashtableArray->max_length; i++) {
                            Hashtable* hashtable = il2cpp_array_get(hashtableArray, Hashtable*, i);

                            if (hashtable != nullptr) {

                                std::string hashtableString1 = ReadIl2CppString(hashtable->ToString());
                                Log::debug("Hashtable Data: \n " + prettyHashtableString(hashtableString1));

                                if (hashtableString1.find("(System.Byte)5=(System.Object[])System.Object[]") != std::string::npos) {
                                    Il2CppArray* objectArray = (Il2CppArray*)hashtable->get_Item(5); // key 5 is Object[]

                                    Log::debug("object array max: " + std::to_string(objectArray->max_length));

                                    for (int i = 0; i < objectArray->max_length; i++) {
                                        Il2CppObject* object = il2cpp_array_get(objectArray, Hashtable*, i);

                                        if (object != nullptr) {

                                            Type* objectType = (Type*)Type::GetType(object);

                                            std::string objectTypeString = ReadIl2CppString(objectType->ToString());
                                            Log::debug("object type: \n " + objectTypeString);
                                        }
                                    }

                                    ///native serialization test start
#ifdef ksjmdksjd
                                    Log::debug("json mid");

                                    Il2CppString* stringy2 = NativeJson::SerializeObject(objectArray);

                                    Log::debug(ReadIl2CppString(stringy2));

                                    Log::debug("json end");


                                    Il2CppType* dicttype = Type::getType(WriteIl2CppString("System.Collections.Generic.Dictionary`2"));

                                    if (false) {
                                        Log::debug("dict good type");
                                        //Log::debug("dict good type");

                                        //Il2CppArray* okarray = Array::createInstance()

                                        //Log::debug("dict good type");

                                        Il2CppObject* obj = NativeJson::DeserializeObject(WriteIl2CppString(R"({"RRIR_PVID":"fe194e53-0c75-4283-af4a-8063654a3709","CO_STT":467,"cv2_cpi":"bc1f2f7b-0493-5d74-abef-bfaefdeda1e1","cv2_cpd":true,"cv2_cpp":"b89e86dc-6a84-5bf7-a2f1-3eb08cf77f34"})"), dicttype, nullptr);

                                        if (obj != nullptr)
                                            Log::debug("objecty good!~");

                                        Log::debug("post derserial");

                                        Il2CppString* stringy21 = NativeJson::SerializeObject(obj);

                                        Log::debug(ReadIl2CppString(stringy21));

                                    }
#endif

                                }
                            }
                        }
                    }

                }

                if (blockPlayerInstantiation) {

                    if (blockAllPlayerInstantiation) {
                        if (eventCode == 204) { // 204 "Destroy" is related to room leave/join

                            Il2CppObject* targetPhotonViewObject = payloadHashtable->get_Item(0); // key 0 is target PhotonViewID

                            int* pTargetPhotonViewID = reinterpret_cast<int*>(il2cpp_object_unbox_spoof(targetPhotonViewObject));
                            std::string targetPhotonViewIDString = std::to_string(*pTargetPhotonViewID);

                            if (localPlayerExists) { /// this is bad code we should determine localPlayer from photon and not gameobject name!!!!
                                if (*pTargetPhotonViewID == localPlayer.photonViewID) {
                                    return false;
                                }
                            }
                        }
                    }

                    if (eventCode == 202) { // instantiate event is 202

                        Il2CppObject* prefabObject = payloadHashtable->get_Item(0); // key 0 is the prefab

                        if (prefabObject != nullptr) {
                            Type* prefabObjectType = (Type*)Type::GetType(prefabObject);
                            std::string objectTypeString = ReadIl2CppString(prefabObjectType->ToString());

                            if (objectTypeString.find("String") != std::string::npos) { // yes we could check the hashtable string directly but this method is safer
                                std::string prefabString = ReadIl2CppString((Il2CppString*)prefabObject);

                                std::vector<std::string> blacklist{ "[Player]"/*, "[MakerPen]", "[ShareCamera]", "[FeedbackTool]", "[ClothingCustomizerTool]"*/ };

                                for (auto& prefab : blacklist) {
                                    if (prefabString.find(prefab) != std::string::npos) {
                                        Log::debug("[Meep Mode] Blocked Prefab: " + prefabString + " from instantiating.");
                                        return false;
                                    }
                                }

                            }
                        }
                    }
                }

#ifdef aimbotoldcode
                // RangedWeapon.Fire event (for aimbot)
                if (hashtableString.find("(System.Byte)0") != std::string::npos && hashtableString.find("(System.Byte)2") != std::string::npos && hashtableString.find("(System.Byte)5") != std::string::npos && hashtableString.find("(System.Byte)4") != std::string::npos)
                {

                    // only cache this cuz raiseEventOptions & sendOptions are Others
                    OpRaiseEventCache::instance = instance;
                    OpRaiseEventCache::eventCode = eventCode;
                    OpRaiseEventCache::payload = payload;
                    OpRaiseEventCache::eventOptions = raiseEventOptions;
                    OpRaiseEventCache::sendOptions = sendOptions;

                    Il2CppObject* payloadFourthKeyObject = getItem(payload, 4); // key 4 is the payload
                    Il2CppObject* payloadFifthKeyObject = getItem(payload, 5); // rpc code i think

                    bool internalToggle = globals::photon::aimbot::toggle;
                    bool internalNearestToggle = globals::photon::aimbot::nearestToggle;
                    int internalFloorOffset = globals::photon::aimbot::floorOffset;

                    if (internalToggle) {
                        if (hashtableString.find("(System.Byte)5=(System.Int16)34") != std::string::npos) // 34 is Fire() rpc code i think
                        {
                            Vector3 position{ 0, 0, 0 };

                            Il2CppArray* payloadIl2CppObjectArray = reinterpret_cast<Il2CppArray*>(payloadFourthKeyObject);
                            for (int i = 0; i < payloadIl2CppObjectArray->max_length; i++)
                            {
                                Il2CppObject* object = il2cpp_array_get(payloadIl2CppObjectArray, Il2CppObject*, i);
                                std::string insideArrayTypeString = Unity::GetType(object)->ToString();

                                OurPhoton::PhotonHashtable* payloadHashtable = reinterpret_cast<OurPhoton::PhotonHashtable*>(payload);

                                int internalMultiplier = globals::photon::aimbot::multiplier;

                                switch (i)
                                {
                                case 0: { // array[0] - position Vector3
                                    Il2CppObject* positionObject = il2cpp_array_get(payloadIl2CppObjectArray, Il2CppObject*, i);
                                    Vector3* pPosition = reinterpret_cast<Vector3*>(il2cpp_object_unbox(positionObject));
                                    position = *pPosition;
                                    break;
                                }
                                case 1: // array[1] - rotation Quaternion
                                    break;
                                case 2: { // array[2] - velocity Vector3
                                    Player targetPlayer;
                                    Vector3 targetPosition = { 0, 0, 0 };
                                    Transform* localChildBodyPartsTransform = nullptr;

                                    if (internalNearestToggle) { // this needs to be rewritten
                                        //targetPosition = getClosestPlayerHeadPosition(cachedPlayerlist);
                                    }
                                    else {
                                        for (int i = 0; i < cachedPlayerlist.size(); ++i) {
                                            if (!cachedPlayerlist[photonPlayerlist[i]].isLocalPlayer) {

                                                Player player = cachedPlayerlist[photonPlayerlist[i]];

                                                if (player.photonActorID == globals::photon::aimbot::targetActorID) {
                                                    targetPlayer = player;
                                                    break;
                                                }
                                            }
                                        }

                                        if (targetPlayer.playerGameObject != nullptr)
                                        {
                                            Transform* cuntFuckTransform = targetPlayer.playerGameObject->get_Transform();
                                            localChildBodyPartsTransform = cuntFuckTransform->getChild(0);
                                            Transform* localHeadTransform = localChildBodyPartsTransform->getChild(0);

                                            if (localHeadTransform)
                                            {
                                                targetPosition = localHeadTransform->get_Position();
                                            }
                                        }
                                    }

                                    Vector3 shotPosition = position;

                                    targetPosition.x = (targetPosition.x - shotPosition.x);
                                    targetPosition.y = ((targetPosition.y - shotPosition.y) + internalFloorOffset);
                                    targetPosition.z = (targetPosition.z - shotPosition.z);

                                    float magnitude = internalMultiplier; //sqrt(targetPosition.x * targetPosition.x + targetPosition.y * targetPosition.y + targetPosition.z * targetPosition.z); <- based on distance
                                    Vector3 normalizedVector = Vector3(targetPosition.x * magnitude, targetPosition.y * magnitude, targetPosition.z * magnitude);

                                    Il2CppObject* velocityObject = il2cpp_value_box(findClass("UnityEngine.Vector3"), &normalizedVector);

                                    il2cpp_array_set(payloadIl2CppObjectArray, Il2CppObject*, i, velocityObject);

                                    payloadHashtable->Set(4, reinterpret_cast<Object*>(payloadIl2CppObjectArray)); // 4th key is payload hashtable

                                    //PLH::FnCast(globals::hooks::OpRaiseEvent_o, (OpRaiseEvent_t)(methods::obfuscated::photon::OpRaiseEvent))(instance, eventCode, reinterpret_cast<Il2CppObject*>(payloadHashtable), raiseEventOptions, sendOptions);

                                    return PLH::FnCast(globals::hooks::OpRaiseEvent_o, (OpRaiseEvent_t)(methods::obfuscated::photon::OpRaiseEvent))(instance, eventCode, reinterpret_cast<Il2CppObject*>(payloadHashtable), raiseEventOptions, sendOptions);

                                    break;
                                }
                                case 3: // array[3] - chargeAmount float
                                    break;
                                case 4: // array[4] - misFire bool
                                    break;
                                case 5: // array[5] - shotId int
                                    break;
                                default:
                                    break;
                                }
                            }
                        }
                    }

                    if (internalDebugToggle) {
                        std::string payloadFourthKeyTypeString = Unity::GetType(payloadFourthKeyObject)->ToString();

                        if (payloadFourthKeyTypeString == "Type: Object[]")
                        {

                            Log::debug("Payload Hashtable's 4th Key is Object[]");
                            Il2CppArray* payloadIl2CppObjectArray = reinterpret_cast<Il2CppArray*>(payloadFourthKeyObject);
                            for (int i = 0; i < payloadIl2CppObjectArray->max_length; i++)
                            {
                                Il2CppObject* object = il2cpp_array_get(payloadIl2CppObjectArray, Il2CppObject*, i);
                                std::string insideArrayTypeString = Unity::GetType(object)->ToString();

                                Log::debug("Inside Array " + insideArrayTypeString);
                                if (insideArrayTypeString == "Type: String")
                                {
                                    Log::debug("Inside String: " + std::string(readIL2CPPString(reinterpret_cast<Il2CppString*>(object))));
                                }
                                if (insideArrayTypeString == "Type: Boolean")
                                {
                                    Log::debug("Inside Bool: " + *reinterpret_cast<bool*>(object) ? "true" : "false");
                                }
                                if (insideArrayTypeString == "Type: Int32")
                                {
                                    Log::debug("Inside Int32: " + std::to_string(*reinterpret_cast<INT32*>(il2cpp_object_unbox(object))));
                                }
                            }
                        }
                    }
                }
                //Log::debug("-----------------------------------------------------------------------------------");
#endif
            }
            else if (debugToggle && shouldDebug) {
                Log::debug("-----------------------------------------------------------------------------------");
                Log::debug("Event Code: " + std::to_string(eventCode));
                Log::debug("Payload " + payloadTypeString);
                Log::debug("Pyalod Data Type: \n " + payloadTypeString);
            }
        }
    }

    //bool result = OpRaiseEvent_o(instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo);
    bool result = hook_manager::get()["opraise"]->call<bool>(instance, eventCode, payload, raiseEventOptions, sendOptions, methodInfo);
    
    
    return result;
}