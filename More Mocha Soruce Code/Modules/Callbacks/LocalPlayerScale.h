#pragma once

namespace Callbacks
{
    bool SetLocalPlayerScale() {

        if (localPlayerExists && localPlayer.playerGameObject != nullptr) {
            if (Transform* localPlayerTransform = localPlayer.playerGameObject->get_transform()) {
                const Vector3& internalLocalPlayerScale = globals::photon::antis::outbound::playerScale;
                localPlayerTransform->set_localScale(internalLocalPlayerScale);
            }
            else return false;
        }
        else return false;

        return true;
    }
}