#pragma once
#include "BulletCrash.h"
#include "GoToRoom.h"
#include "Respawns.h"

namespace Callbacks
{
    bool BounceBackTarget(PhotonPlayer* targetPP)
    {
        namespace global = globals::photon::protections::inbound::BounceBack;

        if (const bool& iDuringLoading = global::duringLoading;
            localPlayerExists && (localPlayer.loadingStage >= LoadingStage::LOADED || iDuringLoading))
        {
            bool shouldBounceBack = false;

            std::unique_lock lock(playerlistMutex, std::defer_lock);
            if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout)))
            {
                if (!cachedPlayerlist.contains(targetPP))
                {
                    lock.unlock();
                    return false;
                }

                const auto& iMaxAttempts = global::maxAttempts;

                if (auto& playerInfo = cachedPlayerlist[targetPP];
                    playerInfo.bounceBackAttempts < iMaxAttempts)
                {
                    playerInfo.bounceBackAttempts++;
                    Log::debug(std::string("[BounceBack] Target => ") + playerInfo.DisplayName + " (" + std::to_string(playerInfo.photonActorID) + ").");
                    shouldBounceBack = true;
                }

                lock.unlock();
            }
            else
            {
                Log::error("playerlistMutex timed out in BounceBackTarget!");
                return false;
            }

            if (shouldBounceBack)
            {
                if (const bool& iGoToRoom = global::goToRoom;
                    iGoToRoom)
                {
                    bool& iForceLeavePartyGas = globals::forceLeavePartyGas;
                    const bool originalForceLeaveParty = iForceLeavePartyGas;

                    iForceLeavePartyGas = true;

                    std::string originalRoomNameBuffer = "DormRoom";

                    std::string& iRoomNameBuffer = globals::roomNameBuffer;
                    
                    originalRoomNameBuffer = iRoomNameBuffer;

                    iRoomNameBuffer = "Orientation";

                    bool success = GoToRoomTarget(targetPP);
                    if (success) success = GoToRoomTarget(targetPP);

                    iRoomNameBuffer = "DormRoom";

                    if (success) success = GoToRoomTarget(targetPP);
                    if (success) success = GoToRoomTarget(targetPP);

                    if (!success)
                        Log::error("[BounceBack] GoToRoomTarget failed!");

                    iForceLeavePartyGas = originalForceLeaveParty;
                    iRoomNameBuffer = originalRoomNameBuffer;
                }

                if (const bool& iRespawnAtInfinity = global::respawnAtInfinity;
                    iRespawnAtInfinity)
                {
                    bool success = RespawnAtInfinityTarget(targetPP);
                    if (success) success = RespawnAtInfinityTarget(targetPP);
                    if (!success)
                        Log::error("[BounceBack] RespawnAtInfinityTarget failed!");
                }

                if (const bool& iBulletCrash = global::bulletCrash;
                    iBulletCrash)
                {
                    if (!BulletCrashTarget(targetPP))
                        Log::error("[BounceBack] BulletCrashTarget failed!");
                }

                if (const bool& iDeath = global::death;
                    iDeath)
                {
                    if (!DeathTarget(targetPP))
                        Log::error("[BounceBack] DeathTarget failed!");
                }
            }
        }

        return true;
    }

    bool BounceBackActor(const int targetActorID)
    {
        namespace global = globals::photon::protections::inbound::BounceBack;

        if (const bool& iDuringLoading = global::duringLoading;
            localPlayerExists && (localPlayer.loadingStage >= LoadingStage::LOADED || iDuringLoading))
        {
            PhotonPlayer* targetPhotonPlayer = nullptr;

            std::unique_lock lock(playerlistMutex, std::defer_lock);
            if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout)))
            {
                for (const auto& [photonPlayer, playerInfo] : cachedPlayerlist)
                {
                    if (playerInfo.loadingStage >= LoadingStage::PHOTON && !playerInfo.isLocalPlayer)
                    {
                        if (playerInfo.photonActorID == targetActorID)
                        {
                            Log::debug(std::string("[BounceBack|Actor] Target => ") + playerInfo.DisplayName + " (" + std::to_string(targetActorID) + ").");
                            targetPhotonPlayer = photonPlayer;
                            break;
                        }
                    }
                }

                lock.unlock();
            }
            else
            {
                Log::error("playerlistMutex timed out in BounceBackActor!");
                return false;
            }

            if (targetPhotonPlayer != nullptr)
                return BounceBackTarget(targetPhotonPlayer);

            Log::error("[BounceBack] could not find Actor: " + std::to_string(targetActorID) + "!");
        }

        return true;
    }
}
