#include "main.h"
#include "injector.hpp"
#include <Windows.h>
#include <string>
#include <Thread>
#include <winreg.h>
#include <cstdlib>
#include <conio.h>
#include <random>
#include <array>
#include <signal.h>

#include <TlHelp32.h>
#include <filesystem>

#include "kdmapper.hpp"
//#include "driver.h"
#include "enc_driver.h"
#include "auth.hpp"
//#include "utils.hpp"
#include "AntiDBG.h"
#include "AntiVM/AntiVM.h"

#include <iomanip>
#include "cryptopp/cryptlib.h"
#include "cryptopp/aes.h"
#include "cryptopp/modes.h"
#include "cryptopp/filters.h"
#include "cryptopp/osrng.h"
#include "cryptopp/hex.h"
#include <algorithm>

#pragma comment(lib, "mpr.lib")


#define  _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

//#include "LatteModHandler.h"


// bsod stuff
#ifdef bsod
extern "C" NTSTATUS NTAPI RtlAdjustPrivilege(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN OldValue);
extern "C" NTSTATUS NTAPI NtRaiseHardError(LONG ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask,
	PULONG_PTR Parameters, ULONG ValidResponseOptions, PULONG Response);

#endif

std::string ReadFromJson(std::string path, std::string section)
{
	if (!std::filesystem::exists(path))
		return skCrypt("File Not Found").decrypt();
	std::ifstream file(path);
	json data = json::parse(file);
	return data[section];
}

bool CheckIfJsonKeyExists(std::string path, std::string section)
{
	if (!std::filesystem::exists(path))
		return skCrypt("File Not Found").decrypt();
	std::ifstream file(path);
	json data = json::parse(file);
	return data.contains(section);
}

bool WriteToJson(std::string path, std::string name, std::string value, bool userpass, std::string name2, std::string value2)
{
	json file;
	if (!userpass)
	{
		file[name] = value;
	}
	else
	{
		file[name] = value;
		file[name2] = value2;
	}

	std::ofstream jsonfile(path, std::ios::out);
	jsonfile << file;
	jsonfile.close();
	if (!std::filesystem::exists(path))
		return false;

	return true;
}

const std::string compilation_date = (std::string)skCrypt(__DATE__);
const std::string compilation_time = (std::string)skCrypt(__TIME__);

using namespace KeyAuth;
std::string name = skCrypt("LatteLoader").decrypt(); // App name
std::string ownerid = skCrypt("6VkKQ7nFeY").decrypt(); // Account ID
std::string version = skCrypt("1.0").decrypt(); // Application version. Used for automatic downloads see video here https://www.youtube.com/watch?v=kW195PLCBKs
std::string url = skCrypt("https://keyauth.win/api/1.3/").decrypt(); // change if using KeyAuth custom domains feature
std::string path = skCrypt("").decrypt(); // (OPTIONAL) see tutorial here https://www.youtube.com/watch?v=I9rxt821gMk&t=1s
api KeyAuthApp(name, ownerid, version, url, path);
HANDLE iqvw64e_device_handle;

std::string title{ (std::string)skCrypt("Latte Loader Public v1.0 by @b1tchmxde  ") };

void title_changer()
{
	while (true)
	{
		std::string completeTitle = title;

		for (int i = 0; i < 10; i++) {
			char randomChar = 'A' + rand() % 26;
			completeTitle += randomChar;
		}

		SetConsoleTitleA(completeTitle.c_str());
		Sleep(1);
	}
}

void watch_dog()
{
	while (true) {
		adbg_IsDebuggerPresent();
		adbg_BeingDebuggedPEB();
		adbg_NtGlobalFlagPEB();
		adbg_CheckRemoteDebuggerPresent();
		adbg_NtQueryInformationProcess();
		adbg_CheckWindowClassName();
		adbg_CheckWindowName();
		adbg_ProcessFileName();
		adbg_NtSetInformationThread();
		adbg_HardwareDebugRegisters();
		adbg_MovSS();
		adbg_RDTSC();
		//adbg_QueryPerformanceCounter(); // random detections lol, only run once for consistentcy
		adbg_GetTickCount();
		adbg_CloseHandleException();
		adbg_SingleStepException();
		adbg_Int3();
		adbg_Int2D();
		adbg_PrefixHop();
		adbg_CrashOllyDbg();
		Sleep(2500);
	}
}

