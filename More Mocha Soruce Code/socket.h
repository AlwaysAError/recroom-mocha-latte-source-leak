#pragma once

#include <winsock.h>
#include <iostream>

#include <cryptopp/eccrypto.h>
#include <cryptopp/oids.h>
#include <cryptopp/osrng.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>
#include <cryptopp/secblock.h>
#include <cryptopp/files.h>

#include "cryptopp/cryptlib.h"
#include "cryptopp/aes.h"
#include "cryptopp/modes.h"
#include "cryptopp/filters.h"
#include "cryptopp/osrng.h"
#include "cryptopp/hex.h"
#include "cryptopp/md5.h"
#include "cryptopp/rsa.h"
#include <functional>
#define PORT 1447
#define BUFFER_SIZE 512

#define ENCRYPT_KEY "EvvrZtkRCfkfYrPAoFrrP3XBYgeWxVzerKRQ8fY9"

std::string DecryptData(const std::string& hexEncryptedText, const std::string& key) {
    using namespace CryptoPP;

    // Decode the hex-encoded encrypted data
    std::vector<BYTE> encryptedData;
    StringSource ss(hexEncryptedText, true,
        new HexDecoder(
            new VectorSink(encryptedData)
        )
    );

    if (encryptedData.size() <= AES::BLOCKSIZE + 32) {
        printf("[!] Layer-2: bad encrypted data!\n");
        return {};
    }

    if (key.size() < AES::MAX_KEYLENGTH / 8) {
        printf("[!] Layer-2: bad decryption key!\n");
        return {};
    }

    // Extract IV from the start
    BYTE iv[AES::BLOCKSIZE];
    std::copy(encryptedData.begin(), encryptedData.begin() + AES::BLOCKSIZE, iv);

    // Extract the random data from the end
    std::vector<BYTE> randomData(32);
    std::copy(encryptedData.end() - 32, encryptedData.end(), randomData.begin());

    // Hash the random data with SHA-256
    SHA256 sha256;
    std::vector<BYTE> sha256Hash(SHA256::DIGESTSIZE);
    sha256.CalculateDigest(sha256Hash.data(), randomData.data(), randomData.size());

    // Hash the SHA-256 hash with MD5 to derive the IV
    MD5 md5;
    std::vector<BYTE> derivedIV(MD5::DIGESTSIZE);
    md5.CalculateDigest(derivedIV.data(), sha256Hash.data(), sha256Hash.size());

    // Prepare the AES key
    SecByteBlock keyBlock(AES::MAX_KEYLENGTH);
    std::memcpy(keyBlock, key.data(), min(key.size(), (size_t)AES::MAX_KEYLENGTH));

    // Decrypt the data
    std::vector<BYTE> decryptedData;
    CBC_Mode<AES>::Decryption decryption;

    try {
        decryption.SetKeyWithIV(keyBlock, keyBlock.size(), derivedIV.data());

        StringSource(&encryptedData[AES::BLOCKSIZE], encryptedData.size() - AES::BLOCKSIZE - 32, true,
            new StreamTransformationFilter(decryption,
                new VectorSink(decryptedData)
            )
        );
    }
    catch (const CryptoPP::Exception& e) {
        printf("[!] Layer-2: decryption error: %s\n", e.what());
        return {};
    }

    // Convert decrypted data to string
    return std::string(decryptedData.begin(), decryptedData.end());
}

void SocketThread(void* null) {

    WSADATA wsaData;
    int iResult;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        return;
    }

    // Create the server socket
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        WSACleanup();
        return;
    }

    // Set up the address structure
    sockaddr_in serverAddr = {};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Bind to any available network interface
    serverAddr.sin_port = htons(PORT);      // Convert port to network byte order

    // Bind the socket
    iResult = bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)); /// fake error. project will compile.
    if (iResult == SOCKET_ERROR) {
        closesocket(serverSocket);
        WSACleanup();
        return;
    }

    // Listen for incoming connections
    iResult = listen(serverSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        closesocket(serverSocket);
        WSACleanup();
        return;
    }

    // Accept a client socket
    sockaddr_in clientAddr = {};
    int clientAddrSize = sizeof(clientAddr);
    SOCKET clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);
    if (clientSocket == INVALID_SOCKET) {
        closesocket(serverSocket);
        WSACleanup();
        return;
    }

    // Receive the encrypted message
    char encryptedBuffer[BUFFER_SIZE];
    int bytesReceived = recv(clientSocket, encryptedBuffer, BUFFER_SIZE - 1, 0);
    if (bytesReceived > 0) {
        encryptedBuffer[bytesReceived] = '\0'; // Null-terminate the received encrypted message
        std::string encryptedMessage = std::string(encryptedBuffer);

        // Decrypt the message
        std::string decryptedMessage = DecryptData(encryptedMessage, ENCRYPT_KEY); // Use your Decrypt function

        // Parse the decrypted message: split into key and timestamp
        size_t delimiterPos = decryptedMessage.find('|');
        if (delimiterPos != std::string::npos) {
            std::string key = decryptedMessage.substr(0, delimiterPos);
            std::string timeStr = decryptedMessage.substr(delimiterPos + 1);

            time_t receivedTime = std::stol(timeStr);
            time_t currentTime = time(nullptr);
            int timeDifference = static_cast<int>(currentTime - receivedTime);

            // Check time difference
            if (timeDifference < 30) {

                if (key.find("clothing") != std::string::npos)
                    clothingEnabled = true;
            }
        }
        else {
            std::cout << "[L-2] Failed decryption!" << std::endl;
        }
    }
    else {
        std::cout << "[L-2] Failed code: 0x31!" << std::endl;
    }

    // Cleanup
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
}