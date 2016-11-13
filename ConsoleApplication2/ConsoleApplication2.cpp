// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <Stdio.h>
#include <Conio.h>
#include <Winbio.h>
HRESULT LogonIdentifiedUser()
{
	// Declare variables.
	HRESULT hr;
	WINBIO_SESSION_HANDLE sessionHandle = NULL;
	WINBIO_UNIT_ID  UnitId;
	WINBIO_IDENTITY Identity;
	WINBIO_BIOMETRIC_SUBTYPE SubFactor;
	WINBIO_REJECT_DETAIL RejectDetail;
	BOOL    bContinue = TRUE;

	// Connect to the system pool. 
	hr = WinBioOpenSession(
		WINBIO_TYPE_FINGERPRINT,    // Service provider
		WINBIO_POOL_SYSTEM,         // Pool type
		WINBIO_FLAG_DEFAULT,        // Configuration and access
		NULL,                       // Array of biometric unit IDs
		0,                          // Count of biometric unit IDs
		WINBIO_DB_DEFAULT,                       // Database ID
		&sessionHandle              // [out] Session handle
		);
	if (FAILED(hr))
	{
		wprintf_s(L"\n WinBioOpenSession failed. hr = 0x%x\n", hr);
		goto e_Exit;
	}

	// Locate the biometric sensor and retrieve a WINBIO_IDENTITY object.
	// You must swipe your finger on the sensor.
	wprintf_s(L"\n Calling WinBioIdentify - Swipe finger on sensor...\n");
	while (bContinue)
	{
		hr = WinBioIdentify(
			sessionHandle,          // Session handle    
			&UnitId,                // Biometric unit ID
			&Identity,              // User SID or GUID
			&SubFactor,             // Finger sub factor
			&RejectDetail           // rejection information
			);

		switch (hr)
		{
		case S_OK:
			bContinue = FALSE;
			break;
		default:
			wprintf_s(L"\n WinBioIdentify failed. hr = 0x%x\n", hr);
			break;
		}
	}

	if (SUCCEEDED(hr))
	{
		// Switch to the target after receiving a good identity.
		hr = WinBioLogonIdentifiedUser(sessionHandle);

		switch (hr)
		{
		case S_FALSE:
			printf("\n Target is the logged on user. No action taken.\n");
			break;
		case S_OK:
			printf("\n Fast user switch initiated.\n");
			break;
		default:
			wprintf_s(L"\n WinBioLogonIdentifiedUser failed. hr = 0x%x\n", hr);
			break;
		}
	}

e_Exit:

	if (sessionHandle != NULL)
	{
		WinBioCloseSession(sessionHandle);
		sessionHandle = NULL;
	}

	wprintf_s(L"\n Press any key to exit...");
	//_getch();

	return hr;
}
int main()
{
	while(true)
	LogonIdentifiedUser();
    return 0;
}