BOOL CtrlHandler(DWORD fdwCtrlType)
{
	if (fdwCtrlType == CTRL_CLOSE_EVENT || CTRL_C_EVENT || CTRL_BREAK_EVENT || CTRL_LOGOFF_EVENT || CTRL_SHUTDOWN_EVENT)
	{

		void deleteFiles();
		return TRUE;
	}
	return FALSE;
}

bool callbackExample(ULONG64* param1, ULONG64* param2, ULONG64 allocationPtr, ULONG64 allocationSize, ULONG64 mdlptr) {
	UNREFERENCED_PARAMETER(param1);
	UNREFERENCED_PARAMETER(param2);
	UNREFERENCED_PARAMETER(allocationPtr);
	UNREFERENCED_PARAMETER(allocationSize);
	UNREFERENCED_PARAMETER(mdlptr);
	//Log("[+] Callback example called" << std::endl);
	return true;
}

bool start();

int main() {
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE);

	
	std::thread([]() noexcept { AntiVM(); }).detach();

	adbg_IsDebuggerPresent();
	adbg_BeingDebuggedPEB();
	adbg_NtGlobalFlagPEB();
	adbg_CheckRemoteDebuggerPresent();
	adbg_NtQueryInformationProcess();
	adbg_CheckWindowClassName();
	adbg_CheckWindowName();
	adbg_ProcessFileName();
	adbg_NtSetInformationThread();
	adbg_HardwareDebugRegisters();
	adbg_MovSS();
	adbg_RDTSC();
	adbg_QueryPerformanceCounter();
	adbg_GetTickCount();
	adbg_CloseHandleException();
	adbg_SingleStepException();
	adbg_Int3();
	adbg_Int2D();
	adbg_PrefixHop();
	adbg_CrashOllyDbg();

	std::thread([]() noexcept { watch_dog(); }).detach();
	std::thread([]() noexcept { title_changer(); }).detach();

	// Freeing memory to prevent memory leak or memory scraping
	name.clear(); ownerid.clear(); version.clear(); url.clear();

	//std::string consoleTitle = skCrypt("Loader - Built at:  ").decrypt() + compilation_date + " " + compilation_time;
	//SetConsoleTitleA(consoleTitle.c_str());

	HWND hwnd = GetConsoleWindow();
	SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(hwnd, 0, 225, LWA_ALPHA);

	std::cout << skCrypt("[+] Connecting...");
	KeyAuthApp.init();
	if (!KeyAuthApp.response.success)
	{
		std::cout << skCrypt("[+] Status: ") << KeyAuthApp.response.message << std::endl;
		Sleep(1500);
		exit(1);
	}

	KeyAuthApp.log(std::string(skCrypt("Latte Loader Started.")));

	system("cls");

	std::string username;
	std::string password;
	std::string key;

	if (std::filesystem::exists("login.json")) //change test.txt to the path of your file :smile:
	{
		if (!CheckIfJsonKeyExists("login.json", "username"))
		{
			std::string key = ReadFromJson("login.json", "license");
			KeyAuthApp.license(key);
			if (!KeyAuthApp.response.success)
			{
				std::remove("login.json");
				std::cout << skCrypt("\n Status: ") << KeyAuthApp.response.message;
				Sleep(1500);
				exit(1);
			}
			KeyAuthApp.log(std::string(skCrypt("Logged In Using Json, key: [")) + key + std::string(skCrypt("].")));
			std::cout << skCrypt("[+] Successfully Automatically Logged In.\n");
		}
		else
		{
			username = ReadFromJson("login.json", "username");
			password = ReadFromJson("login.json", "password");
			KeyAuthApp.login(username, password);
			if (!KeyAuthApp.response.success)
			{
				std::remove("login.json");
				std::cout << skCrypt("[+] Status: ") << KeyAuthApp.response.message << std::endl;
				Sleep(1500);
				exit(1);
			}
			KeyAuthApp.log(std::string(skCrypt("Logged In Using Json, username: [")) + username + std::string(skCrypt("], Password: [")) + password + std::string(skCrypt("].")));
			std::cout << skCrypt("[+] Successfully Automatically Logged In\n");
		}
	}
	else
	{
		std::cout << skCrypt("[1] Login\n[2] Register\n");
		char passchar;

		int option;
		std::cin >> option;
		switch (option) {
		case 1:
			system("cls");
			std::cout << skCrypt("[/] Enter username:\n");
			std::cin >> username;

			system("cls");
			std::cout << skCrypt("[/] Enter password:\n");
			while ((passchar = _getch()) != '\r') {
				if (passchar == '\b' && password.length() != 0) {
					std::cout << "\b \b";
					password.pop_back();
				}
				else if (passchar != '\b') {
					password.push_back(passchar);
					std::cout << '*';
				}
			}
			KeyAuthApp.log(std::string(skCrypt("Logged In Manually, username: [")) + username + std::string(skCrypt("], Password: [")) + password + std::string(skCrypt("].")));
			KeyAuthApp.login(username, password);
			break;
		case 2:
			system("cls");
			std::cout << skCrypt("[/] Enter username:\n");
			std::cin >> username;
			system("cls");
			std::cout << skCrypt("[/] Enter password:\n");
			while ((passchar = _getch()) != '\r') {
				if (passchar == '\b' && password.length() != 0) {
					std::cout << "\b \b";
					password.pop_back();
				}
				else if (passchar != '\b') {
					password.push_back(passchar);
					std::cout << '*';
				}
			}
			system("cls");
			std::cout << skCrypt("[/] Enter license:\n");
			std::cin >> key;

			KeyAuthApp.log(std::string(skCrypt("Registered, username: [")) + username + std::string(skCrypt("], Password: [")) + password + std::string(skCrypt("], key: [")) + key + std::string(skCrypt("].")));
			KeyAuthApp.regstr(username, password, key);
			KeyAuthApp.login(username, password);
			break;
		default:
			system("cls");
			KeyAuthApp.log(std::string(skCrypt("User Made Bad Selection.")));
			std::cout << skCrypt("[!] Invalid Selection.\n");
			Sleep(3000);
			exit(1);
		}
	}
	if (!KeyAuthApp.response.success)
	{
		system("cls");
		std::cout << skCrypt("[+] Status: ") << KeyAuthApp.response.message << std::endl;
		Sleep(1500);
		exit(1);
	}

	if (username.empty() || password.empty())
	{
		WriteToJson("login.json", "license", key, false, "", "");
		KeyAuthApp.log(std::string(skCrypt("Empty Json, created new json.")));
		std::cout << skCrypt("[+] Successfully Created File For Auto Login.\n");
	}
	else
	{
		if (KeyAuthApp.response.success) {
			KeyAuthApp.log(std::string(skCrypt("Created json with username: [")) + username + std::string(skCrypt("], Password: [")) + password + std::string(skCrypt("].")));
			WriteToJson("login.json", "username", username, true, "password", password);
			std::cout << skCrypt("[+] Successfully Created File For Auto Login.\n");
		}
	}

	system("cls");
	if (!start()) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << skCrypt("[!] Loader Error.\n");
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	}

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << skCrypt("[+] Finished. Bye-Bye!\n");
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	Sleep(5000);

	return 0;
}

