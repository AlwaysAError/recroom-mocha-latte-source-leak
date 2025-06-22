#pragma once

typedef bool (*SetMasterClient_t)(PhotonPlayer*, void*);
SetMasterClient_t SetMasterClient_o = nullptr;
bool __fastcall SetMasterClient_Ihook(PhotonPlayer* photonPlayer, void* methodInfo) {
    
    if (const auto& iToggle = globals::Ihooks::setMasterClient;
        !iToggle)
        return SetMasterClient_o(photonPlayer, methodInfo);

    if (photonPlayer == nullptr)
    {
        const std::string notifString = "[Anti-Master|Request] Blocked Invalid Player Request.";
        pGui->notify.PushNotification<ImVec4(0.996, 0.647, 0.455, 1), 3.0f>(pGui->m_pTextures->tWarnFilled, notifString);
        return false;
    }
    
    if (const auto& iDuringLoading = globals::photon::protections::master::request::duringLoading;
        localPlayerExists && (localPlayer.loadingStage >= LoadingStage::LOADED || iDuringLoading)) {

        if (RecRoomPlayer* localPlayerPlayer = RecRoomPlayer::GetFromActorNumber(localPlayer.photonActorID)) {
            if (localPlayerPlayer->get_IsInitialized() && localPlayerPlayer->get_IsInitialLoadFinished()) { //! setting master client during loading breaks room loading and causes crash

                bool isRequestedLocal = false;
                
                if (cachedPlayerlist.contains(photonPlayer)) {

                    const PlayerInfo& requestingPlayer = cachedPlayerlist[photonPlayer];

                    if (requestingPlayer.isLocalPlayer)
                        isRequestedLocal = true;

                    if (!isRequestedLocal)
                    {
                        const std::string notifString = "[Anti-Master|Request] Blocked Request From: " + std::string(requestingPlayer.DisplayName);
                        pGui->notify.PushNotification<ImVec4(0.996, 0.647, 0.455, 1), 3.0f>(pGui->m_pTextures->tWarnFilled, notifString);
                    }
                }
                
                if (!isRequestedLocal)
                    return false;
            }
        }
    }
    else
    {
        if (const auto& iLoadingFixToggle = globals::photon::protections::master::request::loadingFix;
            iLoadingFixToggle && !iDuringLoading && (localPlayerExists && localPlayer.loadingStage < LoadingStage::LOADED))
        {
            const PlayerInfo* requestedPlayer = &localPlayer;
            if (cachedPlayerlist.contains(photonPlayer))
            {
                requestedPlayer = &cachedPlayerlist[photonPlayer];
            }

            if (requestedPlayer->isLocalPlayer && !localPlayer.isMasterClient)
            {
                const std::string notifString = "[MCR|LoadFix] Blocked Loading Crash Exploit.";
                pGui->notify.PushNotification<ImVec4(1.0f, 0.0f, 0.0f, 1), 3.0f>(pGui->m_pTextures->tWarnFilled, notifString);
                return false;
            }
            if (localPlayer.isMasterClient && cachedPlayerlist.size() > 1 && localPlayer.loadingStage < LoadingStage::LOADED)
            {
                const PlayerInfo* masterClientRecipient = &localPlayer;
                bool switchLocalPlayerMaster = false;

                for (const auto& i : cachedPlayerlist)
                {
                    if (!i.second.isLocalPlayer) continue;

                    switchLocalPlayerMaster = true;
                    masterClientRecipient = &i.second;
                    break;
                }

                if (!switchLocalPlayerMaster)
                {
                    const std::string notifString = "[MCR|LoadFix] Switching MasterClient to " + std::string(masterClientRecipient->DisplayName) + ".";
                    pGui->notify.PushNotification<ImVec4(1.0f, 0.0f, 0.0f, 1), 3.0f>(pGui->m_pTextures->tWarnFilled, notifString);
                    return SetMasterClient_o(masterClientRecipient->photonPlayer, methodInfo);
                }
                return false;
            }
        }
    }

    return SetMasterClient_o(photonPlayer, methodInfo);
}

