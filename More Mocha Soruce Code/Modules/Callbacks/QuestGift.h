#pragma once

namespace Callbacks {
	bool GenerateQuestGift() {

		QuestManager* manager = QuestManager::get_Instance();

		if (manager == nullptr) return true;

		std::random_device rd;  // Seed for the random number engine
		std::mt19937 gen(rd()); // Standard Mersenne Twister engine
		std::uniform_int_distribution<> distr(99999999, 2147483647);
		manager->TryGenerateLocalPlayerGift(distr(gen));

		return true;
	}
}