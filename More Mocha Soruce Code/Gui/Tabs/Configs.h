#pragma once

namespace Configs {

	static class Save {
	private:
		static bool Aimbot();
		static bool AutoGun();
		static bool ESP();
		static bool Chams();
		static bool SkinColor();
		static bool Movement();
		static bool Theme();
		static bool Fov();
	public:
		static bool SaveConfigs() {
			Aimbot();
			AutoGun();
			ESP();
			SkinColor();
			Movement();
			Theme();
			Chams();
			Fov();
			return true;
		}
	};

	static class Load {
	private:
		static bool Aimbot();
		static bool AutoGun();
		static bool ESP();
		static bool SkinColor();
		static bool Chams();
		static bool Movement();
		static bool Theme();
		static bool Fov();
	public:
		static bool Chai();

		static bool LoadConfigs() {
			Aimbot();
			AutoGun();
			ESP();
			SkinColor();
			Movement();
			Theme();
			Chams();
			Fov();
#ifndef PROD
			Chai();
#endif
			return true;
		}
	};
}

bool Configs::Save::Aimbot() {
	try {

		std::filesystem::path directoryPath = "Mocha";
		std::filesystem::path filePath = directoryPath / "aimbot.toml";

		if (!std::filesystem::exists(directoryPath)) {
			std::filesystem::create_directories(directoryPath);
		}

		toml::table settings{
			{"aimbot", toml::table{
				{"toggle", globals::aimbot::toggle},
				{"radius", globals::aimbot::radius},
				{"aimSpeed", globals::aimbot::aimSpeed},
				{"steps", globals::aimbot::steps}
			}},
			{"hitbox", toml::table{
				{"toggle", globals::hitboxes::toggle},
				{"yToggle", globals::hitboxes::yToggle},
				{"multiplier", globals::hitboxes::multiplier}
			}}
		};

		std::ofstream file(filePath.string());
		if (!file.is_open()) {
			throw std::runtime_error("Could not open file: " + filePath.string());
		}

		file << settings;
		file.close();

		Log::debug("Aimbot config saved successfully.");
		return true;
	}
	catch (const std::exception& e) {
		Log::error("Error saving aimbot config: " + std::string(e.what()));
		return false;
	}
}

bool Configs::Load::Aimbot() {

	std::ifstream file("Mocha/aimbot.toml");
	if (!file.good()) {
		Log::error("Error: File does not exist or cannot be opened: Mocha/aimbot.toml");
		return false;
	}

	try {
		auto config = toml::parse_file("Mocha/aimbot.toml");

		globals::aimbot::toggle = config["aimbot"]["toggle"].value_or(false);
		globals::aimbot::radius = config["aimbot"]["radius"].value_or(0);
		globals::aimbot::aimSpeed = config["aimbot"]["aimSpeed"].value_or(0.0f);
		globals::aimbot::steps = config["aimbot"]["steps"].value_or(0);

		globals::hitboxes::toggle = config["hitbox"]["toggle"].value_or(false);
		globals::hitboxes::yToggle = config["hitbox"]["yToggle"].value_or(false);
		globals::hitboxes::multiplier = config["hitbox"]["steps"].value_or(1);

		Log::debug("Aimbot config loaded successfully.");
		return true;
	}
	catch (const std::exception& e) {
		Log::error("Error loading aimbot config: " + std::string(e.what()));
		return false;
	}
}

bool Configs::Save::AutoGun() {
	try {

		std::filesystem::path directoryPath = "Mocha";
		std::filesystem::path filePath = directoryPath / "autogun.toml";

		if (!std::filesystem::exists(directoryPath)) {
			std::filesystem::create_directories(directoryPath);
		}

		toml::table settings{
			{"autogun", toml::table{
				{"multiplierMode", globals::autoGun::multiplierMode},
				{"bulletSpeed", globals::autoGun::bulletSpeed},
				{"bulletSpeedAmount", globals::autoGun::bulletSpeedAmount},
				{"bulletSpeedMultiplier", globals::autoGun::bulletSpeedMultiplier},
				{"automaticBulletSpeed", globals::autoGun::automaticBulletSpeed},
				{"automaticBulletSpeedAmount", globals::autoGun::automaticBulletSpeedAmount},
				{"automaticBulletSpeedMultiplier", globals::autoGun::automaticBulletSpeedMultiplier},
				{"fireRate", globals::autoGun::fireRate},
				{"fireRateAmount", globals::autoGun::fireRateAmount},
				{"fireRateMultiplier", globals::autoGun::fireRateMultiplier},
				{"ammo", globals::autoGun::ammo},
				{"ammoAmount", globals::autoGun::ammoAmount},
				{"ammoMultiplier", globals::autoGun::ammoMultiplier},
				{"recoil", globals::autoGun::recoil},
				{"autoGunToggle", globals::autoGun::autoGunToggle},
				{"burstGunMods", globals::autoGun::burstGunMods},
				{"burstAmount", globals::autoGun::burstAmount},
				{"beamGunMods", globals::autoGun::beamGunMods},
				{"beamAmount", globals::autoGun::beamAmount}
			}}
		};

		std::ofstream file(filePath.string());
		if (!file.is_open()) {
			throw std::runtime_error("Could not open file: " + filePath.string());
		}

		file << settings;
		file.close();

		Log::debug("Autogun config saved successfully.");
		return true;
	}
	catch (const std::exception& e) {
		Log::error("Error saving autogun config: " + std::string(e.what()));
		return false;
	}
}

bool Configs::Load::AutoGun() {

	std::ifstream file("Mocha/autogun.toml");
	if (!file.good()) {
		Log::error("Error: File does not exist or cannot be opened: Mocha/autogun.toml");
		return false;
	}

	try {
		auto config = toml::parse_file("Mocha/autogun.toml");

		globals::autoGun::multiplierMode = config["autogun"]["multiplierMode"].value_or(false);
		globals::autoGun::bulletSpeed = config["autogun"]["bulletSpeed"].value_or(false);
		globals::autoGun::bulletSpeedAmount = config["autogun"]["bulletSpeedAmount"].value_or(0.0f);
		globals::autoGun::bulletSpeedMultiplier = config["autogun"]["bulletSpeedMultiplier"].value_or(0.0f);
		globals::autoGun::automaticBulletSpeed = config["autogun"]["automaticBulletSpeed"].value_or(false);
		globals::autoGun::automaticBulletSpeedAmount = config["autogun"]["automaticBulletSpeedAmount"].value_or(0.0f);
		globals::autoGun::automaticBulletSpeedMultiplier = config["autogun"]["automaticBulletSpeedMultiplier"].value_or(0.0f);
		globals::autoGun::fireRate = config["autogun"]["fireRate"].value_or(false);
		globals::autoGun::fireRateAmount = config["autogun"]["fireRateAmount"].value_or(0.0f);
		globals::autoGun::fireRateMultiplier = config["autogun"]["fireRateMultiplier"].value_or(0.0f);
		globals::autoGun::ammo = config["autogun"]["ammo"].value_or(false);
		globals::autoGun::ammoAmount = config["autogun"]["ammoAmount"].value_or(0);
		globals::autoGun::ammoMultiplier = config["autogun"]["ammoMultiplier"].value_or(0);
		globals::autoGun::recoil = config["autogun"]["recoil"].value_or(false);
		globals::autoGun::autoGunToggle = config["autogun"]["autoGunToggle"].value_or(false);
		globals::autoGun::burstGunMods = config["autogun"]["burstGunMods"].value_or(false);
		globals::autoGun::burstAmount = config["autogun"]["burstAmount"].value_or(0);
		globals::autoGun::beamGunMods = config["autogun"]["beamGunMods"].value_or(false);
		globals::autoGun::beamAmount = config["autogun"]["beamAmount"].value_or(0);

		Log::debug("Autogun config loaded successfully.");
		return true;
	}
	catch (const std::exception& e) {
		Log::error("Error loading autogun config: " + std::string(e.what()));
		return false;
	}
}

