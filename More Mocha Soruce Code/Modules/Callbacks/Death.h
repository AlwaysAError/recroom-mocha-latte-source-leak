#pragma once

namespace Callbacks
{
    std::chrono::steady_clock::time_point lastDeathExecutionTime = std::chrono::steady_clock::time_point::clock::now();
    
    bool DeathTarget(PhotonPlayer* targetPP) {

        const auto now = std::chrono::steady_clock::now();

        // Check if 5 seconds have passed since the last execution
        if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - lastDeathExecutionTime).count() >= 5) { /// 5 seconds
            lastDeathExecutionTime = now; // Update the last execution time
            
            if (targetPP != nullptr) {

                const PlayerInfo& targetPlayerInfo = cachedPlayerlist[targetPP];

                std::unique_lock opRaiseEventLock(globals::opRaiseEventEdit::opRaiseEventEditMutex, std::defer_lock);

                if (opRaiseEventLock.try_lock_for(std::chrono::seconds(globals::opRaiseEventMutexTimeout))) {

                    auto editInfo = globals::opRaiseEventEdit::EditInfo{
                        "",
                        {},			 //! only initiialize empty targetActorIDs vector if using a preset!!!
                        { 1, 1, 1 }, // scale
                        { 1, 1, 1 }, // position
                        1,
                        globals::opRaiseEventEdit::EditInfo::CustomType::Die
                    };

                    editInfo.SetActorIDs(globals::opRaiseEventEdit::EditInfo::ActorIDsPreset::Target, targetPlayerInfo.photonActorID);
                    globals::opRaiseEventEdit::opRaiseEventEditQueue.push_back(editInfo);
                    Log::debug("spawning shit");
                    GameObject* dummyGO = PhotonNetwork::photonInstantiate(WriteIl2CppString(globals::opRaiseEventEdit::magicPrefab.c_str()), { 0, 2, 0 }, { 0, 0, 0, 0 }, { 1, 1, 1 }, 0, nullptr, false);
                    Log::debug("spawning shit end");
                    dummyGO->Destroy();
                    Log::debug("dummy destroyed");
                    opRaiseEventLock.unlock();
                }
                else {
                    Log::error("opRaiseEventLock timed out in DeathTarget!");
                    return false;
                }
            }
        }
        
        return true;
    }
}