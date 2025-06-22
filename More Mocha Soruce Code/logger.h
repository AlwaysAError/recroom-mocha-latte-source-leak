#pragma once
#include <iostream>

#define MY_PI 3.14159265358979323846f
//#define pldebug
#define ENERGY

namespace Log {
    std::mutex logMutex;
    bool logfileEnabled = true;

    // Function to initialize log file management
    void init() {
        std::lock_guard<std::mutex> guard(logMutex); // Ensure thread safety

        std::filesystem::path logPath("log.txt");
        std::filesystem::path prevLogPath("log-prev.txt");

        // Check if prev-log.txt exists and delete it
        if (std::filesystem::exists(prevLogPath)) {
            std::filesystem::remove(prevLogPath);
        }

        // Check if log.txt exists and rename it to prev-log.txt
        if (std::filesystem::exists(logPath)) {
            std::filesystem::rename(logPath, prevLogPath);
        }
    }

    void writeToLogFile(const std::string& message) {
        std::lock_guard<std::mutex> guard(logMutex);
        std::ofstream logFile("log.txt", std::ios_base::app);
        if (logFile.is_open()) {
            logFile << message << std::endl;
            logFile.close();
        }
    }

    void logAsync(const std::string& prefixSymbol, const std::string& message) {
        std::lock_guard<std::mutex> guard(logMutex);

        if (logfileEnabled) {
            std::ofstream logFile("log.txt", std::ios_base::app);
            if (logFile.is_open()) {
                logFile << "[" + prefixSymbol + "] " + message << std::endl;
            }
        }

        std::cout << "[" << prefixSymbol << "] " << message << std::endl;
    }

    // we only want to log errors in prod

    void error(const std::string& message) {
#ifndef PROD
        logAsync("-", "Error: " + message);
#endif
    }

    void prod(const std::string& message) {
        logAsync(">>", "PROD LOG: " + message);
    }

    void debug(const std::string& message) {
#ifndef PROD
        logAsync(">", "Debug: " + message);
#endif
    }

    void log(const std::string& message) {
#ifndef PROD
        logAsync("+", "Log: " + message);
#endif
    }
}