bool Configs::Save::ESP() {
	try {

		std::filesystem::path directoryPath = "Mocha";
		std::filesystem::path filePath = directoryPath / "esp.toml";

		if (!std::filesystem::exists(directoryPath)) {
			std::filesystem::create_directories(directoryPath);
		}

		toml::table settings{
			{"state", globals::ESP::toggle},

			{"skeleton", toml::table{
				{"state", globals::ESP::skeleton.state},
				{"renderSelf", globals::ESP::skeleton.renderSelf},
				{"rainbowColor", globals::ESP::skeleton.rainbowColor},
				{"gradientColor", globals::ESP::skeleton.gradientColor},
				{"distanceColor", globals::ESP::skeleton.distanceColor},
				{"fade", globals::ESP::skeleton.fade},
				{"fadeDistance", globals::ESP::skeleton.fadeDistance},
				{"maxDistance", globals::ESP::skeleton.maxDistance},
				{"minDistance", globals::ESP::skeleton.minDistance},
				{"gradientSpeed", globals::ESP::skeleton.gradientSpeed},
				{"staticColor", toml::array{
					globals::ESP::skeleton.staticColor.x,
					globals::ESP::skeleton.staticColor.y,
					globals::ESP::skeleton.staticColor.z,
					globals::ESP::skeleton.staticColor.w
				}},
				{"gradientStartColor", toml::array{
					globals::ESP::skeleton.gradientStartColor.x,
					globals::ESP::skeleton.gradientStartColor.y,
					globals::ESP::skeleton.gradientStartColor.z,
					globals::ESP::skeleton.gradientStartColor.w
				}},
				{"gradientEndColor", toml::array{
					globals::ESP::skeleton.gradientEndColor.x,
					globals::ESP::skeleton.gradientEndColor.y,
					globals::ESP::skeleton.gradientEndColor.z,
					globals::ESP::skeleton.gradientEndColor.w
				}},
				{"closeDistanceColor", toml::array{
					globals::ESP::skeleton.closeDistanceColor.x,
					globals::ESP::skeleton.closeDistanceColor.y,
					globals::ESP::skeleton.closeDistanceColor.z,
					globals::ESP::skeleton.closeDistanceColor.w
				}},
				{"farDistanceColor", toml::array{
					globals::ESP::skeleton.farDistanceColor.x,
					globals::ESP::skeleton.farDistanceColor.y,
					globals::ESP::skeleton.farDistanceColor.z,
					globals::ESP::skeleton.farDistanceColor.w
				}},
				{"lineThickness", globals::ESP::skeleton.lineThickness}
			}},

			{"tracer", toml::table{
				{"state", globals::ESP::tracer.state},
				{"renderSelf", globals::ESP::tracer.renderSelf},
				{"rainbowColor", globals::ESP::tracer.rainbowColor},
				{"gradientColor", globals::ESP::tracer.gradientColor},
				{"distanceColor", globals::ESP::tracer.distanceColor},
				{"fade", globals::ESP::tracer.fade},
				{"fadeDistance", globals::ESP::tracer.fadeDistance},
				{"maxDistance", globals::ESP::tracer.maxDistance},
				{"minDistance", globals::ESP::tracer.minDistance},
				{"gradientSpeed", globals::ESP::tracer.gradientSpeed},
				{"staticColor", toml::array{
					globals::ESP::tracer.staticColor.x,
					globals::ESP::tracer.staticColor.y,
					globals::ESP::tracer.staticColor.z,
					globals::ESP::tracer.staticColor.w
				}},
				{"gradientStartColor", toml::array{
					globals::ESP::tracer.gradientStartColor.x,
					globals::ESP::tracer.gradientStartColor.y,
					globals::ESP::tracer.gradientStartColor.z,
					globals::ESP::tracer.gradientStartColor.w
				}},
				{"gradientEndColor", toml::array{
					globals::ESP::tracer.gradientEndColor.x,
					globals::ESP::tracer.gradientEndColor.y,
					globals::ESP::tracer.gradientEndColor.z,
					globals::ESP::tracer.gradientEndColor.w
				}},
				{"closeDistanceColor", toml::array{
					globals::ESP::tracer.closeDistanceColor.x,
					globals::ESP::tracer.closeDistanceColor.y,
					globals::ESP::tracer.closeDistanceColor.z,
					globals::ESP::tracer.closeDistanceColor.w
				}},
				{"farDistanceColor", toml::array{
					globals::ESP::tracer.farDistanceColor.x,
					globals::ESP::tracer.farDistanceColor.y,
					globals::ESP::tracer.farDistanceColor.z,
					globals::ESP::tracer.farDistanceColor.w
				}},
				{"lineThickness", globals::ESP::tracer.lineThickness}
			}},

			{"box", toml::table{
				{"state", globals::ESP::box.state},
				{"simpleGradient", globals::ESP::box.simpleGradient},
				{"renderSelf", globals::ESP::box.renderSelf},
				{"rainbowColor", globals::ESP::box.rainbowColor},
				{"gradientColor", globals::ESP::box.gradientColor},
				{"distanceColor", globals::ESP::box.distanceColor},
				{"fade", globals::ESP::box.fade},
				{"fadeDistance", globals::ESP::box.fadeDistance},
				{"maxDistance", globals::ESP::box.maxDistance},
				{"minDistance", globals::ESP::box.minDistance},
				{"gradientSpeed", globals::ESP::box.gradientSpeed},
				{"staticColor", toml::array{
					globals::ESP::box.staticColor.x,
					globals::ESP::box.staticColor.y,
					globals::ESP::box.staticColor.z,
					globals::ESP::box.staticColor.w
				}},
				{"gradientStartColor", toml::array{
					globals::ESP::box.gradientStartColor.x,
					globals::ESP::box.gradientStartColor.y,
					globals::ESP::box.gradientStartColor.z,
					globals::ESP::box.gradientStartColor.w
				}},
				{"gradientEndColor", toml::array{
					globals::ESP::box.gradientEndColor.x,
					globals::ESP::box.gradientEndColor.y,
					globals::ESP::box.gradientEndColor.z,
					globals::ESP::box.gradientEndColor.w
				}},
				{"closeDistanceColor", toml::array{
					globals::ESP::box.closeDistanceColor.x,
					globals::ESP::box.closeDistanceColor.y,
					globals::ESP::box.closeDistanceColor.z,
					globals::ESP::box.closeDistanceColor.w
				}},
				{"farDistanceColor", toml::array{
					globals::ESP::box.farDistanceColor.x,
					globals::ESP::box.farDistanceColor.y,
					globals::ESP::box.farDistanceColor.z,
					globals::ESP::box.farDistanceColor.w
				}},
				{"lineThickness", globals::ESP::box.lineThickness}
			}},

			{"boxOutline", toml::table{
				{"state", globals::ESP::boxOutline.state},
				{"rainbowColor", globals::ESP::boxOutline.rainbowColor},
				{"gradientColor", globals::ESP::boxOutline.gradientColor},
				{"distanceColor", globals::ESP::boxOutline.distanceColor},
				{"fade", globals::ESP::boxOutline.fade},
				{"fadeDistance", globals::ESP::boxOutline.fadeDistance},
				{"staticColor", toml::array{
					globals::ESP::boxOutline.staticColor.x,
					globals::ESP::boxOutline.staticColor.y,
					globals::ESP::boxOutline.staticColor.z,
					globals::ESP::boxOutline.staticColor.w
				}},
				{"gradientStartColor", toml::array{
					globals::ESP::boxOutline.gradientStartColor.x,
					globals::ESP::boxOutline.gradientStartColor.y,
					globals::ESP::boxOutline.gradientStartColor.z,
					globals::ESP::boxOutline.gradientStartColor.w
				}},
				{"gradientEndColor", toml::array{
					globals::ESP::boxOutline.gradientEndColor.x,
					globals::ESP::boxOutline.gradientEndColor.y,
					globals::ESP::boxOutline.gradientEndColor.z,
					globals::ESP::boxOutline.gradientEndColor.w
				}},
				{"closeDistanceColor", toml::array{
					globals::ESP::boxOutline.closeDistanceColor.x,
					globals::ESP::boxOutline.closeDistanceColor.y,
					globals::ESP::boxOutline.closeDistanceColor.z,
					globals::ESP::boxOutline.closeDistanceColor.w
				}},
				{"farDistanceColor", toml::array{
					globals::ESP::boxOutline.farDistanceColor.x,
					globals::ESP::boxOutline.farDistanceColor.y,
					globals::ESP::boxOutline.farDistanceColor.z,
					globals::ESP::boxOutline.farDistanceColor.w
				}},
				{"lineThickness", globals::ESP::boxOutline.lineThickness},
				{"simpleGradient", globals::ESP::boxOutline.simpleGradient}
			}},

			{"nametag", toml::table{
				{"state", globals::ESP::nametag.state},
				{"renderSelf", globals::ESP::nametag.renderSelf},
				{"rainbowColor", globals::ESP::nametag.rainbowColor},
				{"gradientColor", globals::ESP::nametag.gradientColor},
				{"distanceColor", globals::ESP::nametag.distanceColor},
				{"fade", globals::ESP::nametag.fade},
				{"fadeDistance", globals::ESP::nametag.fadeDistance},
				{"maxDistance", globals::ESP::nametag.maxDistance},
				{"minDistance", globals::ESP::nametag.minDistance},
				{"gradientSpeed", globals::ESP::nametag.gradientSpeed},
				{"staticColor", toml::array{
					globals::ESP::nametag.staticColor.x,
					globals::ESP::nametag.staticColor.y,
					globals::ESP::nametag.staticColor.z,
					globals::ESP::nametag.staticColor.w
				}},
				{"gradientStartColor", toml::array{
					globals::ESP::nametag.gradientStartColor.x,
					globals::ESP::nametag.gradientStartColor.y,
					globals::ESP::nametag.gradientStartColor.z,
					globals::ESP::nametag.gradientStartColor.w
				}},
				{"gradientEndColor", toml::array{
					globals::ESP::nametag.gradientEndColor.x,
					globals::ESP::nametag.gradientEndColor.y,
					globals::ESP::nametag.gradientEndColor.z,
					globals::ESP::nametag.gradientEndColor.w
				}},
				{"closeDistanceColor", toml::array{
					globals::ESP::nametag.closeDistanceColor.x,
					globals::ESP::nametag.closeDistanceColor.y,
					globals::ESP::nametag.closeDistanceColor.z,
					globals::ESP::nametag.closeDistanceColor.w
				}},
				{"farDistanceColor", toml::array{
					globals::ESP::nametag.farDistanceColor.x,
					globals::ESP::nametag.farDistanceColor.y,
					globals::ESP::nametag.farDistanceColor.z,
					globals::ESP::nametag.farDistanceColor.w
				}},
				{"lineThickness", globals::ESP::nametag.lineThickness},
				{"showActorNumber", globals::ESP::nametag.showActorNumber},
				{"showPing", globals::ESP::nametag.showPing},
				{"showMasterClient", globals::ESP::nametag.showMasterClient},
				{"showVMOD", globals::ESP::nametag.showVMOD},
				{"showIRC", globals::ESP::nametag.showIRC},
				{"showDistance", globals::ESP::nametag.showDistance},
				{"background", globals::ESP::nametag.background},
				{"backgroundColor", toml::array{
					globals::ESP::nametag.backgroundColor.x,
					globals::ESP::nametag.backgroundColor.y,
					globals::ESP::nametag.backgroundColor.z,
					globals::ESP::nametag.backgroundColor.w
				}}
			}},

			{"nametagOutline", toml::table{
				{"rainbowColor", globals::ESP::nametagOutline.rainbowColor},
				{"gradientColor", globals::ESP::nametagOutline.gradientColor},
				{"distanceColor", globals::ESP::nametagOutline.distanceColor},
				{"gradientSpeed", globals::ESP::nametagOutline.gradientSpeed},
				{"staticColor", toml::array{
					globals::ESP::nametagOutline.staticColor.x,
					globals::ESP::nametagOutline.staticColor.y,
					globals::ESP::nametagOutline.staticColor.z,
					globals::ESP::nametagOutline.staticColor.w
				}},
				{"gradientStartColor", toml::array{
					globals::ESP::nametagOutline.gradientStartColor.x,
					globals::ESP::nametagOutline.gradientStartColor.y,
					globals::ESP::nametagOutline.gradientStartColor.z,
					globals::ESP::nametagOutline.gradientStartColor.w
				}},
				{"gradientEndColor", toml::array{
					globals::ESP::nametagOutline.gradientEndColor.x,
					globals::ESP::nametagOutline.gradientEndColor.y,
					globals::ESP::nametagOutline.gradientEndColor.z,
					globals::ESP::nametagOutline.gradientEndColor.w
				}},
				{"closeDistanceColor", toml::array{
					globals::ESP::nametagOutline.closeDistanceColor.x,
					globals::ESP::nametagOutline.closeDistanceColor.y,
					globals::ESP::nametagOutline.closeDistanceColor.z,
					globals::ESP::nametagOutline.closeDistanceColor.w
				}},
				{"farDistanceColor", toml::array{
					globals::ESP::nametagOutline.farDistanceColor.x,
					globals::ESP::nametagOutline.farDistanceColor.y,
					globals::ESP::nametagOutline.farDistanceColor.z,
					globals::ESP::nametagOutline.farDistanceColor.w
				}},
				{"lineThickness", globals::ESP::nametagOutline.lineThickness},
				{"rounding", globals::ESP::nametagOutline.rounding}
			}}
		};

		std::ofstream file(filePath.string());
		if (!file.is_open()) {
			throw std::runtime_error("Could not open file: " + filePath.string());
		}

		file << settings;
		file.close();

		Log::debug("ESP config saved successfully.");
		return true;
	}
	catch (const std::exception& e) {
		Log::error("Error saving esp config: " + std::string(e.what()));
		return false;
	}
}

