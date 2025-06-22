#pragma once

class UIText {

private:

    UText* textComponent = nullptr;

public:

    std::string label = "";
    Vector3 position = Vector3(0, 0, 0);
    GameObject* parent = nullptr;
    GameObject* gameObject = nullptr;
    bool initialized = false;
    bool isTabChild = false;
    TabType tabType;
    int fontSize = 12;
    bool isSelectedPlayerText = false;
    static void* selectedPlayerText;

    UIText(std::string Label, Vector3 Position, TabType TabType, int FontSize, bool IsSelectedPlayerText = false) {
        label = Label;
        position = Position;
        fontSize = FontSize;
        parent = nullptr;
        isTabChild = true;
        tabType = TabType;
        initialized = false;
        IsSelectedPlayerText = IsSelectedPlayerText;
    }

    bool SetText(std::string text) {
        
        if ((!initialized) || (textComponent == nullptr)) return false;

        textComponent->set_Text(WriteIl2CppString(text.c_str()));

        return true;
    }

    // Standard Button Initialize
    bool Initialize() {

        parent = tabGameObjects[tabType];
        if (parent == nullptr) return false;

        GameObject* buttonTextGO = GameObject::ctor(WriteIl2CppString(std::string("Mocha-Text+'" + label + "'").c_str()));

        gameObject = buttonTextGO;

        buttonTextGO->set_layer(5);

        buttonTextGO->get_transform()->SetParent(parent->get_transform());

        buttonTextGO->AddComponent(Type::getType(WriteIl2CppString("UnityEngine.CanvasRenderer")));

        textComponent = (UText*)buttonTextGO->AddComponent(Type::getType(WriteIl2CppString("UnityEngine.UI.Text")));
        textComponent->set_Text(WriteIl2CppString(label.c_str()));
        textComponent->setFont(UFont::getDefaultFont());
        textComponent->setFontSize(fontSize);
        textComponent->set_alignment(4);

        buttonTextGO->get_transform()->set_localPosition(position);
        buttonTextGO->get_transform()->set_localRotation({0, 0, 0, 0});
        buttonTextGO->get_transform()->set_localScale({1, 1, 1});

        RectTransform* textTransform = (RectTransform*)buttonTextGO->get_transform();
        if (textTransform)
        {
            textTransform->set_sizeDelta({ 500,50 });
        }

        if (position.x != 0 || position.y != 0 || position.z != 0) {
            newThread(&SetButtonActualPos, this);
        }

        selectedPlayerText = this;

        initialized = true;
        return true;
    }

};

void* UIText::selectedPlayerText = nullptr;