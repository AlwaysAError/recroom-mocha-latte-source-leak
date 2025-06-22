#pragma once

namespace Callbacks {
    
    bool ForceMakerPenTarget(PhotonPlayer* targetPP) {

        if (targetPP == nullptr) return true;

        if (!cachedPlayerlist.contains(targetPP)) return true; // no player found

        if (const PlayerInfo& targetPlayer = cachedPlayerlist[targetPP];
            targetPlayer.loadingStage >= LoadingStage::LOADED)
        {
            if (RecRoomPlayer* playerPlayer = RecRoomPlayer::GetFromActorNumber(targetPlayer.photonActorID);
                playerPlayer->get_IsInitialized() && playerPlayer->get_IsInitialLoadFinished())
            {
                if (auto* playerHand = (PlayerHand*)playerPlayer->get_RightHand())
                {
                    if (GameObject* makerPenGO = PhotonNetwork::photonInstantiate(il2cpp_string_new_spoof("[MakerPen]"), { 0, -1000, 0 }, { 0, 0, 0, 0 }, { 0.1, 0.1, 0.1 }, 0, nullptr, false))
                    {
                        if (auto* cachedMakerPenTool = (Tool*)makerPenGO->GetComponent("Tool"))
                        {
                            playerHand->TryReleaseTool({ 0, 0, 0 }, { 0, 0, 0 });
                            playerHand->TryPickupTool(cachedMakerPenTool, false);
                            playerHand->TryReleaseTool({ 0, 0, 0 }, { 0, 0, 0 });     
                        }
                    }
                }
            }
        }
        return true;
    }
}