#include "main.h"
#include <windows.h>
#include <Lmcons.h>
#include <fstream>

using namespace std;

//#define PROD
class Init {
public:
    static void initThread();
};

void Init::initThread() {
#ifndef PROD
    AllocConsole();

    // Redirect standard input/output streams
    FILE* stream;
    freopen_s(&stream, "CONIN$", "r", stdin);
    freopen_s(&stream, "CONOUT$", "w", stdout);

    // Set console title
    SetConsoleTitleA("Mocha Mod Console");


    // Enable ANSI escape code support
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        GetConsoleMode(hConsole, &dwMode);
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hConsole, dwMode);
    }
#endif

    Main();
    return;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call != DLL_PROCESS_ATTACH) {
        return false;
    }

    DisableThreadLibraryCalls(hModule);
    Init::initThread();

    return true;
}
