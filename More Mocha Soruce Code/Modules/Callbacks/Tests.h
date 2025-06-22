#pragma once

PhotonView* cachedSeat = nullptr;
Transform* cachedTargetHead = nullptr;
static ShareCameraPhotonView* shareCameraPV = nullptr;

namespace Callbacks
{
    bool TypeShit()
    {
        Log::debug("called type shit");

        Il2CppString* okstr = localPlayer.photonPlayer->GetPlayerID();

        if (okstr != nullptr)
        {
            Log::debug("called okstr");

            Log::debug("str: " + std::string(ReadIl2CppString(okstr)));
            
        }
        
        Log::debug("fin");
        
        return true;
    }
    
    bool ScheduledBulletCrashPL(PhotonPlayer* targetPP) {
        //if (targetPP != nullptr)
            //newThread(//PlayerList::BulletCrashPL, targetPP);
        return true;
    }
    
    bool PlayerTest(PhotonPlayer* targetPP) {
		
        if (PlayerInfo& targetPlayer = cachedPlayerlist[targetPP];
            (CreationObject*)targetPlayer.playerGameObject->GetComponent("RecRoom.Core.Creation.CreationObject")) {

            std::vector<PhotonView::PayloadEntry> payloadVector = {};

            if (!PhotonNetwork::get_isMasterClient(localPlayer.photonPlayer)) {
                if (!PhotonNetwork::set_MasterClient(localPlayer.photonPlayer))
                    Log::error("Failed to set master client for: " + std::string(localPlayer.DisplayName));
                Sleep(250);
            }

            targetPlayer.photonView->SendRPC("RpcMasterDespawn", Others, payloadVector);

            Log::debug("destroyed by rpc!");
        }

        return true;
        
#ifdef cuh
        if (targetPP != nullptr) {

            PhotonPlayer* targetPhotonPlayer = (PhotonPlayer*)targetPP;

            Il2CppClass* photonNetworkClass = FindClass("DLEKLKKDJDP"); // PhotonNetwork

            List* foundPhotonViews = GetStaticField<List*>(photonNetworkClass, "MNMIPBPACDD");

            Log::debug("list good: " + std::to_string((uintptr_t)foundPhotonViews));

            int32_t listcount = foundPhotonViews->get_Count();

            Log::debug("count good");
            Log::debug("count good: " + std::to_string(listcount));

            for (int i = 0; i < listcount; i++) {

                PhotonView* photonView = (PhotonView*)foundPhotonViews->get_Item(i);

                Log::debug("got photon view at: " + std::to_string(i));
                Log::debug("got photon view id: " + std::to_string(photonView->get_ViewID()));
            }

            //GameObject* PlayerGO = PhotonNetwork::photonInstantiateMC(WriteIl2CppString("[Player]"), { 0, 1, 0 }, { 0, 0, 0, 0 }, { 1, 1, 1 }, 0, nullptr);

            //PhotonView* GOpv = (PhotonView*)PlayerGO->GetComponent("PhotonView");

            //GOpv->TransferOwnership(targetPhotonPlayer);
        }
#endif
    }

    bool TestCamera()
    {
        Camera* camera = Camera::get_current();

        if (camera != nullptr)
        {
            Log::debug("camera good");
            auto cameraGO = camera->get_gameObject();
            if (cameraGO != nullptr)
            Log::debug("transform GO: " + std::string(ReadIl2CppString(cameraGO->GetName())));
        }
        
        return true;
    }

