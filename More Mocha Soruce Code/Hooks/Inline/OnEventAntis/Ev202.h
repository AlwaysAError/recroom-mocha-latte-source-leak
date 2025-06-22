#pragma once

// instantiate event

struct FilterResponse
{
    bool flagged;
    std::string message;
};

FilterResponse FilterInstantiatebHashtable(Hashtable*& hashtablePayload)
{
    namespace global = globals::photon::protections::inbound::Ev202;

    std::string hashtableString;
    if (Il2CppString* customDataHashtableString = hashtablePayload->ToString();
        customDataHashtableString != nullptr && customDataHashtableString->length > 0)
    {
        hashtableString = ReadIl2CppString(customDataHashtableString);
    }

    const std::string normalizedHashtableString = ToUpperCase(hashtableString);

    if (const auto& iFilterPrefab = global::filterPrefab;
        iFilterPrefab)
    {
        for (const auto& iBlacklistedPrefabPresets = global::blacklistedPrefabPresets;
             const auto& preset : iBlacklistedPrefabPresets | std::views::values)
        {
            if (preset.enabled)
            {
                for (const auto& substring : preset.prefabList)
                {
                    if (normalizedHashtableString.find(substring) != std::string::npos)
                    {
                        std::string prefabString = "NOT_FOUND";

                        if (Il2CppObject* keyZeroObject = hashtablePayload->get_Item(0))
                        {
                            if (auto* keyZeroType = static_cast<Type*>(Type::GetType(keyZeroObject)))
                            {
                                if (Il2CppString* keyZeroIl2CppString = keyZeroType->ToString();
                                    keyZeroIl2CppString->length > 0)
                                {
                                    if (std::string typeString = ReadIl2CppString(keyZeroIl2CppString);
                                        typeString == "Type: String")
                                    {
                                        prefabString = ReadIl2CppString((Il2CppString*)keyZeroObject);
                                    }
                                }
                            }
                        }

                        return FilterResponse{true, "bad prefab: \"" + prefabString + "\""};
                    }
                }
            }
        }
    }

    if (const auto& iFilterScale = global::filterScale;
        iFilterScale)
    {
        if (hashtableString.find("(System.Byte)9=(UnityEngine.Vector3)") != std::string::npos)
        {
            if (Il2CppObject* keyNineObject = hashtablePayload->get_Item(9))
            {
                // key 9 is scale

                const Vector3* pScale = static_cast<Vector3*>(il2cpp_object_unbox_spoof(keyNineObject));
                Vector3 scale = *pScale;

                bool unusual = false;
                bool limits = false;

                switch (const auto& iScaleFilterMode = global::scaleFilterMode;
                    iScaleFilterMode)
                {
                case (global::ScaleFilterMode::Unusual):
                    {
                        unusual = true;
                        break;
                    }
                case (global::ScaleFilterMode::Limits):
                    {
                        limits = true;
                        break;
                    }
                case (global::ScaleFilterMode::Both):
                    {
                        unusual = true;
                        limits = true;
                        break;
                    }
                }

                if (unusual)
                {
                    constexpr float EPSILON = 0.0001f;
                    
                    if (!(fabsf(scale.x - scale.y) < EPSILON && fabsf(scale.y - scale.z) < EPSILON))
                    {
                        return FilterResponse{true, "bad prefab scale"};
                    }
                }

                const auto& iScaleMinimumLimit = global::scaleMinimumLimit;
                const auto& iScaleMaximumLimit = global::scaleMaximumLimit;

                if (limits)
                {
                    if (!(scale.x >= iScaleMinimumLimit && scale.x <= iScaleMaximumLimit &&
                        scale.y >= iScaleMinimumLimit && scale.y <= iScaleMaximumLimit &&
                        scale.z >= iScaleMinimumLimit && scale.z <= iScaleMaximumLimit))
                    {
                        return FilterResponse{true, "bad prefab scale"};
                    }
                }
            }
        }
    }

    if (const auto& iFilterVectors = global::filterVectors;
        iFilterVectors)
    {
        if (hashtableString.find("(System.Byte)1=(UnityEngine.Vector3)") != std::string::npos)
        {
            if (Il2CppObject* keyOneObject = hashtablePayload->get_Item(1))
            {
                // key 1 is position

                const Vector3* pPosition = static_cast<Vector3*>(il2cpp_object_unbox_spoof(keyOneObject));

                const auto& iVectorsMinimumLimit = global::vectorsMinimumLimit;
                const auto& iVectorsMaximumLimit = global::vectorsMaximumLimit;

                if (const Vector3 position = *pPosition;
                    position.x >= iVectorsMinimumLimit && position.x <= iVectorsMaximumLimit &&
                    position.y >= iVectorsMinimumLimit && position.y <= iVectorsMaximumLimit &&
                    position.z >= iVectorsMinimumLimit && position.z <= iVectorsMaximumLimit)
                {
                }
                else
                {
                    return FilterResponse{true, "prefab too far"};
                }
            }
        }

        /*
        if (hashtableString.find("(System.Byte)2=(") != std::string::npos)
        {
            if (Il2CppObject* keyTwoObject = hashtablePayload->get_Item(2);
                // key 2 is rotation (custom obfuscated quaternion class)
                keyTwoObject->klass->field_count == 1)
            {
                //todo: add check for field type is quaternion

                if (keyTwoObject != nullptr)
                {
                    const auto& iVectorsMinimumLimit = global::vectorsMinimumLimit;
                    const auto& iVectorsMaximumLimit = global::vectorsMaximumLimit;

                    if (const auto rotation = GetField<Quaternion>(keyTwoObject, 16);
                        rotation.x >= iVectorsMinimumLimit && rotation.x <= iVectorsMaximumLimit &&
                        rotation.y >= iVectorsMinimumLimit && rotation.y <= iVectorsMaximumLimit &&
                        rotation.z >= iVectorsMinimumLimit && rotation.z <= iVectorsMaximumLimit &&
                        rotation.w >= iVectorsMinimumLimit && rotation.w <= iVectorsMaximumLimit)
                    {
                    }
                    else
                    {
                        return FilterResponse{true, "prefab not sigma enough"};
                    }
                }
            }
        }
        */
    }

    if (const auto& iVectorsFilterData = global::vectorsFilterData;
        iVectorsFilterData)
    {
        if (hashtableString.find("(System.Byte)5=(System.Object[])System.Object[]") != std::string::npos)
        {
            if (auto* keyFiveObject = static_cast<Il2CppArray*>(hashtablePayload->get_Item(5)))
            {
                // key 5 is Object[] (data)

                for (unsigned long long i = 0; i < keyFiveObject->max_length; i++)
                {
                    if (Il2CppObject* objectObject = il2cpp_array_get(keyFiveObject, Il2CppObject*, i))
                    {
                        if (auto* objectObjectType = static_cast<Type*>(Type::GetType(objectObject)))
                        {
                            if (Il2CppString* objectObjectTypeString = objectObjectType->ToString();
                                objectObjectTypeString != nullptr && (objectObjectTypeString->length > 0))
                            {
                                std::string typeString = ReadIl2CppString(objectObjectTypeString);

                                if (typeString == "Type: Vector3")
                                {
                                    const Vector3* pVector = static_cast<Vector3*>(il2cpp_object_unbox_spoof(
                                        objectObject));

                                    const auto& iVectorsMinimumLimit = global::vectorsMinimumLimit;
                                    const auto& iVectorsMaximumLimit = global::vectorsMaximumLimit;

                                    if (const Vector3 vector = *pVector;
                                        vector.x >= iVectorsMinimumLimit && vector.x <= iVectorsMaximumLimit &&
                                        vector.y >= iVectorsMinimumLimit && vector.y <= iVectorsMaximumLimit &&
                                        vector.z >= iVectorsMinimumLimit && vector.z <= iVectorsMaximumLimit)
                                    {
                                    }
                                    else
                                    {
                                        return FilterResponse{true, "prefab data is bad"};
                                    }

                                    break;
                                }

                                if (typeString == "Type: Quaternion")
                                {
                                    const Quaternion* pQuaternion = static_cast<Quaternion*>(il2cpp_object_unbox_spoof(
                                        objectObject));

                                    const auto& iVectorsMinimumLimit = global::vectorsMinimumLimit;
                                    const auto& iVectorsMaximumLimit = global::vectorsMaximumLimit;

                                    if (const Quaternion quaternion = *pQuaternion;
                                        quaternion.x >= iVectorsMinimumLimit && quaternion.x <= iVectorsMaximumLimit &&
                                        quaternion.y >= iVectorsMinimumLimit && quaternion.y <= iVectorsMaximumLimit &&
                                        quaternion.z >= iVectorsMinimumLimit && quaternion.z <= iVectorsMaximumLimit &&
                                        quaternion.w >= iVectorsMinimumLimit && quaternion.w <= iVectorsMaximumLimit)
                                    {
                                    }
                                    else
                                    {
                                        return FilterResponse{true, "prefab data is bad"};
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

    return FilterResponse{false, "filter not flagged"};
}

bool Ev202Protection(Hashtable*& customDataHashtable, const int& senderActorID)
{
    namespace global = globals::photon::protections::inbound::Ev202;

    if (const auto& iToggle = global::toggle;
        iToggle)
    {
        const auto& iDropAllEvents = global::dropAllEvents;
        const auto& iDropServerEvents = global::dropServerEvents;

        #ifdef PROD

        { // whitelist so our RAM Crash guns dont get blocked.
            std::string hashtableString = "";
            if (Il2CppString* customDataHashtableString = customDataHashtable->ToString();
                customDataHashtableString != nullptr && customDataHashtableString->length > 0)
            {
                hashtableString = ReadIl2CppString(customDataHashtableString);
            }

            if (hashtableString.find("[QuEsT_dRaCuLa1_BlUnDeRbUsS]") != std::string::npos || hashtableString.find("[QuEsT_gObLiN_wAnD]") != std::string::npos)
            {
                return false;
            }
        }
        
        #endif
        
        if (const auto& iDropSelfEvents = global::dropSelfEvents;
            iDropAllEvents && ((senderActorID != 0 || iDropServerEvents) || ((localPlayerExists && senderActorID !=
                localPlayer.photonActorID) || iDropSelfEvents)))
            return true;

        if (const auto& iFilterServerEvents = global::filterServerEvents;
            senderActorID == 0 && !iFilterServerEvents)
            return false;

        if (const auto& iFilterSelfEvents = global::filterSelfEvents;
            localPlayerExists && senderActorID == localPlayer.photonActorID && !iFilterSelfEvents)
            return false;

        bool detected = false;
        std::string message = "being indian.";
        std::string senderDisplayName = "NAME_NOT_FOUND";

        const auto& iTotalActorLimit = global::totalActorLimit;
        if (const auto& iRateLimit = global::rateLimit;
            iRateLimit || iTotalActorLimit)
        {
            std::unique_lock lock(playerlistMutex, std::defer_lock);
            if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout)))
            {
                PhotonPlayer* targetPhotonPlayer = nullptr;
                for (const auto& [photonPlayer, playerInfo] : cachedPlayerlist)
                {
                    if (playerInfo.photonActorID == senderActorID)
                    {
                        targetPhotonPlayer = photonPlayer;
                        break;
                    }
                }

                if (!targetPhotonPlayer || !cachedPlayerlist.contains(targetPhotonPlayer))
                {
                    lock.unlock();
                    return true;
                }

                PlayerInfo& playerInfo = cachedPlayerlist[targetPhotonPlayer];
                senderDisplayName = playerInfo.DisplayName;

                if (iTotalActorLimit)
                {
                    if (const auto& iTotalActorLimitAmount = global::totalActorLimitAmount;
                        playerInfo.Ev202TotalInstantiations >= iTotalActorLimitAmount)
                    {
                        detected = true;
                        const std::string notifString = ("[ObjectFilter] Total Event Limit Exceeded: [" + std::to_string(senderActorID) + "] " + playerInfo.DisplayName);
                        pGui->notify.PushNotification<ImVec4(0.996f, 0.455f, 0.388f, 1), 3.0f>(pGui->m_pTextures->tWarnFilled, notifString);
                    }
                    else
                        playerInfo.Ev202TotalInstantiations++;
                }

                if (const auto& iRateLimitDuringLoading = global::rateLimitDuringLoading;
                    iRateLimit && (playerInfo.loadingStage >= LoadingStage::LOADED || iRateLimitDuringLoading))
                {
                    const int& EVENT_LIMIT = global::rateLimitLimit;
                    const std::chrono::milliseconds EVENT_WINDOW(global::rateLimitMS);

                    // Check rate limit
                    if (const auto now = std::chrono::steady_clock::now();
                        now - playerInfo.Ev202RateLimitWindowStart > EVENT_WINDOW)
                    {
                        // Window expired, reset count
                        playerInfo.Ev202RateLimitWindowStart = now;
                        playerInfo.Ev202RateLimitEventCount = 1;
                    }

                    if (playerInfo.Ev202RateLimitEventCount < EVENT_LIMIT)
                    {
                        playerInfo.Ev202RateLimitEventCount++;
                    }
                    else
                    {
                        detected = true;
                        const std::string notifString = ("[ObjectFilter] Rate Limitting: [" + std::to_string(senderActorID) + "] " + playerInfo.DisplayName);
                        pGui->notify.PushNotification<ImVec4(0.996f, 0.455f, 0.388f , 1), 3.0f>(pGui->m_pTextures->tWarnFilled, notifString);

                        Log::debug(notifString);
                    }
                }

                lock.unlock();
            }
            else
            {
                Log::error("playerlistMutex timed out in Ev202Protection!");
                return true;
            }
        }

        std::string hashtableString = "";
        if (Il2CppString* customDataHashtableString = customDataHashtable->ToString();
            customDataHashtableString != nullptr && customDataHashtableString->length > 0)
        {
            hashtableString = ReadIl2CppString(customDataHashtableString);
        }

        if (const auto& iDropMalformedPayload = global::dropMalformedPayload;
            iDropMalformedPayload)
        {
            bool found = false;

            if (hashtableString.find("(System.Byte)0=(System.String)") == std::string::npos)
            {
                found = true;
            }
            else
            {
                auto* prefabString = (Il2CppString*)customDataHashtable->get_Item(0); // key 0 is prefab name, System.String

                if (prefabString == nullptr || prefabString->length <= 0)
                {
                    found = true;
                }

                if (const std::string prefabStringString = ReadIl2CppString(prefabString);
                    !found && (prefabStringString.empty() || prefabStringString == std::string("")))
                {
                    found = true;
                }
            }

            if (found)
            {
                /// Malformed 202 events throw an exception thats not an Il2CppException*
                /// which is supposed to get picked by some higher SEH, this does not happen
                /// because we're inline hooking using a manually mapped dll. These events are
                /// not always sent by cheaters so we return here skipping other logic.

                Log::debug("[ObjectFilter] dropped malformed event from actor: " + std::to_string(senderActorID) + ".");
                const std::string notifString = ("[ObjectFilter] Blocked Malformed Payload from Actor: " + std::to_string(senderActorID) + ".");
                pGui->notify.PushNotification<ImVec4(1.0, 0.0, 1.0, 1), 3.0f>(pGui->m_pTextures->tWarnFilled, notifString);
                return true;
            }
        }

        const auto& iFilterWhileLoading = global::filterWhileLoading;

        if (const auto& iFilterToggle = global::filterToggle;
            !detected && iFilterToggle && ((localPlayerExists && localPlayer.loadingStage >= LoadingStage::LOADED) ||
                iFilterWhileLoading))
        {

            if (const auto& iDropBackpacks = global::dropBackpacks;
                iDropBackpacks)
            {
                if (Il2CppString* customDataHashtableString = customDataHashtable->ToString();
                    customDataHashtableString != nullptr && customDataHashtableString->length > 0)
                {
                    hashtableString = ReadIl2CppString(customDataHashtableString);
                }
                
                if (const std::string normalizedHashtableString = ToUpperCase(hashtableString);
                    normalizedHashtableString.find("[RECROYALE_BACKPACK]") != std::string::npos || normalizedHashtableString.find("[RECROYALE_PLAYERMAP]") != std::string::npos)
                {
                    PhotonNetwork::set_MasterClient(localPlayer.photonPlayer);
                    
                    if (hashtableString.find("(System.Byte)7=(System.Int32)") != std::string::npos)
                    {
                        if (Il2CppObject* keySevenObject = customDataHashtable->get_Item(7)) // key 7 is instantiated object photon view id, Int32
                        {
                            void* ppvid = il2cpp_object_unbox_spoof(keySevenObject);
                            EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::DestroyGameObject, ppvid);
                        }
                    }
                    
                    const std::string notifString = ("[NoBackpack] Dropped Backpack from: " + std::to_string(senderActorID) + ".");
                    pGui->notify.PushNotification<ImVec4(1.0, 0.0, 0.0, 1), 3.0f>(pGui->m_pTextures->tWarnFilled, notifString);
                    return true;   
                }
            }
            
            auto response = FilterInstantiatebHashtable(customDataHashtable);
            detected = response.flagged;
            message = response.message;
        }

        if (const auto& iDestroyDetectedPrefab = global::destroyDetectedPrefab;
            detected && iDestroyDetectedPrefab)
        {
            if (hashtableString.find("(System.Byte)7=(System.Int32)") != std::string::npos)
            {
                if (Il2CppObject* keySevenObject = customDataHashtable->get_Item(7)) // key 7 is instantiated object photon view id, Int32
                {
                    void* ppvid = il2cpp_object_unbox_spoof(keySevenObject);
                    EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::DestroyGameObject, ppvid);
                }
            }
        }

        if (detected && (senderActorID != 0 && (!localPlayerExists || (localPlayerExists && senderActorID != localPlayer
            .photonPlayer->getActorNumber()))))
        {
            if (const auto& iRestrictActor = global::restrictActor;
                iRestrictActor)
            {
                blockedActorIds.push_back(senderActorID);
            }

            if (const auto& iBounceBack = global::bounceBack;
                iBounceBack)
            {
                EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::BounceBackActor, senderActorID);
            }

            const std::string notifString = ("[ObjectFilter] Detected malicious payload from: " + std::to_string(senderActorID) + ".");
            pGui->notify.PushNotification<ImVec4(0.996f, 0.455f, 0.388f, 1), 3.0f>(pGui->m_pTextures->tWarnFilled, notifString);

            if (const auto& iAnnounceOffender = global::announceOffender;
                iAnnounceOffender)
            {
                std::unique_lock lock(playerlistMutex, std::defer_lock);
                if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout)))
                {
                    for (const auto& [photonPlayer, playerInfo] : cachedPlayerlist)
                    {
                        if (playerInfo.loadingStage >= LoadingStage::PHOTON && !playerInfo.isLocalPlayer)
                        {
                            if (playerInfo.photonActorID == senderActorID)
                            {
                                senderDisplayName = playerInfo.DisplayName;
                                break;
                            }
                        }
                    }

                    lock.unlock();
                }
                else
                {
                    Log::error("playerlistMutex timed out in Ev202Protection!");
                }
                printf("nigger detected: %s for: %s\n", senderDisplayName.c_str(), message.c_str());
                EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::ShowNotificationAllInternal, "[Mocha]\nCheat Engine nigga detected: " + senderDisplayName + "\n" + message);
            }
        }

        if (const auto& iDropDetectedEvent = global::dropDetectedEvent;
            detected && iDropDetectedEvent)
        {
            return true;
        }
    }

    return false;
}
