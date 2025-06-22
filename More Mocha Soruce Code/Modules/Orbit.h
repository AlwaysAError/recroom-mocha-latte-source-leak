#pragma once

#include <cmath>

void SpawnOrbitObject(void* null) // this must be async or you will hang
{
	ThreadFix();
	/*
	std::unique_lock<std::timed_mutex> onUpdateLock(globals::onUpdate::onUpdateMutex, std::defer_lock);

	if (onUpdateLock.try_lock_for(std::chrono::seconds(globals::onUpdateMutexTimeout))) {

		void* object = nullptr;
		void** pObject = &object;

		globals::onUpdate::functionQueue.push_back(
			globals::onUpdate::Exec(
				globals::onUpdate::OnUpdateFunc::ItemSpawn,
				globals::onUpdate::Info::ItemSpawn(
					true,
					true,
					Vector3(0, 0, 0),
					Quaternion(0, 0, 0, 0),
					globals::instantiateAssets::scale,
					il2cpp_string_new_spoof(globals::instantiateAssets::prefab),
					nullptr // this might crash
				))
		);

		onUpdateLock = ExecuteOnUpdateQueue(std::move(onUpdateLock));

		while (globals::onUpdate::inExecution) {
			Sleep(10); // prevent high cpu usuage
		}

		GameObject* internalGameObject = (GameObject*)object;

		globals::orbit::orbitObjects.push_back(internalGameObject);

		onUpdateLock.unlock();
	}
	else {
		Log::error("onUpdateLock timed out in SpawnOrbitObject!");
	}
	*/
}

void OrbitThread(void* null)
{
	ThreadFix();
	globals::orbit::orbitThreadRun = true;
	while (globals::orbit::orbitThreadRun)
	{
		if (globals::orbit::orbitObjects.size() != 0)
		{

			Transform* playerTransform = localPlayer.playerGameObject->get_transform();
			Transform* localChildBodyPartsTransform = playerTransform->GetChild(0);
			Transform* localHeadTransform = localChildBodyPartsTransform->GetChild(0);

			Vector3 localPosition = localHeadTransform->get_position();

			float degrees = 360 / globals::orbit::orbitObjects.size();
			float objectDistance = globals::orbit::objectDistance;
			float objectHeight = globals::orbit::objectHeight;
			float speed = globals::orbit::speed;

			std::vector<void*> internalOrbitGameObjects = globals::orbit::orbitObjects;

			int index = 0;
			for (void* internalGameObject : internalOrbitGameObjects)
			{
				if (internalGameObject == nullptr) continue;

				GameObject* object = (GameObject*)internalGameObject;

				Transform* objectTransform = object->get_transform();
				float timeNeed = Time::get_Time();

				Vector3 objectPosition = { sin(timeNeed * speed + (degrees * index)) * objectDistance, objectHeight, cos(timeNeed * speed + (degrees * index)) * objectDistance };

				float desiredPosX = localPosition.x + objectPosition.x;
				float desiredPosY = localPosition.y + objectPosition.y;
				float desiredPosZ = localPosition.z + objectPosition.z;

				Vector3 desiredPos = { desiredPosX, desiredPosY, desiredPosZ };
				objectTransform->set_localPosition(desiredPos);
				index++;
			}
		}
	}

	globals::orbit::orbitObjects.clear();
	return;
}