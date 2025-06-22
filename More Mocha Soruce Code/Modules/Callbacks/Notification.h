#pragma once

namespace Callbacks
{
    bool ShowNotificationTarget(PhotonPlayer* targetPP)
    {
        if (targetPP != nullptr)
        {
            if (localPlayerExists && localPlayer.loadingStage >= LoadingStage::LOADED)
            {
                std::unique_lock lock(playerlistMutex, std::defer_lock);

                if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout)))
                {
                    if (auto* manager = CircuitsV2Manager::GetCircuitsV2Manager())
                    {
                        if (auto* photonView = static_cast<PhotonView*>(manager->get_gameObject()->GetComponent(
                            "PhotonView")))
                        {
                            std::vector<PhotonView::PayloadEntry> payloadVector = {
                                {(Il2CppObject*)WriteIl2CppString(globals::messageBuffer.c_str())}
                            };

                            photonView->SendRPC("RpcSendMajorNotification", targetPP, payloadVector);
                        }
                    }

                    lock.unlock();
                }
                else
                {
                    Log::error("playerlistMutex timed out in ShowNotificationTarget!");
                    return false;
                }
            }
        }

        return true;
    }

    bool ShowNotificationAll()
    {
        if (localPlayerExists && localPlayer.loadingStage >= LoadingStage::LOADED)
        {
            if (auto* manager = CircuitsV2Manager::GetCircuitsV2Manager())
            {
                if (auto* photonView = static_cast<PhotonView*>(manager->get_gameObject()->GetComponent("PhotonView")))
                {
                    std::vector<PhotonView::PayloadEntry> payloadVector = {
                        {(Il2CppObject*)WriteIl2CppString(globals::messageBuffer.c_str())}
                    };

                    photonView->SendRPC("RpcSendMajorNotification", All, payloadVector);
                }
            }
        }
        return true;
    }

    bool ShowNotificationAllInternal(std::string message)
    {
        if (localPlayerExists && localPlayer.loadingStage >= LoadingStage::LOADED)
        {
            if (auto* manager = CircuitsV2Manager::GetCircuitsV2Manager())
            {
                if (auto* photonView = static_cast<PhotonView*>(manager->get_gameObject()->GetComponent("PhotonView")))
                {
                    const char* messageToSend = message.c_str();
                    std::vector<PhotonView::PayloadEntry> payloadVector = {
                        {(Il2CppObject*)WriteIl2CppString(messageToSend)}
                    };

                    photonView->SendRPC("RpcSendMajorNotification", All, payloadVector);
                }
            }
        }
        return true;
    }
}
