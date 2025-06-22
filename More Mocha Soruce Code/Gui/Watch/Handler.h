#pragma once

#include <variant>
#include <cryptopp/md5.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>

class WatchMenuHandler {

public:

	using UIElementVariant = std::variant<UIButton, UIToggleButton, UIText>;

	std::vector<UIElementVariant> UIElements;

	std::chrono::steady_clock::time_point lastExecution500 = std::chrono::steady_clock::now();
	const std::chrono::milliseconds timeThreshold = std::chrono::milliseconds(60);

	bool wasLoadingLastFrame = false;
	bool wasIntialized = false;
	bool isOnMenu = false;

	uint32_t selectedPlayerId = 0;

	GameObject* router = nullptr;
	GameObject* mochaMenuGO = nullptr;

	Sprite* buttonSprite = nullptr;
	Sprite* menuButtonSprite = nullptr;
	Sprite* playerSelectButtonSprite = nullptr;
	Sprite* toggleOnSprite = nullptr;
	Sprite* toggleOffSprite = nullptr;
	Sprite* backgroundSprite = nullptr;

	bool SetupSprites();

	void Initialize();
	void HandleMenuToggle();
	void HandlePlayerSelectButton();

	void Update();

};

WatchMenuHandler* pWatchMenuHandler = nullptr;

void WatchMenuHandler::Update() {

	//Log::debug("d");
	
	if (!localPlayerExists) /// skip if there's no localplayer
		return;

	auto currentTime = std::chrono::steady_clock::now();
	auto elapsedTime500 = currentTime - lastExecution500;

	/// watch is so fat it wants get_IsInitialLoadFinished rec room devs are fucking shit
	if ((localPlayer.loadingStage >= LoadingStage::LOADED) && RecRoomPlayer::GetFromActorNumber(localPlayer.photonActorID)->get_IsInitialLoadFinished()) {

		if (wasLoadingLastFrame)
			wasIntialized = false;

		wasLoadingLastFrame = false;

	}
	else {

		if (!wasLoadingLastFrame) {
			for (auto& uiElement : UIElements) {

				if (std::holds_alternative<UIButton>(uiElement)) {
					UIButton& element = std::get<UIButton>(uiElement);

					element.initialized = false;
					element.gameObject = nullptr;

					continue;
				}

				if (std::holds_alternative<UIToggleButton>(uiElement)) {
					UIToggleButton& element = std::get<UIToggleButton>(uiElement);

					element.initialized = false;
					element.gameObject = nullptr;

					continue;
				}

				if (std::holds_alternative<UIText>(uiElement)) {
					UIText& element = std::get<UIText>(uiElement);

					element.initialized = false;
					element.gameObject = nullptr;

					continue;
				}
			}
			wasLoadingLastFrame = true;
		}
	}

	/// initialize the menu here
	if (!wasIntialized && !wasLoadingLastFrame) {
		Initialize();
	}

	/// this will not execute if we're loading
	/// this is the "update" loop, handling callbacks
	if (wasIntialized && !wasLoadingLastFrame && (elapsedTime500 > timeThreshold)) { // only every 500ms

		auto isElementOutsideMenu = [&](UIElementVariant uiElement) {
			if (std::holds_alternative<UIButton>(uiElement)) {
				UIButton& element = std::get<UIButton>(uiElement);
				if (element.isMenuToggleButton || element.isPlayerSelectButton) return true;
			}
			else return false;
			};

		for (auto& uiElement : UIElements) {

			if (isOnMenu || (isElementOutsideMenu(uiElement))) { // dont handle when menu isn't open

				if (std::holds_alternative<UIButton>(uiElement)) {
					UIButton& element = std::get<UIButton>(uiElement);

					if (!element.parent->get_active()) continue;
					
					if (element.get_State())
					{
						element.set_State(false);
						element.CallClick();
					}

					continue;
				}

				if (std::holds_alternative<UIToggleButton>(uiElement)) {
					UIToggleButton& element = std::get<UIToggleButton>(uiElement);

					if (!element.parent->get_active()) continue;

					bool toggleState = element.get_State();
					bool value = *element.value;

					if ((toggleState == element.lastFrameState) && (toggleState != value))
					{
						element.set_State(value);

						element.lastFrameState = value;
						element.cachedImage->set_sprite(value ? element.spriteOn : element.spriteOff);
					}


					if (toggleState != element.lastFrameState)
					{

						*element.value = toggleState;
						element.cachedImage->set_sprite(value ? element.spriteOff : element.spriteOn); // reverse here cuz value is local var

						element.CallClick();

						element.lastFrameState = toggleState;
					}


					continue;
				}

			}

		}

		HandleMenuToggle();
		HandlePlayerSelectButton();

		lastExecution500 = std::chrono::steady_clock::now();
	}

}

