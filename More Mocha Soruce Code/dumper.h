#pragma once
#include <windows.h>
#include <psapi.h>
#include <iostream>
#include <fstream>

void DumpDLL(const char* dllName, const char* outputFileName) {
	// Get a handle to the current process
	HANDLE hProcess = GetCurrentProcess();

	// Get a list of all modules in the process
	HMODULE hModules[1024];
	DWORD cbNeeded;
	if (!EnumProcessModules(hProcess, hModules, sizeof(hModules), &cbNeeded)) {
		std::cout << "Failed to enumerate process modules.\n";
		return;
	}

	// Iterate through the modules to find the target DLL
	for (unsigned int i = 0; i < (cbNeeded / sizeof(HMODULE)); ++i) {
		char moduleName[MAX_PATH];
		if (GetModuleFileNameExA(hProcess, hModules[i], moduleName, sizeof(moduleName) / sizeof(char))) {
			// Check if the current module is the target DLL
			if (strstr(moduleName, dllName)) {
				// Get module information
				MODULEINFO modInfo;
				if (GetModuleInformation(hProcess, hModules[i], &modInfo, sizeof(modInfo))) {
					std::cout << "Found DLL: " << moduleName << "\n";
					std::cout << "Base Address: " << modInfo.lpBaseOfDll << "\n";
					std::cout << "Size: " << modInfo.SizeOfImage << " bytes\n";

					// Dump the DLL memory to a file
					std::ofstream outputFile(outputFileName, std::ios::binary);
					if (!outputFile) {
						std::cout << "Failed to create output file.\n";
						return;
					}

					// Read the memory of the DLL
					outputFile.write(reinterpret_cast<const char*>(modInfo.lpBaseOfDll), modInfo.SizeOfImage);
					outputFile.close();

					std::cout << "Dumped DLL to: " << outputFileName << "\n";
				}
				else {
					std::cout << "Failed to get module information.\n";
				}
				return;
			}
		}
	}

	std::cout << "DLL not found: " << dllName << "\n";
}