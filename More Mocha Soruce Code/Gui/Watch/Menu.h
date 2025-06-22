#pragma once
#include "Callbacks/PlayerList.h"

void InitializeWatchMenuUI() {

	int buttonCount = 6;
	int spacing = 220;
	std::vector<int> xPositions(buttonCount);

	for (int i = 0; i < buttonCount; ++i) {
		xPositions[i] = (i - (buttonCount - 1) / 2.0) * spacing;
	}

	ColorBlock menuColor;
	menuColor.normalColor = { 0, 0, 0, 0 };
	menuColor.highlightedColor = { 0, 0, 0, 0.3f };
	menuColor.pressedColor = { 0, 0, 0, 0.7f };
	menuColor.disabledColor = { 0, 0, 0, 0 };
	menuColor.selectedColor = { 0, 0, 0, 0.5f };
	menuColor.fadeDuration = 0.1f;
	menuColor.colorMultiplier = 1;

	ColorBlock colorBlock;
	colorBlock.normalColor = { 0, 0, 0, 1 };
	colorBlock.highlightedColor = { 1, 0, 0, 1 };
	colorBlock.pressedColor = { 0, 1, 0, 1 };
	colorBlock.disabledColor = { 0, 0, 1, 1 };
	colorBlock.selectedColor = { 0, 0, 0, 1 };
	colorBlock.fadeDuration = 0.1f;
	colorBlock.colorMultiplier = 1;

	ColorBlock buttonColor;
	buttonColor.normalColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	buttonColor.highlightedColor = { 0.7f, 0.7f, 0.7f, 1.0f };
	buttonColor.pressedColor = { 0.3f, 0.3f, 0.3f, 1.0f };
	buttonColor.disabledColor = { 1.0f, 1.0f, 1.0f, 0.5f };
	buttonColor.selectedColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	buttonColor.fadeDuration = 0.1f;
	buttonColor.colorMultiplier = 1;

	ColorBlock buttonTabColor;
	buttonTabColor.normalColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	buttonTabColor.highlightedColor = { 0.7f, 0.7f, 0.7f, 1.0f };
	buttonTabColor.pressedColor = { 0.3f, 0.3f, 0.3f, 1.0f };
	buttonTabColor.disabledColor = { 1.0f, 1.0f, 1.0f, 0.5f };
	buttonTabColor.selectedColor = { 0.5f, 0.5f, 0.5f, 1.0f };
	buttonTabColor.fadeDuration = 0.1f;
	buttonTabColor.colorMultiplier = 1;
	
	/// Menu Toggle
	pWatchMenuHandler->UIElements.push_back(UIButton("MOCHA", Vector3(500.0f, 460.0f, 0.0f), menuColor, ButtonCallbacks::MenuToggleCallback));

	/// Player Select
	pWatchMenuHandler->UIElements.push_back(UIButton("SELECT", Vector3(875.0f, 132.0f, 0.0f), menuColor, ButtonCallbacks::SwitchToPlayerlistTab, true));

	const float tabHeight = 1030.0f;

	/// Tabs
	pWatchMenuHandler->UIElements.push_back(UIButton("Movement", Vector3(xPositions.at(0), tabHeight, 0.0f), buttonTabColor, ButtonCallbacks::SwitchTab, TabType::Movement));
	pWatchMenuHandler->UIElements.push_back(UIButton("Misc", Vector3(xPositions.at(1), tabHeight, 0.0f), buttonTabColor, ButtonCallbacks::SwitchTab, TabType::Misc));
	pWatchMenuHandler->UIElements.push_back(UIButton("Exploits", Vector3(xPositions.at(2), tabHeight, 0.0f), buttonTabColor, ButtonCallbacks::SwitchTab, TabType::Exploits));
	pWatchMenuHandler->UIElements.push_back(UIButton("Asset Spawn", Vector3(xPositions.at(3), tabHeight, 0.0f), buttonTabColor, ButtonCallbacks::SwitchTab, TabType::Assets));
	pWatchMenuHandler->UIElements.push_back(UIButton("Player List", Vector3(xPositions.at(4), tabHeight, 0.0f), buttonTabColor, ButtonCallbacks::SwitchTab, TabType::PlayerList));

#ifndef PROD
	pWatchMenuHandler->UIElements.push_back(UIButton("Image", Vector3(xPositions.at(5), tabHeight, 0.0f), buttonTabColor, ButtonCallbacks::SwitchTab, TabType::Image));
#endif


	// movement
	{
		// first row
		pWatchMenuHandler->UIElements.push_back(UIToggleButton("Force Static Fly", Vector3(-700.0f, 875.0f, 0.0f), buttonColor, TabType::Movement, &globals::staticFlyToggle, ButtonCallbacks::Null));
		pWatchMenuHandler->UIElements.push_back(UIButton("Set Gravity", Vector3(-700.0f, 755.0f, 0.0f), buttonColor, TabType::Movement, ButtonCallbacks::SetGravity));
		pWatchMenuHandler->UIElements.push_back(UIButton("Restore Gravity", Vector3(-700.0f, 635.0f, 0.0f), buttonColor, TabType::Movement, ButtonCallbacks::RestoreGravity));
	}
	
	// misc
	{
		// first row
		pWatchMenuHandler->UIElements.push_back(UIButton("Send Chat", Vector3(-700.0f, 875.0f, 0.0f), buttonColor, TabType::Misc, ButtonCallbacks::SendChatMessage));
		pWatchMenuHandler->UIElements.push_back(UIButton("Announce CV1", Vector3(-700.0f, 755.0f, 0.0f), buttonColor, TabType::Misc, ButtonCallbacks::ShowNotificationAll));
		pWatchMenuHandler->UIElements.push_back(UIButton("Announce CV2", Vector3(-700.0f, 635.0f, 0.0f), buttonColor, TabType::Misc, ButtonCallbacks::ShowBannerNotificationAll));
		pWatchMenuHandler->UIElements.push_back(UIToggleButton("Fling: Random", Vector3(-700.0f, 515.0f, 0.0f), buttonColor, TabType::Misc, &globals::fling::random, ButtonCallbacks::Null));
		pWatchMenuHandler->UIElements.push_back(UIButton("Select Camera", Vector3(-700.0f, 395.0f, 0.0f), buttonColor, TabType::Misc, ButtonCallbacks::SelectTMZCamera));
		pWatchMenuHandler->UIElements.push_back(UIButton("Clear Camera", Vector3(-700.0f, 275.0f, 0.0f), buttonColor, TabType::Misc, ButtonCallbacks::ClearTMZCameraSelection));
		pWatchMenuHandler->UIElements.push_back(UIToggleButton("TMZ Camera", Vector3(-700.0f, 155.0f, 0.0f), buttonColor, TabType::Misc, &globals::CameraTMZMode, ButtonCallbacks::Null));

		// new row
		pWatchMenuHandler->UIElements.push_back(UIButton("Jew Royalty", Vector3(-385.0f, 875.0f, 0.0f), buttonColor, TabType::Misc, ButtonCallbacks::SetSelfMasterClient));
		pWatchMenuHandler->UIElements.push_back(UIButton("Delete All", Vector3(-385.0f, 755.0f, 0.0f), buttonColor, TabType::Misc, ButtonCallbacks::DeleteAll));
		pWatchMenuHandler->UIElements.push_back(UIButton("Spawn Jedi Object", Vector3(-385.0f, 635.0f, 0.0f), buttonColor, TabType::Misc, ButtonCallbacks::SpawnJediObject));
		pWatchMenuHandler->UIElements.push_back(UIToggleButton("Jedi: Dominant Hand", Vector3(-385.0f, 515.0f, 0.0f), buttonColor, TabType::Misc, &globals::jedi::dominantHand, ButtonCallbacks::Null));
		pWatchMenuHandler->UIElements.push_back(UIToggleButton("Jedi: Legacy", Vector3(-385.0f, 395.0f, 0.0f), buttonColor, TabType::Misc, &globals::jedi::legacyMode, ButtonCallbacks::Null));
		pWatchMenuHandler->UIElements.push_back(UIButton("Skip Quest", Vector3(-385.0f, 275.0f, 0.0f), buttonColor, TabType::Misc, ButtonCallbacks::QuestSkip));
		pWatchMenuHandler->UIElements.push_back(UIButton("Give S+ Rank", Vector3(-385.0f, 155.0f, 0.0f), buttonColor, TabType::Misc, ButtonCallbacks::GiveSRank));
	
		// new row
		pWatchMenuHandler->UIElements.push_back(UIButton("Quest Gift", Vector3(-70.0f, 875.0f, 0.0f), buttonColor, TabType::Misc, ButtonCallbacks::GenerateQuestGift));
		pWatchMenuHandler->UIElements.push_back(UIButton("Rename Texts", Vector3(-70.0f, 755.0f, 0.0f), buttonColor, TabType::Misc, ButtonCallbacks::RenameTextObjects));
		pWatchMenuHandler->UIElements.push_back(UIButton("Destroy Sit Seats", Vector3(-70.0f, 635.0f, 0.0f), buttonColor, TabType::Misc, ButtonCallbacks::DestroySitSeats));
		pWatchMenuHandler->UIElements.push_back(UIToggleButton("Sit Loop", Vector3(-70.0f, 515.0f, 0.0f), buttonColor, TabType::Misc, &globals::enableSitLoop, ButtonCallbacks::Null));
		pWatchMenuHandler->UIElements.push_back(UIButton("Destroy Head Seat", Vector3(-70.0f, 395.0f, 0.0f), buttonColor, TabType::Misc, ButtonCallbacks::DestroySitOnHeadSeat));
	}
	
	// exploits
	{
		// first row
		pWatchMenuHandler->UIElements.push_back(UIButton("RAM Crash All", Vector3(-700.0f, 875.0f, 0.0f), buttonColor, TabType::Exploits, ButtonCallbacks::BulletCrashAll));
		pWatchMenuHandler->UIElements.push_back(UIButton("Promote All", Vector3(-700.0f, 755.0f, 0.0f), buttonColor, TabType::Exploits, ButtonCallbacks::UpdateRolesAll));
		pWatchMenuHandler->UIElements.push_back(UIButton("Swap Players", Vector3(-700.0f, 635.0f, 0.0f), buttonColor, TabType::Exploits, ButtonCallbacks::RotateAllPL));
		pWatchMenuHandler->UIElements.push_back(UIButton("Give All Tool", Vector3(-700.0f, 515.0f, 0.0f), buttonColor, TabType::Exploits, ButtonCallbacks::ForceToolAll));
		pWatchMenuHandler->UIElements.push_back(UIButton("Spawn Asset All", Vector3(-700.0f, 395.0f, 0.0f), buttonColor, TabType::Exploits, ButtonCallbacks::SpawnAssetAll));
		pWatchMenuHandler->UIElements.push_back(UIButton("Jew Royalty", Vector3(-700.0f, 275.0f, 0.0f), buttonColor, TabType::Exploits, ButtonCallbacks::SetSelfMasterClient));
		pWatchMenuHandler->UIElements.push_back(UIToggleButton("GAS: LeaveParty", Vector3(-700.0f, 155.0f, 0.0f), buttonColor, TabType::Exploits, &globals::forceLeavePartyGas, ButtonCallbacks::Null));


		// new row
		pWatchMenuHandler->UIElements.push_back(UIButton("GAS All", Vector3(-385.0f, 875.0f, 0.0f), buttonColor, TabType::Exploits, ButtonCallbacks::GoToRoomAll));
		pWatchMenuHandler->UIElements.push_back(UIButton("Update Audio", Vector3(-385.0f, 755.0f, 0.0f), buttonColor, TabType::Exploits, ButtonCallbacks::UpdateAudioPlayer));
		pWatchMenuHandler->UIElements.push_back(UIButton("Play Audio", Vector3(-385.0f, 635.0f, 0.0f), buttonColor, TabType::Exploits, ButtonCallbacks::PlayAudioSampleAll));
		pWatchMenuHandler->UIElements.push_back(UIButton("Stop Audio", Vector3(-385.0f, 515.0f, 0.0f), buttonColor, TabType::Exploits, ButtonCallbacks::StopCachedAudioSample));
		pWatchMenuHandler->UIElements.push_back(UIButton("Clean Up Bosses", Vector3(-385.0f, 395.0f, 0.0f), buttonColor, TabType::Exploits, ButtonCallbacks::CleanGarbagePrefabs));
		pWatchMenuHandler->UIElements.push_back(UIToggleButton("Disable CV2", Vector3(-385.0f, 275.0f, 0.0f), buttonColor, TabType::Exploits, &globals::disableCircuits, ButtonCallbacks::Null));
		pWatchMenuHandler->UIElements.push_back(UIToggleButton("Aura Check", Vector3(-385.0f, 155.0f, 0.0f), buttonColor, TabType::Exploits, &globals::makerPenDropperToggle, ButtonCallbacks::Null));
		
		// new row
		pWatchMenuHandler->UIElements.push_back(UIToggleButton("Aura Announce", Vector3(-70.0f, 875.0f, 0.0f), buttonColor, TabType::Exploits, &globals::makerPenDropperAnnounceToggle, ButtonCallbacks::Null));
		pWatchMenuHandler->UIElements.push_back(UIToggleButton("Vanish 2.0", Vector3(-70.0f, 755.0f, 0.0f), buttonColor, TabType::Exploits, &globals::photon::antis::outbound::blockPlayerInstantiation, ButtonCallbacks::Null));
	}

	// asset spawn
	{
		pWatchMenuHandler->UIElements.push_back(UIButton("Spawn Asset", Vector3(-700.0f, 875.0f, 0.0f), buttonColor, TabType::Assets, ButtonCallbacks::SpawnAssetOnSelf));
	}

	// playerlist
	{
		// unique placement
		pWatchMenuHandler->UIElements.push_back(UIText("Selected Player: LocalPlayer", Vector3(0.0f, 950.0f, 0.0f), TabType::PlayerList, 32, true));
		
		// first row
		pWatchMenuHandler->UIElements.push_back(UIButton("Set Royalty", Vector3(-700.0f, 875.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PlayerList::SetMasterClientTarget));
		pWatchMenuHandler->UIElements.push_back(UIButton("Kick", Vector3(-700.0f, 755.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PlayerList::RespawnAtInfinityTarget));
		pWatchMenuHandler->UIElements.push_back(UIButton("RAM Crash", Vector3(-700.0f, 635.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PlayerList::BulletCrashTarget));
#ifndef PROD
		pWatchMenuHandler->UIElements.push_back(UIButton("Death", Vector3(-700.0f, 515.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PlayerList::DeathTarget));
#endif
		pWatchMenuHandler->UIElements.push_back(UIButton("Grab", Vector3(-700.0f, 395.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PlayerList::TeleportToMeTarget));
		pWatchMenuHandler->UIElements.push_back(UIButton("Teleport", Vector3(-700.0f, 275.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PlayerList::TeleportToTarget));
		pWatchMenuHandler->UIElements.push_back(UIButton("Teleport All", Vector3(-700.0f, 155.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PlayerList::TeleportAllToTarget));

		// new row
		pWatchMenuHandler->UIElements.push_back(UIButton("Void", Vector3(-385.0f, 875.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PlayerList::TeleportToLimitTarget));
		pWatchMenuHandler->UIElements.push_back(UIButton("Respawn", Vector3(-385.0f, 755.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PlayerList::RespawnPlayerTarget));
		pWatchMenuHandler->UIElements.push_back(UIButton("Despawn", Vector3(-385.0f, 635.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PlayerList::DespawnPlayerTarget));
		pWatchMenuHandler->UIElements.push_back(UIButton("Spawn", Vector3(-385.0f, 515.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PlayerList::SpawnPlayerTarget));
		pWatchMenuHandler->UIElements.push_back(UIButton("Spawn Asset", Vector3(-385.0f, 395.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PlayerList::SpawnAssetOnTarget));
		pWatchMenuHandler->UIElements.push_back(UIButton("Jedi", Vector3(-385.0f, 275.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PlayerList::JediTarget));
		pWatchMenuHandler->UIElements.push_back(UIButton("MSG CV1", Vector3(-385.0f, 155.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PlayerList::ShowNotificationTarget));

		// new row
		pWatchMenuHandler->UIElements.push_back(UIButton("MSG CV2", Vector3(-70.0f, 875.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PlayerList::ShowBannerNotificationTarget));
		pWatchMenuHandler->UIElements.push_back(UIButton("Promote", Vector3(-70.0f, 755.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PlayerList::UpdateRolesTarget));
		pWatchMenuHandler->UIElements.push_back(UIButton("Sit", Vector3(-70.0f, 635.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PlayerList::SitTarget));
		pWatchMenuHandler->UIElements.push_back(UIButton("Clothing", Vector3(-70.0f, 515.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PlayerList::ForceHoldClothingTarget));
		pWatchMenuHandler->UIElements.push_back(UIButton("Exterminate", Vector3(-70.0f, 395.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PlayerList::ExterminateTarget));
		pWatchMenuHandler->UIElements.push_back(UIButton("HEAT", Vector3(-70.0f, 275.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PlayerList::PlayAudioSampleTarget));
		pWatchMenuHandler->UIElements.push_back(UIButton("Fling", Vector3(-70.0f, 155.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PlayerList::FlingTarget));

		// new row
		pWatchMenuHandler->UIElements.push_back(UIButton("Join My Party", Vector3(245.0f, 875.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PlayerList::JoinMyPartyTarget));
		pWatchMenuHandler->UIElements.push_back(UIButton("Join Party", Vector3(245.0f, 755.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PlayerList::JoinPartyTarget));
		pWatchMenuHandler->UIElements.push_back(UIButton("Leave Party", Vector3(245.0f, 635.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PlayerList::LeavePartyTarget));
		pWatchMenuHandler->UIElements.push_back(UIButton("Sit On Head", Vector3(245.0f, 515.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PlayerList::SitOnPlayerHeadTarget));
		pWatchMenuHandler->UIElements.push_back(UIButton("Fake Vote Kick", Vector3(245.0f, 395.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PlayerList::FakeVoteKickTarget));
		pWatchMenuHandler->UIElements.push_back(UIButton("Level Up", Vector3(245.0f, 275.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PlayerList::LevelUpTarget));
#ifndef PROD
		pWatchMenuHandler->UIElements.push_back(UIButton("BAN", Vector3(245.0f, 155.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PlayerList::ForceMakerPenTarget));
#endif
		
		// new row
		pWatchMenuHandler->UIElements.push_back(UIButton("GAS", Vector3(560.0f, 875.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PlayerList::GoToRoomTarget));
		pWatchMenuHandler->UIElements.push_back(UIButton("Gift Test", Vector3(560.0f, 755.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PlayerList::GiftPlayerTest));

	}

#ifndef PROD
	// image
	{
		// first row
		pWatchMenuHandler->UIElements.push_back(UIButton("Hide UI", Vector3(-700.0f, 900.0f, 0.0f), buttonColor, TabType::Image, ButtonCallbacks::HideUI));
		pWatchMenuHandler->UIElements.push_back(UIButton("Refresh Images", Vector3(0.0f, 900.0f, 0.0f), buttonColor, TabType::Image, ButtonCallbacks::RefreshImages));
		pWatchMenuHandler->UIElements.push_back(UIButton("Previous", Vector3(-320.0f, 900.0f, 0.0f), buttonColor, TabType::Image, ButtonCallbacks::PreviousImage));
		pWatchMenuHandler->UIElements.push_back(UIButton("Next", Vector3(320.0f, 900.0f, 0.0f), buttonColor, TabType::Image, ButtonCallbacks::NextImage));
		pWatchMenuHandler->UIElements.push_back(UIButton("Restore Background", Vector3(-700.0f, 780.0f, 0.0f), buttonColor, TabType::Image, ButtonCallbacks::RestoreBackground));
	}
#endif
	
#ifdef lolshit
	
	/// Movement
	pWatchMenuHandler->UIElements.push_back(UIToggleButton("Dynamic", Vector3(-700.0f, 900.0f, 0.0f), buttonColor, TabType::Movement, &globals::Ihooks::get_IsFlyingEnabled, ButtonCallbacks::Null));
	pWatchMenuHandler->UIElements.push_back(UIToggleButton("Static Fly", Vector3(-700.0f, 780.0f, 0.0f), buttonColor, TabType::Movement, &globals::Ihooks::AddFlyEnabled, ButtonCallbacks::Null));
	pWatchMenuHandler->UIElements.push_back(UIToggleButton("Force Fly", Vector3(-700.0f, 660.0f, 0.0f), buttonColor, TabType::Movement, &globals::staticFlyToggle, ButtonCallbacks::Null));
#ifndef CHEAP
	pWatchMenuHandler->UIElements.push_back(UIToggleButton("Packet Fly", Vector3(-700.0f, 540.0f, 0.0f), buttonColor, TabType::Movement, &globals::packetfly::toggle, ButtonCallbacks::Null));
#endif

	/// Misc
	pWatchMenuHandler->UIElements.push_back(UIToggleButton("Chams", Vector3(-700.0f, 900.0f, 0.0f), buttonColor, TabType::Misc, &globals::chams::toggle, ButtonCallbacks::Null));
	pWatchMenuHandler->UIElements.push_back(UIToggleButton("Hitboxes", Vector3(-700.0f, 780.0f, 0.0f), buttonColor, TabType::Misc, &globals::hitboxes::toggle, ButtonCallbacks::Null));
	pWatchMenuHandler->UIElements.push_back(UIToggleButton("Auto Gun Mods", Vector3(-700.0f, 660.0f, 0.0f), buttonColor, TabType::Misc, &globals::autoGun::autoGunToggle, ButtonCallbacks::Null));
#ifndef CHEAP
	pWatchMenuHandler->UIElements.push_back(UIButton("Change Head Size", Vector3(-700.0f, 540.0f, 0.0f), buttonColor, TabType::Misc, ButtonCallbacks::ChangeHeadSize));
	pWatchMenuHandler->UIElements.push_back(UIButton("Broadcast Announcement", Vector3(-700.0f, 420.0f, 0.0f), buttonColor, TabType::Misc, ButtonCallbacks::ShowNotificationAll));
	pWatchMenuHandler->UIElements.push_back(UIButton("Spawn JediTarget Object", Vector3(-700.0f, 300.0f, 0.0f), buttonColor, TabType::Misc, ButtonCallbacks::SpawnJediObject));
#endif

	/// Exploits
#ifndef CHEAP
	//pWatchMenuHandler->UIElements.push_back(UIButton("Disable Camera", Vector3(-700.0f, 900.0f, 0.0f), buttonColor, TabType::Exploits, ButtonCallbacks::DisableShareCamera));
	pWatchMenuHandler->UIElements.push_back(UIButton("RAM Crash All", Vector3(-700.0f, 780.0f, 0.0f), buttonColor, TabType::Exploits, ButtonCallbacks::BulletCrashAll));
	pWatchMenuHandler->UIElements.push_back(UIButton("Promote All", Vector3(-700.0f, 660.0f, 0.0f), buttonColor, TabType::Exploits, ButtonCallbacks::PromoteAll));
	pWatchMenuHandler->UIElements.push_back(UIButton("Swap Players", Vector3(-700.0f, 540.0f, 0.0f), buttonColor, TabType::Exploits, ButtonCallbacks::SwapPL));
	pWatchMenuHandler->UIElements.push_back(UIButton("Give All Tools", Vector3(-700.0f, 420.0f, 0.0f), buttonColor, TabType::Exploits, ButtonCallbacks::GiveAllTools));
	pWatchMenuHandler->UIElements.push_back(UIButton("Jew Royalty", Vector3(-700.0f, 300.0f, 0.0f), buttonColor, TabType::Exploits, ButtonCallbacks::JewRoyalty));
	pWatchMenuHandler->UIElements.push_back(UIButton("Vanish", Vector3(-700.0f, 180.0f, 0.0f), buttonColor, TabType::Exploits, ButtonCallbacks::Vanish));
#endif
	pWatchMenuHandler->UIElements.push_back(UIButton("Promote Self", Vector3(-385.0, 900.0f, 0.0f), buttonColor, TabType::Exploits, ButtonCallbacks::PromoteSelf));
#ifndef CHEAP
	pWatchMenuHandler->UIElements.push_back(UIToggleButton("Skill Gap", Vector3(-385.0, 780.0f, 0.0f), buttonColor, TabType::Exploits, &globals::skillGapToggle, ButtonCallbacks::Null));
	pWatchMenuHandler->UIElements.push_back(UIToggleButton("Auto Vanish", Vector3(-385.0, 660.0f, 0.0f), buttonColor, TabType::Exploits, &globals::autoVanishToggle, ButtonCallbacks::Null));
	pWatchMenuHandler->UIElements.push_back(UIToggleButton("Cloak", Vector3(-385.0, 540.0f, 0.0f), buttonColor, TabType::Exploits, &globals::cloakToggle, ButtonCallbacks::Null));
#endif

	/// Assets Spawn
	pWatchMenuHandler->UIElements.push_back(UIButton("Spawn Asset", Vector3(-700.0f, 900.0f, 0.0f), buttonColor, TabType::Assets, ButtonCallbacks::SpawnAsset));

	/// Player List
	pWatchMenuHandler->UIElements.push_back(UIText("Selected Player: LocalPlayer", Vector3(0.0f, 950.0f, 0.0f), TabType::PlayerList, 32, true));
#ifndef CHEAP
	// exploits
	pWatchMenuHandler->UIElements.push_back(UIButton("Set Royalty", Vector3(-700.0f, 875.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PL::SetRoyalty));
	pWatchMenuHandler->UIElements.push_back(UIButton("Kick", Vector3(-700.0f, 755.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PL::Kick));
	pWatchMenuHandler->UIElements.push_back(UIButton("RAM Crash", Vector3(-700.0f, 635.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PL::BulletCrash));
	// teleports
#endif
	pWatchMenuHandler->UIElements.push_back(UIButton("Grab", Vector3(-385.0f, 875.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PL::Grab));
	pWatchMenuHandler->UIElements.push_back(UIButton("Teleport", Vector3(-385.0f, 755.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PL::Teleport));
#ifndef CHEAP
	pWatchMenuHandler->UIElements.push_back(UIButton("Teleport All", Vector3(-385.0f, 635.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PL::TeleportAll));
	pWatchMenuHandler->UIElements.push_back(UIButton("Void", Vector3(-385.0f, 515.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PL::Void));
	pWatchMenuHandler->UIElements.push_back(UIButton("Respawn", Vector3(-385.0f, 395.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PL::Respawn));
	pWatchMenuHandler->UIElements.push_back(UIButton("Despawn", Vector3(-385.0f, 275.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PL::Despawn));
	pWatchMenuHandler->UIElements.push_back(UIButton("Spawn", Vector3(-385.0f, 155.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PL::Spawn));
	// Misc
	pWatchMenuHandler->UIElements.push_back(UIButton("Spawn Item", Vector3(-70.0f, 875.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PL::SpawnItem));
	pWatchMenuHandler->UIElements.push_back(UIButton("JediTarget", Vector3(-70.0f, 755.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PL::Jedi));
	pWatchMenuHandler->UIElements.push_back(UIButton("Message", Vector3(-70.0f, 635.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PL::Message));
	pWatchMenuHandler->UIElements.push_back(UIButton("Promotion", Vector3(-70.0f, 515.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PL::Promotion));
	pWatchMenuHandler->UIElements.push_back(UIButton("Clothing", Vector3(-70.0f, 395.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PL::Clothing));
	pWatchMenuHandler->UIElements.push_back(UIButton("Exterminate", Vector3(-70.0f, 275.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PL::Exterminate));
#endif
#ifndef PROD
	pWatchMenuHandler->UIElements.push_back(UIButton("SitTarget", Vector3(-70.0f, 155.0f, 0.0f), buttonColor, TabType::PlayerList, ButtonCallbacks::PL::Sit));
#endif

#endif
}