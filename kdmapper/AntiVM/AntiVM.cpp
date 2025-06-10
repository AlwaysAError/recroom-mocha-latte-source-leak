#include "AntiVM.h"
#include <iostream>
#include <windows.h>

void AntiVM() noexcept
{
	LPNETRESOURCEA lpnr = NULL;

	if (CheckDevices())
	{
		MessageBox(NULL, L"we be skiddin", L"skid [100]", MB_OK);
		exit(0);
	}

	if (DriverCheck())
	{
		MessageBox(NULL, L"we be skiddin", L"skid [200]", MB_OK);
		exit(0);
	}

	if (ProviderCheck(lpnr))
	{
		MessageBox(NULL, L"we be skiddin", L"skid [300]", MB_OK);
		exit(0);
	}

	if (CheckDlls())
	{
		MessageBox(NULL, L"we be skiddin", L"skid [400]", MB_OK);
		exit(0);
	}
}