#pragma once

std::vector<GameObject*> allSceneGameObjects;

bool viewingObject = false;
GameObject* currentObject;
const char* objectName = "";
bool objectActive;
int objectLayer;
std::vector<GameObject*> objectChildren;
std::vector<Component*> objectComponents;

static float objectPosition[3] = { 1.0, 1.0, 1.0 };
static float objectRotation[3] = { 1.0, 1.0, 1.0 };
static float objectScale[3] = { 1.0, 1.0, 1.0 };

int rowSize;


bool viewingComponent = false;
Component* currentComponent;
const char* componentName = "";

std::vector<FieldInfo*> fieldInfos;
std::vector<const char*> fieldNames;
std::vector<const char*> fieldTypeNames;
std::vector<const char*> fieldValues;

bool fieldsToggle = true;
bool propertiesToggle = true;
bool methodsToggle = true;

std::map<std::string, std::array<char, 256>> cachedFieldList = {};

void GetAllObjects()
{
    allSceneGameObjects.clear();

    Il2CppArray* objects = GameObject::FindObjectsOfType("UnityEngine.GameObject");

    for (int i = 0; i < objects->max_length; i++)
    {
        GameObject* object = il2cpp_array_get(objects, GameObject*, i);
        if (object->get_transform()->get_parent() == nullptr)
            allSceneGameObjects.push_back(object);
    }
}

void ClearObjects()
{
    allSceneGameObjects.clear();
    viewingObject = false;
    viewingComponent = false;
}

void viewObject(GameObject* object)
{
    viewingComponent = false;

    objectChildren.clear();
    objectComponents.clear();

    currentObject = object;
    objectName = ReadIl2CppString(object->GetName());
    objectActive = object->get_active();
    objectLayer = object->get_layer();

    Vector3 objectPos = object->get_transform()->get_position();

    objectPosition[0] = objectPos.x;
    objectPosition[1] = objectPos.y;
    objectPosition[2] = objectPos.z;

    Quaternion objectRot = object->get_transform()->get_localRotation();

    objectRotation[0] = objectRot.x;
    objectRotation[1] = objectRot.y;
    objectRotation[2] = objectRot.z;

    Vector3 objectSca = object->get_transform()->get_localScale();

    objectScale[0] = objectSca.x;
    objectScale[1] = objectSca.y;
    objectScale[2] = objectSca.z;

    for (int i = 0; i < object->get_transform()->get_ChildCount(); i++)
    {
        objectChildren.push_back(object->get_transform()->GetChild(i)->get_gameObject());
    }

    Il2CppArray* components = object->GetComponents("UnityEngine.Component");
    for (int j = 0; j < components->max_length; j++)
    {
        Component* component = il2cpp_array_get(components, Component*, j);
        objectComponents.push_back(component);
    }

    rowSize = (objectChildren.size() >= objectComponents.size()) ? objectChildren.size() : objectComponents.size();

    viewingObject = true;
}

void viewComponent(Component* component)
{
    viewingObject = false;

    fieldInfos.clear();
    fieldNames.clear();
    fieldTypeNames.clear();
    fieldValues.clear();

    currentComponent = component;
    componentName = ReadIl2CppString(Type::getClassName((Il2CppClass*)component));

    Il2CppClass* classType = FindClass(ReadIl2CppString(Type::getClassName((Il2CppClass*)component)));

    void* iterator = nullptr;
    FieldInfo* field = nullptr;
    while ((field = il2cpp_class_get_fields_spoof(classType, &iterator)) != nullptr)
    {
        fieldInfos.push_back(field);
        fieldNames.push_back(il2cpp_field_get_name_spoof(field));
        fieldTypeNames.push_back(il2cpp_type_get_name_spoof(il2cpp_field_get_type_spoof(field)));
        const char* valuePlaceHolder = "Not Done.";
        std::string TypeName = il2cpp_type_get_name_spoof(il2cpp_field_get_type_spoof(field));
        if (TypeName == std::string("System.String"))
        {
            Il2CppString* placeHolder = reinterpret_cast<Il2CppString*>(il2cpp_field_get_value_object_spoof(field, component));
            valuePlaceHolder = ReadIl2CppString(placeHolder);
        }
        else if (TypeName == std::string("System.Boolean"))
        {
            bool placeHolder;
            il2cpp_field_get_value_spoof(component, field, &placeHolder);
            valuePlaceHolder = (placeHolder) ? "True" : "False";
        }
        else if (TypeName == std::string("System.Int32"))
        {
            int* placeHolder = reinterpret_cast<int*>(il2cpp_object_unbox_spoof(il2cpp_field_get_value_object_spoof(field, component)));
            valuePlaceHolder = std::to_string(*placeHolder).c_str();
        }
        //Type* valueType = (Type*)il2cpp_object_unbox_spoof(il2cpp_field_get_value_object_spoof(field, component));
        fieldValues.push_back(valuePlaceHolder);
    }

    viewingComponent = true;
}

