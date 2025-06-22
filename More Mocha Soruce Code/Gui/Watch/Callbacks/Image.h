#pragma once

namespace ButtonCallbacks
{
	void HideUI(UIButton* instance) {
		pWatchMenuHandler->mochaMenuGO->set_active(false);
	}

	void RefreshImages(UIButton* instance) {

		globals::images::images.clear();

		auto LoadImageFile = [&](std::string filepath) -> Sprite* {

			if (!UFile::Exists(WriteIl2CppString(filepath.c_str()))) {
				Log::error("Image file not found: " + filepath);
				return nullptr;
			}

			Vector2 imageSize = GetPNGDimensions(filepath.c_str());
			Texture2D* texture = Texture2D::ctor(imageSize.x, imageSize.y);
			if (texture == nullptr) return nullptr;

			texture->loadImage(UFile::ReadAllBytes(WriteIl2CppString(filepath.c_str())));
			Sprite* spriteImage = Sprite::Create(texture,
				Rect(0, 0, texture->get_width(), texture->get_height()),
				{ 0.5f, 0.5f });
			return spriteImage;
			};

		const std::string folderPath = "Mocha/Watch/Images";

		for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
			//if (entry.path().extension() == ".png") {
				std::string filepath = entry.path().string();

				std::replace(filepath.begin(), filepath.end(), '\\', '/'); // unity doesn't like windows style filepaths (\)

				Sprite* sprite = LoadImageFile(filepath);
				if (sprite != nullptr) {
					globals::images::images.push_back(sprite);
				}
			//}
		}

		if (globals::images::currentIndex >= globals::images::images.size() || globals::images::currentIndex < 0)
			globals::images::currentIndex = 0;

		if (!globals::images::images.empty()) {

			Image* backgroundImage = (Image*)pWatchMenuHandler->router->GetComponent("UnityEngine.UI.Image");
			if (backgroundImage != nullptr)
				backgroundImage->set_sprite((Sprite*)globals::images::images.at(0));
		}
	}

	void NextImage(UIButton* instance) {

		if (globals::images::images.empty()) return;

		globals::images::currentIndex += 1;
		if (globals::images::currentIndex >= globals::images::images.size())
			globals::images::currentIndex = 0;  // wrap around

		Image* backgroundImage = (Image*)pWatchMenuHandler->router->GetComponent("UnityEngine.UI.Image");
		if (backgroundImage != nullptr)
			backgroundImage->set_sprite((Sprite*)globals::images::images[globals::images::currentIndex]);

	}

	void PreviousImage(UIButton* instance) {

		if (globals::images::images.empty()) return;

		if ((globals::images::currentIndex > 0) && (globals::images::currentIndex < globals::images::images.size())) {
			globals::images::currentIndex -= 1;
		}
		else if (globals::images::currentIndex == 0) {
			globals::images::currentIndex = globals::images::images.size() - 1;
		}

		Image* backgroundImage = (Image*)pWatchMenuHandler->router->GetComponent("UnityEngine.UI.Image");
		if (backgroundImage != nullptr)
			backgroundImage->set_sprite((Sprite*)globals::images::images[globals::images::currentIndex]);
	}

	void RestoreBackground(UIButton* instance) {
		Image* backgroundImage = (Image*)pWatchMenuHandler->router->GetComponent("UnityEngine.UI.Image");
		if (backgroundImage != nullptr)
			backgroundImage->set_sprite(pWatchMenuHandler->backgroundSprite);
	}
}