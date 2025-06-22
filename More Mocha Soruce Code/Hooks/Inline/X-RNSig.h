#pragma once

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) {
        return "";
    }
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

typedef Il2CppString* (*GenerateRequestSignature_t)(void*, Il2CppString*, Il2CppArray*, int32_t, void*);
GenerateRequestSignature_t GenerateRequestSignature_o = nullptr;
Il2CppString* __fastcall GenerateRequestSignature_Ihook(void* instance, Il2CppString* url, Il2CppArray* body, int32_t contentLength, void* methodInfo) {
    // Early return if hook is not enabled
    if (!globals::Ihooks::GenerateRequestSignature)
        return GenerateRequestSignature_o(instance, url, body, contentLength, methodInfo);

    if ((url != nullptr) && (body != nullptr)) {
        // Handle URL loading
        Il2CppString* ourURL = nullptr;
        std::ifstream file("Mocha/url.txt");
        if (file.is_open()) {
            std::string urll;
            std::getline(file, urll);
            urll = trim(urll);
            ourURL = WriteIl2CppString(urll.c_str());
            file.close();
        } else {
            ourURL = WriteIl2CppString(globals::xrnsig::urlBuffer.c_str());
        }

        // Log the URL
        Log::debug("URL: " + std::string(ReadIl2CppString(url)));

        // Prepare byte array type for request body
        Il2CppType* byteType = Type::getType(WriteIl2CppString("System.Byte"));

        // Handle request body loading
        if (std::ifstream file2("Mocha/request.txt"); file2.is_open()) {
            // Read entire file content
            const std::string contentbody((std::istreambuf_iterator<char>(file2)), std::istreambuf_iterator<char>());
            file2.close();
            
            const size_t length = contentbody.size();
            Il2CppArray* contentBodyArray = Array::createInstance(byteType, length);

            // Fill the IL2CPP array with body content
            for (size_t i = 0; i < length; i++) {
                const uint8_t byteValue = static_cast<uint8_t>(contentbody[i]);
                il2cpp_array_set(contentBodyArray, uint8_t, i, byteValue);
            }

            // Log the body content using IL2CPP array access
            std::string bodyStr;
            for (size_t i = 0; i < body->max_length; i++) {
                uint8_t byte = il2cpp_array_get(body, uint8_t, i);
                bodyStr += static_cast<char>(byte);
            }
            Log::debug("Body: " + bodyStr);

            // Generate and log the signature
            Il2CppString* generatedXRNSIG = GenerateRequestSignature_o(instance, ourURL, contentBodyArray, length, methodInfo);
            
            Log::debug("==============================================");
            Log::debug(std::string(ReadIl2CppString(generatedXRNSIG)));
            Log::debug("==============================================");
        } else {
            Log::error("Failed to open Mocha/request.txt");
        }
    }

    // Always return the original function call with original parameters
    return GenerateRequestSignature_o(instance, url, body, contentLength, methodInfo);
}
