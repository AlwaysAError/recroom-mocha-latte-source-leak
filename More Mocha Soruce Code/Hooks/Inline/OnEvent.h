#pragma once

std::string ToUpperCase(std::string& str)
{
    std::string upperCaseStr;
    upperCaseStr.reserve(str.size());

    std::ranges::transform(str.begin(), str.end(), std::back_inserter(upperCaseStr), [](const unsigned char c)
    {
        return std::toupper(c);
    });

    return upperCaseStr;
}

struct OnEventParamInfo
{
    EventData* eventData;
    void* methodInfo;
};

void __fastcall SafeCall_OnEvent_o(void*);

using OnEvent_t = void(*)(EventData*, void*);
OnEvent_t OnEvent_o = nullptr;

void __fastcall OnEvent_Ihook(EventData* eventData, void* methodInfo)
{
    OnEventParamInfo params{
        eventData,
        methodInfo
    };

    OnEventParamInfo* pParams = &params;

#ifdef OLDANTIS

    //! this is the only way to not have fucked global values in this hook.
    bool& internalDebugToggle = globals::photon::antis::inbound::debugToggle;
    bool& internalDebugAntiCheatToggle = globals::photon::antis::inbound::debugAntiCheatToggle;
    bool& internalBlockFreezeToggle = globals::photon::antis::inbound::blockFreezeToggle;
    bool& internalBlockByeByeToggle = globals::photon::antis::inbound::blockByeByeToggle;
    bool& internalBlockEv207Toggle = globals::photon::antis::inbound::blockEv207Toggle;
    bool& internalBlockMovementToggle = globals::photon::antis::inbound::blockMovementToggle;
    bool& internalblockAllRPCs = globals::photon::antis::inbound::blockAllRPCs;
    bool& internalBlockAllToggle = globals::photon::antis::inbound::blockAllToggle;
    bool& internalBlockAntiCheatToggle = globals::photon::antis::inbound::blockAntiCheatToggle;
    bool& internalBlockHeartbeatToggle = globals::photon::antis::inbound::blockHeartbeatToggle;
    bool& internalBlockEv204Toggle = globals::photon::antis::inbound::blockEv204Toggle;

    bool& internalSanitizeEv200Toggle = globals::photon::antis::inbound::sanitizeEv200Toggle;
    bool& internalSanitizeEv200BounceBack = globals::photon::antis::inbound::sanitizeEv200BounceBack;
    auto& internalSanitizeEv200Mode = globals::photon::antis::inbound::sanitizeEv200Mode;
    auto& internalSanitizeEv200BounceBackMode = globals::photon::antis::inbound::sanitizeEv200BounceBackMode;
    float& internalMaxVectors = globals::photon::antis::inbound::maxVectors;
    float& internalMinVectors = globals::photon::antis::inbound::minVectors;

    bool& internalBlockMovementDuringLoad = globals::photon::antis::inbound::blockMovementDuringLoad;
    bool& internalBlockMovementDuringLoadStrict = globals::photon::antis::inbound::blockMovementDuringLoadStrict;

    bool& internalBlockRpcsDuringLoad = globals::photon::antis::inbound::blockRpcsDuringLoad;
    bool& internalBlockRpcsDuringLoadStrict = globals::photon::antis::inbound::blockRpcsDuringLoadStrict;
    bool& internalBlockRpcsDuringLoadBlockServer = globals::photon::antis::inbound::blockRpcsDuringLoadBlockServer;

    bool& AC_toggle = globals::photon::antis::inbound::antiCheat::toggle;
    bool& AC_blockEvent = globals::photon::antis::inbound::antiCheat::blockEvent;
    bool& AC_developerPrefabs = globals::photon::antis::inbound::antiCheat::developerPrefabs;
    bool& AC_commonPrefabs = globals::photon::antis::inbound::antiCheat::commonPrefabs;
    bool& AC_bossPrefabs = globals::photon::antis::inbound::antiCheat::bossPrefabs;
    bool& AC_managerPrefabs = globals::photon::antis::inbound::antiCheat::managerPrefabs;
    bool& AC_enemyPrefabs = globals::photon::antis::inbound::antiCheat::enemyPrefabs;
    bool& AC_scaleCheck = globals::photon::antis::inbound::antiCheat::scaleCheck;
    auto& AC_scaleMode = globals::photon::antis::inbound::antiCheat::scaleMode;
    float& AC_maxScale = globals::photon::antis::inbound::antiCheat::maxScale;
    float& AC_minScale = globals::photon::antis::inbound::antiCheat::minScale;
    bool& AC_vectorsCheck = globals::photon::antis::inbound::antiCheat::vectorsCheck;
    bool& AC_vectorsCheckStrict = globals::photon::antis::inbound::antiCheat::vectorsCheckStrict;
    float& AC_maxVectors = globals::photon::antis::inbound::antiCheat::maxVectors;
    float& AC_minVectors = globals::photon::antis::inbound::antiCheat::minVectors;
    bool& AC_bounceBack = globals::photon::antis::inbound::antiCheat::bounceBack;
    auto& AC_bounceBackMode = globals::photon::antis::inbound::antiCheat::bounceBackMode;
    bool& AC_destroyPrefab = globals::photon::antis::inbound::antiCheat::destroyPrefab;
    bool& AC_excludeServerEvents = globals::photon::antis::inbound::antiCheat::excludeServerEvents;
    bool& AC_pauseOnLoading = globals::photon::antis::inbound::antiCheat::pauseOnLoading;
    bool& AC_announceOffender = globals::photon::antis::inbound::antiCheat::announceOffender;
    bool& AC_blockOffenderEvents = globals::photon::antis::inbound::antiCheat::blockOffenderEvents;

    auto& BlockedActors = blockedActorIds;

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

    Il2CppObject* customData = eventData->get_CustomData();
    const int32_t senderActorID = eventData->get_Sender();

    if (customData == nullptr) return OnEvent_o(eventData, methodInfo);

    Type* eventCustomDataType = (Type*)Type::GetType(customData);

    std::string typeCDString{ "NULLPTR" };

    //Log::debug("cuh11");

    if (eventCustomDataType != nullptr) {
        Il2CppString* eventCustomDataTypeString = eventCustomDataType->ToString();
        if (eventCustomDataTypeString != nullptr && eventCustomDataTypeString->length > 0)
            typeCDString = ReadIl2CppString(eventCustomDataTypeString);
    }
    //Log::debug("cuh112");
    const uint8_t eventCode = GetField<uint8_t>(eventData, 16);

#ifdef nvm
    if (eventCodeString.find("24") != std::string::npos) {
        globals::photon::antis::inbound::cachedEv24 = eventData;
        Log::debug("cached Ev24 EventData");
    }
#endif
    //Log::debug("cuh113");
    if (internalBlockAllToggle) {

        bool shouldBlock = true;

        if (!internalBlockAntiCheatToggle && eventCode == 3)
            shouldBlock = false;

        if (shouldBlock)
            return;
    }
    //Log::debug("cuh114");

    if (eventCode != 201 && eventCode != 10) { /// allow movement events & pv ownership updates only
        for (auto& actor : BlockedActors) {
            if (actor == senderActorID)
                return;
        }
    }
    //Log::debug("cuh115");
    bool shouldDebug = true;

    if (!internalDebugAntiCheatToggle && eventCode == 3)
        shouldDebug = false;

    /*
    if (internalBlockEv204Toggle || internalBlockEv207Toggle) {
        if (eventCode == 204) {
#ifndef PROD
                int senderActorID = senderID;
                printf("[Ev204-Strict] Protected localplayer from Actor: %d\n", senderActorID);
#endif
                return;
            }
        }
        */
    //Log::debug("cuh116");
    if (internalBlockMovementToggle) {
        if (eventCode == 201) { // movement events
            return;
        }
    }

    if (internalblockAllRPCs) {
        if (eventCode == 200) { // RPC events

            if (!localPlayerExists)
                return;
            else {
                if (senderActorID != localPlayer.photonActorID) { // allow us to recieve our own events
                    return;
                }
            }
        }
    }

    if (internalBlockMovementDuringLoad) {
        if (eventCode == 201) {

            if (!localPlayerExists)
                return;

            if (localPlayer.loadingStage < LoadingStage::LOADED)
                return;

            if (internalBlockMovementDuringLoadStrict) {
                RecRoomPlayer* localPlayerPlayer = RecRoomPlayer::GetFromActorNumber(localPlayer.photonActorID);

                if (localPlayerPlayer == nullptr || !localPlayerPlayer->get_IsInitialLoadFinished())
                    return;
            }
        }
    }

    if (internalBlockRpcsDuringLoad) {
        if (eventCode == 200) {

            bool shouldBlock = false;

            if (!localPlayerExists)
                shouldBlock = true;

            if (localPlayer.loadingStage < LoadingStage::LOADED)
                shouldBlock = true;

            if (internalBlockRpcsDuringLoadStrict) {
                RecRoomPlayer* localPlayerPlayer = RecRoomPlayer::GetFromActorNumber(localPlayer.photonActorID);

                if (localPlayerPlayer == nullptr || !localPlayerPlayer->get_IsInitialLoadFinished())
                    shouldBlock = true;
            }

            if (!internalBlockRpcsDuringLoadBlockServer && senderActorID == 0)
                shouldBlock = false;

            if (shouldBlock)
                return;
        }
    }

    //Log::debug("cuh117");
    if (typeCDString == "Type: Hashtable")
    {
        //Log::debug("cuh118");
        Hashtable* customDataHashtable = (Hashtable*)customData;
        std::string hashtableString = "";
        Il2CppString* customDataHashtableString = customDataHashtable->ToString();
        if (customDataHashtableString != nullptr && customDataHashtableString->length > 0) {
            hashtableString = ReadIl2CppString(customDataHashtableString);
        }

        if (eventCode == 202) { // block instantiate events that cause exceptions aka no prefab instantiate events

            bool found = false;

            if (hashtableString.find("(System.Byte)0=(System.String)") == std::string::npos) {
                found = true;
            }
            else {
                Il2CppString* prefabString = (Il2CppString*)customDataHashtable->get_Item(0); // key 0 is prefab name

                if (prefabString == nullptr || prefabString->length <= 0) {
                    found = true;
                }

                std::string prefabStringString = ReadIl2CppString(prefabString);

                if (prefabStringString.empty() || prefabStringString == std::string("")) {
                    found = true;
                }
            }

            if (found) {

                Log::debug("blocked bad 202 event");

                std::string notifString = ("[ObjectFilter] Blocked Malicious Payload from Actor: " + std::to_string(senderActorID) + ".");
                pGui->notify.PushNotification<ImVec4(1.0, 0.0, 1.0, 1), 3.0f>(pGui->m_pTextures->tWarnFilled, notifString);

                return;
            }
        }

        //Log::debug("cuh119");
        if (internalDebugToggle && shouldDebug)
        {

            Log::debug("-----------------------------------------------------------------------------------");
            Log::debug("Sender: " + std::to_string(senderActorID));
            Log::debug("Event Code: " + std::to_string(eventCode));
            Log::debug("Payload: " + typeCDString);

            Log::debug("Hashtable Data: \n " + prettyHashtableString(hashtableString));

            if (eventCode == 200) {

                if (hashtableString.find("(System.Byte)5=(System.Int16)253") != std::string::npos) {

                    Il2CppArray* payloadArray = (Il2CppArray*)customDataHashtable->get_Item(4); // key 7 is target rpc payload

                    if (payloadArray != nullptr) {

                        Log::debug("object array max: " + std::to_string(payloadArray->max_length));

                        for (int i = 0; i < payloadArray->max_length; i++) {
                            Il2CppObject* object = il2cpp_array_get(payloadArray, Il2CppObject*, i);

                            if (object != nullptr) {

                                Type* objectType = (Type*)Type::GetType(object);

                                std::string objectTypeString = ReadIl2CppString(objectType->ToString());
                                Log::debug("object type: " + objectTypeString);
                            }
                        }
                    }

                    Il2CppObject* targetPhotonViewObject = customDataHashtable->get_Item(0); // key 0 is target photonviewid

                    int* pTargetPhotonViewID = reinterpret_cast<int*>(il2cpp_object_unbox_spoof(targetPhotonViewObject));

                    int photonViewID = *pTargetPhotonViewID;

                    PhotonView* photonView = PhotonView::findPhotonView(photonViewID);

                    if (photonView != nullptr) {

                        GameObject* pvGO = photonView->get_gameObject();

                        if (pvGO != nullptr) {
                            Log::debug("pv owner: " + std::string(ReadIl2CppString(pvGO->GetName())));
                        }
                    }

                    
                    Il2CppString* serializedArray = NativeJson::SerializeObject((Il2CppObject*)payloadArray);

                    if (serializedArray != nullptr) {
                        Log::debug(ReadIl2CppString(serializedArray));
                    }
                    

                }

            }
        }
        /*
        if (internalBlockByeByeToggle || internalBlockFreezeToggle) { // event which controls player leave/join state "Destroy"
            if (eventCode == 204) {

                int senderActorID = senderID;

                Il2CppObject* targetPhotonViewObject = customDataHashtable->get_Item(0); // key 0 is target PhotonViewID

                int* pTargetPhotonViewID = reinterpret_cast<int*>(il2cpp_object_unbox_spoof(targetPhotonViewObject));
                std::string targetPhotonViewIDString = std::to_string(*pTargetPhotonViewID);

                //Log::debug("[ev204] target photonviewid: " + targetPhotonViewIDString);

                if (*pTargetPhotonViewID == localPlayer.photonViewID) {
                    //Log::debug("[ev204] Protected localplayer from Actor: " + std::to_string(senderActorID));
#ifndef PROD
                        printf("[Ev204] Protected localplayer from Actor: %d\n", senderActorID);
#endif
                        //playerlistMutex.unlock();
                        return;
                    }
                    else {
                        //Log::debug("[ev204] Allowed ev204 from Actor: " + std::to_string(senderActorID));
                        //playerlistMutex.unlock();
                    }
                }
            }
            */
        //Log::debug("cuh1191");
        if (internalBlockByeByeToggle) {

            if (eventCode == 200) {

                Il2CppObject* targetPhotonViewObject = customDataHashtable->get_Item(0); // key 7 is target PhotonViewID

                if (targetPhotonViewObject != nullptr) {

                    int* pTargetPhotonViewID = reinterpret_cast<int*>(il2cpp_object_unbox_spoof(targetPhotonViewObject));

                    if (*pTargetPhotonViewID == (std::stoi((std::to_string(localPlayer.photonActorID) + "00007"))) ||
                        *pTargetPhotonViewID == (std::stoi((std::to_string(localPlayer.photonActorID) + "00006"))) ||
                        *pTargetPhotonViewID == (std::stoi((std::to_string(localPlayer.photonActorID) + "00004"))) ||
                        *pTargetPhotonViewID == (std::stoi((std::to_string(localPlayer.photonActorID) + "00003"))) ||
                        *pTargetPhotonViewID == (std::stoi((std::to_string(localPlayer.photonActorID) + "00008"))) ||
                        *pTargetPhotonViewID == (std::stoi((std::to_string(localPlayer.photonActorID) + "00002")))) {

                        //Log::debug("[ev200] Protected localplayer from Actor: " + std::to_string(senderActorID));
#ifndef PROD
                        printf("[Ev200] Protected localplayer from Actor: %d\n" + senderActorID);
#endif

                        //playerlistMutex.unlock();

                        return;
                    }
                    else {
                        //Log::debug("[ev200] Allowed ev202 from Actor:" + std::to_string(senderActorID));
                        //playerlistMutex.unlock();
                    }
                }
                else {
                    //playerlistMutex.unlock();
                }
            }

            if (eventCode == 202) { // instantiate (do not instantiate us twice)

                Il2CppObject* targetPhotonViewObject = customDataHashtable->get_Item(7); // key 7 is target PhotonViewID

                if (targetPhotonViewObject != nullptr) {

                    int* pTargetPhotonViewID = reinterpret_cast<int*>(il2cpp_object_unbox_spoof(targetPhotonViewObject));

                    if (*pTargetPhotonViewID == localPlayer.photonViewID) {
                        //Log::debug("[ev202] Protected localplayer from Actor: " + std::to_string(senderActorID));
#ifndef PROD
                        printf("[ObjectFilter] Protected localplayer from Actor: %d\n", senderActorID);
#endif

                        //playerlistMutex.unlock();

                        ///return; //todo: uncomment this later
                    }
                    else {
                        //Log::debug("[ev202] Allowed ev202 from Actor:" + std::to_string(senderActorID));
                        //playerlistMutex.unlock();
                    }
                }
                else {
                    //playerlistMutex.unlock();
                }
            }

            if (eventCode == 405) // no idea wtf this is tbh but its recieved alongside 207
            {
#ifndef PROD
                printf("[Ev405] Protected localplayer from Actor: %d\n", senderActorID);
#endif
                return;
            }
        }
        //Log::debug("cuh1192");
        if (internalBlockEv207Toggle) {
            if (eventCode == 207) { // photon destroy photonplayer event
                return;
            }
        }
        //Log::debug("cuh1193");

        if (internalSanitizeEv200Toggle) {
            if (eventCode == 200) {

                if (localPlayerExists && localPlayer.loadingStage >= LoadingStage::PHOTON) {

                    if (/*senderID != localPlayer.photonActorID*/true) { //todo: remove this after testing

                        if (hashtableString.find("(System.Byte)4=(System.Object[])System.Object[]") != std::string::npos) {

                            Il2CppArray* keyFourObject = (Il2CppArray*)customDataHashtable->get_Item(4); // key 4 is rpc payload

                            if (keyFourObject != nullptr) {

                                bool detected = false;
                                bool doLimits = false;
                                bool doOwner = false;

                                switch (internalSanitizeEv200Mode) {

                                case (globals::photon::antis::inbound::SanitizeEv200Mode::Limits): {
                                    doLimits = true;
                                    break;
                                }
                                case (globals::photon::antis::inbound::SanitizeEv200Mode::Owned): {
                                    doOwner = true;
                                    break;
                                }
                                default:
                                    doLimits = true;
                                    doOwner = true;
                                    break;
                                }

                                if (doOwner) {
                                    if (senderActorID == 0) /// ignore server RPCs
                                        return OnEvent_o(eventData, methodInfo); //todo: RPCs can be sent viaServer by other players, this should be considered!

                                    bool found = false;
                                    int32_t targetPVID = -1;

                                    if (hashtableString.find("(System.Byte)7=(System.Int32)") != std::string::npos) {
                                        Il2CppObject* keySevenObject = customDataHashtable->get_Item(7);
                                        int32_t* pTargetPVID = reinterpret_cast<int32_t*>(il2cpp_object_unbox_spoof(keySevenObject));
                                        targetPVID = *pTargetPVID;
                                    }
                                    if (!found && (hashtableString.find("(System.Byte)0=(System.Int32)") != std::string::npos)) {
                                        Il2CppObject* keyZeroObject = customDataHashtable->get_Item(0);
                                        int32_t* pTargetPVID = reinterpret_cast<int32_t*>(il2cpp_object_unbox_spoof(keyZeroObject));
                                        targetPVID = *pTargetPVID;
                                    }

                                    if (found && (targetPVID != -1)) {

                                        PhotonView* targetPV = PhotonView::findPhotonView(targetPVID);

                                        if (targetPV != nullptr) {

                                            PhotonPlayer* targetPVOwnerPP = targetPV->get_Owner();

                                            if (targetPVOwnerPP != nullptr && (targetPVOwnerPP->getActorNumber() == localPlayer.photonPlayer->getActorNumber())) {
                                                detected = true;
                                            }
                                        }
                                    }
                                }

                                if (!detected) {
                                    for (int i = 0; i < keyFourObject->max_length; i++) {
                                        Il2CppObject* object = il2cpp_array_get(keyFourObject, Il2CppObject*, i);

                                        if (object != nullptr) {

                                            Type* objectType = (Type*)Type::GetType(object);
                                            std::string objectTypeString = "";
                                            if (objectType != nullptr) {

                                                Il2CppString* objectTypeIlString = objectType->ToString();

                                                if (objectTypeIlString != nullptr && objectTypeIlString->length > 0)
                                                    objectTypeString = ReadIl2CppString(objectTypeIlString);
                                            }

                                            if (doLimits) {
                                                if (objectTypeString.find("Vector3") != std::string::npos) {
                                                    Vector3* pPosition = reinterpret_cast<Vector3*>(il2cpp_object_unbox_spoof(object));

                                                    Vector3 position = *pPosition;

                                                    if (position.x >= AC_minVectors && position.x <= AC_maxVectors &&
                                                        position.y >= AC_minVectors && position.y <= AC_maxVectors &&
                                                        position.z >= AC_minVectors && position.z <= AC_maxVectors) {
                                                    }
                                                    else {
                                                        detected = true;
                                                    }
                                                    continue;
                                                }

                                                if (objectTypeString.find("Quaternion") != std::string::npos) {

                                                    Quaternion* pRotation = reinterpret_cast<Quaternion*>(il2cpp_object_unbox_spoof(object));

                                                    Quaternion rotation = *pRotation;

                                                    if (rotation.x >= AC_minVectors && rotation.x <= AC_maxVectors &&
                                                        rotation.y >= AC_minVectors && rotation.y <= AC_maxVectors &&
                                                        rotation.z >= AC_minVectors && rotation.z <= AC_maxVectors &&
                                                        rotation.w >= AC_minVectors && rotation.w <= AC_maxVectors) {
                                                    }
                                                    else {
                                                        detected = true;
                                                    }
                                                    continue;
                                                }
                                            }
                                        }
                                    }
                                }

                                if (detected) {

                                    //Log::debug("[Ev200] detected malicious RPC event!");
                                    //Log::debug(hashtableString);

                                    if (!internalSanitizeEv200BounceBack) {

                                        std::string notifString = ("[Ev200] Blocked malicious RPC Event from: " + std::to_string(senderActorID) + ".");
                                        pGui->notify.PushNotification<ImVec4(0.996, 0.455, 0.388, 1), 3.0f>(pGui->m_pTextures->tWarnFilled, notifString);

                                        return;
                                    }
                                    else {
                                        if (senderActorID != 0) { // ActorID 0 is the server
                                            std::unique_lock<std::timed_mutex> lock(playerlistMutex, std::defer_lock);

                                            if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {
                                                for (const auto& [targetPP, player] : cachedPlayerlist) {
                                                    if (player.photonActorID == senderActorID) {

                                                        switch (internalSanitizeEv200BounceBackMode) {
                                                        case (globals::photon::antis::BounceBackMode::BulletCrash): {
                                                            if (localPlayer.loadingStage >= LoadingStage::LOADED) {

                                                                //newThread(PlayerList::BulletCrashPL, targetPP);

                                                                std::string notifString = ("[Ev200] Bouncing RAM Crash to Actor: " + std::to_string(senderActorID) + ", " + player.DisplayName + ".");

                                                                pGui->notify.PushNotification<ImVec4(1.0, 0.0, 0.0, 1), 3.0f>(pGui->m_pTextures->tWarnFilled, notifString);
                                                            }
                                                            else {
                                                                Log::debug("[Ev200] Cannot RAM Crash, localPlayer is loading! Scheduling RAM Crash...");
                                                                /*
                                                                globals::onUpdate::functionQueueLoaded.push_back(
                                                                    globals::onUpdate::Exec(
                                                                        globals::onUpdate::OnUpdateFunc::Callback,
                                                                        globals::onUpdate::Info::Callback(Callbacks::ScheduledBulletCrashPL, targetPP)
                                                                    )
                                                                );

                                                                ExecuteOnUpdateQueue();
                                                                */
                                                            }
                                                            break;
                                                        }
                                                        case (globals::photon::antis::BounceBackMode::Death): {
                                                            //Log::debug("[Ev200] Scheduling Death...");
                                                            /*

                                                            globals::onUpdate::functionQueueLoaded.push_back(
                                                                globals::onUpdate::Exec(
                                                                    globals::onUpdate::OnUpdateFunc::Callback,
                                                                    globals::onUpdate::Info::Callback(Callbacks::DeathTarget, targetPP)
                                                                )
                                                            );

                                                            ExecuteOnUpdateQueue();
                                                            */

                                                            break;
                                                        }
                                                        default:
                                                            Log::error("invalid bounce back mode!");
                                                            break;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        //Log::debug("cuh1194");
        if (AC_toggle) { // anti cheat toggle

            bool runAntiCheat = true;

            if (AC_pauseOnLoading) {

                runAntiCheat = false;

                if (localPlayerExists && (localPlayer.loadingStage >= LoadingStage::LOADED))
                {
                    RecRoomPlayer* playerPlayer = RecRoomPlayer::GetFromActorNumber(localPlayer.photonActorID);

                    if (playerPlayer != nullptr) {
                        if (playerPlayer->get_IsInitialized() && playerPlayer->get_IsInitialLoadFinished())
                            runAntiCheat = true;
                    }
                }
            }

            if (AC_excludeServerEvents) {
                if (senderActorID <= 0)
                    runAntiCheat = false;
            }

            if (runAntiCheat && eventCode == 202) { // instantiate event is 202

                std::string normalizedHashtableString = ToUpperCase(hashtableString);

                bool detected{ false };

                // im way too lazy to not use a shit ton of if statements here, go fuck yourself, optimize urself then biiiiiiaatch

                if (AC_developerPrefabs) {

                    std::vector<std::string> blacklist{ "SANDBOX_LADDER_HOOK", "SANDBOX_FRIENDOTRON", "GREENSCREEN_TOOL", "STUNTRUNNER" };
                    for (auto& prefab : blacklist) {
                        if (normalizedHashtableString.find(prefab) != std::string::npos) {
                            detected = true;
                        }
                    }
                }

                if (AC_commonPrefabs) {

                    std::vector<std::string> blacklist{ "ARENA", "QUEST", "PAINTBALL", "VEHICLE", "SANDBOX" }; // common prefabs spawned in by IDIOTS

                    for (auto& prefab : blacklist) {
                        if (normalizedHashtableString.find(prefab) != std::string::npos) {
                            detected = true;
                        }
                    }
                }

                if (!detected && AC_bossPrefabs) {

                    std::vector<std::string> blacklist{ "BOSS", "BOGMONSTER" };

                    for (auto& prefab : blacklist) {
                        if (normalizedHashtableString.find(prefab) != std::string::npos) {
                            detected = true;
                        }
                    }
                }

                if (!detected && AC_managerPrefabs) {
                    if (normalizedHashtableString.find("MANAGER]") != std::string::npos) {
                        detected = true;
                    }
                }

                if (!detected && AC_enemyPrefabs) {
                    if (normalizedHashtableString.find("ENEMY") != std::string::npos) {
                        detected = true;
                    }
                }

                if (!detected && AC_scaleCheck) {

                    if (hashtableString.find("(System.Byte)9=(UnityEngine.Vector3)") != std::string::npos) {

                        Il2CppObject* keyNineObject = customDataHashtable->get_Item(9); // key 1 is position

                        if (keyNineObject != nullptr) {

                            Vector3* pScale = reinterpret_cast<Vector3*>(il2cpp_object_unbox_spoof(keyNineObject));
                            Vector3 scale = *pScale;

                            bool unusual = false;
                            bool limits = false;

                            switch (AC_scaleMode) {
                            case (globals::photon::antis::inbound::antiCheat::BadScaleMode::Unusual): {
                                unusual = true;
                                break;
                            }
                            case (globals::photon::antis::inbound::antiCheat::BadScaleMode::Limits): {
                                limits = true;
                                break;
                            }
                            case (globals::photon::antis::inbound::antiCheat::BadScaleMode::Both): {
                                unusual = true;
                                limits = true;
                                break;
                            }
                            default:
                                break;
                            }

                            if (unusual) {
                                if (!(scale.x == scale.y && scale.y == scale.z)) {
                                    detected = true;
                                }
                            }

                            if (limits) {
                                if (!(scale.x >= AC_minScale && scale.x <= AC_maxScale &&
                                    scale.y >= AC_minScale && scale.y <= AC_maxScale &&
                                    scale.z >= AC_minScale && scale.z <= AC_maxScale)) {
                                    detected = true;
                                }
                            }
                        }
                    }
                }

                if (!detected && AC_vectorsCheck) {


                    if (hashtableString.find("(System.Byte)1=(UnityEngine.Vector3)") != std::string::npos) {

                        Il2CppObject* keyOneObject = customDataHashtable->get_Item(1); // key 1 is position

                        if (keyOneObject != nullptr) {

                            Vector3* pPosition = reinterpret_cast<Vector3*>(il2cpp_object_unbox_spoof(keyOneObject));

                            Vector3 position = *pPosition;

                            if (position.x >= AC_minVectors && position.x <= AC_maxVectors &&
                                position.y >= AC_minVectors && position.y <= AC_maxVectors &&
                                position.z >= AC_minVectors && position.z <= AC_maxVectors) {
                            }
                            else {
                                detected = true;
                            }
                        }
                    }

                    if (hashtableString.find("(System.Byte)2=(") != std::string::npos) {

                        Il2CppObject* keyTwoObject = customDataHashtable->get_Item(2); // key 2 is rotation (custom quaternion class)

                        if (keyTwoObject->klass->field_count == 1) { //todo: add check for field type is quaternion

                            if (keyTwoObject != nullptr) {

                                Quaternion rotation = GetField<Quaternion>(keyTwoObject, 16);

                                if (rotation.x >= AC_minVectors && rotation.x <= AC_maxVectors &&
                                    rotation.y >= AC_minVectors && rotation.y <= AC_maxVectors &&
                                    rotation.z >= AC_minVectors && rotation.z <= AC_maxVectors &&
                                    rotation.w >= AC_minVectors && rotation.w <= AC_maxVectors) {
                                }
                                else {
                                    detected = true;
                                }
                            }
                        }
                    }
                }

                if (!detected && AC_vectorsCheck && AC_vectorsCheckStrict) {

                    Il2CppArray* keyFiveObject = (Il2CppArray*)customDataHashtable->get_Item(5); // key 5 is Object[]

                    if (keyFiveObject != nullptr) {

                        for (int i = 0; i < keyFiveObject->max_length; i++) {
                            Il2CppObject* objectObject = il2cpp_array_get(keyFiveObject, Il2CppObject*, i);

                            if (objectObject != nullptr) {

                                if (objectObject != nullptr) {
                                    Type* objectObjectType = (Type*)Type::GetType(objectObject);
                                    if (objectObjectType != nullptr) {

                                        Il2CppString* objectObjectTypeString = objectObjectType->ToString();

                                        if (objectObjectTypeString != nullptr && (objectObjectTypeString->length > 0)) {
                                            std::string typeString = ReadIl2CppString(objectObjectTypeString);

                                            if (typeString == "Type: Vector3") {

                                                Vector3* pVector = reinterpret_cast<Vector3*>(il2cpp_object_unbox_spoof(objectObject));
                                                Vector3 vector = *pVector;

                                                if (vector.x >= AC_minVectors && vector.x <= AC_maxVectors &&
                                                    vector.y >= AC_minVectors && vector.y <= AC_maxVectors &&
                                                    vector.z >= AC_minVectors && vector.z <= AC_maxVectors) {
                                                }
                                                else {
                                                    detected = true;
                                                }

                                                break;
                                            }
                                            else if (typeString == "Type: Quaternion") {

                                                Quaternion* pQuaternion = reinterpret_cast<Quaternion*>(il2cpp_object_unbox_spoof(objectObject));
                                                Quaternion quaternion = *pQuaternion;

                                                if (quaternion.x >= AC_minVectors && quaternion.x <= AC_maxVectors &&
                                                    quaternion.y >= AC_minVectors && quaternion.y <= AC_maxVectors &&
                                                    quaternion.z >= AC_minVectors && quaternion.z <= AC_maxVectors &&
                                                    quaternion.w >= AC_minVectors && quaternion.w <= AC_maxVectors) {
                                                }
                                                else {
                                                    detected = true;
                                                }
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                if (detected) {

                    std::string prefabString = "PREFAB_NOT_FOUND";
                    Il2CppObject* keyZeroObject = customDataHashtable->get_Item(0);

                    if (keyZeroObject != nullptr) {
                        Type* keyZeroType = (Type*)Type::GetType(keyZeroObject);
                        if (keyZeroType != nullptr) {

                            Il2CppString* keyZeroIl2CppString = keyZeroType->ToString();

                            if (keyZeroIl2CppString != nullptr && (keyZeroIl2CppString->length > 0)) {
                                std::string typeString = ReadIl2CppString(keyZeroIl2CppString);

                                if (typeString == "Type: String") {
                                    prefabString = ReadIl2CppString((Il2CppString*)keyZeroObject);
                                }
                            }
                        }
                    }

                    Log::debug("[Ev202-AC] detected blacklisted prefab: " + prefabString + " from Actor: " + std::to_string(senderActorID));
                    //Log::debug(hashtableString);

                    if (AC_destroyPrefab) {

                        Il2CppObject* keySevenObject = customDataHashtable->get_Item(7); // key 7 is instantiated object photon view id

                        if (keySevenObject != nullptr) {
                            int32_t* ppvid = reinterpret_cast<int32_t*>(il2cpp_object_unbox_spoof(keySevenObject));

                            //todo: transfer ownership of the pv with Ev210 before sending destroy events

                            bool localPlayerLoaded = false;

                            if (localPlayerExists && localPlayer.loadingStage >= LoadingStage::LOADED) {
                                auto playerPlayer = RecRoomPlayer::GetFromActorNumber(localPlayer.photonActorID);
                                if (playerPlayer != nullptr && playerPlayer->get_IsInitialized() && playerPlayer->get_IsInitialLoadFinished()) {
                                    //PlayerList::DestroyGameObject(ppvid);
                                    localPlayerLoaded = true;
                                }
                            }

                            if (!localPlayerLoaded) { /// schedule prefab for destroy when we load in
                                /*
                                globals::onUpdate::functionQueueLoaded.push_back(
                                    globals::onUpdate::Exec(
                                        globals::onUpdate::OnUpdateFunc::Callback,
                                        globals::onUpdate::Info::Callback(PlayerList::DestroyGameObject, ppvid)
                                    )
                                );

                                ExecuteOnUpdateQueue();
                                */
                            }
                        }
                    }

                    if (!AC_blockEvent) {
                        bool found = false;
                        std::unique_lock<std::timed_mutex> lock(playerlistMutex, std::defer_lock);

                        if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {
                            for (const auto& [targetPP, player] : cachedPlayerlist) {
                                if (player.photonActorID == senderActorID) {
                                    found = true;
                                    std::string notifString = ("[Ev202-AC] Detected Prefab: " + prefabString + " from Actor: " + std::to_string(senderActorID) + ", " + player.DisplayName + ".");
                                    pGui->notify.PushNotification<ImVec4(0.996, 0.455, 0.388, 1), 3.0f>(pGui->m_pTextures->tWarnFilled, notifString);
                                    break;
                                }
                            }
                            lock.unlock();
                        }
                        else {
                            Log::error("playerlistMutex timed out in OnEvent Ihook!");
                        }
                        if (!found) {
                            std::string notifString = ("[Ev202-AC] Detected Prefab " + prefabString + " from Actor: " + std::to_string(senderActorID) + ", No Player Found!.");
                            pGui->notify.PushNotification<ImVec4(1.0, 0.0, 0.0, 1), 3.0f>(pGui->m_pTextures->tWarnFilled, notifString);
                        }
                    }

                    if (AC_bounceBack) {
                        if (senderActorID != 0) { // ActorID 0 is the server
                            std::unique_lock<std::timed_mutex> lock(playerlistMutex, std::defer_lock);

                            if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {
                                for (const auto& [targetPP, player] : cachedPlayerlist) {
                                    if ((player.photonActorID == senderActorID) && (senderActorID != localPlayer.photonActorID)) {

                                        Log::debug("[Ev202-AC] Bouncing Back to Actor: " + std::to_string(senderActorID));

                                        switch (AC_bounceBackMode) {
                                        case (globals::photon::antis::BounceBackMode::BulletCrash): {
                                            if (localPlayer.loadingStage >= LoadingStage::LOADED) {

                                                //newThread(PlayerList::BulletCrashPL, targetPP);

                                                std::string notifString = ("[Ev202-AC] Bouncing RAM Crash to Actor: " + std::to_string(senderActorID) + ", " + player.DisplayName + ".");

                                                pGui->notify.PushNotification<ImVec4(1.0, 0.0, 0.0, 1), 3.0f>(pGui->m_pTextures->tWarnFilled, notifString);
                                            }
                                            else {
                                                Log::debug("[Ev202-AC] Cannot RAM Crash, localPlayer is loading! Scheduling RAM Crash...");
                                                /*
                                                globals::onUpdate::functionQueueLoaded.push_back(
                                                    globals::onUpdate::Exec(
                                                        globals::onUpdate::OnUpdateFunc::Callback,
                                                        globals::onUpdate::Info::Callback(Callbacks::ScheduledBulletCrashPL, targetPP)
                                                    )
                                                );

                                                ExecuteOnUpdateQueue();
                                                */
                                            }
                                            break;
                                        }

                                        case (globals::photon::antis::BounceBackMode::Death): {

                                            Log::debug("[Ev202-AC] Scheduling Death...");
                                            /*
                                            globals::onUpdate::functionQueueLoaded.push_back(
                                                globals::onUpdate::Exec(
                                                    globals::onUpdate::OnUpdateFunc::Callback,
                                                    globals::onUpdate::Info::Callback(Callbacks::DeathTarget, targetPP)
                                                )
                                            );

                                            ExecuteOnUpdateQueue();
                                            */

                                            break;
                                        }
                                        default:
                                            Log::error("Invalid BounceBack Selection!");
                                            break;
                                        }
                                        break;
                                    }
                                }
                                lock.unlock();
                            }
                            else {
                                Log::error("playerlistMutex timed out in OnEvent Ihook!");
                            }
                        }
                    }


                    if (AC_announceOffender) {

                        if (localPlayerExists) {

                            RecRoomPlayer* localRecRoomPlayer = RecRoomPlayer::GetFromActorNumber(localPlayer.photonActorID);
                            if (localRecRoomPlayer != nullptr) {

                                if (!PhotonNetwork::get_isMasterClient(localPlayer.photonPlayer)) {
                                    PhotonNetwork::set_MasterClient(localPlayer.photonPlayer);
                                    Sleep(500);
                                }

                                CircuitsV2Manager* manager = CircuitsV2Manager::GetCircuitsV2Manager();
                                if (manager != nullptr) {

                                    PhotonView* photonView = (PhotonView*)manager->get_gameObject()->GetComponent("PhotonView");

                                    Type* objectType = (Type*)Type::getType(il2cpp_string_new_spoof("System.Object"));

                                    std::string notifString = ("[Mocha|Anti-Cheat] Detected " + prefabString + " from Actor: " + std::to_string(senderActorID) + ", No Name Found!.");

                                    {
                                        std::unique_lock<std::timed_mutex> lock(playerlistMutex, std::defer_lock);

                                        if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {
                                            for (const auto& [targetPP, player] : cachedPlayerlist) {
                                                if (player.photonActorID == senderActorID) {
                                                    notifString = ("[Mocha|Anti-Cheat] Detected " + prefabString + " from: " + player.DisplayName + ".");
                                                    break;
                                                }
                                            }
                                            lock.unlock();
                                        }
                                        else {
                                            Log::error("playerlistMutex timed out in OnEvent Ihook!");
                                        }
                                    }

                                    Il2CppObject* object = (Il2CppObject*)il2cpp_string_new_spoof(notifString.c_str());
                                    Il2CppArray* payloadArray = Array::createInstance(objectType, 1);

                                    il2cpp_array_set(payloadArray, Il2CppObject*, 0, object);
                                    /*
                                    globals::onUpdate::functionQueueLoaded.push_back(
                                        globals::onUpdate::Exec(
                                            globals::onUpdate::OnUpdateFunc::RPC,
                                            globals::onUpdate::Info::RPC(photonView, il2cpp_string_new_spoof("RpcSendMajorNotification"), All, payloadArray, 2, true)
                                        )
                                    );

                                    ExecuteOnUpdateQueue();
                                    */
                                }
                            }
                        }

                    }

                    if (AC_blockOffenderEvents) {

                        std::unique_lock<std::timed_mutex> lock(playerlistMutex, std::defer_lock);

                        if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {
                            for (auto& [targetPP, player] : cachedPlayerlist) {
                                if (player.photonActorID == senderActorID) {
                                    player.blockEvents = true;
                                    std::string notifString = ("[Ev202-AC] Blocked Events from Actor: " + std::to_string(senderActorID) + ", " + player.DisplayName + ".");
                                    Log::debug(notifString);
                                    pGui->notify.PushNotification<ImVec4(0.0, 1.0, 0.0, 1), 3.0f>(pGui->m_pTextures->tWarnFilled, notifString);
                                    break;
                                }
                            }
                            lock.unlock();
                        }
                        else {
                            Log::error("playerlistMutex timed out in OnEvent Ihook!");
                        }
                    }

                    if (AC_blockEvent) {
                        return;
                    }

                }
            }
        }
        //Log::debug("cuh1195");
        if (internalDebugToggle && shouldDebug)
            Log::debug("-----------------------------------------------------------------------------------");

        //Log::debug("cuh119");
    }
    else {
        if (internalDebugToggle && shouldDebug)
        {
            //Log::debug("cuh1100");
            Log::debug("-----------------------------------------------------------------------------------");
            Log::debug("Sender: " + std::to_string(senderActorID));
            Log::debug("Event Code: " + std::to_string(eventCode));
            Log::debug("Payload: " + typeCDString);

            if (eventCode == 201) {

                Il2CppArray* payloadArray = (Il2CppArray*)customData;

                if (payloadArray != nullptr) {

                    Log::debug("object array max: " + std::to_string(payloadArray->max_length));

                    for (int i = 0; i < payloadArray->max_length; i++) {
                        Il2CppObject* object = il2cpp_array_get(payloadArray, Il2CppObject*, i);

                        if (object != nullptr) {

                            Type* objectType = (Type*)Type::GetType(object);

                            std::string objectTypeString = ReadIl2CppString(objectType->ToString());
                            Log::debug("object type: " + objectTypeString);
                        }
                    }
                }

            }

            Log::debug("-----------------------------------------------------------------------------------");
        }
    }
#endif
    //return OnEvent_o(eventData, methodInfo);
    return SafeCall_OnEvent_o(pParams);
    //return CallWithExceptionHandling(SafeCall_OnEvent_o, pParams);
}


void __fastcall SafeCall_OnEvent_o(void* params)
{
    const auto pParams = static_cast<OnEventParamInfo*>(params);

    EventData*& eventData = pParams->eventData;
    void*& methodInfo = pParams->methodInfo;
    
    if (const bool& shouldHook = globals::Ihooks::OnEvent;
        !shouldHook)
        return hook_manager::get()["onevent"]->call<void>(eventData, methodInfo);
        //return OnEvent_o(eventData, methodInfo);

    if (eventData == nullptr)
        return hook_manager::get()["onevent"]->call<void>(eventData, methodInfo);
        //return OnEvent_o(eventData, methodInfo);

    const int senderActorID = eventData->get_Sender();
    const uint8_t eventCode = GetField<uint8_t>(eventData, 16);

    if (InvalidActorProtection(senderActorID))
        return;
    if (RestrictedActorProtection(senderActorID, eventCode))
        return;
    switch (eventCode)
    {
    case 201:
        {
            if (Ev201Protection(senderActorID))
                return;
            break;
        }
    case 207:
        {
            if (Ev207Protection(senderActorID))
                return;
            break;
        }
    default:
        break;
    }
    
    Il2CppObject* customData = eventData->get_CustomData();
    if (customData == nullptr)
        return hook_manager::get()["onevent"]->call<void>(eventData, methodInfo);
      //return OnEvent_o(eventData, methodInfo);

    const auto eventCustomDataType = static_cast<Type*>(Type::GetType(customData));
    std::string customDataTypeString{"NULLPTR"};

    if (eventCustomDataType != nullptr)
    {
        if (Il2CppString* customDataTypeIlString = eventCustomDataType->ToString();
            customDataTypeIlString != nullptr && customDataTypeIlString->length > 0)
            customDataTypeString = ReadIl2CppString(customDataTypeIlString);
    }

    if (customDataTypeString == "Type: Hashtable")
    {
        auto* customDataHashtable = static_cast<Hashtable*>(customData);

        switch (eventCode)
        {
        case 200:
            {
                if (Ev200Protection(customDataHashtable, senderActorID))
                    return;
                break;
            }
        case 202:
            {
                if (Ev202Protection(customDataHashtable, senderActorID))
                    return;
                break;
            }
        case 204:
            {
                if (Ev204Protection(customDataHashtable, senderActorID))
                    return;
                break;
            }
        default:
            break;
        }
    }
    
    return hook_manager::get()["onevent"]->call<void>(eventData, methodInfo);
    //return OnEvent_o(pParams->eventData, pParams->methodInfo);
}
