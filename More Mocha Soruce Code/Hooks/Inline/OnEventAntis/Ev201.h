#pragma once

// movement/voice event

bool Ev201Protection(const int& senderActorID)
{
    namespace global = globals::photon::protections::inbound::Ev201;

    if (const bool& iToggle = global::toggle;
        iToggle)
    {
        const bool& iDropAllEvents = global::dropAllEvents;
        const bool& iDropServerEvents = global::dropServerEvents;

        if (const bool& iDropSelfEvents = global::dropSelfEvents;
            iDropAllEvents && ((senderActorID != 0 || iDropServerEvents) || ((localPlayerExists && senderActorID != localPlayer.photonActorID) || iDropSelfEvents)))
            return true;

        if (const bool& iDropDuringLoading = global::dropDuringLoading;
            iDropDuringLoading)
        {
            if (!localPlayerExists)
                return true;

            if (localPlayer.loadingStage < LoadingStage::LOADED)
                return true;

            if (const bool& iDropDuringLoadingStrict = global::dropDuringLoadingStrict;
                iDropDuringLoadingStrict)
            {
                if (RecRoomPlayer* localPlayerPlayer = RecRoomPlayer::GetFromActorNumber(localPlayer.photonActorID);
                    !localPlayerPlayer->get_IsInitialLoadFinished())
                    return true;
            }
        }
    }

    return false;
}
