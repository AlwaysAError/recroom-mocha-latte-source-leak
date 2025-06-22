#pragma once

typedef void*(*instantiateAssets_t)(Il2CppString*, Vector3, Quaternion, Vector3, uint8_t, Il2CppArray*, bool, bool);
static void* __fastcall instantiateAssets_hook(Il2CppString* prefabName, Vector3 position, Quaternion rotation, Vector3 scale, uint8_t group, Il2CppArray* data, bool destroyOnLeave, bool idk) {

    const auto func = (instantiateAssets_t)(methods::obfuscated::photon::photonInstantiateAssets);

    bool debugToggle = globals::instantiateAssets::debugToggle;
    bool internalVectorsToggle = globals::instantiateAssets::vectorsToggle;
    bool internalPrefabTypeToggle = globals::instantiateAssets::prefabTypeToggle;
    bool internalInfinityToggle = globals::instantiateAssets::infinityToggle;
    bool internalInfinityScaleToggle = globals::instantiateAssets::infinityScaleToggle;
    bool internalInfinityScaleType = globals::instantiateAssets::infinityScaleType;
    bool internalReturnTypeFixToggle = globals::instantiateAssets::returnTypeFixToggle;
    bool internalReturnTypeNULLToggle = globals::instantiateAssets::returnTypeNULLToggle;
    bool internalAdvancedConfigToggle = globals::instantiateAssets::advancedConfigToggle;
    bool internalBlackFlashToggle = globals::instantiateAssets::blackFlashToggle;
    bool internalDespawnToggle = globals::instantiateAssets::despawnToggle;
    int internalCount = globals::instantiateAssets::Count;

    Il2CppString* internalPrefab = internalPrefabTypeToggle ? WriteIl2CppString(globals::instantiateAssets::prefab.c_str()) : prefabName;

    Vector3 internalScale = globals::instantiateAssets::scale;

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
            << "\n[/] Scale: " << (globals::instantiateAssets::randomScaleToggle ? internalScale : scale)
            << "\n[/] destroyOnLeave: " << destroyOnLeave
            << "\n[/] Bool: " << idk
            << "\n|=---------------------------------------------=|\n";
    }
    else {
        Log::debug("Item spawned.");
    }

    bool whitelistActive = globals::instantiateAssets::playerSpawnWhitelistToggle || globals::instantiateAssets::polaroidWhitelistToggle;
    bool isWhitelisted = false;
    if (whitelistActive) {
        const char* prefabNameStr = ReadIl2CppString(prefabName);
        isWhitelisted = (globals::instantiateAssets::playerSpawnWhitelistToggle && strcmp(prefabNameStr, "[StandaloneShapeContainer]") == 0) ||
            (globals::instantiateAssets::polaroidWhitelistToggle && strcmp(prefabNameStr, "[Polaroid]") == 0);
        if (!isWhitelisted) {
            internalCount = 0;
        }
    }

    Il2CppString* chosenPrefab = (internalPrefabTypeToggle && (!whitelistActive || isWhitelisted)) ? internalPrefab : prefabName;
    Vector3 chosenPosition = internalVectorsToggle && isWhitelisted ? globals::instantiateAssets::position : position;
    Quaternion chosenRotation = internalVectorsToggle && isWhitelisted ? globals::instantiateAssets::rotation : rotation;
    Vector3 chosenScale = (!globals::instantiateAssets::randomScaleToggle || isWhitelisted) ? internalScale : scale;

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

        chosenPrefab = il2cpp_string_new_spoof("[sandbox_ladder_hook]");

        Il2CppString* returnPrefab = il2cpp_string_new_spoof("[Dart]");

        chosenScale = Vector3{ minn, minn, minn };

        veh::CallOriginal<void*>(func, chosenPrefab, chosenPosition, chosenRotation, chosenScale, 0, nullptr, false, idk);
        veh::CallOriginal<void*>(func, chosenPrefab, chosenPosition, chosenRotation, chosenScale, 0, nullptr, false, idk);
        veh::CallOriginal<void*>(func, chosenPrefab, chosenPosition, chosenRotation, chosenScale, 0, nullptr, false, idk);
        veh::CallOriginal<void*>(func, chosenPrefab, chosenPosition, chosenRotation, chosenScale, 0, nullptr, false, idk);
        veh::CallOriginal<void*>(func, chosenPrefab, chosenPosition, chosenRotation, chosenScale, 0, nullptr, false, idk);
        veh::CallOriginal<void*>(func, chosenPrefab, chosenPosition, chosenRotation, chosenScale, 0, nullptr, false, idk);
        veh::CallOriginal<void*>(func, chosenPrefab, chosenPosition, chosenRotation, chosenScale, 0, nullptr, false, idk);

        globals::instantiateAssets::blackFlashToggle = false;

        return veh::CallOriginal<void*>(func, returnPrefab, position, rotation, Vector3{ 3, 3, 3 }, group, data, destroyOnLeave, idk);
    }

    if (internalAdvancedConfigToggle) {
        const char* internalPrefabName = ReadIl2CppString(prefabName); // yes ik this code can be better but fuck off it's good enough
        if (strcmp(internalPrefabName, "[ShareCamera]") == 0) {
            internalReturnTypeNULLToggle = false;
            internalReturnTypeFixToggle = false;
            internalScale = globals::instantiateAssets::scaleShareCamera; // internal scale cause ??? c++ is dogshit sometimes
            chosenPrefab = WriteIl2CppString(globals::instantiateAssets::prefabShareCamera);
        }

        if (strcmp(internalPrefabName, "[FeedbackTool]") == 0) {
            internalReturnTypeNULLToggle = false;
            internalReturnTypeFixToggle = false;
            internalScale = globals::instantiateAssets::scaleFeedbackTool;
            chosenPrefab = WriteIl2CppString(globals::instantiateAssets::prefabFeedbackTool);
        }

        if (strcmp(internalPrefabName, "[HandheldStreamerCamera]") == 0) {
            internalReturnTypeNULLToggle = false;
            internalReturnTypeFixToggle = true;
            internalScale = globals::instantiateAssets::scaleStreamerCam;
            chosenPrefab = WriteIl2CppString(globals::instantiateAssets::prefabStreamerCam);
        }
    }

    for (int i = 0; i < internalCount; ++i) {

        if (globals::instantiateAssets::randomScaleToggle) {
            internalScale.x = getRandomScale(globals::instantiateAssets::randomScaleX);
            internalScale.y = getRandomScale(globals::instantiateAssets::randomScaleY);
            internalScale.z = getRandomScale(globals::instantiateAssets::randomScaleZ);
        }
        veh::CallOriginal<void*>(func, chosenPrefab, chosenPosition, chosenRotation, chosenScale, 0, nullptr, internalDespawnToggle, idk);
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

    return veh::CallOriginal<void*>(func, chosenPrefab, chosenPosition, chosenRotation, chosenScale, group, data, destroyOnLeave, idk);
}