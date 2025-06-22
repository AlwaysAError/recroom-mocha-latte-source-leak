#pragma once

PhotonView* cachedAudioPlayer = nullptr;

namespace Callbacks
{
    bool UpdateAudioPlayer()
    {
        if (cachedAudioPlayer != nullptr)
        {
            if (GameObject* GO = cachedAudioPlayer->get_gameObject())
            {
                if (const auto audioPlayerComp = static_cast<AudioPlayer*>(GO->GetComponent(
                    "RecRoom.Core.Creation.SandboxGizmos.AudioPlayer")))
                {
                    audioPlayerComp->set_VolumeModifier(globals::audio::volume);
                    audioPlayerComp->set_SpeedModifier(globals::audio::speed);
                    audioPlayerComp->set_LoopAudio(globals::audio::loop);
                    audioPlayerComp->set_AudioChannel((AudioPlayer::Channel)globals::audio::channel);
                }
            }
        }

        return true;
    }

    bool PlayAudioSampleTarget(PhotonPlayer* targetPP)
    {
        if (targetPP != nullptr)
        {
            if (GameObject* audioPlayerGO = PhotonNetwork::photonInstantiate(
                WriteIl2CppString("[AudioPlayerNodeVisualization_CV2]"), {0, -1000, 0}, {0, 0, 0, 0}, {1, 1, 1}, 0,
                nullptr, false))
            {
                if (auto* audioPlayerPhotonView = static_cast<PhotonView*>(audioPlayerGO->GetComponent("PhotonView")))
                {
                    cachedAudioPlayer = audioPlayerPhotonView;

                    std::unique_lock lock(playerlistMutex, std::defer_lock);

                    if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout)))
                    {
                        if (!UpdateAudioPlayer()) return false;

                        std::vector<PhotonView::PayloadEntry> payloadVector = {
                            {(Il2CppObject*)WriteIl2CppString(globals::audio::blobNameAudioBuffer.c_str())},    // blobName
                            {globals::audio::audioLength, "System.Single"},                                     // audioLength
                            {(Il2CppObject*)WriteIl2CppString("Sample Audio")}                                  // audioName
                        };

                        audioPlayerPhotonView->SendRPC("RpcPlaySample", targetPP, payloadVector);

                        lock.unlock();
                    }
                    else
                    {
                        Log::error("playerlistMutex timed out in PlayAudioSampleTarget!");
                        return false;
                    }
                }
            }
        }

        return true;
    }

    bool PlayAudioSampleAll()
    {
        if (GameObject* audioPlayerGO = PhotonNetwork::photonInstantiate(
            WriteIl2CppString("[AudioPlayerNodeVisualization_CV2]"), {0, -1000, 0}, {0, 0, 0, 0}, {1, 1, 1}, 0, nullptr,
            false))
        {
            if (auto* audioPlayerPhotonView = static_cast<PhotonView*>(audioPlayerGO->GetComponent("PhotonView")))
            {
                cachedAudioPlayer = audioPlayerPhotonView;

                if (!UpdateAudioPlayer()) return false;

                std::vector<PhotonView::PayloadEntry> payloadVector = {
                    {(Il2CppObject*)WriteIl2CppString(globals::audio::blobNameAudioBuffer.c_str())},    // blobName
                    {globals::audio::audioLength, "System.Single"},                                     // audioLength
                    {(Il2CppObject*)WriteIl2CppString("Sample Audio")}                                  // audioName
                };

                audioPlayerPhotonView->SendRPC("RpcPlaySample", All, payloadVector);
            }
        }

        return true;
    }

    bool StopCachedAudioSample()
    {
        if (PhotonView* audioPlayerPhotonView = cachedAudioPlayer)
        {
            std::vector<PhotonView::PayloadEntry> payloadVector = {};

            audioPlayerPhotonView->SendRPC("RpcStop", All, payloadVector);
        }

        return true;
    }
}