bool Configs::Load::ESP() {

	std::ifstream file("Mocha/esp.toml");
	if (!file.good()) {
		Log::error("Error: File does not exist or cannot be opened: Mocha/esp.toml");
		return false;
	}

	try {
		auto config = toml::parse_file("Mocha/esp.toml");

		
		globals::ESP::toggle = config["state"].value_or(false);

		// Skeleton
		{
			auto skeletonConfig = config["skeleton"];
			globals::ESP::skeleton.state = skeletonConfig["state"].value_or(false);
			globals::ESP::skeleton.renderSelf = skeletonConfig["renderSelf"].value_or(false);
			globals::ESP::skeleton.rainbowColor = skeletonConfig["rainbowColor"].value_or(false);
			globals::ESP::skeleton.gradientColor = skeletonConfig["gradientColor"].value_or(false);
			globals::ESP::skeleton.distanceColor = skeletonConfig["distanceColor"].value_or(false);
			globals::ESP::skeleton.fade = skeletonConfig["fade"].value_or(false);
			globals::ESP::skeleton.fadeDistance = skeletonConfig["fadeDistance"].value_or(0.0f);
			globals::ESP::skeleton.maxDistance = skeletonConfig["maxDistance"].value_or(0.0f);
			globals::ESP::skeleton.minDistance = skeletonConfig["minDistance"].value_or(0.0f);
			globals::ESP::skeleton.gradientSpeed = skeletonConfig["gradientSpeed"].value_or(0.0f);

			ImVec4 staticColor;
			staticColor.x = skeletonConfig["staticColor"][0].value_or(0.0f);
			staticColor.y = skeletonConfig["staticColor"][1].value_or(0.0f);
			staticColor.z = skeletonConfig["staticColor"][2].value_or(0.0f);
			staticColor.w = skeletonConfig["staticColor"][3].value_or(1.0f);
			globals::ESP::skeleton.staticColor = staticColor;


			ImVec4 gradientStartColor;
			gradientStartColor.x = skeletonConfig["gradientStartColor"][0].value_or(0.0f);
			gradientStartColor.y = skeletonConfig["gradientStartColor"][1].value_or(0.0f);
			gradientStartColor.z = skeletonConfig["gradientStartColor"][2].value_or(0.0f);
			gradientStartColor.w = skeletonConfig["gradientStartColor"][3].value_or(0.0f);

			globals::ESP::skeleton.gradientStartColor = gradientStartColor;
			ImVec4 gradientEndColor;
			gradientEndColor.x = skeletonConfig["gradientEndColor"][0].value_or(0.0f);
			gradientEndColor.y = skeletonConfig["gradientEndColor"][1].value_or(0.0f);
			gradientEndColor.z = skeletonConfig["gradientEndColor"][2].value_or(0.0f);
			gradientEndColor.w = skeletonConfig["gradientEndColor"][3].value_or(1.0f);
			globals::ESP::skeleton.gradientEndColor = gradientEndColor;

			ImVec4 closeDistanceColor;
			closeDistanceColor.x = skeletonConfig["closeDistanceColor"][0].value_or(0.0f);
			closeDistanceColor.y = skeletonConfig["closeDistanceColor"][1].value_or(0.0f);
			closeDistanceColor.z = skeletonConfig["closeDistanceColor"][2].value_or(0.0f);
			closeDistanceColor.w = skeletonConfig["closeDistanceColor"][3].value_or(1.0f);
			globals::ESP::skeleton.closeDistanceColor = closeDistanceColor;

			ImVec4 farDistanceColor;
			farDistanceColor.x = skeletonConfig["farDistanceColor"][0].value_or(0.0f);
			farDistanceColor.y = skeletonConfig["farDistanceColor"][1].value_or(0.0f);
			farDistanceColor.z = skeletonConfig["farDistanceColor"][2].value_or(0.0f);
			farDistanceColor.w = skeletonConfig["farDistanceColor"][3].value_or(1.0f);
			globals::ESP::skeleton.farDistanceColor = farDistanceColor;

			globals::ESP::skeleton.lineThickness = skeletonConfig["lineThickness"].value_or(1.0f);

		}

		// Tracer
		{
			auto tracerConfig = config["tracer"];
			globals::ESP::tracer.state = tracerConfig["state"].value_or(false);
			globals::ESP::tracer.renderSelf = tracerConfig["renderSelf"].value_or(false);
			globals::ESP::tracer.rainbowColor = tracerConfig["rainbowColor"].value_or(false);
			globals::ESP::tracer.gradientColor = tracerConfig["gradientColor"].value_or(false);
			globals::ESP::tracer.distanceColor = tracerConfig["distanceColor"].value_or(false);
			globals::ESP::tracer.fade = tracerConfig["fade"].value_or(false);
			globals::ESP::tracer.fadeDistance = tracerConfig["fadeDistance"].value_or(0.0f);
			globals::ESP::tracer.maxDistance = tracerConfig["maxDistance"].value_or(0.0f);
			globals::ESP::tracer.minDistance = tracerConfig["minDistance"].value_or(0.0f);
			globals::ESP::tracer.gradientSpeed = tracerConfig["gradientSpeed"].value_or(0.0f);

			ImVec4 staticColor;
			staticColor.x = tracerConfig["staticColor"][0].value_or(0.0f);
			staticColor.y = tracerConfig["staticColor"][1].value_or(0.0f);
			staticColor.z = tracerConfig["staticColor"][2].value_or(0.0f);
			staticColor.w = tracerConfig["staticColor"][3].value_or(1.0f);
			globals::ESP::tracer.staticColor = staticColor;

			ImVec4 gradientStartColor;
			gradientStartColor.x = tracerConfig["gradientStartColor"][0].value_or(0.0f);
			gradientStartColor.y = tracerConfig["gradientStartColor"][1].value_or(0.0f);
			gradientStartColor.z = tracerConfig["gradientStartColor"][2].value_or(0.0f);
			gradientStartColor.w = tracerConfig["gradientStartColor"][3].value_or(1.0f);
			globals::ESP::tracer.gradientStartColor = gradientStartColor;

			ImVec4 gradientEndColor;
			gradientEndColor.x = tracerConfig["gradientEndColor"][0].value_or(0.0f);
			gradientEndColor.y = tracerConfig["gradientEndColor"][1].value_or(0.0f);
			gradientEndColor.z = tracerConfig["gradientEndColor"][2].value_or(0.0f);
			gradientEndColor.w = tracerConfig["gradientEndColor"][3].value_or(1.0f);
			globals::ESP::tracer.gradientEndColor = gradientEndColor;

			ImVec4 closeDistanceColor;
			closeDistanceColor.x = tracerConfig["closeDistanceColor"][0].value_or(0.0f);
			closeDistanceColor.y = tracerConfig["closeDistanceColor"][1].value_or(0.0f);
			closeDistanceColor.z = tracerConfig["closeDistanceColor"][2].value_or(0.0f);
			closeDistanceColor.w = tracerConfig["closeDistanceColor"][3].value_or(1.0f);
			globals::ESP::tracer.closeDistanceColor = closeDistanceColor;

			ImVec4 farDistanceColor;
			farDistanceColor.x = tracerConfig["farDistanceColor"][0].value_or(0.0f);
			farDistanceColor.y = tracerConfig["farDistanceColor"][1].value_or(0.0f);
			farDistanceColor.z = tracerConfig["farDistanceColor"][2].value_or(0.0f);
			farDistanceColor.w = tracerConfig["farDistanceColor"][3].value_or(1.0f);
			globals::ESP::tracer.farDistanceColor = farDistanceColor;

			globals::ESP::tracer.lineThickness = tracerConfig["lineThickness"].value_or(1.0f);
		}

		// Box
		{
			auto boxConfig = config["box"];
			globals::ESP::box.state = boxConfig["state"].value_or(false);
			globals::ESP::box.simpleGradient = boxConfig["simpleGradient"].value_or(false);
			globals::ESP::box.renderSelf = boxConfig["renderSelf"].value_or(false);
			globals::ESP::box.rainbowColor = boxConfig["rainbowColor"].value_or(false);
			globals::ESP::box.gradientColor = boxConfig["gradientColor"].value_or(false);
			globals::ESP::box.distanceColor = boxConfig["distanceColor"].value_or(false);
			globals::ESP::box.fade = boxConfig["fade"].value_or(false);
			globals::ESP::box.fadeDistance = boxConfig["fadeDistance"].value_or(0.0f);
			globals::ESP::box.maxDistance = boxConfig["maxDistance"].value_or(0.0f);
			globals::ESP::box.minDistance = boxConfig["minDistance"].value_or(0.0f);
			globals::ESP::box.gradientSpeed = boxConfig["gradientSpeed"].value_or(0.0f);

			ImVec4 staticColor;
			staticColor.x = boxConfig["staticColor"][0].value_or(0.0f);
			staticColor.y = boxConfig["staticColor"][1].value_or(0.0f);
			staticColor.z = boxConfig["staticColor"][2].value_or(0.0f);
			staticColor.w = boxConfig["staticColor"][3].value_or(1.0f);
			globals::ESP::box.staticColor = staticColor;

			ImVec4 gradientStartColor;
			gradientStartColor.x = boxConfig["gradientStartColor"][0].value_or(0.0f);
			gradientStartColor.y = boxConfig["gradientStartColor"][1].value_or(0.0f);
			gradientStartColor.z = boxConfig["gradientStartColor"][2].value_or(0.0f);
			gradientStartColor.w = boxConfig["gradientStartColor"][3].value_or(1.0f);
			globals::ESP::box.gradientStartColor = gradientStartColor;

			ImVec4 gradientEndColor;
			gradientEndColor.x = boxConfig["gradientEndColor"][0].value_or(0.0f);
			gradientEndColor.y = boxConfig["gradientEndColor"][1].value_or(0.0f);
			gradientEndColor.z = boxConfig["gradientEndColor"][2].value_or(0.0f);
			gradientEndColor.w = boxConfig["gradientEndColor"][3].value_or(1.0f);
			globals::ESP::box.gradientEndColor = gradientEndColor;

			ImVec4 closeDistanceColor;
			closeDistanceColor.x = boxConfig["closeDistanceColor"][0].value_or(0.0f);
			closeDistanceColor.y = boxConfig["closeDistanceColor"][1].value_or(0.0f);
			closeDistanceColor.z = boxConfig["closeDistanceColor"][2].value_or(0.0f);
			closeDistanceColor.w = boxConfig["closeDistanceColor"][3].value_or(1.0f);
			globals::ESP::box.closeDistanceColor = closeDistanceColor;

			ImVec4 farDistanceColor;
			farDistanceColor.x = boxConfig["farDistanceColor"][0].value_or(0.0f);
			farDistanceColor.y = boxConfig["farDistanceColor"][1].value_or(0.0f);
			farDistanceColor.z = boxConfig["farDistanceColor"][2].value_or(0.0f);
			farDistanceColor.w = boxConfig["farDistanceColor"][3].value_or(1.0f);
			globals::ESP::box.farDistanceColor = farDistanceColor;

			globals::ESP::box.lineThickness = boxConfig["lineThickness"].value_or(1.0f);

		}

		// Box Outline
		{
			auto boxOutlineConfig = config["boxOutline"];
			globals::ESP::boxOutline.state = boxOutlineConfig["state"].value_or(false);
			globals::ESP::boxOutline.rainbowColor = boxOutlineConfig["rainbowColor"].value_or(false);
			globals::ESP::boxOutline.gradientColor = boxOutlineConfig["gradientColor"].value_or(false);
			globals::ESP::boxOutline.distanceColor = boxOutlineConfig["distanceColor"].value_or(false);
			globals::ESP::boxOutline.fade = boxOutlineConfig["fade"].value_or(false);
			globals::ESP::boxOutline.fadeDistance = boxOutlineConfig["fadeDistance"].value_or(0.0f);

			ImVec4 staticColor;
			staticColor.x = boxOutlineConfig["staticColor"][0].value_or(0.0f);
			staticColor.y = boxOutlineConfig["staticColor"][1].value_or(0.0f);
			staticColor.z = boxOutlineConfig["staticColor"][2].value_or(0.0f);
			staticColor.w = boxOutlineConfig["staticColor"][3].value_or(1.0f);
			globals::ESP::boxOutline.staticColor = staticColor;

			ImVec4 gradientStartColor;
			gradientStartColor.x = boxOutlineConfig["gradientStartColor"][0].value_or(0.0f);
			gradientStartColor.y = boxOutlineConfig["gradientStartColor"][1].value_or(0.0f);
			gradientStartColor.z = boxOutlineConfig["gradientStartColor"][2].value_or(0.0f);
			gradientStartColor.w = boxOutlineConfig["gradientStartColor"][3].value_or(1.0f);
			globals::ESP::boxOutline.gradientStartColor = gradientStartColor;

			ImVec4 gradientEndColor;
			gradientEndColor.x = boxOutlineConfig["gradientEndColor"][0].value_or(0.0f);
			gradientEndColor.y = boxOutlineConfig["gradientEndColor"][1].value_or(0.0f);
			gradientEndColor.z = boxOutlineConfig["gradientEndColor"][2].value_or(0.0f);
			gradientEndColor.w = boxOutlineConfig["gradientEndColor"][3].value_or(1.0f);
			globals::ESP::boxOutline.gradientEndColor = gradientEndColor;

			ImVec4 closeDistanceColor;
			closeDistanceColor.x = boxOutlineConfig["closeDistanceColor"][0].value_or(0.0f);
			closeDistanceColor.y = boxOutlineConfig["closeDistanceColor"][1].value_or(0.0f);
			closeDistanceColor.z = boxOutlineConfig["closeDistanceColor"][2].value_or(0.0f);
			closeDistanceColor.w = boxOutlineConfig["closeDistanceColor"][3].value_or(1.0f);
			globals::ESP::boxOutline.closeDistanceColor = closeDistanceColor;

			ImVec4 farDistanceColor;
			farDistanceColor.x = boxOutlineConfig["farDistanceColor"][0].value_or(0.0f);
			farDistanceColor.y = boxOutlineConfig["farDistanceColor"][1].value_or(0.0f);
			farDistanceColor.z = boxOutlineConfig["farDistanceColor"][2].value_or(0.0f);
			farDistanceColor.w = boxOutlineConfig["farDistanceColor"][3].value_or(1.0f);
			globals::ESP::boxOutline.farDistanceColor = farDistanceColor;

			globals::ESP::boxOutline.lineThickness = boxOutlineConfig["lineThickness"].value_or(1.0f);
			globals::ESP::boxOutline.simpleGradient = boxOutlineConfig["simpleGradient"].value_or(false);

		}

		// Nametag
		{
			auto nametagConfig = config["nametag"];
			globals::ESP::nametag.state = nametagConfig["state"].value_or(false);
			globals::ESP::nametag.renderSelf = nametagConfig["renderSelf"].value_or(false);
			globals::ESP::nametag.rainbowColor = nametagConfig["rainbowColor"].value_or(false);
			globals::ESP::nametag.gradientColor = nametagConfig["gradientColor"].value_or(false);
			globals::ESP::nametag.distanceColor = nametagConfig["distanceColor"].value_or(false);
			globals::ESP::nametag.fade = nametagConfig["fade"].value_or(false);
			globals::ESP::nametag.fadeDistance = nametagConfig["fadeDistance"].value_or(0.0f);
			globals::ESP::nametag.maxDistance = nametagConfig["maxDistance"].value_or(0.0f);
			globals::ESP::nametag.minDistance = nametagConfig["minDistance"].value_or(0.0f);
			globals::ESP::nametag.gradientSpeed = nametagConfig["gradientSpeed"].value_or(0.0f);

			ImVec4 staticColor;
			staticColor.x = nametagConfig["staticColor"][0].value_or(0.0f);
			staticColor.y = nametagConfig["staticColor"][1].value_or(0.0f);
			staticColor.z = nametagConfig["staticColor"][2].value_or(0.0f);
			staticColor.w = nametagConfig["staticColor"][3].value_or(1.0f);
			globals::ESP::nametag.staticColor = staticColor;

			ImVec4 gradientStartColor;
			gradientStartColor.x = nametagConfig["gradientStartColor"][0].value_or(0.0f);
			gradientStartColor.y = nametagConfig["gradientStartColor"][1].value_or(0.0f);
			gradientStartColor.z = nametagConfig["gradientStartColor"][2].value_or(0.0f);
			gradientStartColor.w = nametagConfig["gradientStartColor"][3].value_or(1.0f);
			globals::ESP::nametag.gradientStartColor = gradientStartColor;

			ImVec4 gradientEndColor;
			gradientEndColor.x = nametagConfig["gradientEndColor"][0].value_or(0.0f);
			gradientEndColor.y = nametagConfig["gradientEndColor"][1].value_or(0.0f);
			gradientEndColor.z = nametagConfig["gradientEndColor"][2].value_or(0.0f);
			gradientEndColor.w = nametagConfig["gradientEndColor"][3].value_or(1.0f);
			globals::ESP::nametag.gradientEndColor = gradientEndColor;

			ImVec4 closeDistanceColor;
			closeDistanceColor.x = nametagConfig["closeDistanceColor"][0].value_or(0.0f);
			closeDistanceColor.y = nametagConfig["closeDistanceColor"][1].value_or(0.0f);
			closeDistanceColor.z = nametagConfig["closeDistanceColor"][2].value_or(0.0f);
			closeDistanceColor.w = nametagConfig["closeDistanceColor"][3].value_or(1.0f);
			globals::ESP::nametag.closeDistanceColor = closeDistanceColor;

			ImVec4 farDistanceColor;
			farDistanceColor.x = nametagConfig["farDistanceColor"][0].value_or(0.0f);
			farDistanceColor.y = nametagConfig["farDistanceColor"][1].value_or(0.0f);
			farDistanceColor.z = nametagConfig["farDistanceColor"][2].value_or(0.0f);
			farDistanceColor.w = nametagConfig["farDistanceColor"][3].value_or(1.0f);
			globals::ESP::nametag.farDistanceColor = farDistanceColor;

			globals::ESP::nametag.lineThickness = nametagConfig["lineThickness"].value_or(1.0f);

			globals::ESP::nametag.showActorNumber = nametagConfig["showActorNumber"].value_or(false);
			globals::ESP::nametag.showPing = nametagConfig["showPing"].value_or(false);
			globals::ESP::nametag.showMasterClient = nametagConfig["showMasterClient"].value_or(false);
			globals::ESP::nametag.showVMOD = nametagConfig["showVMOD"].value_or(false);
			globals::ESP::nametag.showIRC = nametagConfig["showIRC"].value_or(false);
			globals::ESP::nametag.showDistance = nametagConfig["showDistance"].value_or(false);
			globals::ESP::nametag.background = nametagConfig["background"].value_or(false);

			ImVec4 backgroundColor;
			backgroundColor.x = nametagConfig["backgroundColor"][0].value_or(0.0f);
			backgroundColor.y = nametagConfig["backgroundColor"][1].value_or(0.0f);
			backgroundColor.z = nametagConfig["backgroundColor"][2].value_or(0.0f);
			backgroundColor.w = nametagConfig["backgroundColor"][3].value_or(1.0f);
			globals::ESP::nametag.backgroundColor = backgroundColor;

		}

		// Nametag Outline
		{
			auto nametagOutlineConfig = config["nametagOutline"];
			globals::ESP::nametagOutline.rainbowColor = nametagOutlineConfig["rainbowColor"].value_or(false);
			globals::ESP::nametagOutline.gradientColor = nametagOutlineConfig["gradientColor"].value_or(false);
			globals::ESP::nametagOutline.distanceColor = nametagOutlineConfig["distanceColor"].value_or(false);
			globals::ESP::nametagOutline.gradientSpeed = nametagOutlineConfig["gradientSpeed"].value_or(0.0f);

			ImVec4 staticColor;
			staticColor.x = nametagOutlineConfig["staticColor"][0].value_or(0.0f);
			staticColor.y = nametagOutlineConfig["staticColor"][1].value_or(0.0f);
			staticColor.z = nametagOutlineConfig["staticColor"][2].value_or(0.0f);
			staticColor.w = nametagOutlineConfig["staticColor"][3].value_or(1.0f);
			globals::ESP::nametagOutline.staticColor = staticColor;

			ImVec4 gradientStartColor;
			gradientStartColor.x = nametagOutlineConfig["gradientStartColor"][0].value_or(0.0f);
			gradientStartColor.y = nametagOutlineConfig["gradientStartColor"][1].value_or(0.0f);
			gradientStartColor.z = nametagOutlineConfig["gradientStartColor"][2].value_or(0.0f);
			gradientStartColor.w = nametagOutlineConfig["gradientStartColor"][3].value_or(1.0f);
			globals::ESP::nametagOutline.gradientStartColor = gradientStartColor;

			ImVec4 gradientEndColor;
			gradientEndColor.x = nametagOutlineConfig["gradientEndColor"][0].value_or(0.0f);
			gradientEndColor.y = nametagOutlineConfig["gradientEndColor"][1].value_or(0.0f);
			gradientEndColor.z = nametagOutlineConfig["gradientEndColor"][2].value_or(0.0f);
			gradientEndColor.w = nametagOutlineConfig["gradientEndColor"][3].value_or(1.0f);
			globals::ESP::nametagOutline.gradientEndColor = gradientEndColor;

			ImVec4 closeDistanceColor;
			closeDistanceColor.x = nametagOutlineConfig["closeDistanceColor"][0].value_or(0.0f);
			closeDistanceColor.y = nametagOutlineConfig["closeDistanceColor"][1].value_or(0.0f);
			closeDistanceColor.z = nametagOutlineConfig["closeDistanceColor"][2].value_or(0.0f);
			closeDistanceColor.w = nametagOutlineConfig["closeDistanceColor"][3].value_or(1.0f);
			globals::ESP::nametagOutline.closeDistanceColor = closeDistanceColor;

			ImVec4 farDistanceColor;
			farDistanceColor.x = nametagOutlineConfig["farDistanceColor"][0].value_or(0.0f);
			farDistanceColor.y = nametagOutlineConfig["farDistanceColor"][1].value_or(0.0f);
			farDistanceColor.z = nametagOutlineConfig["farDistanceColor"][2].value_or(0.0f);
			farDistanceColor.w = nametagOutlineConfig["farDistanceColor"][3].value_or(1.0f);
			globals::ESP::nametagOutline.farDistanceColor = farDistanceColor;

			globals::ESP::nametagOutline.lineThickness = nametagOutlineConfig["lineThickness"].value_or(1.0f);
			globals::ESP::nametagOutline.rounding = nametagOutlineConfig["rounding"].value_or(0.0f);

			Log::debug("ESP config loaded successfully.");
			return true;
		}
	}
	catch (const toml::parse_error& e) {
		Log::error("Error parsing TOML file: " + std::string(e.what()));
		return false;
	}

	return true;
}