bool WatchMenuHandler::SetupSprites() {

	auto CalculateMD5 = [&](const std::string& filepath) -> std::string {
		if (!UFile::Exists(WriteIl2CppString(filepath.c_str()))) {
			return "";
		}

		std::ifstream file(filepath, std::ios::binary | std::ios::ate);
		if (!file) {
			return "";
		}

		std::streamsize size = file.tellg();
		file.seekg(0, std::ios::beg);

		std::vector<char> bytes(size);
		if (!file.read(bytes.data(), size)) {
			return "";
		}

		CryptoPP::MD5 hash;
		std::string digest;

		CryptoPP::StringSource(
			reinterpret_cast<const BYTE*>(bytes.data()),
			bytes.size(),
			true,
			new CryptoPP::HashFilter(hash,
				new CryptoPP::HexEncoder(
					new CryptoPP::StringSink(digest),
					false  // lowercase output
				)
			)
		);

		return digest;
		};

	auto LoadImageFile = [&](std::string filepath, const std::string& expectedHash = "") -> Sprite* {
		if (!UFile::Exists(WriteIl2CppString(filepath.c_str()))) {
			Log::error("Image file not found: " + filepath);
			return nullptr;
		}

#ifdef PROD
		// Hash verification
		if (!expectedHash.empty()) {
			std::string actualHash = CalculateMD5(filepath);
			if (actualHash.empty()) {
				Log::error("Failed to calculate MD5 hash for: " + filepath);
				return nullptr;
			}

			if (actualHash != expectedHash) {
				Log::error("Hash mismatch for: " + filepath);
				Log::error("Expected: " + expectedHash);
				Log::error("Actual: " + actualHash);
				exit(0);
				return nullptr;
			}
		}
#endif

		Vector2 imageSize = GetPNGDimensions(filepath.c_str());
		Texture2D* texture = Texture2D::ctor(imageSize.x, imageSize.y);
		if (texture == nullptr) return nullptr;

		texture->loadImage(UFile::ReadAllBytes(WriteIl2CppString(filepath.c_str())));
		Sprite* spriteImage = Sprite::Create(texture,
			Rect(0, 0, texture->get_width(), texture->get_height()),
			{ 0.5f, 0.5f });
		return spriteImage;
		};

	buttonSprite = LoadImageFile("Mocha/Watch/button.png", "e8ded2bc2783e0362c447dba695a028c");
	if (buttonSprite == nullptr) return false;
	menuButtonSprite = LoadImageFile("Mocha/Watch/menu_button.png", "a063226943952e781c2b5789448f94b8");
	if (menuButtonSprite == nullptr) return false;
	toggleOnSprite = LoadImageFile("Mocha/Watch/toggle_on.png", "6e415bbcbfd76f580298ca904277ad51");
	if (toggleOnSprite == nullptr) return false;
	toggleOffSprite = LoadImageFile("Mocha/Watch/toggle_off.png", "b445c3b3e69e2e9541fdbf1fa127291a");
	if (toggleOffSprite == nullptr) return false;
	backgroundSprite = LoadImageFile("Mocha/Watch/background.png", "6f2ace91a7f40342dc242116396427be");
	if (backgroundSprite == nullptr) return false;
	playerSelectButtonSprite = LoadImageFile("Mocha/Watch/player.png", "d71609632e94431dd7ffc43402688fac");
	if (playerSelectButtonSprite == nullptr) return false;
	
	for (auto& uiElement : UIElements) {

		if (std::holds_alternative<UIButton>(uiElement)) {
			UIButton& element = std::get<UIButton>(uiElement);

			if (element.isMenuToggleButton)
				element.buttonSprite = menuButtonSprite;
			else if (element.isPlayerSelectButton)
				element.buttonSprite = playerSelectButtonSprite;
			else
				element.buttonSprite = buttonSprite;

			continue;
		}

		if (std::holds_alternative<UIToggleButton>(uiElement)) {
			UIToggleButton& element = std::get<UIToggleButton>(uiElement);

			element.spriteOff = toggleOffSprite;
			element.spriteOn = toggleOnSprite;

			continue;
		}
	}

	return true;

}

