#pragma once
#include "../globals.h"
#include "../includes.h"

void SitOnHeadLoop()
{
    if (globals::enableSitLoop)
    {
        if (localPlayerExists && localPlayer.loadingStage >= LoadingStage::LOADED)
        {
            if (const auto localPlayerPlayer = RecRoomPlayer::GetFromActorNumber(localPlayer.photonActorID);
                localPlayerPlayer->get_IsInitialized() && localPlayerPlayer->get_IsInitialLoadFinished())
            {
                if (cachedTargetHead != nullptr && cachedSeat != nullptr)
                {

                    Vector3 seatPosition = cachedTargetHead->get_position();
                    Quaternion seatRotation = cachedTargetHead->get_rotation();
                    seatPosition.y += globals::sitLoopOffset;
                    
                    cachedSeat->get_transform()->set_position(seatPosition);
                    cachedSeat->get_transform()->set_rotation(seatRotation);
                    
                    {
                        std::vector<PhotonView::PayloadEntry> payloadVector = {
                            {seatPosition, "UnityEngine.Vector3"},  // position
                        };
				
                        cachedSeat->SendRPC("RpcAuthorityCV2SetPosition", Others, payloadVector);
                    }

                    {
                        std::vector<PhotonView::PayloadEntry> payloadVector = {
                            {seatRotation, "UnityEngine.Quaternion"},   // rotation
                        };
				
                        cachedSeat->SendRPC("RpcAuthorityCV2SetRotation", Others, payloadVector);
                    }
                }
            }
        }
    }
}