bool Configs::Save::Movement() {
	try {

		std::filesystem::path directoryPath = "Mocha";
		std::filesystem::path filePath = directoryPath / "movement.toml";

		if (!std::filesystem::exists(directoryPath)) {
			std::filesystem::create_directories(directoryPath);
		}

		toml::table settings{
			{"movement", toml::table{
				{"StaticFly_safe", globals::veh::fly},
				{"StaticFly_exp", globals::Ihooks::AddFlyEnabled},
				{"DynamicFly", globals::Ihooks::get_IsFlyingEnabled},
				{"ForceStaticFly", globals::staticFlyToggle},
				{"packetfly", toml::table{
					{"toggle", globals::packetfly::toggle},
					{"horizontal", globals::packetfly::horizontal},
					{"vertical", globals::packetfly::vertical},
					{"lockVertical", globals::packetfly::lockVertical},
					{"verticalSpeed", globals::packetfly::verticalSpeed},
					{"verticalFactor", globals::packetfly::verticalFactor},
					{"horizontalSpeed", globals::packetfly::horizontalSpeed}
				}}
			}}
		};

		std::ofstream file(filePath.string());
		if (!file.is_open()) {
			throw std::runtime_error("Could not open file: " + filePath.string());
		}

		file << settings;
		file.close();

		Log::debug("Movement config saved successfully.");
		return true;
	}
	catch (const std::exception& e) {
		Log::error("Error saving movement config: " + std::string(e.what()));
		return false;
	}
}

