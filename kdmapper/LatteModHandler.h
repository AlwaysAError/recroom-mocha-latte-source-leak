#pragma once
#include <string>
#include <vector>
#include <windows.h>
#include "skStr.h"

class LatteModHandler {
public:
    LatteModHandler();
    static PVOID ConvertDll(const std::string& lmPath, const std::string& key);
    static std::string GetHeaderData(const std::string& lmPath);
    static std::vector<uint8_t> DecryptData(const std::vector<uint8_t>& encryptedData, const std::string& key);
    static std::vector<uint8_t> ReadFile(const std::string& filePath);
};
