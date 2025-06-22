#pragma once

namespace ButtonCallbacks
{
    void SpawnAssetOnSelf(UIButton* instance)
    {
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::SpawnAssetOnTarget, localPlayer.photonPlayer);
    }
}