//void PlayerList::BulletCrashPL(PhotonPlayer* targetPP);

typedef void (*OnMasterClientSwitched_t)(void*, PhotonPlayer*, void*);
OnMasterClientSwitched_t OnMasterClientSwitched_o = nullptr;
void __fastcall OnMasterClientSwitched_Ihook(void* photonHandler, PhotonPlayer* photonPlayer, void* methodInfo) { // from PhotonHandler.h

    if (const auto& iToggle = globals::Ihooks::OnMasterClientSwitched;
        !iToggle)
        return OnMasterClientSwitched_o(photonHandler, photonPlayer, methodInfo);

    bool setLocalPlayerAsMaster = false;
    
    if (const auto& iDuringLoading = globals::photon::protections::master::callback::duringLoading;
        localPlayerExists && (localPlayer.loadingStage >= LoadingStage::LOADED || iDuringLoading))
    {

        const PlayerInfo* requestingPlayer = &localPlayer;
        
        if (cachedPlayerlist.contains(photonPlayer))
        {
            requestingPlayer = &cachedPlayerlist[photonPlayer];
        }
        
        if (RecRoomPlayer* localPlayerPlayer = RecRoomPlayer::GetFromActorNumber(localPlayer.photonActorID)) {
            if (localPlayerPlayer->get_IsInitialized() && localPlayerPlayer->get_IsInitialLoadFinished()) { //! setting master client during loading breaks room loading and causes crash

                if (!requestingPlayer->isLocalPlayer)
                {
                    setLocalPlayerAsMaster = true;
                    
                    const std::string notifString = "[Anti-Master|Callback] Triggered by: " + std::string(requestingPlayer->DisplayName);
                    pGui->notify.PushNotification<ImVec4(0.996, 0.647, 0.455, 1), 3.0f>(pGui->m_pTextures->tWarnFilled, notifString);
                }
            }
        }

        if (const auto& iBounceBack = globals::photon::protections::master::callback::bounceBack;
            iBounceBack && !requestingPlayer->isLocalPlayer)
        {
            EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::BounceBackTarget, photonPlayer);
        }

        if (const auto& iRestrictOffender = globals::photon::protections::master::callback::restrictOffender;
            iRestrictOffender && !requestingPlayer->isLocalPlayer)
        {
            if (cachedPlayerlist.contains(photonPlayer))
            {
                blockedActorIds.push_back(cachedPlayerlist[photonPlayer].photonActorID);
            }
            else
            {
                Log::error("[MCC|RS] Cannot find player to restrict!");
            }
        }
    }
    else
    {
        if (const auto& iLoadingFixToggle = globals::photon::protections::master::callback::loadingFix;
            iLoadingFixToggle && !iDuringLoading && (localPlayerExists && localPlayer.loadingStage < LoadingStage::LOADED))
        {
            
            if (localPlayer.isMasterClient && cachedPlayerlist.size() > 1 && localPlayer.loadingStage < LoadingStage::LOADED)
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
                    const std::string notifString = "[MCC|LoadFix] Switching MasterClient to " + std::string(masterClientRecipient->DisplayName) + ".";
                    pGui->notify.PushNotification<ImVec4(1.0f, 0.0f, 0.0f, 1), 3.0f>(pGui->m_pTextures->tWarnFilled, notifString);
                    PhotonNetwork::set_MasterClient(masterClientRecipient->photonPlayer);
                }
            }
        }
    }

    if (setLocalPlayerAsMaster)
    {
        Log::debug("MCC Set MC");
        Log::debug("MCC pp: " + std::to_string((uintptr_t)localPlayer.photonPlayer));
        PhotonNetwork::set_MasterClient(localPlayer.photonPlayer);
    }
    
    return OnMasterClientSwitched_o(photonHandler, photonPlayer, methodInfo);
}