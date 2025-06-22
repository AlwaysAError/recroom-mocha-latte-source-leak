#pragma once

enum class TabType : int
{
    Movement = 0,
    Misc = 1,
    Exploits = 2,
    Assets = 3,
    PlayerList = 4,
    Image = 5,
    None = -1,
};

std::map<TabType, GameObject*> tabGameObjects;

void SetButtonActualPos(void* button);

Vector2 GetPNGDimensions(const char* filepath) {
    Vector2 dimensions = { 0, 0 };
    std::ifstream file(filepath, std::ios::binary);

    if (!file.is_open()) {
        return dimensions;
    }

    // PNG signature is 8 bytes
    unsigned char signature[8];
    file.read(reinterpret_cast<char*>(signature), 8);

    // Verify PNG signature
    const unsigned char pngSignature[8] = { 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A };
    for (int i = 0; i < 8; i++) {
        if (signature[i] != pngSignature[i]) {
            file.close();
            return dimensions;
        }
    }

    // IHDR chunk is always first, skip to width/height
    file.seekg(16);

    // Read width and height (4 bytes each, big-endian)
    unsigned char dimensionBytes[8];
    file.read(reinterpret_cast<char*>(dimensionBytes), 8);

    // Convert big-endian bytes to integers
    dimensions.x = (dimensionBytes[0] << 24) | (dimensionBytes[1] << 16) |
        (dimensionBytes[2] << 8) | dimensionBytes[3];
    dimensions.y = (dimensionBytes[4] << 24) | (dimensionBytes[5] << 16) |
        (dimensionBytes[6] << 8) | dimensionBytes[7];

    file.close();
    return dimensions;
}

class UIButton {

private:
    // Common initialization helper function to reduce code duplication
    bool InitializeCommonElements(GameObject* buttonGO, GameObject* buttonBackgroundGO, GameObject* buttonTextGO) {
        // Set layers
        buttonGO->set_layer(5);
        buttonBackgroundGO->set_layer(5);
        buttonTextGO->set_layer(5);

        // Setup transform hierarchy
        auto buttonTransform = buttonGO->get_transform();
        auto buttonBackgroundTransform = buttonBackgroundGO->get_transform();
        auto buttonTextTransform = buttonTextGO->get_transform();

        // Set button background and text as children of button
        buttonBackgroundTransform->SetParent(buttonTransform);
        buttonTextTransform->SetParent(buttonTransform);

        // Add required components
        buttonGO->AddComponent(Type::getType(WriteIl2CppString("UnityEngine.CanvasRenderer")));
        buttonBackgroundGO->AddComponent(Type::getType(WriteIl2CppString("UnityEngine.CanvasRenderer")));
        buttonTextGO->AddComponent(Type::getType(WriteIl2CppString("UnityEngine.CanvasRenderer")));

        // Setup Text
        UText* buttonText = (UText*)buttonTextGO->AddComponent(Type::getType(WriteIl2CppString("UnityEngine.UI.Text")));
        buttonText->set_Text(WriteIl2CppString(label.c_str()));
        buttonText->setFont(UFont::getDefaultFont());
        if (isTabButton)
            buttonText->setFontSize(32);
        else
            buttonText->setFontSize(25);
        buttonText->set_alignment(4);

        return true;
    }

public:
	std::string label = "";
	Vector3 position = Vector3(0, 0, 0);
	GameObject* parent = nullptr;
	GameObject* gameObject = nullptr;
    Sprite* buttonSprite = nullptr;
	ColorBlock color;
	bool initialized = false;
	bool isMenuToggleButton = false;
    bool isTabButton = false;
    bool isTabChild = false;
    bool isPlayerSelectButton = false;
    TabType tabType;
    static void* pPlayerSelectButton;

	// Add callback type definition
	using CallbackFunction = std::function<void(UIButton*)>;

	CallbackFunction onClick;

    UIButton(std::string Label, Vector3 Position, ColorBlock Color, TabType TabType, CallbackFunction OnClick) {
        label = Label;
        position = Position;
        color = Color;
        onClick = OnClick;
        parent = nullptr;
        isMenuToggleButton = false;
        isTabButton = false;
        isTabChild = true;
        tabType = TabType;
        initialized = false;
    }

