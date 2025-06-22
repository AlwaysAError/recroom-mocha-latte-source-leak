#pragma once

namespace Callbacks
{
    bool DeleteAll()
    {
        if (!PhotonNetwork::get_isMasterClient(localPlayer.photonPlayer))
        {
            if (!PhotonNetwork::set_MasterClient(localPlayer.photonPlayer))
                Log::error("Failed to set master client for: " + std::string(localPlayer.DisplayName));
            return false;
        }

        const bool original_toggle = globals::photon::protections::inbound::Ev200::toggle;
        const bool original_dropAllEvents = globals::photon::protections::inbound::Ev200::dropAllEvents;

        globals::photon::protections::inbound::Ev200::toggle = true;        // prevent niggers from loading in type shit
        globals::photon::protections::inbound::Ev200::dropAllEvents = true; // prevent niggers from loading in type shit

        Il2CppArray* objects = UObject::FindObjectsOfType("UnityEngine.GameObject");

        int objectsDestroyed = 0;

        for (int i = 0; i < objects->max_length; i++)
        {
            if (GameObject* gameObject = il2cpp_array_get(objects, GameObject*, i))
            {
                if (auto* gameObjectPhotonView = static_cast<PhotonView*>(gameObject->GetComponent("PhotonView"));
                    gameObjectPhotonView != nullptr)
                {
                    if (static_cast<CreationObject*>(gameObject->GetComponent("RecRoom.Core.Creation.CreationObject")))
                    {

                        if (PhotonPlayer* ownerPP = gameObjectPhotonView->get_Owner();
                            ownerPP != nullptr)
                        {

                            if (int ownerActorID = ownerPP->getActorNumber();
                                ownerActorID != localPlayer.photonActorID)
                            {
                                gameObjectPhotonView->TransferOwnership(localPlayer.photonPlayer);
                            }
                        }

                        if (!PhotonNetwork::get_isMasterClient(localPlayer.photonPlayer))
                        {
                            if (!PhotonNetwork::set_MasterClient(localPlayer.photonPlayer))
                                Log::error("Failed to set master client for: " + std::string(localPlayer.DisplayName));
                        }

                        std::vector<PhotonView::PayloadEntry> payloadVector = {};

                        gameObjectPhotonView->SendRPC("RpcMasterDespawn", All, payloadVector);

                        objectsDestroyed++;
                    }
                }
            }
        }

        globals::photon::protections::inbound::Ev200::toggle = original_toggle;
        globals::photon::protections::inbound::Ev200::dropAllEvents = original_dropAllEvents;

        ShowNotificationAllInternal("[Mocha] Deleted [" + std::to_string(objectsDestroyed) + "] Objects!");
        return true;
    }
}