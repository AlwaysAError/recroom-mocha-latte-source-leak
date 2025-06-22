#pragma once

namespace Callbacks
{
    bool RenameAllTexts() {

        Il2CppArray* objects = UObject::FindObjectsOfType("UnityEngine.GameObject");

        for (int i = 0; i < objects->max_length; i++) {

            if (GameObject* gameObject = il2cpp_array_get(objects, GameObject*, i)) {
                
                if (auto* multiPlayerEditableTextV2 = (MultiPlayerEditableTextV2*)gameObject->GetComponent("MultiPlayerEditableTextV2")) {

                    multiPlayerEditableTextV2->DefaultMessageSet(WriteIl2CppString(globals::textBuffer.c_str()));
                    continue;
                }
                
                if (auto* multiPlayerEditableText = (MultiPlayerEditableText*)gameObject->GetComponent("MultiPlayerEditableText")) {

                    const int32_t numberOfSerializedMessages = GetField<int32_t>(multiPlayerEditableText, 204);

                    for (int j = 0; j < numberOfSerializedMessages; j++) {
                        multiPlayerEditableText->SynchronizedMessageSet(j, WriteIl2CppString(globals::textBuffer.c_str()));
                    }
                }
            }
        }

        return true;
    }
}