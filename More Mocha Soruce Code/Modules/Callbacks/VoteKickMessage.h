#pragma once

namespace Callbacks
{
    bool FakeVoteKickTarget(PhotonPlayer* targetPP) {

        if (targetPP != nullptr) {

            std::unique_lock lock(playerlistMutex, std::defer_lock);

            if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {

                if (!cachedPlayerlist.contains(targetPP))
                {
                    lock.unlock();
                    return true;
                }
                
                const PlayerInfo& targetPlayer = cachedPlayerlist[targetPP];

                std::vector<PhotonView::PayloadEntry> payloadVector = {};

                targetPlayer.photonView->SendRPC("RpcModerationBroadcastKickMessage", All, payloadVector);

                lock.unlock();
            }
            else {
                Log::error("playerlistMutex timed out in FakeVoteKickTarget!");
                return false;
            }
        }
        
        return true;
    }
}