#pragma once

std::chrono::steady_clock::time_point lastExecutionTimeFMC = std::chrono::steady_clock::now();
constexpr std::chrono::seconds thresholdFMC(3);

void ForceMasterClient()
{
    namespace global = globals::photon::protections::master::force;

#undef min
    // Declare a static variable to track the last time we were loading
    static std::chrono::steady_clock::time_point lastLoadingTime = std::chrono::steady_clock::time_point::min();

    // Get the current time
    const auto now = std::chrono::steady_clock::now();

    // If currently loading, update the last loading time
    if (!localPlayerExists || (localPlayerExists && localPlayer.loadingStage < LoadingStage::LOADED))
    {
        lastLoadingTime = now;
    }

    // Check if we were loading within the last 1 second
    const bool wereLoadingRecently = (now - lastLoadingTime < thresholdFMC);
    
    if (const auto& iToggle = global::toggle;
        iToggle)
    {
        const PlayerInfo& iLocalPlayer = localPlayer;
        
        if (const auto& iDuringLoading = global::duringLoading;
            iDuringLoading || (localPlayerExists && iLocalPlayer.loadingStage >= LoadingStage::LOADED && !wereLoadingRecently))
        {
            bool switchMasterToLocalPlayer = false;
            const auto& iSpam = global::spam;
            
            if (!iDuringLoading)
            {
                if (auto* playerPlayer = RecRoomPlayer::GetFromActorNumber(iLocalPlayer.photonActorID);
                    playerPlayer != nullptr && playerPlayer->get_IsInitialized() && playerPlayer->get_IsInitialLoadFinished())
                {
                    if (!PhotonNetwork::get_isMasterClient(iLocalPlayer.photonPlayer) || iSpam)
                    {
                        switchMasterToLocalPlayer = true;
                    }
                }
            }

            if (!switchMasterToLocalPlayer && (localPlayerExists && !iLocalPlayer.isMasterClient))
            {
                switchMasterToLocalPlayer = true;
            }

            if (switchMasterToLocalPlayer) // todo: add bounceback & restrict here
            {
                const PlayerInfo* currentMasterClient = nullptr;
                
                if (!iLocalPlayer.isMasterClient)
                {
                    for (const auto& i : cachedPlayerlist)
                    {
                        if (!PhotonNetwork::get_isMasterClient(i.first)) continue;
                    
                        currentMasterClient = &i.second;
                        break;
                    }
                }
                
                if (const auto& iBounceBack = global::bounceBack;
                    iBounceBack && currentMasterClient != nullptr && !currentMasterClient->isLocalPlayer)
                {
                    const std::string notifString = "[Anti-Master|Force] Bounced Back => " + std::string(currentMasterClient->DisplayName) + ".";
                    pGui->notify.PushNotification<ImVec4(1.0f, 0.0f, 0.0f, 1), 3.0f>(pGui->m_pTextures->tWarnFilled, notifString);
                    EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::BounceBackTarget, currentMasterClient->photonPlayer);
                }
                
                if (const auto& iRestrictOffender = global::restrictOffender;
                    iRestrictOffender && !currentMasterClient->isLocalPlayer)
                {
                    blockedActorIds.push_back(currentMasterClient->photonActorID);
                    const std::string notifString = "[Anti-Master|Force] Restricted " + std::string(currentMasterClient->DisplayName) + ".";
                    pGui->notify.PushNotification<ImVec4(1.0f, 0.0f, 0.0f, 1), 3.0f>(pGui->m_pTextures->tWarnFilled, notifString);
                }

                if (currentMasterClient != nullptr && !currentMasterClient->isLocalPlayer)
                {
                    const std::string notifString = "[MCF|Anti] Offender: " + std::string(currentMasterClient->DisplayName) + ".";
                    pGui->notify.PushNotification<ImVec4(1.0f, 0.0f, 0.0f, 1), 3.0f>(pGui->m_pTextures->tWarnFilled, notifString);
                }
                
                if (!PhotonNetwork::set_MasterClient(iLocalPlayer.photonPlayer))
                    Log::error("Failed to set target as Master Client!");
                
                SetMasterClient_o(iLocalPlayer.photonPlayer, nullptr);
            }
        }
        else
        {
            if (const auto& iLoadingFixToggle = global::loadingFix;
                iLoadingFixToggle && !iDuringLoading && (localPlayerExists && iLocalPlayer.loadingStage < LoadingStage::LOADED) && iLocalPlayer.isMasterClient)
            {
            
                if (iLocalPlayer.isMasterClient && cachedPlayerlist.size() > 1 && iLocalPlayer.loadingStage < LoadingStage::LOADED)
                {
                    const PlayerInfo* masterClientRecipient = &localPlayer;
                    bool switchLocalPlayerMaster = false;

                    for (auto& i : cachedPlayerlist)
                    {
                        if (!i.second.isLocalPlayer) continue;

                        switchLocalPlayerMaster = true;
                        masterClientRecipient = &i.second;
                        break;
                    }

                    if (!switchLocalPlayerMaster)
                    {
                        const std::string notifString = "[Anti-Master|Force|LoadFix] Switching MasterClient to " + std::string(masterClientRecipient->DisplayName) + ".";
                        pGui->notify.PushNotification<ImVec4(1.0f, 0.0f, 0.0f, 1), 3.0f>(pGui->m_pTextures->tWarnFilled, notifString);
                        PhotonNetwork::set_MasterClient(masterClientRecipient->photonPlayer);
                    }
                }
            }
        }
    }
}

