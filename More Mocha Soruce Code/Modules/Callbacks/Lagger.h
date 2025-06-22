#pragma once

namespace Callbacks
{
    bool LaggerTarget(PhotonPlayer* targetPP) {

        if (targetPP != nullptr && cachedPlayerlist.contains(targetPP)) {

            const PlayerInfo& targetPlayer = cachedPlayerlist[targetPP];

            std::unique_lock opRaiseEventLock(globals::opRaiseEventEdit::opRaiseEventEditMutex, std::defer_lock);

            if (opRaiseEventLock.try_lock_for(std::chrono::seconds(globals::opRaiseEventMutexTimeout))) {

                auto editInfo = globals::opRaiseEventEdit::EditInfo{
                    "[Player]",
                    {},			     //! only initiialize empty targetActorIDs vector if using a preset!!!
                    { 1, 1, 1 },     // scale
                    { 0, -1000, 0 }, // position
                    500
                };

                editInfo.SetActorIDs(globals::opRaiseEventEdit::EditInfo::ActorIDsPreset::Target, targetPlayer.photonActorID);
                globals::opRaiseEventEdit::opRaiseEventEditQueue.push_back(editInfo);
                Log::debug("spawning shit");
                GameObject* dummyGO = PhotonNetwork::photonInstantiate(WriteIl2CppString(globals::opRaiseEventEdit::magicPrefab.c_str()), { 0, 2, 0 }, { 0, 0, 0, 0 }, { 1, 1, 1 }, 0, nullptr, false);
                Log::debug("spawning shit end");
                dummyGO->Destroy();
                Log::debug("dummy destroyed");
                opRaiseEventLock.unlock();
            }
            else {
                Log::error("opRaiseEventLock timed out in LaggerTarget!");
                return false;
            }
        }

        return true;
    }
}