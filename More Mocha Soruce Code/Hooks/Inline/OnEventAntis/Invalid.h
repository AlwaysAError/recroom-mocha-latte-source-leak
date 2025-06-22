#pragma once

bool InvalidActorProtection(const int& senderActorID)
{
    if (const auto iDropInvalidActorEvents = globals::photon::protections::inbound::dropInvalidActorEvents;
        iDropInvalidActorEvents)
    {
        if (localPlayerExists && localPlayer.loadingStage >= LoadingStage::LOADED)
        // actors can be invalid during loading causing some weird ass issues
        {
            for (const auto& playerInfo : cachedPlayerlist | std::views::values)
            {
                if (playerInfo.photonActorID == senderActorID)
                    return false;
            }

            return true;
        }
    }

    return false;
}
