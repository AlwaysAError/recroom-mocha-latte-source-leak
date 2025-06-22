#pragma once

void TabChange(TabType tabType) {
	for (auto& [TabType, TabGO] : tabGameObjects) {
		if (tabType == TabType)
			TabGO->set_active(true);
		else
			TabGO->set_active(false);
	}
}

namespace ButtonCallbacks
{
	void MenuToggleCallback(UIButton* instance) {

		for (int i = 0; i < pWatchMenuHandler->router->get_transform()->get_ChildCount(); i++) {
			GameObject* childGO = pWatchMenuHandler->router->get_transform()->GetChild(i)->get_gameObject();

			if (childGO != nullptr)
			{
				childGO->set_active(false);
			}
		}

		if (pWatchMenuHandler->mochaMenuGO != nullptr) {
			pWatchMenuHandler->mochaMenuGO->set_active(true);
			pWatchMenuHandler->isOnMenu = true;
		}

		TabChange(TabType::Movement);
	}

	void SwitchTab(UIButton* instance) {
		TabChange(instance->tabType);
	}

	void SwitchToPlayerlistTab(UIButton* instance) {

		bool foundProfile = false;

		for (int i = 0; i < pWatchMenuHandler->router->get_transform()->get_ChildCount(); i++) {

			GameObject* childGO = pWatchMenuHandler->router->get_transform()->GetChild(i)->get_gameObject();

			if (childGO != nullptr)
			{
				if ((std::string(ReadIl2CppString(childGO->GetName())).find("Page: (PlayerProfile)") != std::string::npos) && childGO->get_active()) {

					auto playerProfileGO = childGO->get_transform()->GetChild(0)->get_gameObject();

					if (playerProfileGO == nullptr) return; /// we love split tests! unstable shits...

					BaseAccountModel* accountModel = (BaseAccountModel*)playerProfileGO->GetComponent("RRUI.Data.AccountModel"); // this inherits BaseAccountModel

					if (accountModel == nullptr) return;

					pWatchMenuHandler->selectedPlayerId = accountModel->get_AccountId();

					foundProfile = true;
					break;
				}
			}
		}

		if (!foundProfile)
			pWatchMenuHandler->selectedPlayerId = 0; // when we switch to tab from menu instead of profile ui

		PhotonPlayer* selectedPlayer = nullptr;

		if (foundProfile && (pWatchMenuHandler->selectedPlayerId != 0)) {
			for (const auto& [photonPlayer, player] : cachedPlayerlist) {

				if (int32_t(std::stoi(player.playerID)) == pWatchMenuHandler->selectedPlayerId) {
					selectedPlayer = photonPlayer;
					break;
				}
			}
		}

		if (selectedPlayer != nullptr) {
			pSelectedPlayer = selectedPlayer;
			Log::debug("Selected: " + std::string(cachedPlayerlist[selectedPlayer].DisplayName));
			((UIText*)UIText::selectedPlayerText)->SetText(std::string("Selected Player: ") + cachedPlayerlist[selectedPlayer].DisplayName);
		}
		else
			((UIText*)UIText::selectedPlayerText)->SetText(std::string("Selected Player: ") + localPlayer.DisplayName);

		for (int i = 0; i < pWatchMenuHandler->router->get_transform()->get_ChildCount(); i++) {
			GameObject* childGO = pWatchMenuHandler->router->get_transform()->GetChild(i)->get_gameObject();

			if (childGO != nullptr)
			{
				childGO->set_active(false);
			}
		}

		if (pWatchMenuHandler->mochaMenuGO != nullptr) {
			pWatchMenuHandler->mochaMenuGO->set_active(true);
			pWatchMenuHandler->isOnMenu = true;
		}

		((UIButton*)UIButton::pPlayerSelectButton)->gameObject->set_active(false);

		TabChange(instance->tabType);
	}

	void Null(void* instance) { return; };
}