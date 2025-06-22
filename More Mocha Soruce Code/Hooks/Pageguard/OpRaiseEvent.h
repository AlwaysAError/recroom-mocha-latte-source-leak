#pragma once

typedef bool(*OpRaiseEvent_t)(void*, BYTE, Il2CppObject*, Il2CppObject*, Il2CppObject*, void*);
bool __fastcall OpRaiseEvent_hook(void* instance, BYTE eventCode, Il2CppObject* payload, Il2CppObject* raiseEventOptions, Il2CppObject* sendOptions, void* methodInfo) {

    const auto func = (OpRaiseEvent_t)(methods::obfuscated::photon::OpRaiseEvent);

    if (payload != nullptr) {
        Il2CppString* payloadClassName = Type::getClassName((Il2CppClass*)payload);
        Type* payloadType = (Type*)Type::GetType(payload);
        std::string payloadTypeString = ReadIl2CppString(payloadType->ToString());

        if (payloadTypeString == "Type: Hashtable" && (eventCode == 200)) // 200 is RPC code
        {
            OpRaiseEventCache::instance = instance;
            OpRaiseEventCache::eventCode = eventCode;
            OpRaiseEventCache::payload = payload;
            OpRaiseEventCache::eventOptions = raiseEventOptions;
            OpRaiseEventCache::sendOptions = sendOptions;
            globals::opRaiseEventCached = true;
        }
    }

    return veh::CallOriginal<bool>(func, instance, eventCode, payload, raiseEventOptions, sendOptions, nullptr);
}