bool Configs::Load::Movement() {

	std::ifstream file("Mocha/movement.toml");
	if (!file.good()) {
		Log::error("Error: File does not exist or cannot be opened: Mocha/movement.toml");
		return false;
	}

	try {
		auto config = toml::parse_file("Mocha/movement.toml");

		globals::veh::fly = config["movement"]["StaticFly_safe"].value_or(false);
		globals::Ihooks::AddFlyEnabled = config["movement"]["StaticFly_exp"].value_or(false);
		globals::Ihooks::get_IsFlyingEnabled = config["movement"]["DynamicFly"].value_or(false);
		globals::staticFlyToggle = config["movement"]["staticFlyToggle"].value_or(false);

		globals::packetfly::toggle = config["movement"]["packetfly"]["toggle"].value_or(false);
		globals::packetfly::horizontal = config["movement"]["packetfly"]["horizontal"].value_or(false);
		globals::packetfly::vertical = config["movement"]["packetfly"]["vertical"].value_or(false);
		globals::packetfly::lockVertical = config["movement"]["packetfly"]["lockVertical"].value_or(false);
		globals::packetfly::verticalSpeed = config["movement"]["packetfly"]["verticalSpeed"].value_or(0.0f);
		globals::packetfly::verticalFactor = config["movement"]["packetfly"]["verticalFactor"].value_or(0.0f);
		globals::packetfly::horizontalSpeed = config["movement"]["packetfly"]["horizontalSpeed"].value_or(0.0f);

		Log::debug("Movement config loaded successfully.");
		return true;
	}
	catch (const std::exception& e) {
		Log::error("Error loading movement config: " + std::string(e.what()));
		return false;
	}
}