void setField(int btnNum)
{
    FieldInfo* field = fieldInfos.at(btnNum);
    std::string TypeName = fieldNames.at(btnNum);
    std::string stringValue;
    int counter = 0;
    for (auto it = cachedFieldList.begin(); it != cachedFieldList.end(); ++it) {
        if (counter == btnNum) {
            stringValue = std::string(it->second.data());
            break;
        }
        counter++;
    }
    if (TypeName == std::string("System.String"))
    {
        fieldValues[btnNum] = stringValue.c_str();
        Il2CppString* strVal = il2cpp_string_new_spoof(stringValue.c_str());
        il2cpp_field_set_value_object_spoof(currentComponent, field, (Il2CppObject*)strVal);
    }
    else if (TypeName == std::string("System.Boolean"))
    {
        std::string fieldValue;
        bool actValue;

        if (stringValue == std::string("True"))
        {
            actValue = true;
            fieldValue = "True";
            fieldValues[btnNum] = fieldValue.c_str();
            il2cpp_field_set_value_spoof(currentComponent, field, &actValue);
        }
        else if (stringValue == std::string("False"))
        {
            actValue = false;
            fieldValue = "False";
            fieldValues[btnNum] = fieldValue.c_str();
            il2cpp_field_set_value_spoof(currentComponent, field, &actValue);

        }
        else
        {
            return;
        }
    }
    else if (TypeName == std::string("System.Int32"))
    {
        fieldValues[btnNum] = stringValue.c_str();
        int fieldValue = std::stoi(stringValue);
        il2cpp_field_set_value_spoof(currentComponent, field, &fieldValue);
    }
    else
    {
        return;
    }
}

