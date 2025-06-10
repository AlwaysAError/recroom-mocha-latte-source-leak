#include "injector.hpp"
#include <iostream>
#include <TlHelp32.h>
#include <string>
#include <filesystem>
#include <windows.h>

bool load(SOCKET connection)
{
	std::wstring currentDir = std::filesystem::current_path().wstring();
	std::wstring modsDir = currentDir + L"\\Mods";
	std::wstring configFile = currentDir + L"\\config.txt";

	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "[+] Searching for Mods...\n";
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	if (!std::filesystem::exists(modsDir)) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << "[!] Mods folder can't be found, attempting to make one.\n";
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		try {
			if (!std::filesystem::create_directory(modsDir)) {
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
				std::cout << "[!] Failed to create Mods folder.\n";
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				return false;
			}
			else {
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				std::wcout << "[+] Sucessfully created Mods folder at: \"" << modsDir << "\".\n";
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				std::cout << "[/] Place your Mods in the Mods folder and restart Latte.\n";
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				return false;
			}
		}
		catch (const std::filesystem::filesystem_error& e) {
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
			std::cout << "[!] Error creating Mods folder: " << e.what() << std::endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			return false;
		}
	}

	std::vector<std::wstring> dllFilePaths;

	for (const auto& entry : std::filesystem::directory_iterator(modsDir)) {
		if (entry.path().extension() == L".dll") {
			dllFilePaths.push_back(entry.path().wstring());
		}
	}

	std::ifstream config(configFile);
	std::wstring prefix = L"path: \"";
	if (config) {
		std::string line;
		while (std::getline(config, line)) {
			std::wstring wline(line.begin(), line.end());
			if (wline.find(prefix) == 0) {
				std::wstring path = wline.substr(prefix.length(), wline.length() - prefix.length() - 1); // -1 for closing quote
				if (std::filesystem::exists(path)) {
					for (const auto& entry : std::filesystem::directory_iterator(path)) {
						if (entry.path().extension() == L".dll") {
							dllFilePaths.push_back(entry.path().wstring());
						}
					}
				}
				else {
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
					std::wcout << L"[!] Invalid path in config.txt: \"" << path << L"\"\n";
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				}
			}
		}
	}
	else {
		std::ofstream(configFile).close();
	}

	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	switch (dllFilePaths.size()) {
	case 0:
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::wcout << "[-] Error: No Mods Found! Place your Mods in: \"" << modsDir << "\".\n";
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		return false;
	case 1:
		std::cout << "[+] Found 1 Mod!\n";
		break;
	default:
		std::cout << "[+] Found " << dllFilePaths.size() << " Mods!\n";
		break;
	}

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("[/] Focus the Target Process!\n");
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	for (const auto& filePath : dllFilePaths) {
		inject(filePath.c_str(), connection);
	}
	return true; // success
}

int main()
{
	SetConsoleTitle("Latte Loader v1.2");
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	std::cout // don't touch or it'll fuck up the coffe art
		<< " __         ______     ______   ______   ______                                                   .\n"
		<< "/\\ \\       /\\  __ \\   /\\__  _\\ /\\__  _\\ /\\  ___\\                                                   `:.\n"
		<< "\\ \\ \\____  \\ \\  __ \\  \\/_/\\ \\/ \\/_/\\ \\/ \\ \\  __\\             v1.2                                    `:.\n"
		<< " \\ \\_____\\  \\ \\_\\ \\_\\    \\ \\_\\    \\ \\_\\  \\ \\_____\\                                           .:'     ,::\n"
		<< "  \\/_____/   \\/_/\\/_/     \\/_/     \\/_/   \\/_____/                                          .:'      ;:'\n"
		<< "                                                                                            ::      ;:'\n"
		<< "             __         ______     ______     _____     ______     ______                    :    .:'\n"
		<< "            /\\ \\       /\\  __ \\   /\\  __ \\   /\\  __-.  /\\  ___\\   /\\  == \\                    `.  :.\n"
		<< "            \\ \\ \\____  \\ \\ \\/\\ \\  \\ \\  __ \\  \\ \\ \\/\\ \\ \\ \\  __\\   \\ \\  __<           _________________________\n"
		<< "             \\ \\_____\\  \\ \\_____\\  \\ \\_\\ \\_\\  \\ \\____-  \\ \\_____\\  \\ \\_\\ \\_\\        : _ _ _ _ _ _ _ _ _ _ _ _ :\n"
		<< "              \\/_____/   \\/_____/   \\/_/\\/_/   \\/____/   \\/_____/   \\/_/ /_/    ,---:\".\".\".\".\".\".\".\".\".\".\".\".\":\n"
		<< "                                                                               : ,\'\"`::.:.:.:.:.:.:.:.:.:.:.::\'\n"
		<< "                                                                               `.`.  `:-===-===-===-===-===-:'\n"
		<< "                     Written with love by breww <3                                `.`-._:                   :\n"
		<< "                       With big help from Energy :)                                 `-.__`.               ,'\n"
		<< "                                                                               ,--------`\"`-------------'--------.\n"
		<< "                                                                                `\"--.__                   __.--\"'\n"
		<< "                                                                                       `\"\"-------------\"\"'\n"
		<< "\n";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	driver::initialize();

	const auto connection = driver::connect();
	if (connection == INVALID_SOCKET)
	{
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		printf("[!] Error Code: 0x04.\n");
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		driver::disconnect(connection);
		driver::deinitialize();
		std::cin.get();
		return 0;
	}

	driver::clean_piddbcachetable(connection);
	driver::clean_mmunloadeddrivers(connection);

	if (!load(connection)) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		printf("[!] Mod Loader Failed!\n");
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		driver::disconnect(connection);
		driver::deinitialize();
		std::cin.get();
		return 0;
	}
	else {
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		printf("[+] Mod Loading Completed, Cleaning Up...\n");
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	}

	driver::disconnect(connection);
	driver::deinitialize();
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("[+] Finished Cleaning, Bye-Bye!\n");
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cin.get();
}
