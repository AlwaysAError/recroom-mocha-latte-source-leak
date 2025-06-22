#pragma once

namespace Callbacks
{
    bool SetMasterClientTarget(PhotonPlayer* targetPP) {
        if (!PhotonNetwork::set_MasterClient(targetPP))
            Log::error("Failed to set target as Master Client!");
        return true;
    }
}