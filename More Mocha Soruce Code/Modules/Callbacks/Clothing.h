#pragma once

namespace Callbacks
{

    bool ForceHoldClothingTarget(PhotonPlayer* targetPP) {

        if (!cachedPlayerlist.contains(targetPP)) return true;

        if (const PlayerInfo& targetPlayer = cachedPlayerlist[targetPP];
            targetPlayer.loadingStage >= LoadingStage::LOADED)
        {
            if (RecRoomPlayer* playerPlayer = RecRoomPlayer::GetFromActorNumber(targetPlayer.photonActorID);
                playerPlayer->get_IsInitialized() && playerPlayer->get_IsInitialLoadFinished())
            {
                auto* playerHand = (PlayerHand*)playerPlayer->get_RightHand();

                if (playerHand == nullptr) return true;

                GameObject* outfitToolGO = nullptr;

                Il2CppArray* objects = UObject::FindObjectsOfType("UnityEngine.GameObject");

                for (int i = 0; i < objects->max_length; i++) {

                    if (GameObject* gameObject = il2cpp_array_get(objects, GameObject*, i)) {

                        if (gameObject->GetComponent("RecRoom.Avatars.Outfit.OutfitTool")) {
                            outfitToolGO = gameObject;
                        }
                    }
                }

                if (outfitToolGO == nullptr) return true;

                auto* toolTool = (Tool*)outfitToolGO->GetComponent("Tool");

                if (toolTool == nullptr) return true;

                playerHand->TryReleaseTool({ 0, 0, 0 }, { 0, 0, 0 });
                playerHand->TryPickupTool(toolTool, false);
            }
        }
        return true;
    }
    
}