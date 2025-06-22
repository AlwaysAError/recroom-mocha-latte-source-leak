#pragma once

namespace Callbacks
{
    bool BlackFlashTarget(PhotonPlayer* targetPP) {

        if (targetPP != nullptr) {

            const PlayerInfo& targetPI = cachedPlayerlist[targetPP];
            
            std::unique_lock opRaiseEventLock(globals::opRaiseEventEdit::opRaiseEventEditMutex, std::defer_lock);

            if (opRaiseEventLock.try_lock_for(std::chrono::seconds(globals::opRaiseEventMutexTimeout))) {

                float maxx = 99999993215964691371151521984339247104.000f;
                float minn = -99999993215964691371151521984339247104.000f;

                auto editInfo1 = globals::opRaiseEventEdit::EditInfo{
                    "[sandbox_ladder_hook]",
                    {},							//! only initiialize empty targetActorIDs vector if using a preset!!!
                    { 2, 2, 2 },				// scale
                    { maxx, minn, maxx },		// position
                    40
                };

                auto editInfo2 = globals::opRaiseEventEdit::EditInfo{
                    "[sandbox_ladder_hook]",
                    {},							//! only initiialize empty targetActorIDs vector if using a preset!!!
                    { 2, 2, 2 },				// scale
                    { minn, maxx, minn },		// position
                    40
                };

                editInfo1.SetActorIDs(globals::opRaiseEventEdit::EditInfo::ActorIDsPreset::Target, targetPI.photonActorID);
                editInfo2.SetActorIDs(globals::opRaiseEventEdit::EditInfo::ActorIDsPreset::Target, targetPI.photonActorID);
                globals::opRaiseEventEdit::opRaiseEventEditQueue.push_back(editInfo1);
                globals::opRaiseEventEdit::opRaiseEventEditQueue.push_back(editInfo2);

                GameObject* dummyGO = PhotonNetwork::photonInstantiate(WriteIl2CppString(globals::opRaiseEventEdit::magicPrefab.c_str()), { 0, 2, 0 }, { 0, 0, 0, 0 }, { 1, 1, 1 }, 0, nullptr, false);
                dummyGO->Destroy();

                opRaiseEventLock.unlock();
            }
            else {
                Log::error("opRaiseEventLock timed out in BlackFlashTarget!");
                return false;
            }
        }

        return true;
    }
}