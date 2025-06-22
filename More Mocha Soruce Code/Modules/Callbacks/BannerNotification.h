#pragma once

namespace Callbacks
{
	namespace Banner {

		enum UGCBannerNotificationPosition
		{
			Upper = 0,
			Lower = 1,
		};

		enum class TextSize
		{
			Small = 0,
			Medium = 1,
			Large = 2,
		};

	}

	bool ShowBannerNotificationTarget(PhotonPlayer* targetPP) {

		if (targetPP != nullptr) {

			std::unique_lock lock(playerlistMutex, std::defer_lock);

			if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {

				const PlayerInfo& targetPlayer = cachedPlayerlist[targetPP];

				std::vector<PhotonView::PayloadEntry> payloadVector = {
					{globals::bannerNotif::notificationPosition,							"System.Int32"},		// notificationPosition
					{globals::bannerNotif::notificationDuration,							"System.Single"},		// notificationDuration
					{(Il2CppObject*)WriteIl2CppString(globals::bannerNotif::titleText.c_str())},							// titleText
					{globals::bannerNotif::titleTextColor,									"UnityEngine.Color"},	// titleTextColor
					{globals::bannerNotif::titleTextBackgroundColor,						"UnityEngine.Color"},	// titleTextBackgroundColor
					{2,																		"System.Int32"},		// titleTextSize
					{(Il2CppObject*)WriteIl2CppString(globals::bannerNotif::mainText.c_str())},								// mainText
					{globals::bannerNotif::mainTextColor,									"UnityEngine.Color"},	// mainTextColor
					{globals::bannerNotif::mainTextBackgroundColor,							"UnityEngine.Color"},	// mainTextBackgroundColor
					{0,																		"System.Int32"},		// mainTextSize
					{(Il2CppObject*)WriteIl2CppString(globals::bannerNotif::leftSideText.c_str())},							// leftSideText
					{(Il2CppObject*)WriteIl2CppString(globals::bannerNotif::rightSideText.c_str())}							// rightSideText
				};

				targetPlayer.photonView->SendRPC("RpcLocalCV2ShowBannerNotification", targetPlayer.photonPlayer, payloadVector);

				lock.unlock();
			}
			else {
				Log::error("playerlistMutex timed out in ShowBannerNotificationTarget!");
				return false;
			}
		}
		
		return true;
	}

	bool ShowBannerNotificationAll() {

		std::unique_lock lock(playerlistMutex, std::defer_lock);

		if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {

			PlayerInfo& dummyPlayer = localPlayer;
			bool found = false;

			for (const auto& playerInfo : std::views::values(cachedPlayerlist)) {
				if (!playerInfo.isLocalPlayer && (playerInfo.loadingStage >= LoadingStage::LOADED)) {
					dummyPlayer = playerInfo;
					found = true;
					break;
				}
			}

			if (!found) {
				Log::error("No dummy PhotonView found for ShowBannerNotificationAll!");
			}

			std::vector<PhotonView::PayloadEntry> payloadVector = {
				{globals::bannerNotif::notificationPosition,							"System.Int32"},		// notificationPosition
				{globals::bannerNotif::notificationDuration,							"System.Single"},		// notificationDuration
				{(Il2CppObject*)WriteIl2CppString(globals::bannerNotif::titleText.c_str())},							// titleText
				{globals::bannerNotif::titleTextColor,									"UnityEngine.Color"},	// titleTextColor
				{globals::bannerNotif::titleTextBackgroundColor,						"UnityEngine.Color"},	// titleTextBackgroundColor
				{2,																		"System.Int32"},		// titleTextSize
				{(Il2CppObject*)WriteIl2CppString(globals::bannerNotif::mainText.c_str())},								// mainText
				{globals::bannerNotif::mainTextColor,									"UnityEngine.Color"},	// mainTextColor
				{globals::bannerNotif::mainTextBackgroundColor,							"UnityEngine.Color"},	// mainTextBackgroundColor
				{0,																		"System.Int32"},		// mainTextSize
				{(Il2CppObject*)WriteIl2CppString(globals::bannerNotif::leftSideText.c_str())},							// leftSideText
				{(Il2CppObject*)WriteIl2CppString(globals::bannerNotif::rightSideText.c_str())}							// rightSideText
			};

			dummyPlayer.photonView->SendRPC("RpcLocalCV2ShowBannerNotification", All, payloadVector);

			lock.unlock();
		}
		else {
			Log::error("playerlistMutex timed out in ShowBannerNotificationAll!");
			return false;
		}
		
		return true;
	}
}