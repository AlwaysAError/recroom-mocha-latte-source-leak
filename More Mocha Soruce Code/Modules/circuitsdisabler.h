#pragma once

bool wasCircuitsDisabledLastFrame = false;

void CircuitsDisablerLogic() {

	if (globals::disableCircuits) {

		if (localPlayerExists && localPlayer.loadingStage >= LoadingStage::LOADED) {

			CircuitsV2Manager* circuitsManager = CircuitsV2Manager::GetCircuitsV2Manager();

			if (circuitsManager != nullptr) {

				GameObject* circuitManagerGO = circuitsManager->get_gameObject();

				if (circuitManagerGO != nullptr) {
					
					if (circuitManagerGO->get_active())
						circuitManagerGO->set_active(false);

					if (globals::destroyCircuitsManager)
					{
						circuitManagerGO->Destroy();
					}
					
					wasCircuitsDisabledLastFrame = true;
				}
			}
		}
	}
	else {

		if (wasCircuitsDisabledLastFrame) {

			CircuitsV2Manager* circuitsManager = CircuitsV2Manager::GetCircuitsV2Manager();

			if (circuitsManager != nullptr) {

				GameObject* circuitManagerGO = circuitsManager->get_gameObject();

				if (circuitManagerGO != nullptr) {


					if (!circuitManagerGO->get_active())
						circuitManagerGO->set_active(true);

					wasCircuitsDisabledLastFrame = false;
				}
			}
		}
	}
}