    // Tab Button Constructor
    UIButton(std::string Label, Vector3 Position, ColorBlock Color, CallbackFunction OnClick, TabType TabType) {
        label = Label;
        position = Position;
        color = Color;
        onClick = OnClick;
        parent = nullptr;
        isMenuToggleButton = false;
        isTabButton = true;
        isTabChild = false;
        tabType = TabType;
        initialized = false;
    }

    // Menu Toggle Button Constructor
    UIButton(std::string Label, Vector3 Position, ColorBlock Color, CallbackFunction OnClick) {
        label = Label;
        position = Position;
        color = Color;
        onClick = OnClick;
        parent = nullptr;
        isMenuToggleButton = true;
        isTabButton = false;
        isTabChild = false;
        tabType = TabType::None;
        initialized = false;
    }

    // Player Select Button Constructor
    UIButton(std::string Label, Vector3 Position, ColorBlock Color, CallbackFunction OnClick, bool difference) {
        label = Label;
        position = Position;
        color = Color;
        onClick = OnClick;
        parent = nullptr;
        isMenuToggleButton = false;
        isTabButton = false;
        isTabChild = false;
        tabType = TabType::PlayerList;
        initialized = false;
        isPlayerSelectButton = true;
    }

	bool get_State() {

		if (!initialized || (localPlayer.loadingStage < LoadingStage::LOADED))
			return false;

		if (gameObject == nullptr) return false;

		Toggle* toggleComponent = (Toggle*)gameObject->GetComponent("UnityEngine.UI.Toggle");

		if (toggleComponent == nullptr) return false;

		return toggleComponent->get_isOn();

	}

	void set_State(bool value) {

		if (!initialized || (localPlayer.loadingStage < LoadingStage::LOADED))
			return;

		if (gameObject == nullptr) return;

		Toggle* toggleComponent = (Toggle*)gameObject->GetComponent("UnityEngine.UI.Toggle");

		if (toggleComponent == nullptr) return;

		return toggleComponent->set_isOn(value);

	}

	void CallClick() {
		if (onClick != nullptr) {
			onClick(this);
		}
	}

    // Standard Button Initialize
    bool InitializeButton() {

        parent = tabGameObjects[tabType];
        if (parent == nullptr) return false;

        GameObject* buttonGO = GameObject::ctor(WriteIl2CppString(std::string("Mocha-button+'" + label + "'").c_str()));
        GameObject* buttonBackgroundGO = GameObject::ctor(WriteIl2CppString(std::string("Mocha-bg+'" + label + "'").c_str()));
        GameObject* buttonTextGO = GameObject::ctor(WriteIl2CppString(std::string("Mocha-text+'" + label + "'").c_str()));

        gameObject = buttonGO;

        if (!InitializeCommonElements(buttonGO, buttonBackgroundGO, buttonTextGO)) return false;

        auto buttonTransform = buttonGO->get_transform();
        auto parentTransform = parent->get_transform();

        // Set parent and transforms
        buttonTransform->SetParent(parentTransform);
        buttonTransform->set_localPosition(position);
        buttonTransform->set_localScale({ 1.0f, 1.0f, 1.0f });
        buttonTransform->set_localRotation(parentTransform->get_localRotation());

        // Setup background transform
        buttonBackgroundGO->get_transform()->set_localScale({ 3.0f, 1.0f, 1.0f });
        buttonBackgroundGO->get_transform()->set_localPosition({ 0.0f, 0.0f, 0.0f });
        buttonBackgroundGO->get_transform()->set_localRotation({ 0.0f, 0.0f, 0.0f, 1.0f });

        // Setup text position
        buttonTextGO->get_transform()->set_localPosition({ 0, 0, 0 });

        // Setup Image and Toggle
        Image* image = (Image*)buttonBackgroundGO->AddComponent(Type::getType(WriteIl2CppString("UnityEngine.UI.Image")));
        Toggle* toggleComponent = (Toggle*)buttonGO->AddComponent(Type::getType(WriteIl2CppString("UnityEngine.UI.Toggle")));
        toggleComponent->set_transition(Transition::ColorTint);
        toggleComponent->set_colors(color);
        toggleComponent->set_targetGraphic((Graphic*)image);

        if (buttonSprite != nullptr)
            image->set_sprite(buttonSprite);
        else return false;

        if (position.x != 0 || position.y != 0 || position.z != 0) {
            newThread(&SetButtonActualPos, this);
        }

        RectTransform* textTransform = (RectTransform*)buttonTextGO->get_transform();
        if (textTransform)
        {
            textTransform->set_sizeDelta({ 200,50 });
        }

        initialized = true;
        return true;
    }

