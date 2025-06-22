#pragma once

namespace Callbacks
{

    bool LevelUpTarget(PhotonPlayer* targetPP) {

        if (targetPP != nullptr) {

            std::unique_lock<std::timed_mutex> lock(playerlistMutex, std::defer_lock);

            if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {

                if (!cachedPlayerlist.contains(targetPP))
                {
                    lock.unlock();
                    return true;
                }
                
                const PlayerInfo& targetPlayer = cachedPlayerlist[targetPP];

                std::vector<PhotonView::PayloadEntry> payloadVector = {
                    {globals::levelUpFeedback, "System.Int32"}
                };

                targetPlayer.photonView->SendRPC("RpcPlayLevelUpFeedback", All, payloadVector);

                lock.unlock();
            }
            else {
                Log::error("playerlistMutex timed out in LevelUpTarget!");
                return false;
            }
        }
        
        return true;
    }
    
}