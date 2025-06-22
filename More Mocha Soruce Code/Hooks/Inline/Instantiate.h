#pragma once

typedef void* (*Instantiate_t)(Il2CppString*, Vector3, Quaternion, Vector3, uint8_t, void*, void*);
Instantiate_t Instantiate_o = nullptr;
static void* __fastcall Instantiate_Ihook(Il2CppString* prefabName, Vector3 position, Quaternion rotation, Vector3 scale, uint8_t group, void* data, void* methodInfo) {

    if (!globals::Ihooks::Instantiate)
        return Instantiate_o(prefabName, position, rotation, scale, group, data, methodInfo);

    const bool& debugToggle = globals::instantiate::debugToggle;
    const bool& internalVectorsToggle = globals::instantiate::vectorsToggle;
    const bool& internalPrefabTypeToggle = globals::instantiate::prefabTypeToggle;
    const bool& internalInfinityToggle = globals::instantiate::infinityToggle;
    const bool& internalInfinityScaleToggle = globals::instantiate::infinityScaleToggle;
    const bool& internalInfinityScaleType = globals::instantiate::infinityScaleType;
    const bool& internalReturnTypeFixToggle = globals::instantiate::returnTypeFixToggle;
    const bool& internalReturnTypeNULLToggle = globals::instantiate::returnTypeNULLToggle;
    const bool& internalBlackFlashToggle = globals::instantiate::blackFlashToggle;
    int& internalCount = globals::instantiate::Count;

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

        for (int i = 0; i < 8; i++) {
            Instantiate_o(chosenPrefab, chosenPosition, chosenRotation, chosenScale, 0, nullptr, methodInfo);
        }

        globals::instantiate::blackFlashToggle = false;


        Instantiate_o(returnPrefab, position, rotation, Vector3{ 3, 3, 3 }, 0, nullptr, methodInfo);
    }

    for (int i = 0; i < internalCount; ++i) {

        if (globals::instantiate::randomScaleToggle) {
            internalScale.x = getRandomScale(globals::instantiate::randomScaleX);
            internalScale.y = getRandomScale(globals::instantiate::randomScaleY);
            internalScale.z = getRandomScale(globals::instantiate::randomScaleZ);
        }
        Instantiate_o(chosenPrefab, chosenPosition, chosenRotation, chosenScale, 0, nullptr, methodInfo);
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

    return Instantiate_o(chosenPrefab, chosenPosition, chosenRotation, chosenScale, group, data, methodInfo);
}