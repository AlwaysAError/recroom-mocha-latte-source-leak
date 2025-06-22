#pragma once

void AutoGun() {
	if (globals::autoGun::autoGunToggle) {

		if (localPlayer.loadingStage >= LoadingStage::LOADED) {

			RecRoomPlayer* playerPlayer = RecRoomPlayer::GetFromActorNumber(localPlayer.photonActorID);

			if (playerPlayer != nullptr) {

				if (playerPlayer->get_IsInitialized() && playerPlayer->get_IsInitialLoadFinished()) {

					RecRoomPlayer* localRecRoomPlayer = RecRoomPlayer::GetFromActorNumber(localPlayer.photonActorID);
					if (localRecRoomPlayer != nullptr) {
						Il2CppArray* toolsArray = localRecRoomPlayer->get_AllToolsOnPlayer();
						std::vector<RangedWeapon*> liveRangedWeapons = {};
						if (toolsArray != nullptr) {
							for (int i = 0; i < toolsArray->max_length; i++)
							{

								Component* toolComponent = (Component*)il2cpp_array_get(toolsArray, Il2CppObject*, i);
								GameObject* toolGameObject = toolComponent->get_gameObject();
								if (toolGameObject != nullptr) {

									RangedWeapon* rangedWeaponComponent = (RangedWeapon*)toolGameObject->GetComponent("RecRoom.Core.Combat.RangedWeapon");

									if (rangedWeaponComponent != nullptr) {

										liveRangedWeapons.push_back(rangedWeaponComponent);

										bool foundInList = false;

										for (auto& rangedWeapon : globals::autoGun::autoGunRangedWeapons) {
											if (rangedWeapon.Weapon == rangedWeaponComponent) {
												foundInList = true;
												break;
											}
										}

										if (!foundInList) {
											globals::autoGun::autoGun autoGun = { rangedWeaponComponent, false };
											globals::autoGun::autoGunRangedWeapons.push_back(autoGun);
										}
									}
								}
							}
						}

						for (int i = 0; i < globals::autoGun::autoGunRangedWeapons.size(); i++) {

							auto cachedRangedWeapon = globals::autoGun::autoGunRangedWeapons[i];

							bool foundInList = false;
							for (const auto& liveRangedWeapon : liveRangedWeapons) {
								if (cachedRangedWeapon.Weapon == liveRangedWeapon) {
									foundInList = true;
									break;
								}
							}
							if (!foundInList) {
								globals::autoGun::autoGunRangedWeapons.erase(globals::autoGun::autoGunRangedWeapons.begin() + i);
							}
						}
					}

					for (auto& rangedWeapon : globals::autoGun::autoGunRangedWeapons) {

						if (!rangedWeapon.isModded) {

							if (globals::autoGun::fireRate)
							{

								/*
								Log::debug("start shit");

								bool test1 = GetField<bool>(rangedWeapon.Weapon, 832);
								float test2 = GetField<float>(rangedWeapon.Weapon, 840);
								float test3 = GetField<float>(rangedWeapon.Weapon, 848);
								bool test4 = GetField<bool>(rangedWeapon.Weapon, 856);
								float test5 = GetField<float>(rangedWeapon.Weapon, 864);
								float test6 = GetField<float>(rangedWeapon.Weapon, 872);
								float test7 = GetField<float>(rangedWeapon.Weapon, 880);

								Log::debug("test1: " + std::string(test1 ? "true" : "false"));
								Log::debug("test2: " + std::to_string(test2));
								Log::debug("test3: " + std::to_string(test3));
								Log::debug("test4: " + std::string(test4 ? "true" : "false"));
								Log::debug("test5: " + std::to_string(test5));
								Log::debug("test6: " + std::to_string(test6));
								Log::debug("test7: " + std::to_string(test7));

								Log::debug("end shit");
								*/

								if (globals::autoGun::multiplierMode) {
									float fireRate = GetField<float>(rangedWeapon.Weapon, 572); // FireRate
									fireRate *= globals::autoGun::fireRateMultiplier;
									SetField<float>(rangedWeapon.Weapon, 572, fireRate); // FireRate

								}
								else {
									SetField<float>(rangedWeapon.Weapon, 572, globals::autoGun::fireRateAmount); // FireRate
								}
							}

							if (globals::autoGun::bulletSpeed)
							{
								if (globals::autoGun::multiplierMode) {
									float bulletSpeed = GetField<float>(rangedWeapon.Weapon, 560); // Bullet Speed
									bulletSpeed *= globals::autoGun::bulletSpeedMultiplier;
									SetField<float>(rangedWeapon.Weapon, 560, bulletSpeed); // Bullet Speed

								}
								else {
									SetField<float>(rangedWeapon.Weapon, 560, globals::autoGun::bulletSpeedAmount); // Bullet Speed
								}
							}

							if (globals::autoGun::automaticBulletSpeed)
							{
								if (globals::autoGun::multiplierMode) {
									float automaticBulletSpeed = GetField<float>(rangedWeapon.Weapon, 576); // automatic Bullet Speed
									automaticBulletSpeed *= globals::autoGun::automaticBulletSpeedMultiplier;
									SetField<float>(rangedWeapon.Weapon, 576, automaticBulletSpeed); // automatic Bullet Speed

								}
								else {
									SetField<float>(rangedWeapon.Weapon, 576, globals::autoGun::automaticBulletSpeedAmount); // automatic Bullet Speed
								}
							}

							if (globals::autoGun::recoil)
							{
								RangedWeapon* weapon = (RangedWeapon*)rangedWeapon.Weapon;

								auto screenToolBehaviorConfig = weapon->get_RangedWeaponScreenToolBehaviorConfig();
								if (screenToolBehaviorConfig != nullptr) {

									SetField<bool>(screenToolBehaviorConfig, 200, false); // Recoil
									void* accuracySettings = GetField<void*>(screenToolBehaviorConfig, 168); // ScreenPlayerRangedWeaponAccuracySettings
									if (accuracySettings != nullptr) {
										SetField<float>(accuracySettings, 24, 0); // canonicalMaxSpreadRadius
										SetField<float>(accuracySettings, 28, 0); // dynamicSpreadRadiusChangeTime
										SetField<float>(accuracySettings, 32, 0); // walkingSpreadRadiusScaler
										SetField<float>(accuracySettings, 36, 0); // sprintingSpreadRadiusScaler
										SetField<float>(accuracySettings, 40, 0); // crouchingSpreadRadiusScaler
										SetField<float>(accuracySettings, 44, 0); // proneSpreadRadiusScaler
										SetField<float>(accuracySettings, 48, 0); // aimDownSightsSpreadRadiusScaler
									}
								}
							}

							if (globals::autoGun::beamGunMods)
							{
								Component* component = (Component*)rangedWeapon.Weapon;
								GameObject* gameobject = component->get_gameObject();

								void* BeamGunComponent = (void*)gameobject->GetComponent("RecRoom.Tools.Weapons.BeamGun");
								if (BeamGunComponent != nullptr)
								{
									SetField<float>(BeamGunComponent, 1008, 0); // chargeActivationTime
									SetField<float>(BeamGunComponent, 1048, globals::autoGun::beamAmount); // beamLength
								}
							}

							if (globals::autoGun::burstGunMods) {

								Component* component = (Component*)rangedWeapon.Weapon;
								GameObject* gameobject = component->get_gameObject();

								void* Test = (void*)gameobject->GetComponent("RecRoom.Tools.Weapons.BurstFireGun");
								if (Test != nullptr)
								{
									SetField<float>(Test, 936, 99999999); // burstMode
									SetField<float>(Test, 964, globals::autoGun::burstAmount); // simpleBurstModeBurstSize
									SetField<float>(Test, 960, globals::autoGun::burstAmount); // curveNextShotTimeNormalized ExplosiveWeaponAddon
								}
							}

							if (globals::autoGun::ammo)
							{
								if (globals::autoGun::multiplierMode) {
									int32_t ammoAmount = GetField<int32_t>(rangedWeapon.Weapon, 164); // FireRate
									ammoAmount *= globals::autoGun::ammoMultiplier;
									SetField<int32_t>(rangedWeapon.Weapon, 164, ammoAmount); // FireRate

								}
								else {
									SetField<int32_t>(rangedWeapon.Weapon, 164, globals::autoGun::ammoAmount); // Ammo sidenote: this is actually Weapon* but RangedWeapon* is same so wtv
								}
							}

							if (globals::autoGun::Prediction)
							{
								RangedWeapon* rangedWeaponComponant = (RangedWeapon*)rangedWeapon.Weapon;
								globals::autoGun::BulletSpeed = GetField<float>(rangedWeapon.Weapon, 560);
								globals::autoGun::BulletDrop = rangedWeaponComponant->get_HasBulletDrop();
							}

							rangedWeapon.isModded = true;
						}
					}
				}
			}
		}
	}
}