    bool SitOnPlayerHeadTarget(PhotonPlayer* targetPP)
    {
        Log::debug("SitOnPlayerHeadTarget");

        
                if (localPlayerExists && localPlayer.loadingStage >= LoadingStage::LOADED)
        {
            std::unique_lock lock(playerlistMutex, std::defer_lock);

            if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {

                if (!cachedPlayerlist.contains(targetPP))
                {
                    lock.unlock();
                    return true;
                }

                if (RecRoomPlayer* localRecRoomPlayer = RecRoomPlayer::GetFromActorNumber(localPlayer.photonActorID);
                    localRecRoomPlayer->get_IsInitialized() && localRecRoomPlayer->get_IsInitialLoadFinished())
                {
                    const PlayerInfo& targetPlayer = cachedPlayerlist[targetPP];

                    if (auto* target = RecRoomPlayer::GetFromActorNumber(targetPlayer.photonActorID);
                        target->get_IsInitialized() && target->get_IsInitialLoadFinished())
                    {
                        GameObject* UGCSeat = PhotonNetwork::photonInstantiate(WriteIl2CppString("[Sandbox_Seat]"), Vector3(0, 0, 0), Quaternion(0, 0, 0, 0), Vector3(0.01, 0.01, 0.01), 0, nullptr, true);

                        cachedSeat = (PhotonView*)UGCSeat->GetComponent("PhotonView");
                        
                        if (auto* pUGCSeatManagementProxy = (UGCSeatManagementProxy*)UGCSeat->GetComponent("RecRoom.Core.UGCSeatManagementProxy"))
                        {
                            if (auto* pUGCSeatManagement = pUGCSeatManagementProxy->get_UgcSeatManagement()) {

                                //pUGCSeatManagement->set_LockPlayersIn(true);
                                pUGCSeatManagement->CV2SetSeatedPlayer(localRecRoomPlayer);
                                pUGCSeatManagement->SeatCollisionEnabled_Set(false);
                                //pUGCSeatManagement->set_LockPlayersOut(false);
                        
                                if (auto* moveableProp = (MoveableProp*)UGCSeat->GetComponent("RecRoom.Tools.MoveableProp"))
                                {
                                    moveableProp->ForceSetLocomotionCollisionEnabled(false);   
                                }
                        
                                if (auto* creationObjectComponent = (CreationObject*)UGCSeat->GetComponent("RecRoom.Core.Creation.CreationObject"))
                                {

                                    cachedTargetHead = target->get_Head()->get_transform();
                                    
                                    creationObjectComponent->set_IsFrozen(true);
                                    creationObjectComponent->set_DynamicCollisionEnabled(false);
                                    //UGCSeat->get_transform()->SetParent(target->get_Head()->get_transform());
                                    //creationObjectComponent->get_transform()->set_localPosition(Vector3(0, 2, 0));
                                    //creationObjectComponent->get_transform()->set_localPosition(Vector3(0.0f, -0.5f, 1.3f));
                                    //creationObjectComponent->get_transform()->set_localRotation(Quaternion(0.0f, 0.0f, 0.0f, 0.0f));   
                                }
                            }
                        }
                    }
                }
                lock.unlock();
            }
            else {
                Log::error("playerlistMutex timed out in LeavePartyTarget!");
                return false;
            }
        }
        return true;
    }

    bool DestroySitOnTargetSeat()
    {
        if (cachedSeat != nullptr)
        {
            DestroyGameObject(cachedSeat);

            cachedSeat->Destroy();
            
            cachedSeat = nullptr;
            cachedTargetHead = nullptr;
        }
        
        return true;
    }

    bool GiftPlayerTest(PhotonPlayer* targetPP)
    {
        
        if (targetPP != nullptr && cachedPlayerlist.contains(targetPP))
        {
            globals::photon::giftbox::targetActorID = cachedPlayerlist[targetPP].photonActorID;
            globals::photon::giftbox::enableDataSwap = true;


            Callbacks::Giftbox();
            
            Log::debug("swap finished.");
        }
        

        return true;
        
    }

    bool CuntTest()
    {
        Log::debug("loltest");
            auto* objects = (Array*)UObject::FindObjectsOfType("UnityEngine.GameObject"); // UnityEngine.GameObject

            for (int i = 0; i < objects->max_length; i++)
            {
                auto* gameObject = (GameObject*)objects->GetValue(i);

                if (gameObject != nullptr)
                {
                    if (auto* sprite = (UObject*)gameObject->GetComponent("UnityEngine.Sprite");
                        sprite != nullptr)
                    {
                        Il2CppString* obstr = sprite->GetName();
                        if (obstr != nullptr)
                        {
                            Log::debug(ReadIl2CppString(obstr));
                        }
                    }
                }
            }
        
        
        return true;
    }

    bool SendChatMessage()
    {
        if (localPlayerExists && localPlayer.loadingStage >= LoadingStage::LOADED)
        {
            const char* messageToSend = globals::chatMessage.c_str();
            std::vector<PhotonView::PayloadEntry> payloadVector = {
                {(Il2CppObject*)WriteIl2CppString(messageToSend)}, // message
                {0,                               "System.Int32"}  // fuck knows tbh it's always 0 anyways
            };

            localPlayer.photonView->SendRPC("RpcChatMessage", All, payloadVector);
            return true;
        }
        
        return false;
    }

    bool SelectTMZCamera()
    {
        RecRoomPlayer* localRecRoomPlayer = RecRoomPlayer::GetFromActorNumber(localPlayer.photonActorID);
        if (localRecRoomPlayer != nullptr) {
            Il2CppArray* toolsArray = localRecRoomPlayer->get_AllToolsOnPlayer();
            if (toolsArray != nullptr) {
                for (int i = 0; i < toolsArray->max_length; i++)
                {
                    Component* toolComponent = (Component*)il2cpp_array_get(toolsArray, Il2CppObject*, i);
                    GameObject* toolGameObject = toolComponent->get_gameObject();
                    if (toolGameObject != nullptr) {
                        Component* shareCameraComp = toolGameObject->GetComponent("RecRoom.ShareCamera");

                        if (shareCameraComp != nullptr) {
                            shareCameraPV = (ShareCameraPhotonView*)toolGameObject->GetComponent("PhotonView");
                        }
                    }
                }
            }
        }
        
        return true;
    }
}