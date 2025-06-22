#pragma once

void MakerPenDropperLoop()
{

    if (globals::makerPenDropperToggle)
    {
        if (localPlayerExists && localPlayer.loadingStage >= LoadingStage::LOADED)
        {
            RecRoomPlayer* localPlayerPlayer = RecRoomPlayer::GetFromActorNumber(localPlayer.photonActorID);

            if (localPlayerPlayer != nullptr)
            {
                if (localPlayerPlayer->get_IsInitialized() && localPlayerPlayer->get_IsInitialLoadFinished())
                {
                    std::unique_lock lock(playerlistMutex, std::defer_lock);

                    if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout)))
                    {
                        for (auto& [_, playerInfo] : cachedPlayerlist)
                        {
                            if (!playerInfo.isLocalPlayer && playerInfo.loadingStage >= LoadingStage::LOADED)
                            {
                                if (RecRoomPlayer* playerPlayer = RecRoomPlayer::GetFromActorNumber(playerInfo.photonActorID);
                                playerPlayer != nullptr && playerPlayer->get_IsInitialLoadFinished())
                                {

                                    /*
                                    enum class HandType {
                                        Unknown = -1,
                                        Left = 0,
                                        Right = 1,
                                    };
                                    */

                                    if (auto* toolsArray = (Array*)playerPlayer->get_AllToolsOnPlayer();
                                        toolsArray != nullptr)
                                    {
                                        for (int i = 0; i < toolsArray->max_length; i++)
                                        {
                                            if (auto* toolComponent = (Tool*)toolsArray->GetValue(i);
                                                toolComponent != nullptr)
                                            {
                                                if (auto* toolGO = toolComponent->get_gameObject();
                                                    toolGO != nullptr)
                                                {
                                                    if (Il2CppString* GOName = toolGO->GetName();
                                                        GOName != nullptr)
                                                    {
                                                        if (std::string(ReadIl2CppString(GOName)).find("MakerPen") != std::string::npos)
                                                        {
                                                            if (auto* RecRoomSceneManager = RecRoomSceneManager::get_Instance()) {
                                                                if (auto* photonView = RecRoomSceneManager->get_PhotonView()) {

                                                                    Vector3 position = playerPlayer->get_CurrentBodyPosition();
                                                                    Quaternion rotation = playerPlayer->GetRotation();

                                                                    std::vector<PhotonView::PayloadEntry> payloadVector = {
                                                                        {position, "UnityEngine.Vector3"},			// spawnPosition
                                                                        {rotation, "UnityEngine.Quaternion"},		// spawnRotation
                                                                        {(Il2CppObject*)playerInfo.photonView},	    // spawnParent
                                                                        {true, "System.Boolean"}					// dropTools
                                                                    };
							
                                                                    photonView->SendRPC("RpcRespawnPlayer", playerInfo.photonPlayer, payloadVector);

                                                                    if (globals::makerPenDropperAnnounceToggle)
                                                                    {
                                                                        Callbacks::ShowNotificationAllInternal(std::string(playerInfo.DisplayName) + " doesn't have enough aura to use makerpen here!");
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    
                                    /*
                                    constexpr int hands = 1;
                                    for (int i = 0; i < hands; i++){
                                        if (PlayerHand* hand = playerPlayer->getHand(0);
                                            hand != nullptr)
                                        {
                                            if (Tool* heldTool = hand->get_HeldTool();
                                                heldTool != nullptr)
                                            {
                                                if (GameObject* heldToolGO = heldTool->get_gameObject();
                                                    heldToolGO != nullptr)
                                                {
                                                    if (Transform* heldToolGOTransform = heldToolGO->get_transform();
                                                        heldToolGOTransform != nullptr)
                                                    {
                                                        if (Transform* heldToolGOParentTransform = heldToolGOTransform->get_parent();
                                                            heldToolGOParentTransform != nullptr)
                                                        {
                                                            if (GameObject* heldToolParentGO = heldToolGOParentTransform->get_gameObject();
                                                                heldToolParentGO != nullptr)
                                                    
                                                                if (Il2CppString* GOName = heldToolParentGO->GetName();
                                                                GOName != nullptr)
                                                                {
                                                                    if (std::string(ReadIl2CppString(GOName)).find("[MakerPen") != std::string::npos)
                                                                    {
                                                                        if (PhotonView* heldToolPV = (PhotonView*)heldToolGO->GetComponent("PhotonView");
                                                                            heldToolPV != nullptr)
                                                                        {
                                                                            Log::debug("transfered ownership");
                                                                            heldToolPV->TransferOwnership(localPlayer.photonPlayer);
                                                                        }
                                                                        bool status = hand->TryReleaseTool({ 0, 0, 0 }, { 0, 0, 0 }, ReleaseType::Manual);

                                                                        Log::debug("trying to release mp from: " + std::string(playerInfo.DisplayName));
                                                            
                                                                        if (globals::makerPenDropperAnnounceToggle && status)
                                                                        {
                                                                            Callbacks::ShowNotificationAllInternal(std::string(playerInfo.DisplayName) + " does not have enough aura to use makerpen here!");
                                                                        }
                                                                    }
                                                                }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    */
                                }
                            }
                        }
                            
                        lock.unlock();
                    }
                    else
                    {
                        Log::error("playerlistMutex timed out in MakerPenDropperLoop!");
                    }
                }
            }
        }
    }
}