unsigned char* DecryptData(const unsigned char* encryptedData, unsigned int encryptedSize, const std::string& key) {
	using namespace CryptoPP;

	// Input Validation
	if (encryptedSize <= AES::BLOCKSIZE) {
		std::cout << skCrypt("[!] Invalid encrypted data!") << std::endl;
		return nullptr;
	}

	if (key.size() < AES::MAX_KEYLENGTH / 8) {
		std::cout << skCrypt("[!] Invalid decryption key!") << std::endl;
		return nullptr;
	}

	// Inside DecryptData, before returning:
	//std::cout << "Decrypted Data Size: " << encryptedSize - AES::BLOCKSIZE << " bytes" << std::endl;


	// IV Extraction
	unsigned char iv[AES::BLOCKSIZE];
	std::memcpy(iv, encryptedData, AES::BLOCKSIZE);

	// Key Setup (Note: Potential Zero-Padding)
	SecByteBlock keyBlock(AES::MAX_KEYLENGTH); // Size for full AES key
#undef min
	std::memcpy(keyBlock, key.data(), std::min(key.size(), (size_t)AES::MAX_KEYLENGTH));

	// Decryption Setup
	CBC_Mode<AES>::Decryption decryption;
	decryption.SetKeyWithIV(keyBlock, keyBlock.size(), iv);

	// Allocate Memory for Decrypted Data
	unsigned char* decryptedData = new unsigned char[encryptedSize - AES::BLOCKSIZE];

	// Decryption with Filtering
	try {
		ArraySource(encryptedData + AES::BLOCKSIZE, encryptedSize - AES::BLOCKSIZE, true,
			new StreamTransformationFilter(decryption,
				new ArraySink(decryptedData, encryptedSize - AES::BLOCKSIZE) // Sink into array
			)
		);
	}
	catch (const CryptoPP::Exception& e) {
		std::cout << skCrypt("[!] Bad decryption key!") << std::endl;
		delete[] decryptedData;
		return nullptr;
	}

	return decryptedData;
}

