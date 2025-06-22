#pragma once

namespace Callbacks
{
    bool killCv2() {

        Il2CppArray* objects = UObject::FindObjectsOfType("UnityEngine.GameObject");

        for (int i = 0; i < objects->max_length; i++) {

            if (GameObject* gameObject = il2cpp_array_get(objects, GameObject*, i)) {

                Il2CppString* goString = gameObject->ToString();

                if (goString == nullptr)
                    continue;

                if (std::string objname = ReadIl2CppString(goString);
                    (objname.find("[Chip](Clone)") != std::string::npos) || objname.find("[Chip]") != std::string::npos) { // lazy
                    
                    Log::debug("Destroying " + objname + " ...");
                    gameObject->Destroy(); // only destroys locally :P

                }
            }
        }

        return true;
    }
}