bool Configs::Save::Theme() {
	try {

		std::filesystem::path directoryPath = "Mocha";
		std::filesystem::path filePath = directoryPath / "theme.toml";

		if (!std::filesystem::exists(directoryPath)) {
			std::filesystem::create_directories(directoryPath);
		}

		toml::table settings{
			{"theme", toml::table{
				{"theme", iTheme}
			}},
			{"particles", toml::table{
				{"toggle", globals::particles::toggle},
				{"maxParticles", globals::particles::maxParticles},
				{"circleSize", globals::particles::circleSize},
				{"connectionRadius", globals::particles::connectionRadius},
				{"mouseRepelRadius", globals::particles::mouseRepelRadius},
				{"mouseRepelStrength", globals::particles::mouseRepelStrength},
				{"particleSpeed", globals::particles::particleSpeed},
				{"rainbow", globals::particles::rainbow},
				{"particleColor", toml::array{
					globals::particles::particleColor.x,
					globals::particles::particleColor.y,
					globals::particles::particleColor.z,
					globals::particles::particleColor.w
				}},
				{"lineColor", toml::array{
					globals::particles::lineColor.x,
					globals::particles::lineColor.y,
					globals::particles::lineColor.z,
					globals::particles::lineColor.w
				}}
			}}
		};

		std::ofstream file(filePath.string());
		if (!file.is_open()) {
			throw std::runtime_error("Could not open file: " + filePath.string());
		}

		file << settings;
		file.close();

		Log::debug("Theme config saved successfully.");
		return true;
	}
	catch (const std::exception& e) {
		Log::error("Error saving theme config: " + std::string(e.what()));
		return false;
	}
}