bool LoadDriver() {

	bool free = false;
	bool mdlMode = false;
	bool passAllocationPtr = false;

	if (free) {
		//Log(L"[+] Free pool memory after usage enabled" << std::endl);
	}

	if (mdlMode) {
		//Log(L"[+] Mdl memory usage enabled" << std::endl);
	}

	if (passAllocationPtr) {
		//Log(L"[+] Pass Allocation Ptr as first param enabled" << std::endl);
	}

	iqvw64e_device_handle = intel_driver::Load();

	if (iqvw64e_device_handle == INVALID_HANDLE_VALUE)
		return false;

	const char* uuid = skCrypt("54927e5a-274b-40df-9dde-51da6f2d6ec5");

	std::string key = KeyAuthApp.var(uuid);
	if (!KeyAuthApp.response.success) {
		//std::terminate();
		printf("bad data!\n");
		return false;
	}

	auto driver = DecryptData(driver_data, driver_length, key);

	std::vector<uint8_t> raw_image(driver, driver + driver_length);

	NTSTATUS exitCode = 0;
	if (!kdmapper::MapDriver(iqvw64e_device_handle, raw_image.data(), 0, 0, free, true, mdlMode, passAllocationPtr, callbackExample, &exitCode)) {
		Log(L"[-] Failed to map driver" << std::endl);
		intel_driver::Unload(iqvw64e_device_handle);
		return false;
	}

	if (!intel_driver::Unload(iqvw64e_device_handle)) {
		//Log(L"[-] Warning failed to fully unload vulnerable driver " << std::endl);
		return false;
	}
	//Log(L"[+] success" << std::endl);

	return true;
}

