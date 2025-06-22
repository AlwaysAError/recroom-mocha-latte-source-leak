#pragma once

typedef void (*CreateUri_t)(void*, Uri*, Il2CppString*, bool, void*);
CreateUri_t CreateUri_o = nullptr;
static void __fastcall CreateUri_Ihook(void* uri, Uri* baseUri, Il2CppString* relativeUri, bool dontEscape, void* methodInfo) {

    if (!(globals::Ihooks::chai && globals::chai::swapsToggle))
        return hook_manager::get()["chai2"]->call<void>(uri, baseUri, relativeUri, dontEscape, methodInfo);
        //return CreateUri_o(uri, baseUri, relativeUri, dontEscape, methodInfo);

    if (uri == nullptr || baseUri == nullptr)
        return hook_manager::get()["chai2"]->call<void>(uri, baseUri, relativeUri, dontEscape, methodInfo);

    const std::string baseUriStr = ReadIl2CppString(baseUri->ToString());
    const std::string relativeUriStr = ReadIl2CppString(relativeUri);

    if (globals::chai::debugAllToggle)
        Log::debug("[Chai] (" + baseUriStr + relativeUriStr + ")");

    for (const auto& [match, replace] : globals::chai::swaps) {
        // If `match` is "*", skip the baseUri check; otherwise, ensure it matches baseUriStr
        if ((match == "*" || baseUriStr.find(match) != std::string::npos) && relativeUriStr.find(replace) != std::string::npos) { // Check `replace` for relativeUri condition
            if (Uri* newUri = Uri::TryCreate("https://chai.itakewood.vip/", Uri::UriKind::RelativeOrAbsolute)) {

                if (globals::chai::debugToggle)
                    Log::debug("[Chai] Swapped: (" + (baseUriStr + relativeUriStr) + ") -> (" + (ReadIl2CppString(newUri->ToString()) + relativeUriStr) + ")");

                return hook_manager::get()["chai2"]->call<void>(uri, newUri, relativeUri, dontEscape, methodInfo);
                //return CreateUri_o(uri, newUri, relativeUri, dontEscape, methodInfo);
            }
        }
    }

    return hook_manager::get()["chai2"]->call<void>(uri, baseUri, relativeUri, dontEscape, methodInfo);
    //return CreateUri_o(uri, baseUri, relativeUri, dontEscape, methodInfo);
}

static void __fastcall CreateUri_Ihook_PROD(void* uri, Uri* baseUri, Il2CppString* relativeUri, bool dontEscape, void* methodInfo) {

    if (!(globals::Ihooks::chai && clothingEnabled))
        return CreateUri_o(uri, baseUri, relativeUri, dontEscape, methodInfo);

    if (uri == nullptr || baseUri == nullptr)
        return CreateUri_o(uri, baseUri, relativeUri, dontEscape, methodInfo);

    std::string relativeUriStr = ReadIl2CppString(relativeUri);

    if (relativeUriStr.find("api/avatar/v4/items") != std::string::npos || relativeUriStr.find("econ/customAvatarItems/v1/owned") != std::string::npos) { // Check `replace` for relativeUri condition

        if (Uri* newUri = Uri::TryCreate("https://chai.itakewood.vip/", Uri::UriKind::RelativeOrAbsolute);
            newUri != nullptr) {

            return CreateUri_o(uri, newUri, relativeUri, dontEscape, methodInfo);
        }
    }

    return CreateUri_o(uri, baseUri, relativeUri, dontEscape, methodInfo);
}

typedef void (*FatalApplicationQuit_t)(int32_t, Il2CppString*, void*);
FatalApplicationQuit_t FatalApplicationQuit_o = nullptr;
static void __fastcall FatalApplicationQuit_Ihook(int32_t statusCode, Il2CppString* message, void* methodInfo) {

#ifdef PROD
    if (!clothingEnabled)
        return FatalApplicationQuit_o(statusCode, message, methodInfo);
#endif

	if (!globals::Ihooks::chai)
		return FatalApplicationQuit_o(statusCode, message, methodInfo);

	return;
}

typedef bool (*IsValid_t)(void*, Uri*, void*, void*);
IsValid_t IsValid_o = nullptr;
bool __fastcall IsValid_Ihook(void* instance, Uri* targetUri, void* certs, void* methodInfo) {

#ifdef PROD
    if (!clothingEnabled)
        return IsValid_o(instance, targetUri, certs, methodInfo);
#endif

	if (!globals::Ihooks::chai)
		return IsValid_o(instance, targetUri, certs, methodInfo);

	return true;
}