    // Tab Button Initialize
    bool InitializeTabButton() {

        if (parent == nullptr) return false;

        GameObject* tabGO = GameObject::ctor(WriteIl2CppString(std::string("Mocha-Tab+'" + label + "'").c_str()));
        GameObject* tabButtonsGO = GameObject::ctor(WriteIl2CppString(std::string("Mocha-TabButtons+'" + label + "'").c_str()));
        GameObject* buttonGO = GameObject::ctor(WriteIl2CppString(std::string("Mocha-Button+'" + label + "'").c_str()));
        GameObject* buttonBackgroundGO = GameObject::ctor(WriteIl2CppString(std::string("Mocha-bg+'" + label + "'").c_str()));
        GameObject* buttonTextGO = GameObject::ctor(WriteIl2CppString(std::string("Mocha-text+'" + label + "'").c_str()));

        gameObject = buttonGO;
        tabGameObjects[tabType] = tabButtonsGO;

        if (!InitializeCommonElements(buttonGO, buttonBackgroundGO, buttonTextGO)) return false;

        auto buttonTransform = buttonGO->get_transform();
        auto parentTransform = parent->get_transform();

        // Setup tab specific elements
        GameObject* tabButtonGO = GameObject::ctor(WriteIl2CppString(std::string("Mocha-TabButton'" + label + "'").c_str()));
        tabButtonGO->get_transform()->SetParent(buttonGO->get_transform());

        auto tabTransform = tabGO->get_transform();

        tabTransform->SetParent(parentTransform);
        tabTransform->set_localPosition({ 0.0f, 0.0f, 0.0f });
        tabTransform->set_localScale({ 1.0f, 1.0f, 1.0f });
        tabTransform->set_localRotation({0.0f, 0.0f, 0.0f, 0.0f});

        auto tabButtonsTransform = tabButtonsGO->get_transform();

        tabButtonsTransform->SetParent(tabTransform);
        tabButtonsTransform->set_localPosition({ 0.0f, 0.0f, 0.0f });
        tabButtonsTransform->set_localScale({ 1.0f, 1.0f, 1.0f });
        tabButtonsTransform->set_localRotation({ 0.0f, 0.0f, 0.0f, 0.0f });

        buttonTransform->SetParent(tabTransform);
        buttonTransform->set_localPosition(position);
        buttonTransform->set_localScale({ 0.7f, 0.7f, 0.7f });
        buttonTransform->set_localRotation(parentTransform->get_localRotation());

        // Setup background transform
        buttonBackgroundGO->get_transform()->set_localScale({ 3.0f, 1.0f, 1.0f });
        buttonBackgroundGO->get_transform()->set_localPosition({ 0.0f, 0.0f, 0.0f });
        buttonBackgroundGO->get_transform()->set_localRotation({ 0.0f, 0.0f, 0.0f, 1.0f });

        // Setup text position
        buttonTextGO->get_transform()->set_localPosition({ 0, 0, 0 });

        // Setup Image and Toggle
        Image* image = (Image*)buttonBackgroundGO->AddComponent(Type::getType(WriteIl2CppString("UnityEngine.UI.Image")));
        Toggle* toggleComponent = (Toggle*)buttonGO->AddComponent(Type::getType(WriteIl2CppString("UnityEngine.UI.Toggle")));
        toggleComponent->set_transition(Transition::ColorTint);
        toggleComponent->set_colors(color);
        toggleComponent->set_targetGraphic((Graphic*)image);

        if (buttonSprite != nullptr)
            image->set_sprite(buttonSprite);
        else return false;

        if (position.x != 0 || position.y != 0 || position.z != 0) {
            newThread(&SetButtonActualPos, this);
        }

        RectTransform* textTransform = (RectTransform*)buttonTextGO->get_transform();
        if (textTransform)
        {
            textTransform->set_sizeDelta({ 200,50 });
        }

        initialized = true;
        return true;
    }