bool Configs::Load::Theme() {

	std::ifstream file("Mocha/theme.toml");
	if (!file.good()) {
		Log::error("Error: File does not exist or cannot be opened: Mocha/theme.toml");
		return false;
	}

	try {
		auto config = toml::parse_file("Mocha/theme.toml");

		iTheme = config["theme"]["theme"].value_or(THEME_MOCHA);

		globals::particles::toggle = config["particles"]["toggle"].value_or(false);
		globals::particles::maxParticles = config["particles"]["maxParticles"].value_or(100.0f);
		globals::particles::circleSize = config["particles"]["circleSize"].value_or(5.0f);
		globals::particles::connectionRadius = config["particles"]["connectionRadius"].value_or(100.0f);
		globals::particles::mouseRepelRadius = config["particles"]["mouseRepelRadius"].value_or(100.0f);
		globals::particles::mouseRepelStrength = config["particles"]["mouseRepelStrength"].value_or(100.0f);
		globals::particles::particleSpeed = config["particles"]["particleSpeed"].value_or(100.0f);
		globals::particles::rainbow = config["particles"]["rainbow"].value_or(false);

		ImVec4 particleColor;
		particleColor.x = config["particles"]["particleColor"][0].value_or(0.0f);
		particleColor.y = config["particles"]["particleColor"][1].value_or(0.0f);
		particleColor.z = config["particles"]["particleColor"][2].value_or(0.0f);
		particleColor.w = config["particles"]["particleColor"][3].value_or(1.0f);
		globals::particles::particleColor = particleColor;

		ImVec4 lineColor;
		lineColor.x = config["particles"]["lineColor"][0].value_or(0.0f);
		lineColor.y = config["particles"]["lineColor"][1].value_or(0.0f);
		lineColor.z = config["particles"]["lineColor"][2].value_or(0.0f);
		lineColor.w = config["particles"]["lineColor"][3].value_or(1.0f);
		globals::particles::lineColor = lineColor;

		Log::debug("Theme config loaded successfully.");
		return true;
	}
	catch (const std::exception& e) {
		Log::error("Error loading theme config: " + std::string(e.what()));
		return false;
	}
}

bool Configs::Save::SkinColor() {
	try {

		std::filesystem::path directoryPath = "Mocha";
		std::filesystem::path filePath = directoryPath / "skincolor.toml";

		if (!std::filesystem::exists(directoryPath)) {
			std::filesystem::create_directories(directoryPath);
		}

		toml::table settings{
			{"skincolor", toml::table{
				{"toggle", globals::colorSkin::toggle},
				{"glow", globals::colorSkin::glow},
				{"color", toml::array{
					globals::colorSkin::color.x,
					globals::colorSkin::color.y,
					globals::colorSkin::color.z,
					globals::colorSkin::color.w
				}},
				{"rainbow", globals::colorSkin::rainbow},
				{"rainbowSpeed", globals::colorSkin::rainbowSpeed},
				{"self", globals::colorSkin::self},
				{"others", globals::colorSkin::others},
				{"black", globals::colorSkin::black},
			}}
		};

		std::ofstream file(filePath.string());
		if (!file.is_open()) {
			throw std::runtime_error("Could not open file: " + filePath.string());
		}

		file << settings;
		file.close();

		Log::debug("SkinColor config saved successfully.");
		return true;
	}
	catch (const std::exception& e) {
		Log::error("Error saving skincolor config: " + std::string(e.what()));
		return false;
	}
}

bool Configs::Load::SkinColor() {

	std::ifstream file("Mocha/skincolor.toml");
	if (!file.good()) {
		Log::error("Error: File does not exist or cannot be opened: Mocha/skincolor.toml");
		return false;
	}

	try {
		auto config = toml::parse_file("Mocha/skincolor.toml");

		globals::colorSkin::toggle = config["skincolor"]["toggle"].value_or(false);
		globals::colorSkin::glow = config["skincolor"]["glow"].value_or(0.0f);

		ImVec4 Color;
		Color.x = config["color"][0].value_or(0.0f);
		Color.y = config["color"][1].value_or(0.0f);
		Color.z = config["color"][2].value_or(0.0f);
		Color.w = config["color"][3].value_or(1.0f);
		globals::colorSkin::color = Color;

		globals::colorSkin::rainbow = config["skincolor"]["rainbow"].value_or(false);
		globals::colorSkin::rainbowSpeed = config["skincolor"]["rainbowSpeed"].value_or(1.0f);
		globals::colorSkin::self = config["skincolor"]["self"].value_or(false);
		globals::colorSkin::others = config["skincolor"]["others"].value_or(false);
		globals::colorSkin::black = config["skincolor"]["black"].value_or(false);

		Log::debug("SkinColor config loaded successfully.");
		return true;
	}
	catch (const std::exception& e) {
		Log::error("Error loading skincolor config: " + std::string(e.what()));
		return false;
	}
}

bool Configs::Save::Chams() {
	try {

		std::filesystem::path directoryPath = "Mocha";
		std::filesystem::path filePath = directoryPath / "chams.toml";

		if (!std::filesystem::exists(directoryPath)) {
			std::filesystem::create_directories(directoryPath);
		}

		toml::table settings{
			{"chams", toml::table{
				{"toggle", globals::chams::toggle},
				{"glow", globals::chams::settings.glow},
				{"scale", toml::array{
					globals::chams::settings.scale.x,
					globals::chams::settings.scale.y,
					globals::chams::settings.scale.z,
				}},
				{"color", toml::array{
					globals::chams::settings.color.x,
					globals::chams::settings.color.y,
					globals::chams::settings.color.z,
					globals::chams::settings.color.w
				}},
				{"shape", globals::chams::settings.shape}
			}}
		};

		std::ofstream file(filePath.string());
		if (!file.is_open()) {
			throw std::runtime_error("Could not open file: " + filePath.string());
		}

		file << settings;
		file.close();

		Log::debug("Chams config saved successfully.");
		return true;
	}
	catch (const std::exception& e) {
		Log::error("Error saving chams config: " + std::string(e.what()));
		return false;
	}
}

bool Configs::Load::Chams() {

	std::ifstream file("Mocha/chams.toml");
	if (!file.good()) {
		Log::error("Error: File does not exist or cannot be opened: Mocha/chams.toml");
		return false;
	}

	try {
		auto config = toml::parse_file("Mocha/chams.toml");

		globals::chams::toggle = config["chams"]["toggle"].value_or(false);
		globals::chams::settings.glow = config["chams"]["glow"].value_or(1.0f);

		ImVec4 Color;
		Color.x = config["chams"]["color"][0].value_or(0.0f);
		Color.y = config["chams"]["color"][1].value_or(0.0f);
		Color.z = config["chams"]["color"][2].value_or(0.0f);
		Color.w = config["chams"]["color"][3].value_or(1.0f);
		globals::chams::settings.color = Color;

		Vector3 Scale;
		Scale.x = config["chams"]["scale"][0].value_or(0.0f);
		Scale.y = config["chams"]["scale"][1].value_or(0.0f);
		Scale.z = config["chams"]["scale"][2].value_or(0.0f);
		globals::chams::settings.scale = Scale;

		globals::chams::settings.shape = config["chams"]["shape"].value_or(0);

		Log::debug("Chams config loaded successfully.");
		return true;
	}
	catch (const std::exception& e) {
		Log::error("Error loading chams config: " + std::string(e.what()));
		return false;
	}
}

