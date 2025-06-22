#pragma once

static std::string spoofed_hwid = "";

std::string randomizeHWID(const std::string& original) {
    std::string modified = original;
    srand(time(NULL));

    for (char& c : modified) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            c = base + rand() % 26;
        }
        else if (isdigit(c)) {
            c = '0' + rand() % 10;
        }
    }

    return modified;
}

typedef Il2CppString* (*UnityHWID_t)(void*);
UnityHWID_t UnityHWID_o = nullptr;
Il2CppString* __fastcall UnityHWID_Ihook(void* methodInfo) {

    if (!globals::Ihooks::get_deviceUniqueIdentifier)
        return UnityHWID_o(methodInfo);

    std::string original_hwid = ReadIl2CppString(UnityHWID_o(methodInfo));

    srand(time(0));
    if (spoofed_hwid == "") {
        spoofed_hwid = randomizeHWID(original_hwid);
        Log::debug("[Spoofer] Swapped: (" + original_hwid + ") -> (" + spoofed_hwid + ")");
    }

    return WriteIl2CppString(spoofed_hwid.c_str());
}