    // Menu Button Initialize
    bool InitializeMenuButton() {

        if (parent == nullptr) return false;

        GameObject* buttonGO = GameObject::ctor(WriteIl2CppString(std::string("Mocha-button+'" + label + "'").c_str()));
        GameObject* buttonBackgroundGO = GameObject::ctor(WriteIl2CppString(std::string("Mocha-bg+'" + label + "'").c_str()));
        GameObject* buttonTextGO = GameObject::ctor(WriteIl2CppString(std::string("Mocha-text+'" + label + "'").c_str()));

        gameObject = buttonGO;

        // Create menu-specific background
        GameObject* buttonMenuBackgroundMenu = GameObject::ctor(WriteIl2CppString(std::string("Mocha-bgmenu+'" + label + "'").c_str()));
        buttonMenuBackgroundMenu->get_transform()->SetParent(buttonGO->get_transform());
        buttonMenuBackgroundMenu->get_transform()->set_localRotation({ 0.0f, 0.0f, 0.0f, 1.0f });
        buttonMenuBackgroundMenu->get_transform()->set_localScale({ 1.5f, 1.0f, 1.0f });
        buttonMenuBackgroundMenu->get_transform()->set_localPosition({ 0.0f, -17.0f, 0.0f });

        Image* menuImage = (Image*)buttonMenuBackgroundMenu->AddComponent(Type::getType(WriteIl2CppString("UnityEngine.UI.Image")));
        buttonMenuBackgroundMenu->AddComponent(Type::getType(WriteIl2CppString("RRUI.RoundedCorners")));

        if (!InitializeCommonElements(buttonGO, buttonBackgroundGO, buttonTextGO)) return false;

        auto buttonTransform = buttonGO->get_transform();
        auto parentTransform = parent->get_transform();

        // Set parent and transforms
        buttonTransform->SetParent(parentTransform);
        buttonTransform->set_localPosition(position);
        buttonTransform->set_localScale({ 1.0f, 1.0f, 1.0f });
        buttonTransform->set_localRotation(parentTransform->get_localRotation());

        // Setup background transform
        buttonBackgroundGO->get_transform()->set_localScale({ 0.7f, 0.7f, 0.7f });
        buttonBackgroundGO->get_transform()->set_localPosition({ 0.0f, 0.0f, 0.0f });
        buttonBackgroundGO->get_transform()->set_localRotation({ 0.0f, 0.0f, 0.0f, 1.0f });

        // Setup text position
        buttonTextGO->get_transform()->set_localPosition({ 0.0f, -55.0f, 0.0f });

        // Setup Image and Toggle with menu-specific settings
        Image* image = (Image*)buttonBackgroundGO->AddComponent(Type::getType(WriteIl2CppString("UnityEngine.UI.Image")));
        Toggle* toggleComponent = (Toggle*)buttonGO->AddComponent(Type::getType(WriteIl2CppString("UnityEngine.UI.Toggle")));
        toggleComponent->set_transition(Transition::ColorTint);
        toggleComponent->set_colors(color);
        toggleComponent->set_targetGraphic((Graphic*)menuImage);

        // Setup menu-specific material
        Shader* defaultShader = Shader::shaderFind(WriteIl2CppString("UI/Default"));
        Material* defaultMaterial = Material::getDefaultMaterial();
        defaultMaterial->setShader(defaultShader);
        defaultMaterial->setColor({ 1, 1, 1, 1 });
        image->set_material(defaultMaterial);

        if (buttonSprite != nullptr)
            image->set_sprite(buttonSprite);
        else
            return false;

        if (position.x != 0 || position.y != 0 || position.z != 0) {
            newThread(&SetButtonActualPos, this);
        }

        initialized = true;
        return true;
    }

