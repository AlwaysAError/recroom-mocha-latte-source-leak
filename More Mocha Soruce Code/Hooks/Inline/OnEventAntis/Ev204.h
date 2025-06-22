#pragma once

// destroy event

bool Ev204Protection(Hashtable*& customDataHashtable, const int& senderActorID)
{
    namespace global = globals::photon::protections::inbound::Ev204;

    if (const bool& iToggle = global::toggle;
        iToggle)
    {
        const bool& iDropAllEvents = global::dropAllEvents;
        const bool& iDropServerEvents = global::dropServerEvents;

        if (const bool& iDropSelfEvents = global::dropSelfEvents;
            iDropAllEvents && ((senderActorID != 0 || iDropServerEvents) || ((localPlayerExists && senderActorID !=
                localPlayer.photonActorID) || iDropSelfEvents)))
            return true;


        if (const auto& iFilterOwnedPhotonView = global::filterOwnedPhotonView;
            iFilterOwnedPhotonView)
        {
            bool detected = false;

            std::string hashtableString = "";
            if (Il2CppString* customDataHashtableString = customDataHashtable->ToString();
                customDataHashtableString != nullptr && customDataHashtableString->length > 0)
            {
                hashtableString = ReadIl2CppString(customDataHashtableString);
            }

            if (hashtableString.find("(System.Byte)0=(System.Int32)") != std::string::npos)
            {
                Il2CppObject* targetPhotonViewObject = customDataHashtable->get_Item(0); // key 0 is target PhotonViewID

                const int* pTargetPhotonViewID = static_cast<int*>(il2cpp_object_unbox_spoof(targetPhotonViewObject));
                const int targetPhotonViewID = *pTargetPhotonViewID;

                if (PhotonView* targetPhotonView = PhotonView::findPhotonView(targetPhotonViewID))
                {
                    if (PhotonPlayer* ownerPhotonPlayer = targetPhotonView->get_Owner();
                        localPlayerExists && ownerPhotonPlayer)
                    {
                        std::unique_lock lock(playerlistMutex, std::defer_lock);
                        if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout)))
                        {
                            if (!cachedPlayerlist.contains(ownerPhotonPlayer))
                            {
                                Log::error("[DestroyFilter] PhotonView owner PhotonPlayer not found!");
                                return false;
                            }

                            if (const auto& playerInfo = cachedPlayerlist[ownerPhotonPlayer];
                                playerInfo.photonActorID == localPlayer.photonActorID)
                                detected = true;

                            lock.unlock();
                        }
                        else
                        {
                            Log::error("playerlistMutex timed out in Ev204Protection!");
                            return true;
                        }
                    }
                }
            }

            if (detected && (senderActorID != 0 && (!localPlayerExists || (localPlayerExists && senderActorID !=
                localPlayer.photonPlayer->getActorNumber()))))
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
        }
    }

    return false;
}