void StartExplorer()
{

	const float SideBarWidth = 216;

	if (globals::CPPExplorer::open)
	{
        ImGuiStyle& style = ImGui::GetStyle();

        {
            static ImVec2 MenuSize = ImVec2(922, 726);
            ImGui::SetNextWindowSize(MenuSize, ImGuiCond_Once);
            ImGui::SetNextWindowPos(ImGui::GetIO().DisplaySize / 2 - MenuSize / 2, ImGuiCond_Once);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            ImGui::SetNextWindowSizeConstraints(MenuSize, { 9999, 9999 });
            ImGui::Begin("Explorer", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBackground);
            ImGui::PopStyleVar(2);

            // Renders
            {
                ImVec2 pos = ImGui::GetWindowPos();
                ImVec2 size = ImGui::GetWindowSize();
                ImDrawList* drawList = ImGui::GetWindowDrawList();

                drawList->AddRectFilled(pos, pos + ImVec2(SideBarWidth, size.y), ImGui::GetColorU32(ImGuiCol_WindowBg), style.WindowRounding, ImDrawFlags_RoundCornersLeft);
                drawList->AddRectFilled(pos + ImVec2(SideBarWidth, 0), pos + size, ImGui::GetColorU32(ImGuiCol_PopupBg), style.WindowRounding, ImDrawFlags_RoundCornersRight);
            }

            {
                ImGui::BeginChild("Objects", ImVec2(SideBarWidth, 0), ImGuiChildFlags_Border, ImGuiWindowFlags_NoBackground);
                {
                    for (int i = 0; i < allSceneGameObjects.size(); i++)
                    {
                        std::string btnName = ReadIl2CppString(allSceneGameObjects.at(i)->GetName());
                        if (ImGui::Button((btnName + "##" + std::to_string(i)).c_str()))
                        {
                            viewObject(allSceneGameObjects.at(i));
                        }
                    }
                }
                ImGui::EndChild();
                if (viewingObject)
                {
                    ImGui::SameLine(SideBarWidth);
                    ImGui::BeginChild("Inspector", ImVec2(0, 0), ImGuiChildFlags_Border, ImGuiWindowFlags_NoBackground);
                    {
                        ImGui::Text(objectName);
                        if (objectActive)
                        {
                            ImGui::Text("Active: True");
                        }
                        else
                        {
                            ImGui::Text("Active: False");
                        }
                        ImGui::SameLine();
                        ImGui::Text(("Layer: " + std::to_string(objectLayer)).c_str());
                        if (ImGui::Button("Set Active"))
                        {
                            currentObject->set_active(!currentObject->get_active());
                            objectActive = !objectActive;
                        }
                        ImGui::SameLine();
                        if (ImGui::Button("Parent"))
                        {
                            if (currentObject->get_transform()->get_parent() != nullptr)
                                viewObject(currentObject->get_transform()->get_parent()->get_gameObject());
                        }
                        ImGui::SameLine();
                        if (ImGui::Button("Destroy"))
                        {
                            currentObject->Destroy();
                        }

                        ImGui::InputFloat3("Position ##1", objectPosition);
                        ImGui::SameLine();
                        if (ImGui::Button("Set Position"))
                        {
                            currentObject->get_transform()->set_localPosition({ objectPosition[0], objectPosition[1], objectPosition[2] });
                        }

                        ImGui::InputFloat3("Rotation ##2", objectRotation);
                        ImGui::SameLine();
                        if (ImGui::Button("Set Rotation"))
                        {
                            currentObject->get_transform()->set_localRotation({ objectRotation[0], objectRotation[1], objectRotation[2] });
                        }

                        ImGui::InputFloat3("Scale ##3", objectScale);
                        ImGui::SameLine();
                        if (ImGui::Button("Set Scale"))
                        {
                            currentObject->get_transform()->set_localScale({ objectScale[0], objectScale[1], objectScale[2] });
                        }

                        enum ContentsType { CT_Text, CT_FillButton };
                        static ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;
                        static bool display_headers = true;
                        static int contents_type = CT_Text;

                        if (ImGui::BeginTable("Children and Components Table", 2))
                        {
                            ImGui::TableSetupColumn("Children");
                            ImGui::TableSetupColumn("Components");
                            ImGui::TableNextRow(ImGuiTableRowFlags_Headers);

                            for (int column = 0; column < 2; ++column)
                            {
                                ImGui::TableSetColumnIndex(column);
                                const char* headerTitle = (column == 0) ? "Children" : "Components";

                                float headerWidth = ImGui::CalcTextSize(headerTitle).x + ImGui::GetStyle().FramePadding.x * 2;
                                float nextPosX = ImGui::GetCursorPosX() + ImGui::GetStyle().FramePadding.x;
                                ImGui::SetCursorPosX(nextPosX);

                                ImGui::Text("%s", headerTitle);
                            }

                            for (int row = 0; row < rowSize; ++row)
                            {
                                ImGui::TableNextRow();

                                for (int column = 0; column < 2; ++column)
                                {
                                    ImGui::TableSetColumnIndex(column);
                                    std::string buttonText;

                                    if (column == 0 && row < objectChildren.size()) {
                                        buttonText = ReadIl2CppString(objectChildren.at(row)->GetName());
                                    }
                                    else if (column == 1 && row < objectComponents.size()) {
                                        buttonText = ReadIl2CppString(Type::getClassName((Il2CppClass*)objectComponents.at(row)));
                                    }

                                    if (!buttonText.empty())
                                    {
                                        float buttonWidth = ImGui::CalcTextSize(buttonText.c_str()).x + ImGui::GetStyle().FramePadding.x * 2;
                                        float nextPosX = ImGui::GetCursorPosX() + ImGui::GetStyle().FramePadding.x;
                                        ImGui::SetCursorPosX(nextPosX);

                                        if (ImGui::Button(buttonText.c_str(), ImVec2(buttonWidth, 0))) {
                                            if (column == 0) {
                                                viewObject(objectChildren.at(row));
                                            }
                                            else if (column == 1) {
                                                viewComponent(objectComponents.at(row));
                                            }
                                        }
                                    }
                                }
                            }
                            ImGui::EndTable();
                        }
                    }
                    ImGui::EndChild();
                }
                else if (viewingComponent)
                {
                    ImGui::SameLine(SideBarWidth);
                    ImGui::BeginChild("Inspector", ImVec2(0, 0), ImGuiChildFlags_Border, ImGuiWindowFlags_NoBackground);
                    {
                        ImGui::Text(componentName);
                        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 1.0f, 1.0f));
                        ImAdd::ToggleButtonClassic("Fields", &fieldsToggle);
                        ImGui::SameLine();
                        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
                        ImAdd::ToggleButtonClassic("Properties", &propertiesToggle);
                        ImGui::SameLine();
                        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.4f, 0.0f, 1.0f));
                        ImAdd::ToggleButtonClassic("Methods", &methodsToggle);
                        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));

                        if (fieldsToggle)
                        {
                            if (ImGui::BeginTable("Field Table", 4))
                            {
                                ImGui::TableSetupColumn("Type");
                                ImGui::TableSetupColumn("Name");
                                ImGui::TableSetupColumn("Value");
                                ImGui::TableSetupColumn("SetBtns");
                                ImGui::TableNextRow(ImGuiTableRowFlags_Headers);

                                for (int column = 0; column < 4; ++column)
                                {
                                    ImGui::TableSetColumnIndex(column);
                                    const char* headerTitle;
                                    headerTitle = (column == 0) ? "Type" : "Name";
                                    if (column == 2)
                                    {
                                        headerTitle = "Value";
                                    }
                                    else if (column == 3)
                                    {
                                        headerTitle = "SetBtns";
                                    }

                                    float headerWidth = ImGui::CalcTextSize(headerTitle).x + ImGui::GetStyle().FramePadding.x * 3;
                                    float nextPosX = ImGui::GetCursorPosX() + ImGui::GetStyle().FramePadding.x;
                                    ImGui::SetCursorPosX(nextPosX);

                                    ImGui::Text("%s", headerTitle);
                                }

                                for (int row = 0; row < fieldInfos.size(); ++row)
                                {
                                    ImGui::TableNextRow();

                                    for (int column = 0; column < 4; ++column)
                                    {
                                        ImGui::TableSetColumnIndex(column);
                                        std::string buttonText;

                                        if (column == 0 && row < fieldTypeNames.size()) {
                                            buttonText = fieldTypeNames.at(row);
                                        }
                                        else if (column == 1 && row < fieldNames.size()) {
                                            buttonText = fieldNames.at(row);
                                        }
                                        else if (column == 2 && row < fieldValues.size()) {
                                            buttonText = fieldValues.at(row);
                                        }
                                        else if (column == 3 && row < fieldInfos.size()) {
                                            buttonText = "Set Field##" + std::to_string(row);
                                        }

                                        if (!buttonText.empty())
                                        {
                                            float buttonWidth = ImGui::CalcTextSize(buttonText.c_str()).x + ImGui::GetStyle().FramePadding.x * 2;
                                            float nextPosX = ImGui::GetCursorPosX() + ImGui::GetStyle().FramePadding.x;
                                            ImGui::SetCursorPosX(nextPosX);
                                            if (column == 0 || column == 1)
                                            {
                                                if (column == 0)
                                                {
                                                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
                                                }
                                                else if (column == 1)
                                                {
                                                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 1.0f, 1.0f));
                                                }
                                                ImGui::Text(buttonText.c_str(), ImVec2(buttonWidth, 0));
                                            }
                                            else if (column == 2)
                                            {
                                                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
                                                std::string labelS = "##" + std::to_string(row);
                                                std::array<char, 256>& bufferArray = cachedFieldList[labelS];


                                                if (ImGui::InputTextWithHint(labelS.c_str(), buttonText.c_str(), bufferArray.data(), bufferArray.size()))
                                                {
                                                    cachedFieldList[labelS] = bufferArray;
                                                }
                                            }
                                            else
                                            {
                                                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
                                                if (ImGui::Button(buttonText.c_str(), ImVec2(buttonWidth, 0))) {
                                                    if (column == 3) {
                                                        setField(row);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                ImGui::EndTable();
                            }
                        }
                    }
                    ImGui::EndChild();
                }
            }

            ImGui::End();
        }
	}
}