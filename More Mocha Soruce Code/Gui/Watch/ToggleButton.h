#pragma once

class UIToggleButton
{
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
        buttonText->setFontSize(25);
        buttonText->set_alignment(4);

        return true;
    }

public:
    std::string label = "";
    Vector3 position = Vector3(0, 0, 0);
    GameObject* parent = nullptr;
    GameObject* gameObject = nullptr;
    ColorBlock color;
    Sprite* spriteOn = nullptr;
    Sprite* spriteOff = nullptr;
    bool initialized = false;
    bool isTabChild = false;
    TabType tabType;
    bool* value = nullptr;
    bool lastFrameState = false;
    Image* cachedImage = nullptr;

    using CallbackFunction = std::function<void(UIToggleButton*)>;

    CallbackFunction onClick;

    UIToggleButton(std::string Label, Vector3 Position, ColorBlock Color, TabType TabType, bool* Value, CallbackFunction OnClick) {
        label = Label;
        position = Position;
        color = Color;
        parent = nullptr;
        isTabChild = true;
        tabType = TabType;
        value = Value;
        onClick = OnClick;
        initialized = false;
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

    // Standard Button Initialize
    bool InitializeToggleButton() {

        parent = tabGameObjects[tabType];
        if (parent == nullptr) return false;

        GameObject* buttonGO = GameObject::ctor(WriteIl2CppString(std::string("Mocha-Toggle+'" + label + "'").c_str()));
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
        cachedImage = (Image*)buttonBackgroundGO->AddComponent(Type::getType(WriteIl2CppString("UnityEngine.UI.Image")));
        Toggle* toggleComponent = (Toggle*)buttonGO->AddComponent(Type::getType(WriteIl2CppString("UnityEngine.UI.Toggle")));
        toggleComponent->set_transition(Transition::ColorTint);
        toggleComponent->set_colors(color);
        toggleComponent->set_targetGraphic((Graphic*)cachedImage);

        if (spriteOff != nullptr)
            cachedImage->set_sprite(spriteOff);
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

    void CallClick() {
        if (onClick != nullptr) {
            onClick(this);
        }
    }

    bool Initialize() {

        if (initialized) return false;
        return InitializeToggleButton();

    }
};