#ifdef OLDCODE
void ForceMasterClientOld() {
    if (globals::photon::antis::inbound::masterClientForceMode) {

        if (localPlayerExists && localPlayer.loadingStage >= LoadingStage::LOADED && !localPlayer.isMasterClient) {

            RecRoomPlayer* playerPlayer = RecRoomPlayer::GetFromActorNumber(localPlayer.photonActorID);

            if (playerPlayer != nullptr) {

                if (playerPlayer->get_IsInitialLoadFinished()) {

                    if (!loadingLastFrame) { //! cuz im tired of crashing some random nigger when joining a room

                        std::unique_lock<std::timed_mutex> lock(playerlistMutex, std::defer_lock);

                        if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {
                            for (auto& [targetPP, player] : cachedPlayerlist) {
                                if (!player.isLocalPlayer) {

                                    if (PhotonNetwork::get_isMasterClient(targetPP)) {

                                        if (globals::photon::antis::inbound::masterClientBlockOffender) {
                                            player.blockEvents = true;
                                        }

                                        std::string notifString = ("[Anti-MasterClient|Force] Bad Master located: " + std::string(player.DisplayName) + ".");
                                        Log::debug(notifString);
                                        pGui->notify.PushNotification<ImVec4(1.0, 0.0, 0.0, 1), 3.0f>(pGui->m_pTextures->tWarnFilled, notifString);

                                        if (globals::photon::antis::inbound::masterClientBounceBack) {

                                            bool offenderCrashed = false;

                                            switch (globals::photon::antis::inbound::masterClientBounceBackMode) {
                                            case (globals::photon::antis::BounceBackMode::BulletCrash): {

                                                if (player.loadingStage >= LoadingStage::LOADED) {

                                                    RecRoomPlayer* playerPlayer = RecRoomPlayer::GetFromActorNumber(targetPP->getActorNumber());

                                                    if (playerPlayer != nullptr && playerPlayer->get_IsInitialized() && playerPlayer->get_IsInitialLoadFinished()) {
                                                        //newThread(PlayerList::BulletCrashPL, targetPP);
                                                        offenderCrashed = true;
                                                    }
                                                }

                                                break;
                                            }
                                            case (globals::photon::antis::BounceBackMode::Death): {
                                                    /*
                                                std::unique_lock<std::timed_mutex> onUpdateLock(globals::onUpdate::onUpdateMutex, std::defer_lock);

                                                if (onUpdateLock.try_lock_for(std::chrono::seconds(globals::onUpdateMutexTimeout))) {

                                                    globals::onUpdate::functionQueueLoaded.push_back(
                                                        globals::onUpdate::Exec(
                                                            globals::onUpdate::OnUpdateFunc::Callback,
                                                            globals::onUpdate::Info::Callback(Callbacks::DeathTarget, targetPP)
                                                        )
                                                    );

                                                    onUpdateLock = ExecuteOnUpdateQueue(std::move(onUpdateLock));

                                                    onUpdateLock.unlock();

                                                    offenderCrashed = true;
                                                }
                                                else {
                                                    Log::error("onUpdateLock timed out in OnEvent Ihook!");
                                                }
                                                */

                                                break;
                                            }
                                            default:
                                                Log::error("Invalid BounceBack selection!");
                                                break;
                                            }
                                            if (offenderCrashed)
                                                pGui->notify.PushNotification<ImVec4(0.996, 0.455, 0.388, 1), 3.0f>(pGui->m_pTextures->tWarnFilled, std::string("[Anti-MasterClient|Force] Crashed Offender: ") + player.DisplayName);

                                        }

                                        break;
                                    }
                                }
                            }
                            lock.unlock();
                        }
                        else {
                            Log::error("playerlistMutex timed out in OnEvent Ihook!");
                        }
                    }

                    PhotonNetwork::set_MasterClient(localPlayer.photonPlayer);
                    loadingLastFrame = false;
                }
                else {
                    loadingLastFrame = true;
                }
            }
        }
    }
}
#endif