bool Configs::Save::Fov() {
	try {

		std::filesystem::path directoryPath = "Mocha";
		std::filesystem::path filePath = directoryPath / "fov.toml";

		if (!std::filesystem::exists(directoryPath)) {
			std::filesystem::create_directories(directoryPath);
		}

		toml::table settings{
			{"fov", toml::table{
				{"toggle", globals::Ihooks::set_FieldOfView},
				{"zoomToggle", globals::fov::zoomToggle},
				{"fov", globals::fov::fov},
				{"zoomFov", globals::fov::zoomFov}
			}}
		};

		std::ofstream file(filePath.string());
		if (!file.is_open()) {
			throw std::runtime_error("Could not open file: " + filePath.string());
		}

		file << settings;
		file.close();

		Log::debug("Fov config saved successfully.");
		return true;
	}
	catch (const std::exception& e) {
		Log::error("Error saving fov config: " + std::string(e.what()));
		return false;
	}
}

bool Configs::Load::Fov() {

	std::ifstream file("Mocha/fov.toml");
	if (!file.good()) {
		Log::error("Error: File does not exist or cannot be opened: Mocha/fov.toml");
		return false;
	}

	try {
		auto config = toml::parse_file("Mocha/fov.toml");

		globals::Ihooks::set_FieldOfView = config["fov"]["toggle"].value_or(false);
		globals::fov::zoomToggle = config["fov"]["zoomToggle"].value_or(false);
		globals::fov::fov = config["fov"]["fov"].value_or(68);
		globals::fov::zoomFov = config["fov"]["zoomFov"].value_or(30);

		Log::debug("Fov config loaded successfully.");
		return true;
	}
	catch (const std::exception& e) {
		Log::error("Error loading fov config: " + std::string(e.what()));
		return false;
	}
}

bool Configs::Load::Chai() {
	try {
		auto config = toml::parse_file("Mocha/chai.toml");

		globals::Ihooks::chai = config["chai"]["toggle"].value_or(false);
		auto swapList = config["chai"]["swap"].as_array();
		if (swapList) {
			globals::chai::swaps.clear();
			for (const auto& item : *swapList) {
				auto swapRule = item.value<std::string>();
				if (swapRule) {
					auto pos = swapRule->find('$');
					if (pos != std::string::npos) {
						std::string match = swapRule->substr(0, pos);
						std::string replace = swapRule->substr(pos + 1);
						globals::chai::swaps.emplace_back(match, replace);
					}
				}
			}
		}

		Log::debug("Chai config loaded successfully.");
		return true;
	}
	catch (const std::exception& e) {
		Log::error("Error loading chai config: " + std::string(e.what()));
		return false;
	}
}

void CGui::ConfigsTab(ImGuiStyle& style) {

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, style.ItemInnerSpacing);
    ImGui::PushFont(m_Fonts.BigFont);
    {
        ImGui::TextDisabled("Configs");
    }
    ImGui::PopFont();
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4());
    ImGui::BeginChild("Configs", ImVec2(0, (ImGui::GetFontSize() * 2 + style.WindowPadding.y * 4 + style.ItemInnerSpacing.y) + (style.WindowPadding.y * 2 + ImGui::GetFontSize() * 6 + style.ItemInnerSpacing.y * 3) + (ImGui::GetFontSize() + style.WindowPadding.y * 2) * 10), ImGuiChildFlags_Border);
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
    {
#ifndef CHEAP
		const char* items[] = { "Safe Mode", "Experimental" };
		int current_item = static_cast<int>(pHookManager->hookPriority);

		ImGui::PushItemWidth(150);
		if (ImGui::Combo("Safety Priority", &current_item, items, IM_ARRAYSIZE(items))) {
			pHookManager->hookPriority = static_cast<HookManager::HookType>(current_item);

			if (pHookManager->hookPriority == HookManager::HookType::PAGEGUARD) {

				pHookManager->UpdateHooks();
			}
		}

		ImGui::PopItemWidth();
		ImGui::SetItemTooltip("Determines mocha module safety priority. \nSafe Mode: undetected, less modules, more lag, good stability. \nExperimental: maybe detected, more modules, less lag, bad stability.");

		ImAdd::ToggleButtonClassic("No MiddleClick Beacon", &globals::Ihooks::RequestDropBeacon);
		ImGui::SetItemTooltip("Turn off Middle Click Beacon.");

#ifndef PROD
		ImGui::Separator();

		if (ImGui::CollapsingHeader("RAM Crash Config:")) {

			ImGui::Indent(10);
			ImAdd::BeginHighlightGroup();

			ImGui::PushItemWidth(200);
			ImGui::InputFloat("Rate Limit (ms)", &globals::bulletCrashRateLimit);
			ImGui::SetItemTooltip("Rate Limit between RAM Crashes.");
			ImGui::InputInt("Phase One Count", &globals::crashes::bulletCrash::blunderBussCount);
			ImGui::SetItemTooltip("Amount during phase one.");
			ImGui::InputInt("Phase Two Count", &globals::crashes::bulletCrash::wandCount);
			ImGui::SetItemTooltip("Amount during phase two.");
			ImGui::PopItemWidth();

			ImAdd::EndHighlightGroup();
			ImGui::Indent(-10);
		}

		if (ImGui::CollapsingHeader("Death Config:")) {

			ImGui::Indent(10);
			ImAdd::BeginHighlightGroup();

			ImGui::PushItemWidth(200);
			ImGui::InputInt("Directions ##34534", &globals::crashes::death::numberOfDirections);
			ImGui::SetItemTooltip("Number of directions to travel from center. \n(Directions*Steps=Total Events)");
			ImGui::InputInt("Steps ##938", &globals::crashes::death::stepz);
			ImGui::SetItemTooltip("Number of steps to take inbetween directions. \n(Directions*Steps=Total Events)");
			ImGui::InputInt("Count ##938", &globals::crashes::death::countz);
			ImGui::SetItemTooltip("Number of prefabs to spawn per step.");
			ImGui::InputFloat("Min Y-Axis ##34343", &globals::crashes::death::minYz);
			ImGui::SetItemTooltip("Minimum Y-Axis to send events from.");
			ImGui::InputFloat("Max Y-Axis ##3434", &globals::crashes::death::maxYz);
			ImGui::SetItemTooltip("Maximum Y-Axis to send events from.");
			ImGui::InputFloat("Min Scale ##8978", &globals::crashes::death::minScalez);
			ImGui::SetItemTooltip("Minimum scale of events.");
			ImGui::InputFloat("Max Scale ##9812", &globals::crashes::death::maxScalez);
			ImGui::SetItemTooltip("Maximum scale of events.");
			ImGui::InputFloat("Decay Factor", &globals::crashes::death::decayFactorz);
			ImGui::SetItemTooltip("Factor which to decay events from center. \n(events are sent in a slope, not linearly!)");
			ImGui::PopItemWidth();

			ImAdd::ToggleButtonClassic("Extras ##9084985", &globals::crashes::death::extraz);
			ImGui::SetItemTooltip("Extra spawns afetr main loop.");

			ImAdd::EndHighlightGroup();
			ImGui::Indent(-10);
		}

		ImGui::Spacing();
		ImGui::Separator();

#endif
		ImGui::Separator();
#endif

		using namespace Configs;

        if (ImAdd::Button("Load Configs", ImVec2(-0.1f, 0))) {
			Load::LoadConfigs();
        }
        ImGui::SetItemTooltip("Load client configs.");
        if (ImAdd::Button("Save Configs", ImVec2(-0.1f, 0))) {
			Save::SaveConfigs();
        }
        ImGui::SetItemTooltip("Save client configs.");
    }
    ImGui::EndChild();

}