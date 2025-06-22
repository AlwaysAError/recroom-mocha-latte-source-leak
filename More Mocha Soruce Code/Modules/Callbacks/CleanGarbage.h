#pragma once
#include "Notification.h"
#include "PhotonExploits.h"

namespace Callbacks
{
    bool CleanGarbagePrefabs()
    {
        if (!PhotonNetwork::get_isMasterClient(localPlayer.photonPlayer))
        {
            if (!PhotonNetwork::set_MasterClient(localPlayer.photonPlayer))
                Log::error("Failed to set master client for: " + std::string(localPlayer.DisplayName));
        }

        const bool original_toggle = globals::photon::protections::inbound::Ev200::toggle;
        const bool original_dropAllEvents = globals::photon::protections::inbound::Ev200::dropAllEvents;

        globals::photon::protections::inbound::Ev200::toggle = true;        // prevent niggers from loading in type shit
        globals::photon::protections::inbound::Ev200::dropAllEvents = true; // prevent niggers from loading in type shit

        auto* objects = (Array*)UObject::FindObjectsOfType("UnityEngine.GameObject");

        int objectsDestroyed = 0;

        for (int i = 0; i < objects->max_length; i++)
        {
            if (auto* gameObject = (GameObject*)objects->GetValue(i))
            {
                Il2CppString* goString = gameObject->ToString();

                if (goString == nullptr)
                    continue;

                if (goString->length <= 0)
                    continue;

                if (std::string rawPrefabObjectName = ReadIl2CppString(goString);
                    !rawPrefabObjectName.empty())
                {

                    /*
                    if (auto* transform = gameObject->get_transform();
                        transform != nullptr)
                    {
                        constexpr int iVectorsMinimumLimit = 5000;
                        constexpr int iVectorsMaximumLimit = -5000;

                        if (const Vector3 position = transform->get_position();
                            position.x >= iVectorsMinimumLimit && position.x <= iVectorsMaximumLimit &&
                            position.y >= iVectorsMinimumLimit && position.y <= iVectorsMaximumLimit &&
                            position.z >= iVectorsMinimumLimit && position.z <= iVectorsMaximumLimit)
                        {
                        }
                        else
                        {
                            continue;
                        }
                    }
                    */
                    
                    if (
                        std::string objname = ToUpperCase(rawPrefabObjectName);

                        (objname.find("[QUEST_SCIFI_JUMBOTRONBOSS_ENEMY]") != std::string::npos)
                        || (objname.find("[QUEST_GOBLIN_WITCHBOSS]") != std::string::npos)
                        || (objname.find("[QUEST_PIRATE_BOSSENEMY]") != std::string::npos)
                        || (objname.find("[QUEST_GOBLIN_ROTATINGBOSSENEMY]") != std::string::npos)
                        || (objname.find("[QUEST_GOBLIN_BOGMONSTER]") != std::string::npos)
                        || (objname.find("[QUEST_DRACULA1_MINIBOSS") != std::string::npos)
                        || (objname.find("[QUEST_DRACULA1_DRACULABOSS]") != std::string::npos)
                        || (objname.find("[RECROYALE_BACKPACK]") != std::string::npos)
                        || (objname.find("[RECROYALE_PLAYERMAP]") != std::string::npos)
                        || (objname.find("[ARENAMANAGER]") != std::string::npos)
                        || (objname.find("[BATTLEROYALEMANAGER]") != std::string::npos)
                        || (objname.find("[BOWLINGMANAGER]") != std::string::npos)
                        || (objname.find("[CHARADESMANAGER]") != std::string::npos)
                        || (objname.find("[DISCGOLFMANAGER]") != std::string::npos)
                        || (objname.find("[DODGEBALLMANAGER]") != std::string::npos)
                        || (objname.find("[ORIENTATIONMANAGER]") != std::string::npos)
                        || (objname.find("[PADDLEBALLMANAGER]") != std::string::npos)
                        || (objname.find("[PAINTBALLMANAGER]") != std::string::npos)
                        || (objname.find("[QUEST_DRACULA1_MANAGER]") != std::string::npos)
                        || (objname.find("[QUEST_GOBLIN1_MANAGER]") != std::string::npos)
                        || (objname.find("[QUEST_GOBLIN2_MANAGER]") != std::string::npos)
                        || (objname.find("[QUEST_PIRATE1_MANAGER]") != std::string::npos)
                        || (objname.find("[QUEST_SCIFI1_MANAGER]") != std::string::npos)
                        || (objname.find("[RECRALLYMANAGER]") != std::string::npos)
                        || (objname.find("[SOCCERMANAGER]") != std::string::npos)
                        || (objname.find("STUNTRUNNER") != std::string::npos)
                        || (objname.find("[STNMONSTERCOSTUMEDUMMY]") != std::string::npos)
                        || (objname.find("[FLAG") != std::string::npos)
                        || (objname.find("[GLIDER]") != std::string::npos)
                        || (objname.find("[QUEST_WITCH_PROJECTILE]") != std::string::npos)
                        || (objname.find("AUDIOPLAYERNODE") != std::string::npos)

                    )
                    {
                        // lazy
                        //Log::debug("Destroying " + rawPrefabObjectName + " ...");

                        objectsDestroyed++;

                        if (auto* gameObjectPhotonView = static_cast<PhotonView*>(gameObject->
                            GetComponent("PhotonView")))
                        {
                            if (const auto ownerPP = gameObjectPhotonView->get_Owner();
                                ownerPP != nullptr && ownerPP->getActorNumber() != localPlayer.photonActorID)
                            {
                                gameObjectPhotonView->TransferOwnership(localPlayer.photonPlayer);
                                Sleep(10);
                            }

                            if (static_cast<CreationObject*>(gameObject->GetComponent(
                                "RecRoom.Core.Creation.CreationObject")))
                            {
                                std::vector<PhotonView::PayloadEntry> payloadVector = {};

                                if (!PhotonNetwork::get_isMasterClient(localPlayer.photonPlayer))
                                {
                                    if (!PhotonNetwork::set_MasterClient(localPlayer.photonPlayer))
                                        Log::error("Failed to set master client for: " + std::string(localPlayer.DisplayName));
                                }

                                gameObjectPhotonView->SendRPC("RpcMasterDespawn", All, payloadVector);

                                //Log::debug("destroyed by rpc!");
                            }
                            else
                            {
                                int32_t photonViewID = gameObjectPhotonView->get_ViewID();
                                int32_t* ppvid = &photonViewID;

                                int attempts = 0;

                                while (!DestroyGameObject(ppvid) && attempts < 3)
                                {
                                    Sleep(50);
                                    attempts++;
                                }

                                //Log::debug("destroyed by force!");

                                gameObject->Destroy(); // only destroys locally :P
                            }
                        }
                    }
                }
            }
        }

        globals::photon::protections::inbound::Ev200::toggle = original_toggle;
        globals::photon::protections::inbound::Ev200::dropAllEvents = original_dropAllEvents;

        if (objectsDestroyed > 0)
        {
            ShowNotificationAllInternal("[Mocha] Cleaned Up [" + std::to_string(objectsDestroyed) + "] Objects!");
        }

        return true;
    }
}
