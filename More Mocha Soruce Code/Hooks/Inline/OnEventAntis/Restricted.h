#pragma once

bool RestrictedActorProtection(const int& senderActorID, const int& eventCode)
{
    if (eventCode != 201 && eventCode != 10)
    {
        /// allow movement events & pv ownership updates only
        for (const auto& BlockedActors = blockedActorIds;
             auto& actor : BlockedActors)
        {
            if (actor == senderActorID)
                return true;
        }
    }

    return false;
}
