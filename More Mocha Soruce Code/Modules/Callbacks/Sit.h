#pragma once

namespace Callbacks
{
    bool SitTarget(PhotonPlayer* targetPP) {

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
                    const PlayerInfo* targetPlayer = &cachedPlayerlist[targetPP];

                    if (auto* target = RecRoomPlayer::GetFromActorNumber(targetPlayer->photonActorID);
                        targetPlayer != nullptr && target->get_IsInitialized() && target->get_IsInitialLoadFinished())
                    {
                        GameObject* UGCSeat = PhotonNetwork::photonInstantiate(WriteIl2CppString("[Sandbox_Seat]"), Vector3(0, 0, 0), Quaternion(0, 0, 0, 0), Vector3(1, 1, 1), 0, nullptr, true);
        
                        if (auto* pUGCSeatManagementProxy = (UGCSeatManagementProxy*)UGCSeat->GetComponent("RecRoom.Core.UGCSeatManagementProxy"))
                        {
                            if (auto* pUGCSeatManagement = pUGCSeatManagementProxy->get_UgcSeatManagement()) {

                                pUGCSeatManagement->set_LockPlayersIn(true);
                                pUGCSeatManagement->CV2SetSeatedPlayer(target);
                                pUGCSeatManagement->SeatCollisionEnabled_Set(false);
                                pUGCSeatManagement->set_LockPlayersOut(false);
                        
                                if (auto* moveableProp = (MoveableProp*)UGCSeat->GetComponent("RecRoom.Tools.MoveableProp"))
                                {
                                    moveableProp->ForceSetLocomotionCollisionEnabled(false);   
                                }
                        
                                if (auto* creationObjectComponent = (CreationObject*)UGCSeat->GetComponent("RecRoom.Core.Creation.CreationObject"))
                                {
                                    creationObjectComponent->set_IsFrozen(true);
                                    creationObjectComponent->set_DynamicCollisionEnabled(false);
                                    creationObjectComponent->get_transform()->SetParent(localRecRoomPlayer->get_Head()->get_transform());
                                    creationObjectComponent->get_transform()->set_localPosition(Vector3(0.0f, -0.5f, 1.3f));
                                    creationObjectComponent->get_transform()->set_localRotation(Quaternion(0.0f, 0.0f, 0.0f, 0.0f));   
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
}

namespace NewCallbacks
{
    bool Sit(PhotonPlayer* targetPP, const std::string& cuh) {

        Log::debug("cuh: " + cuh);

        GameObject* UGCSeat = PhotonNetwork::photonInstantiate(WriteIl2CppString("[Sandbox_Seat]"), Vector3(0, 0, 0), Quaternion(0, 0, 0, 0), Vector3(1, 1, 1), 0, nullptr, true);

        auto* pUGCSeatManagementProxy = (UGCSeatManagementProxy*)UGCSeat->GetComponent("RecRoom.Core.UGCSeatManagementProxy");
        if (pUGCSeatManagementProxy == nullptr) return false;

        UGCSeatManagement* pUGCSeatManagement = pUGCSeatManagementProxy->get_UgcSeatManagement();
        if (pUGCSeatManagement == nullptr) return false;

        const PlayerInfo& targetPlayer = cachedPlayerlist[(PhotonPlayer*)targetPP];
        RecRoomPlayer* target = RecRoomPlayer::GetFromActorNumber(targetPlayer.photonActorID);

        if (!(target->get_IsInitialized() && target->get_IsInitialLoadFinished())) return false;

        pUGCSeatManagement->set_LockPlayersIn(true);
        pUGCSeatManagement->CV2SetSeatedPlayer(target);
        pUGCSeatManagement->SeatCollisionEnabled_Set(false);
        pUGCSeatManagement->set_LockPlayersOut(false);

        auto* moveableProp = (MoveableProp*)UGCSeat->GetComponent("RecRoom.Tools.MoveableProp");
        if (moveableProp == nullptr) return false;

        moveableProp->ForceSetLocomotionCollisionEnabled(false);

        auto* creationObjectComponent = (CreationObject*)UGCSeat->GetComponent("RecRoom.Core.Creation.CreationObject");
        if (creationObjectComponent == nullptr) return false;

        creationObjectComponent->set_IsFrozen(true);
        creationObjectComponent->set_DynamicCollisionEnabled(false);

        RecRoomPlayer* localRecRoomPlayer = RecRoomPlayer::GetFromActorNumber(localPlayer.photonActorID);

        /// peak lazyness right here :P
        creationObjectComponent->get_transform()->SetParent(localRecRoomPlayer->get_Head()->get_transform());
        creationObjectComponent->get_transform()->set_localPosition(Vector3(0.0f, -0.5f, 1.3f));
        creationObjectComponent->get_transform()->set_localRotation(Quaternion(0.0f, 0.0f, 0.0f, 0.0f));

        return true;
    }
}