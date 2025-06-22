#pragma once

PhotonPlayer* pSelectedPlayer = nullptr;

namespace ButtonCallbacks::PlayerList
{
    bool CheckExistance() {

        if (pWatchMenuHandler->selectedPlayerId == 0) {
            pSelectedPlayer = localPlayer.photonPlayer;
            return true;
        }

        if (cachedPlayerlist.find(pSelectedPlayer) != cachedPlayerlist.end())
            return true;
        else {
            pSelectedPlayer = localPlayer.photonPlayer;
            return true;
        }
    }
    
    // exploits
    void SetMasterClientTarget(UIButton* instance)
    {
        if (!CheckExistance()) return;
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::SetMasterClientTarget, pSelectedPlayer);
    }

    void RespawnAtInfinityTarget(UIButton* instance)
    {
        if (!CheckExistance()) return;
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::RespawnAtInfinityTarget, pSelectedPlayer);
    }

    void BulletCrashTarget(UIButton* instance)
    {
        if (!CheckExistance()) return;
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::BulletCrashTarget, pSelectedPlayer);
    }

    void DeathTarget(UIButton* instance)
    {
        if (!CheckExistance()) return;
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::DeathTarget, pSelectedPlayer);
    }

    
    // teleports
    void TeleportToMeTarget(UIButton* instance)
    {
        if (!CheckExistance()) return;
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::TeleportToMeTarget, pSelectedPlayer);
    }

    void TeleportToTarget(UIButton* instance)
    {
        if (!CheckExistance()) return;
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::TeleportToTarget, pSelectedPlayer);
	
    }

    void TeleportAllToTarget(UIButton* instance)
    {
        if (!CheckExistance()) return;
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::TeleportAllToTarget, pSelectedPlayer);
	
    }

    void TeleportToLimitTarget(UIButton* instance)
    {
        if (!CheckExistance()) return;
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::TeleportToLimitTarget, pSelectedPlayer);
	
    }

    void RespawnPlayerTarget(UIButton* instance)
    {
        if (!CheckExistance()) return;
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::RespawnPlayerTarget, pSelectedPlayer);
	
    }

    void DespawnPlayerTarget(UIButton* instance)
    {
        if (!CheckExistance()) return;
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::DespawnPlayerTarget, pSelectedPlayer);
	
    }

    void SpawnPlayerTarget(UIButton* instance)
    {
        if (!CheckExistance()) return;
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::SpawnPlayerTarget, pSelectedPlayer);
	
    }

    
    // misc
    void SpawnAssetOnTarget(UIButton* instance)
    {
        if (!CheckExistance()) return;
        EnqueueCallback(std::chrono::milliseconds(500), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::SpawnAssetOnTarget, pSelectedPlayer);
	
    }

    void JediTarget(UIButton* instance)
    {
        if (!CheckExistance()) return;
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::JediTarget, pSelectedPlayer);
	
    }

    void ShowNotificationTarget(UIButton* instance)
    {
        if (!CheckExistance()) return;
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::ShowNotificationTarget, pSelectedPlayer);
	
    }

    void ShowBannerNotificationTarget(UIButton* instance)
    {
        if (!CheckExistance()) return;
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::ShowBannerNotificationTarget, pSelectedPlayer);
	
    }

    void UpdateRolesTarget(UIButton* instance)
    {
        if (!CheckExistance()) return;
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::UpdateRolesTarget, pSelectedPlayer);
	
    }

    
    // fun modules
    void SitTarget(UIButton* instance)
    {
        if (!CheckExistance()) return;
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::SitTarget, pSelectedPlayer);
	
    }

    void ForceHoldClothingTarget(UIButton* instance)
    {
        if (!CheckExistance()) return;
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::ForceHoldClothingTarget, pSelectedPlayer);
	
    }
    
    void ExterminateTarget(UIButton* instance)
    {
        if (!CheckExistance()) return;
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::ExterminateTarget, pSelectedPlayer);
	
    }

    void PlayAudioSampleTarget(UIButton* instance)
    {
        if (!CheckExistance()) return;
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::PlayAudioSampleTarget, pSelectedPlayer);
	
    }

    void FlingTarget(UIButton* instance)
    {
        if (!CheckExistance()) return;
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::FlingTarget, pSelectedPlayer);
    }

    void JoinMyPartyTarget(UIButton* instance)
    {
        if (!CheckExistance()) return;
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::JoinMyPartyTarget, pSelectedPlayer);
    }

    void JoinPartyTarget(UIButton* instance)
    {
        if (!CheckExistance()) return;
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::JoinPartyTarget, pSelectedPlayer);
    }

    void LeavePartyTarget(UIButton* instance)
    {
        if (!CheckExistance()) return;
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::LeavePartyTarget, pSelectedPlayer);
    }

    
    // energy modules
    void SitOnPlayerHeadTarget(UIButton* instance)
    {
        if (!CheckExistance()) return;
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::SitOnPlayerHeadTarget, pSelectedPlayer);
    }

    void FakeVoteKickTarget(UIButton* instance)
    {
        if (!CheckExistance()) return;
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::FakeVoteKickTarget, pSelectedPlayer);
    }

    void LevelUpTarget(UIButton* instance)
    {
        if (!CheckExistance()) return;
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::LevelUpTarget, pSelectedPlayer);
    }

    
    //test
    void ForceMakerPenTarget(UIButton* instance)
    {
        if (!CheckExistance()) return;
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::ForceMakerPenTarget, pSelectedPlayer);
	
    }

    void GoToRoomTarget(UIButton* instance)
    {
        if (!CheckExistance()) return;
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::GoToRoomTarget, pSelectedPlayer);
	
    }

    void GiftPlayerTest(UIButton* instance)
    {
        if (!CheckExistance()) return;
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::GiftPlayerTest, pSelectedPlayer);
	
    }
    
}