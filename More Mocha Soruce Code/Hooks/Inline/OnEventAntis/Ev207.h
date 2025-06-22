#pragma once

// destroy photon player event

bool Ev207Protection(const int& senderActorID)
{
    namespace global = globals::photon::protections::inbound::Ev207;

    if (const bool& iToggle = global::toggle;
        iToggle)
    {
        const bool& iDropAllEvents = global::dropAllEvents;
        const bool& iDropServerEvents = global::dropServerEvents;

        if (const bool& iDropSelfEvents = global::dropSelfEvents;
            iDropAllEvents && ((senderActorID != 0 || iDropServerEvents) || ((localPlayerExists && senderActorID !=
                localPlayer.photonActorID) || iDropSelfEvents)))
        {
            if (senderActorID != 0 && (!localPlayerExists || (localPlayerExists && senderActorID != localPlayer.
                photonPlayer->getActorNumber())))
            {
                if (const auto& iRestrictActor = global::restrictActor;
                    iRestrictActor)
                {
                    blockedActorIds.push_back(senderActorID);
                }

                if (const auto& iBounceBack = global::bounceBack;
                    iBounceBack)
                {
                    EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::BounceBackActor, senderActorID);
                }
            }
            return true;
        }
    }
    return false;
}
