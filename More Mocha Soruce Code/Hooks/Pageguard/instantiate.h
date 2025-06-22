#pragma once

typedef void* (*instantiate_t)(Il2CppString*, Vector3, Quaternion, Vector3, uint8_t, void*);
static void* __fastcall instantiate_hook(Il2CppString* prefabName, Vector3 position, Quaternion rotation, Vector3 scale, uint8_t group, void* data) {

    const auto func = (instantiate_t)(methods::obfuscated::photon::photonInstantiate);

    bool debugToggle = globals::instantiate::debugToggle;
    bool internalVectorsToggle = globals::instantiate::vectorsToggle;
    bool internalPrefabTypeToggle = globals::instantiate::prefabTypeToggle;
    bool internalInfinityToggle = globals::instantiate::infinityToggle;
    bool internalInfinityScaleToggle = globals::instantiate::infinityScaleToggle;
    bool internalInfinityScaleType = globals::instantiate::infinityScaleType;
    bool internalReturnTypeFixToggle = globals::instantiate::returnTypeFixToggle;
    bool internalReturnTypeNULLToggle = globals::instantiate::returnTypeNULLToggle;
    bool internalBlackFlashToggle = globals::instantiate::blackFlashToggle;
    int internalCount = globals::instantiate::Count;

    Il2CppString* internalPrefab = internalPrefabTypeToggle ? WriteIl2CppString(globals::instantiate::prefab.c_str()) : prefabName;

    Vector3 internalScale = globals::instantiate::scale;

    if (debugToggle) {
        const char* debugPrefabName = ReadIl2CppString(prefabName);
        const char* debugSpoofedPrefabName = internalPrefabTypeToggle ? ReadIl2CppString(internalPrefab) : debugPrefabName;
        std::cout
            << "|=---------------------------------------------=|\n"
            << "|             Item Spawn Data Block             |\n"
            << "|=---------------------------------------------=|\n"
            << "[/] Real Prefab: " << debugPrefabName
            << "\n[/] Spoofed Prefab: " << debugSpoofedPrefabName
            << "\n[/] Position: " << position
            << "\n[/] Rotation: " << rotation
            << "\n[/] Scale: " << (globals::instantiate::randomScaleToggle ? internalScale : scale)
            << "\n|=---------------------------------------------=|\n";
    }
    else {
        Log::debug("Item spawned.");
    }

    bool whitelistActive = globals::instantiate::playerSpawnWhitelistToggle || globals::instantiate::polaroidWhitelistToggle;
    bool isWhitelisted = false;
    if (whitelistActive) {
        const char* prefabNameStr = ReadIl2CppString(prefabName);
        isWhitelisted = (globals::instantiate::playerSpawnWhitelistToggle && strcmp(prefabNameStr, "[StandaloneShapeContainer]") == 0) ||
            (globals::instantiate::polaroidWhitelistToggle && strcmp(prefabNameStr, "[Polaroid]") == 0);
        if (!isWhitelisted) {
            internalCount = 0;
        }
    }

    Il2CppString* chosenPrefab = (internalPrefabTypeToggle && (!whitelistActive || isWhitelisted)) ? internalPrefab : prefabName;
    Vector3 chosenPosition = internalVectorsToggle && isWhitelisted ? globals::instantiate::position : position;
    Quaternion chosenRotation = internalVectorsToggle && isWhitelisted ? globals::instantiate::rotation : rotation;
    Vector3 chosenScale = (!globals::instantiate::randomScaleToggle || isWhitelisted) ? internalScale : scale;

    float maxx = 99999993215964691371151521984339247104.000f;
    float minn = -99999993215964691371151521984339247104.000f;

    if (internalInfinityToggle) {

        chosenPosition = { maxx, maxx, minn };
        chosenRotation = { maxx, minn, maxx, minn };

        if (internalInfinityScaleToggle)
            chosenScale = internalInfinityScaleType ? Vector3{ maxx, maxx, maxx } : Vector3{ minn, minn, minn };
    }

    if (internalBlackFlashToggle) {
        chosenPosition = { maxx, maxx, minn };
        chosenRotation = { maxx, minn, maxx, minn };

        chosenPrefab = WriteIl2CppString("[sandbox_ladder_hook]");

        Il2CppString* returnPrefab = WriteIl2CppString("[Dart]");

        chosenScale = Vector3{ minn, minn, minn };

        veh::CallOriginal<void*>(func, chosenPrefab, chosenPosition, chosenRotation, chosenScale, 0, nullptr);
        veh::CallOriginal<void*>(func, chosenPrefab, chosenPosition, chosenRotation, chosenScale, 0, nullptr);
        veh::CallOriginal<void*>(func, chosenPrefab, chosenPosition, chosenRotation, chosenScale, 0, nullptr);
        veh::CallOriginal<void*>(func, chosenPrefab, chosenPosition, chosenRotation, chosenScale, 0, nullptr);
        veh::CallOriginal<void*>(func, chosenPrefab, chosenPosition, chosenRotation, chosenScale, 0, nullptr);
        veh::CallOriginal<void*>(func, chosenPrefab, chosenPosition, chosenRotation, chosenScale, 0, nullptr);

        globals::instantiate::blackFlashToggle = false;


        veh::CallOriginal<void*>(func, returnPrefab, position, rotation, Vector3{ 3, 3, 3 }, 0, nullptr);
    }

    for (int i = 0; i < internalCount; ++i) {

        if (globals::instantiate::randomScaleToggle) {
            internalScale.x = getRandomScale(globals::instantiate::randomScaleX);
            internalScale.y = getRandomScale(globals::instantiate::randomScaleY);
            internalScale.z = getRandomScale(globals::instantiate::randomScaleZ);
        }
        veh::CallOriginal<void*>(func, chosenPrefab, chosenPosition, chosenRotation, chosenScale, 0, nullptr);
    }

    if (internalReturnTypeFixToggle) {
        chosenPrefab = prefabName;
        chosenPosition = position;
        chosenRotation = rotation;
        chosenScale = scale;
    }

    if (internalReturnTypeNULLToggle) {
        chosenPrefab = WriteIl2CppString("");
    }

    return veh::CallOriginal<void*>(func, chosenPrefab, chosenPosition, chosenRotation, chosenScale, group, data);
}