void WatchMenuHandler::Initialize() {

	/// yes. really. container -> surface -> mask -> conent -> router
	auto routerGO = GameObject::Find(WriteIl2CppString("[WatchMenuRRUIRoot]"))->get_transform()->GetChild(0)->GetChild(0)->GetChild(1)->GetChild(0)->GetChild(0)->get_gameObject();

	router = routerGO;

	if (routerGO == nullptr) return; // skip this execution, we will initialize when we find the router

	RecRoomPlayer* localPlayerplayer = RecRoomPlayer::GetFromActorNumber(localPlayer.photonActorID);

	if (localPlayerplayer == nullptr) return;

	GameObject* NavigationBar = (localPlayerplayer->get_HardwareType() == Desktop_VRMissing) ? // lazy. yes.
		GameObject::Find(WriteIl2CppString("(NavigationBar)PCConsoleVersion Spawner")) :
		GameObject::Find(WriteIl2CppString("(NavigationBar) VR Version Spawner"));

	GameObject* NavigationHome = GameObject::Find(WriteIl2CppString("Page: (Navigation_Home)(Clone)"));

	if ((NavigationBar == nullptr) || (NavigationHome == nullptr)) return;

	if (!SetupSprites()) return;

	mochaMenuGO = GameObject::ctor(WriteIl2CppString("MochaMenu"));

	mochaMenuGO->get_transform()->SetParent(NavigationBar->get_transform());
	mochaMenuGO->get_transform()->set_localPosition({ 0, 0, 0 });
	mochaMenuGO->get_transform()->set_localRotation({ 0, 0, 0, 1 });
	mochaMenuGO->get_transform()->set_localScale({ 1, 1, 1 });

	// setup sprites will create the sprite used so nullptr cehcks are not needed
	Image* backgroundImage = (Image*)router->GetComponent("UnityEngine.UI.Image");
	backgroundImage->set_sprite(backgroundSprite);

	Log::debug("nigger setup");

	for (auto& uiElement : UIElements) {

		if (std::holds_alternative<UIButton>(uiElement)) {
			UIButton& element = std::get<UIButton>(uiElement);

			if (element.isMenuToggleButton)
				element.parent = NavigationHome;
			else if (element.isTabButton)
				element.parent = mochaMenuGO;
			else if (element.isPlayerSelectButton)
				element.parent = NavigationBar;

			element.Initialize();

			continue;
		}

		if (std::holds_alternative<UIToggleButton>(uiElement)) {
			UIToggleButton& element = std::get<UIToggleButton>(uiElement);

			element.Initialize();

			continue;
		}

		if (std::holds_alternative<UIText>(uiElement)) {
			UIText& element = std::get<UIText>(uiElement);

			element.Initialize();

			continue;
		}
	}

	wasIntialized = true;
}

void WatchMenuHandler::HandleMenuToggle() { /// turns off our UI when UI menu switch is detected

	if (wasIntialized && (router != nullptr)) {

		/// line below is the reason we need to use get_IsInitialLoadFinished, fat piece of shit code man
		for (int i = 0; i < router->get_transform()->get_ChildCount(); i++) {

			GameObject* childGO = router->get_transform()->GetChild(i)->get_gameObject();

			if (childGO != nullptr)
			{
				if ((std::string(ReadIl2CppString(childGO->GetName())).find("Page:") != std::string::npos) && childGO->get_active()) {

					if (mochaMenuGO != nullptr) {
						mochaMenuGO->set_active(false);
						isOnMenu = false;
					}

					break;
				}
			}
		}
	}
}

void WatchMenuHandler::HandlePlayerSelectButton() {
	
	if (wasIntialized && (router != nullptr)) {
		
		bool foundProfilePage = false;

		/// line below is the reason we need to use get_IsInitialLoadFinished, fat piece of shit code man
		for (int i = 0; i < router->get_transform()->get_ChildCount(); i++) {

			GameObject* childGO = router->get_transform()->GetChild(i)->get_gameObject();

			if (childGO != nullptr) {
				if ((std::string(ReadIl2CppString(childGO->GetName())).find("Page: (PlayerProfile)") != std::string::npos) && childGO->get_active()) {
					foundProfilePage = true;
					break;
				}
			}
		}

		UIButton* pButton = (UIButton*)UIButton::pPlayerSelectButton;

		if (foundProfilePage) {
			if (!pButton->gameObject->get_active())
				pButton->gameObject->set_active(true);
		}
		else {
			if (pButton->gameObject->get_active())
				pButton->gameObject->set_active(false);
		}
	}
}

void SetButtonActualPos(void* pElement)
{
	Sleep(1000);

	ThreadFix();

	WatchMenuHandler::UIElementVariant Element = *(WatchMenuHandler::UIElementVariant*)pElement;

	if (std::holds_alternative<UIButton>(Element)) {
		UIButton& element = std::get<UIButton>(Element);

		// fix button position
		element.gameObject->get_transform()->set_localPosition(element.position);

		if (element.isMenuToggleButton || element.isPlayerSelectButton)
			element.gameObject->get_transform()->GetChild(2/*Mocha-Text transform*/)->set_localPosition({ 0.0f, -55.0f, 0.0f });
	}

	if (std::holds_alternative<UIToggleButton>(Element)) {
		UIToggleButton& element = std::get<UIToggleButton>(Element);

		element.gameObject->get_transform()->set_localPosition(element.position);
	}

	if (std::holds_alternative<UIText>(Element)) {
		UIText& element = std::get<UIText>(Element);

		element.gameObject->get_transform()->set_localPosition(element.position);
	}
}