bool load(SOCKET connection)
{

	std::wstring currentDir = std::filesystem::current_path().wstring();
	std::wstring modsDir = currentDir + L"\\Mods";
	std::wstring configFile = currentDir + L"\\config.txt";

	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << skCrypt("[+] Searching for Mods...\n");
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	if (!std::filesystem::exists(modsDir)) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << skCrypt("[!] Mods folder can't be found, attempting to make one.\n");
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		try {
			if (!std::filesystem::create_directory(modsDir)) {
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
				std::cout << skCrypt("[!] Failed to create Mods folder.\n");
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				return false;
			}
			else {
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				KeyAuthApp.log(std::string(skCrypt("Made Mods folder at: [")) + std::string(modsDir.begin(), modsDir.end()) + std::string(skCrypt("].")));
				std::wcout << skCrypt("[+] Sucessfully created Mods folder at: \"") << modsDir << skCrypt("\".\n");
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				std::cout << skCrypt("[/] Place your Mods in the Mods folder and restart Latte.\n");
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				return false;
			}
		}
		catch (const std::filesystem::filesystem_error& e) {
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
			KeyAuthApp.log(std::string(skCrypt("Error Creating Mods folder: [")) + std::string(e.what()) + std::string(skCrypt("].")));
			std::cout << skCrypt("[!] Error creating Mods folder: ") << e.what() << std::endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			return false;
		}
	}

	std::vector<std::wstring> filePaths;

	for (const auto& entry : std::filesystem::directory_iterator(modsDir)) {
		std::filesystem::path filePath = entry.path();
		if (filePath.extension() == L".dll") {
			filePaths.push_back(filePath.wstring());
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
							KeyAuthApp.log(std::string(skCrypt("Found Mod: [")) + entry.path().string() + std::string(skCrypt("].")));
							filePaths.push_back(entry.path().wstring());
						}
					}
				}
				else {
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
					std::wcout << skCrypt("[!] Invalid path in config.txt: \"") << path << skCrypt("\"\n");
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				}
			}
		}
	}
	else {
		std::ofstream(configFile).close();
	}

	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	switch (filePaths.size()) {
	case 0:
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::wcout << skCrypt("[-] Error: No Mods Found! Place your Mods in: \"") << modsDir << skCrypt("\".\n");
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		return false;
	case 1:
		std::cout << skCrypt("[+] Found 1 Mod!\n");
		break;
	default:
		std::cout << skCrypt("[+] Found ") << filePaths.size() << skCrypt(" Mods!\n");
		break;
	}

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf(skCrypt("[/] Focus the Target Process!\n"));
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);


	for (const auto& filePath : filePaths) {
		std::string narrowFilePath;

		int bufferSize = WideCharToMultiByte(CP_UTF8, 0, filePath.c_str(), -1, nullptr, 0, nullptr, nullptr);

		if (bufferSize > 0) {
			std::vector<char> buffer(bufferSize);
			WideCharToMultiByte(CP_UTF8, 0, filePath.c_str(), -1, &buffer[0], bufferSize, nullptr, nullptr);
			narrowFilePath.assign(buffer.begin(), buffer.end() - 1); // skip null
		}

		inject(filePath.c_str(), connection);
	}
	return true; // success
}

