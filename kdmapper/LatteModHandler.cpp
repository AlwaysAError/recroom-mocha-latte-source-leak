#include "LatteModHandler.h"
#include <fstream>
#include <iostream>
#include <random>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "cryptopp/cryptlib.h"
#include "cryptopp/aes.h"
#include "cryptopp/modes.h"
#include "cryptopp/filters.h"
#include "cryptopp/osrng.h"
#include "cryptopp/hex.h"
#include <algorithm>

const int LATTE_LENGTH = 5;
const int KEY_LENGTH = 32;
const int HEADER_LENGTH = (LATTE_LENGTH + KEY_LENGTH);

using namespace CryptoPP;

LatteModHandler::LatteModHandler() {}

const char* XOR_SEED = skCrypt("8itETq8yQXWYt7bbQp8ZiguyNud6mthAgQvnrzCNdE9RGCupnEYdFu8gZLkHTMDwwEzoJAxrfwWdintnAUxBVQpA7JYEpj9JRpQT");
const std::string XOR_KEY = XOR_SEED;

std::string ApplyXOR(const std::string& data, const std::string& xorKey) {
    std::string result = data;
    for (size_t i = 0; i < data.size(); ++i) {
        result[i] ^= xorKey[i % xorKey.size()];
    }
    return result;
}

std::vector<uint8_t> LatteModHandler::ReadFile(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        std::cout << skCrypt("[!] Failed to open file: ") << filePath << std::endl;
        return {};
    }

    std::vector<uint8_t> data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return data;
}

std::string LatteModHandler::GetHeaderData(const std::string& lmPath) {
    auto lmData = ReadFile(lmPath);
    if (lmData.size() <= HEADER_LENGTH) return nullptr;

    std::string latteCheck(lmData.begin(), lmData.begin() + LATTE_LENGTH);
    if (latteCheck != "LATTE") {
        std::cout << skCrypt("[!] Invalid Latte Mod File: ") << lmPath << std::endl;
        return nullptr;
    }

    std::string obfuscatedHeaderData(lmData.begin() + LATTE_LENGTH, lmData.begin() + HEADER_LENGTH);
    std::string headerData = ApplyXOR(obfuscatedHeaderData, XOR_KEY);
    return headerData;
}

PVOID LatteModHandler::ConvertDll(const std::string& lmPath, const std::string& key) {
    auto lmData = ReadFile(lmPath);
    if (lmData.size() <= HEADER_LENGTH) return nullptr;

    std::string latteCheck(lmData.begin(), lmData.begin() + LATTE_LENGTH);
    if (latteCheck != "LATTE") {
        std::cout << skCrypt("[!] Invalid Latte Mod File: ") << lmPath << std::endl;
        return nullptr;
    }

    std::string obfuscatedHeaderData(lmData.begin() + LATTE_LENGTH, lmData.begin() + HEADER_LENGTH);
    std::string headerData = ApplyXOR(obfuscatedHeaderData, XOR_KEY);

    std::vector<uint8_t> encryptedData(lmData.begin() + HEADER_LENGTH, lmData.end());
    std::vector<uint8_t> decryptedData;

    if (headerData.substr(0, 2) == "E4") {
        //std::cout << "[+] UUID: [" << headerData << "]\n";
        if (key == "none") {
            std::cout << skCrypt("[!] No decryption key specified, when one is required!\n");
            return nullptr;
        }
        decryptedData = DecryptData(encryptedData, key);
    }
    else {
        //std::cout << "[+] Decryption key: [" << headerData << "]\n";
        decryptedData = DecryptData(encryptedData, headerData);
    }

    // Allocate memory and copy decrypted data into it
    PVOID modImage = VirtualAlloc(nullptr, decryptedData.size(), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (modImage != nullptr) {
        std::memcpy(modImage, decryptedData.data(), decryptedData.size());
    }
    else {
        std::cout << skCrypt("[!] Failed to allocate memory for mod image.\n");
    }

    return modImage;
}


std::vector<uint8_t> LatteModHandler::DecryptData(const std::vector<uint8_t>& encryptedData, const std::string& key) {
    using namespace CryptoPP;

    if (encryptedData.size() <= AES::BLOCKSIZE) {
        std::cout << skCrypt("[!] Invalid encrypted data!") << std::endl;
        return {};
    }

    if (key.size() < AES::MAX_KEYLENGTH / 8) {
        std::cout << skCrypt("[!] Invalid decryption key!") << std::endl;
        return {};
    }

    byte iv[AES::BLOCKSIZE];
    std::copy(encryptedData.begin(), encryptedData.begin() + AES::BLOCKSIZE, iv);

    SecByteBlock keyBlock(0x00, AES::MAX_KEYLENGTH);
#undef min
    std::memcpy(keyBlock, key.data(), std::min(key.size(), (size_t)AES::MAX_KEYLENGTH));

    std::vector<uint8_t> decryptedData;
    CBC_Mode<AES>::Decryption decryption;

    try {
        decryption.SetKeyWithIV(keyBlock, keyBlock.size(), iv);

        ArraySource(&encryptedData[AES::BLOCKSIZE], encryptedData.size() - AES::BLOCKSIZE, true,
            new StreamTransformationFilter(decryption,
                new VectorSink(decryptedData)
            )
        );
    }
    catch (const CryptoPP::Exception& e) {
        std::cout << skCrypt("[!] Bad decryption key!") << std::endl;
        return {};
    }

    return decryptedData;
}