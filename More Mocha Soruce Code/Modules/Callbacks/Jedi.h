#pragma once

namespace Callbacks
{
    bool JediTarget(PhotonPlayer* targetPP) {

        std::unique_lock lock(playerlistMutex, std::defer_lock);
        
        if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {
            if (!cachedPlayerlist.contains(targetPP)) {
                lock.unlock();
                return true;
            }

            if (!PhotonNetwork::get_isMasterClient(localPlayer.photonPlayer)) {
                if (!PhotonNetwork::set_MasterClient(localPlayer.photonPlayer))
                    Log::error("Failed to set master client for: " + std::string(localPlayer.DisplayName));

                lock.unlock();
                return false;
            }

            if (const PlayerInfo& targetPlayer = cachedPlayerlist[targetPP];
                targetPlayer.loadingStage >= LoadingStage::LOADED) {

                if (auto* playerPlayer = RecRoomPlayer::GetFromActorNumber(targetPlayer.photonActorID);
                    playerPlayer->get_IsInitialized() && playerPlayer->get_IsInitialLoadFinished()) {

                    PlayerHand* playerHand = globals::jedi::dominantHand ? (PlayerHand*)playerPlayer->get_RightHand() : (PlayerHand*)playerPlayer->get_LeftHand();

                    if (playerHand == nullptr) return true;

                    auto* toolObject = (GameObject*)globals::jedi::prefabGameObject;

                    if (toolObject == nullptr) return true;

                    auto* toolObjectTool = (Tool*)toolObject->GetComponent("Tool");

                    if (toolObjectTool == nullptr) return true;

                    playerHand->TryReleaseTool({ 0, 0, 0 }, { 0, 0, 0 });
                    playerHand->TryPickupTool(toolObjectTool, false);
                    }
                }
            
            lock.unlock();
        }
        else {
            Log::error("playerlistMutex timed out in JediTarget!");
            return false;
        }

        return true;
    }

    bool SpawnJediObject() {
        
        auto& internalPrefab = globals::instantiateAssets::prefab;
        const auto& internalDespawnable = globals::instantiateAssets::despawnToggle;

        Vector3 internalScale = globals::instantiateAssets::scale;
		
        if (globals::instantiateAssets::randomScaleToggle) {
            internalScale.x = getRandomScale(globals::instantiateAssets::randomScaleX);
            internalScale.y = getRandomScale(globals::instantiateAssets::randomScaleY);
            internalScale.z = getRandomScale(globals::instantiateAssets::randomScaleZ);
        }
        
        GameObject* internalGameObject = PhotonNetwork::photonInstantiate(WriteIl2CppString(internalPrefab.c_str()), {0, -500, 0}, {0, 0, 0, 0}, internalScale, 0, nullptr, internalDespawnable);

        globals::jedi::prefabGameObject = internalGameObject;

        return true;
        
    }
}