void loading_bar(int duration_seconds) {
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	printf(skCrypt("[+] Loading Driver...\n"));
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	int total_steps = 20;
	int step_duration = duration_seconds * 1000 / total_steps;
	int bar_width = 27; // Width of "[####################] 100%"

	for (int i = 0; i <= total_steps; ++i) {
		std::string bar = "[";
		bar += std::string(i, '#');
		bar += std::string(total_steps - i, ' ');
		bar += "]";

		std::cout << "\r" << bar << " " << std::setw(3) << i * 5 << "%" << std::flush;

		std::this_thread::sleep_for(std::chrono::milliseconds(step_duration));
	}

	// Clear the loading bar line
	std::cout << "\r" << std::string(bar_width, ' ') << "\r";
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf(skCrypt("[+] Loading Complete!\n"));
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

bool start() {
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	std::cout // don't touch or it'll fuck up the coffe art
		<< skCrypt(" __         ______     ______   ______   ______                                                   .\n")
		<< skCrypt("/\\ \\       /\\  __ \\   /\\__  _\\ /\\__  _\\ /\\  ___\\                                                   `:.\n")
		<< skCrypt("\\ \\ \\____  \\ \\  __ \\  \\/_/\\ \\/ \\/_/\\ \\/ \\ \\  __\\             v1.0                                    `:.\n")
		<< skCrypt(" \\ \\_____\\  \\ \\_\\ \\_\\    \\ \\_\\    \\ \\_\\  \\ \\_____\\                                           .:'     ,::\n")
		<< skCrypt("  \\/_____/   \\/_/\\/_/     \\/_/     \\/_/   \\/_____/                                          .:'      ;:'\n")
		<< skCrypt("                                                                                            ::      ;:'\n")
		<< skCrypt("             __         ______     ______     _____     ______     ______                    :    .:'\n")
		<< skCrypt("            /\\ \\       /\\  __ \\   /\\  __ \\   /\\  __-.  /\\  ___\\   /\\  == \\                    `.  :.\n")
		<< skCrypt("            \\ \\ \\____  \\ \\ \\/\\ \\  \\ \\  __ \\  \\ \\ \\/\\ \\ \\ \\  __\\   \\ \\  __<           _________________________\n")
		<< skCrypt("             \\ \\_____\\  \\ \\_____\\  \\ \\_\\ \\_\\  \\ \\____-  \\ \\_____\\  \\ \\_\\ \\_\\        : _ _ _ _ _ _ _ _ _ _ _ _ :\n")
		<< skCrypt("              \\/_____/   \\/_____/   \\/_/\\/_/   \\/____/   \\/_____/   \\/_/ /_/    ,---:\".\".\".\".\".\".\".\".\".\".\".\".\":\n")
		<< skCrypt("                                                                               : ,\'\"`::.:.:.:.:.:.:.:.:.:.:.::\'\n")
		<< skCrypt("                                                                               `.`.  `:-===-===-===-===-===-:'\n")
		<< skCrypt("                     Written with love by breww <3                                `.`-._:                   :\n")
		<< skCrypt("                       With big help from Energy :)                                 `-.__`.               ,'\n")
		<< skCrypt("                                                                               ,--------`\"`-------------'--------.\n")
		<< skCrypt("                                                                                `\"--.__                   __.--\"'\n")
		<< skCrypt("                                                                                       `\"\"-------------\"\"'\n")
		<< skCrypt("\n");

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	
	driver::initialize();
	LoadDriver();
	auto connection = driver::connect();
	if (connection == INVALID_SOCKET)
	{
		driver::disconnect(connection);
		driver::deinitialize();
		KeyAuthApp.log(std::string(skCrypt("Loading Driver.")));
		LoadDriver();
		driver::initialize();
		connection = driver::connect();

		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		loading_bar(3);
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		
		if (connection == INVALID_SOCKET) {
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
			KeyAuthApp.log(std::string(skCrypt("0x4 Triggered!")));
			printf(skCrypt("[!] Error Code: 0x04.\n"));
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			driver::disconnect(connection);
			driver::deinitialize();
			Sleep(3000);
			return false;
		}
	}
	else {
		KeyAuthApp.log(std::string(skCrypt("Driver Loaded.")));
	}

	driver::clean_piddbcachetable(connection);
	driver::clean_mmunloadeddrivers(connection);

	if (!load(connection)) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		KeyAuthApp.log(std::string(skCrypt("Mod Loader Failed!")));
		printf(skCrypt("[!] Mod Loader Failed!\n"));
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		driver::disconnect(connection);
		driver::deinitialize();
		Sleep(3000);
		return false;
	}
	else {
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		KeyAuthApp.log(std::string(skCrypt("Mod Loader Completed!")));
		printf(skCrypt("[+] Mod Loading Completed, Cleaning Up...\n"));
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	}

	driver::disconnect(connection);
	driver::deinitialize();
	

	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf(skCrypt("[+] Closing in 5 seconds. Bye-Bye!\n"));
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	Sleep(5000);
	return true;
}

bool BanUser(std::string check) {
	KeyAuthApp.log(std::string(skCrypt("User Ban Check Triggered! Check: ")) + check);
	const char* isDev = skCrypt("isDeveloper");
	std::string response = KeyAuthApp.getvar(isDev);
	if (KeyAuthApp.response.success && (response == std::string(skCrypt("yuh")))) {
		isUserDeveloper = true;
		return false;
	}
	KeyAuthApp.ban("Anti Debug Triggered! Reason: " + check);
	return true;
}