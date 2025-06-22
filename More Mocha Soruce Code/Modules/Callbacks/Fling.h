#pragma once

namespace Callbacks
{
    bool FlingTarget(PhotonPlayer* targetPP) {

        if (targetPP != nullptr) {

            std::unique_lock lock(playerlistMutex, std::defer_lock);

            if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {

                if (!cachedPlayerlist.contains(targetPP)) return true;
                if (const PlayerInfo& targetPlayer = cachedPlayerlist[targetPP];
                    targetPlayer.loadingStage >= LoadingStage::LOADED)
                {
                    Vector3& velocity = globals::fling::velocity;

                    if (globals::fling::random) {
                        velocity.x = getRandomScale(globals::fling::randomVelocityX);
                        velocity.y = getRandomScale(globals::fling::randomVelocityY);
                        velocity.z = getRandomScale(globals::fling::randomVelocityZ);
                    }

                    std::vector<PhotonView::PayloadEntry> payloadVector = {
                        {velocity, "UnityEngine.Vector3"},				// velocity
                        {globals::fling::multiplier, "System.Single"}	// multiplier
                    };

                    if (!PhotonNetwork::get_isMasterClient(localPlayer.photonPlayer)) {
                        if (!PhotonNetwork::set_MasterClient(localPlayer.photonPlayer))
                            Log::error("Failed to set master client for: " + std::string(localPlayer.DisplayName));
                        return false;
                    }

                    targetPlayer.photonView->SendRPC("RpcAuthorityCV2SetPhysicsVelocity", targetPP, payloadVector);
                }
                lock.unlock();
            }
            else {
                Log::error("playerlistMutex timed out in FlingTarget!");
                return false;
            }
        }
        return true;
    }
}