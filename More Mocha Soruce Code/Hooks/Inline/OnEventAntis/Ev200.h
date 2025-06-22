#pragma once

// rpc event

bool Ev200Protection(Hashtable*& customDataHashtable, const int& senderActorID)
{
    namespace global = globals::photon::protections::inbound::Ev200;

    if (const auto& iToggle = global::toggle;
        iToggle)
    {
        const auto& iDropAllEvents = global::dropAllEvents;
        const auto& iDropServerEvents = global::dropServerEvents;

        if (const auto& iDropSelfEvents = global::dropSelfEvents;
            iDropAllEvents && (senderActorID != 0 || iDropServerEvents || ((localPlayerExists && senderActorID != localPlayer.photonActorID) || iDropSelfEvents)))
            return true;

        if (const auto& iFilterServerEvents = global::filterServerEvents;
            senderActorID == 0 && !iFilterServerEvents)
            return false;

        if (const auto& iFilterSelfEvents = global::filterSelfEvents;
            localPlayerExists && senderActorID == localPlayer.photonActorID && !iFilterSelfEvents)
            return false;

        if (const auto& iFilterWhileLoading = global::filterWhileLoading;
            !iFilterWhileLoading && (!localPlayerExists || localPlayer.loadingStage < LoadingStage::LOADED))
            return false;

        bool detected = false;
        
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

                if (const auto& iRateLimitDuringLoading = global::rateLimitDuringLoading;
                    (playerInfo.loadingStage >= LoadingStage::LOADED) || iRateLimitDuringLoading)
                {
                    const int& EVENT_LIMIT = global::rateLimitLimit;
                    const std::chrono::milliseconds EVENT_WINDOW(global::rateLimitMS);

                    // Check rate limit
                    if (const auto now = std::chrono::steady_clock::now();
                        now - playerInfo.Ev200RateLimitWindowStart > EVENT_WINDOW)
                    {
                        // Window expired, reset count
                        playerInfo.Ev200RateLimitWindowStart = now;
                        playerInfo.Ev200RateLimitEventCount = 1;
                    }

                    if (playerInfo.Ev200RateLimitEventCount < EVENT_LIMIT)
                    {
                        playerInfo.Ev200RateLimitEventCount++;
                    }
                    else
                    {
                        detected = true;
                        const std::string notifString = ("[Ev200] Rate Limitting: [" + std::to_string(senderActorID) + "] " + playerInfo.DisplayName);
                        pGui->notify.PushNotification<ImVec4(0.996, 0.455, 0.388, 1), 3.0f>(pGui->m_pTextures->tWarnFilled, notifString);
                    }
                }

                lock.unlock();
            }
            else
            {
                Log::error("playerlistMutex timed out in Ev200Protection!");
                return true;
            }
        }

        std::string hashtableString = "";
        if (Il2CppString* customDataHashtableString = customDataHashtable->ToString();
            customDataHashtableString != nullptr && customDataHashtableString->length > 0)
        {
            hashtableString = ReadIl2CppString(customDataHashtableString);
        }

        if (!detected && (hashtableString.find("(System.Byte)4=(System.Object[])System.Object[]") != std::string::npos))
        {
            if (auto* keyFourObject = static_cast<Il2CppArray*>(customDataHashtable->get_Item(4))) // key 4 is rpc payload array, object[]
            {
                if (const auto& iFilterOwnedPhotonView = global::filterOwnedPhotonView;
                    iFilterOwnedPhotonView)
                {
                    bool found = false;
                    int32_t targetPVID = -1;

                    if (hashtableString.find("(System.Byte)7=(System.Int32)") != std::string::npos)
                    {
                        Il2CppObject* keySevenObject = customDataHashtable->get_Item(7); // key 7 is target photon view id, Int32
                        const auto* pTargetPVID = static_cast<int32_t*>(il2cpp_object_unbox_spoof(keySevenObject));
                        targetPVID = *pTargetPVID;
                        found = true;
                    }
                    if (!found && (hashtableString.find("(System.Byte)0=(System.Int32)") != std::string::npos))
                    {
                        Il2CppObject* keyZeroObject = customDataHashtable->get_Item(0); // key 0 is target photon view id, Int32
                        const auto* pTargetPVID = static_cast<int32_t*>(il2cpp_object_unbox_spoof(keyZeroObject));
                        targetPVID = *pTargetPVID;
                    }

                    if (found && (targetPVID > 0))
                    {
                        if (PhotonView* targetPV = PhotonView::findPhotonView(targetPVID))
                        {
                            if (PhotonPlayer* targetPVOwnerPP = targetPV->get_Owner();
                                targetPVOwnerPP != nullptr && targetPVOwnerPP->getActorNumber() == localPlayer.photonPlayer->getActorNumber())
                                detected = true;
                        }
                    }
                }

                if (const auto& iFilterVectorsLimit = global::filterVectorsLimit;
                    !detected && iFilterVectorsLimit)
                {
                    const auto& iVectorsMinimumLimit = global::vectorsMinimumLimit;
                    const auto& iVectorsMaximumLimit = global::vectorsMaximumLimit;

                    for (int i = 0; i < keyFourObject->max_length; i++)
                    {
                        if (Il2CppObject* object = il2cpp_array_get(keyFourObject, Il2CppObject*, i))
                        {
                            std::string objectTypeString = "";
                            if (auto* objectType = static_cast<Type*>(Type::GetType(object)))
                            {
                                if (Il2CppString* objectTypeIlString = objectType->ToString();
                                    objectTypeIlString->length > 0)
                                    objectTypeString = ReadIl2CppString(objectTypeIlString);
                            }

                            if (objectTypeString.empty()) continue;

                            if (objectTypeString.find("Vector3") != std::string::npos)
                            {
                                const Vector3* pPosition = static_cast<Vector3*>(il2cpp_object_unbox_spoof(object));

                                if (const Vector3 position = *pPosition;
                                    position.x >= iVectorsMinimumLimit && position.x <= iVectorsMaximumLimit &&
                                    position.y >= iVectorsMinimumLimit && position.y <= iVectorsMaximumLimit &&
                                    position.z >= iVectorsMinimumLimit && position.z <= iVectorsMaximumLimit)
                                {
                                }
                                else
                                {
                                    detected = true;
                                }
                                continue;
                            }

                            if (objectTypeString.find("Quaternion") != std::string::npos)
                            {
                                const Quaternion* pRotation = static_cast<Quaternion*>(
                                    il2cpp_object_unbox_spoof(object));

                                Quaternion rotation = *pRotation;

                                if (rotation.x >= iVectorsMinimumLimit && rotation.x <= iVectorsMaximumLimit &&
                                    rotation.y >= iVectorsMinimumLimit && rotation.y <= iVectorsMaximumLimit &&
                                    rotation.z >= iVectorsMinimumLimit && rotation.z <= iVectorsMaximumLimit &&
                                    rotation.w >= iVectorsMinimumLimit && rotation.w <= iVectorsMaximumLimit)
                                {
                                }
                                else
                                {
                                    detected = true;
                                }
                            }
                        }
                    }
                }
            }
        }

        if (detected)
        {
            if (senderActorID != 0 && (!localPlayerExists || (localPlayerExists && senderActorID != localPlayer.photonPlayer->getActorNumber())))
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
            }

            const std::string notifString = ("[Ev200] Dropped filtered RPC from Actor: " + std::to_string(senderActorID) + ".");
            pGui->notify.PushNotification<ImVec4(0.996, 0.455, 0.388, 1), 3.0f>(pGui->m_pTextures->tWarnFilled, notifString);
            return true;
        }
    }

    return false;
}