    // Player Select Button Initialize
    bool InitializePlayerSelectButton() {

        if (parent == nullptr) return false;

        GameObject* buttonGO = GameObject::ctor(WriteIl2CppString(std::string("Mocha-button+'" + label + "'").c_str()));
        GameObject* buttonBackgroundGO = GameObject::ctor(WriteIl2CppString(std::string("Mocha-bg+'" + label + "'").c_str()));
        GameObject* buttonTextGO = GameObject::ctor(WriteIl2CppString(std::string("Mocha-text+'" + label + "'").c_str()));

        gameObject = buttonGO;

        // Create menu-specific background
        GameObject* buttonMenuBackgroundMenu = GameObject::ctor(WriteIl2CppString(std::string("Mocha-bgmenu+'" + label + "'").c_str()));
        buttonMenuBackgroundMenu->get_transform()->SetParent(buttonGO->get_transform());
        buttonMenuBackgroundMenu->get_transform()->set_localRotation({ 0.0f, 0.0f, 0.0f, 1.0f });
        buttonMenuBackgroundMenu->get_transform()->set_localScale({ 1.5f, 1.0f, 1.0f });
        buttonMenuBackgroundMenu->get_transform()->set_localPosition({ 0.0f, -17.0f, 0.0f });

        Image* menuImage = (Image*)buttonMenuBackgroundMenu->AddComponent(Type::getType(WriteIl2CppString("UnityEngine.UI.Image")));
        buttonMenuBackgroundMenu->AddComponent(Type::getType(WriteIl2CppString("RRUI.RoundedCorners")));

        if (!InitializeCommonElements(buttonGO, buttonBackgroundGO, buttonTextGO)) return false;

        auto buttonTransform = buttonGO->get_transform();
        auto parentTransform = parent->get_transform();

        // Set parent and transforms
        buttonTransform->SetParent(parentTransform);
        buttonTransform->set_localPosition(position);
        buttonTransform->set_localScale({ 1.0f, 1.0f, 1.0f });
        buttonTransform->set_localRotation(parentTransform->get_localRotation());

        // Setup background transform
        buttonBackgroundGO->get_transform()->set_localScale({ 0.7f, 0.7f, 0.7f });
        buttonBackgroundGO->get_transform()->set_localPosition({ 0.0f, 0.0f, 0.0f });
        buttonBackgroundGO->get_transform()->set_localRotation({ 0.0f, 0.0f, 0.0f, 1.0f });

        // Setup text position
        buttonTextGO->get_transform()->set_localPosition({ 0.0f, -55.0f, 0.0f });

        // Setup Image and Toggle with menu-specific settings
        Image* image = (Image*)buttonBackgroundGO->AddComponent(Type::getType(WriteIl2CppString("UnityEngine.UI.Image")));
        Toggle* toggleComponent = (Toggle*)buttonGO->AddComponent(Type::getType(WriteIl2CppString("UnityEngine.UI.Toggle")));
        toggleComponent->set_transition(Transition::ColorTint);
        toggleComponent->set_colors(color);
        toggleComponent->set_targetGraphic((Graphic*)menuImage);

        // Setup menu-specific material
        Shader* defaultShader = Shader::shaderFind(WriteIl2CppString("UI/Default"));
        Material* defaultMaterial = Material::getDefaultMaterial();
        defaultMaterial->setShader(defaultShader);
        defaultMaterial->setColor({ 1, 1, 1, 1 });
        image->set_material(defaultMaterial);

        if (buttonSprite != nullptr)
            image->set_sprite(buttonSprite);
        else return false;

        if (position.x != 0 || position.y != 0 || position.z != 0) {
            newThread(&SetButtonActualPos, this);
        }

        pPlayerSelectButton = this;

        initialized = true;
        return true;
    }

    bool Initialize() {

        if (initialized) return false;
        if (isMenuToggleButton) return InitializeMenuButton();
        if (isTabButton) return InitializeTabButton();
        if (isPlayerSelectButton) return InitializePlayerSelectButton();
        return InitializeButton();

    }
};

void* UIButton::pPlayerSelectButton = nullptr;