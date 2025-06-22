#pragma once

namespace Callbacks
{
    bool DisableEACManager() {

        Il2CppArray* objectArray = UObject::FindObjectsOfType("UnityEngine.GameObject");

        for (int i = 0; i < objectArray->max_length; i++) {

            GameObject* object = il2cpp_array_get(objectArray, GameObject*, i);

            if (Il2CppString* objectName = object->GetName()) {

                if (std::string(ReadIl2CppString(objectName)).find("[EACManager]") != std::string::npos) {
                    object->set_active(false);
                }
            }
        }

        return true;
    }
}