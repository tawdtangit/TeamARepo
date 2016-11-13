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
	WINBIO_BIOMETRIC_SUBTYPE SubFactorComp;
	PWINBIO_BIOMETRIC_SUBTYPE subFactorArray;
	SIZE_T subFactorCount;
	WINBIO_REJECT_DETAIL RejectDetail;
	WINBIO_BIOMETRIC_SUBTYPE subFactor = WINBIO_SUBTYPE_NO_INFORMATION;
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
		hr = WinBioEnumEnrollments( 
            sessionHandle,              // Session handle
            unitId,                     // Biometric unit ID
            &Identity,                  // Template ID
            &subFactorArray,            // Subfactors
            &subFactorCount             // Count of subfactors
            );
    	if (FAILED(hr))
	    {
	        wprintf_s(L"\n WinBioEnumEnrollments failed. hr = 0x%x\n", hr);
	        goto e_Exit;
	    }

	    // Print the sub-factor(s) to the console.
	    wprintf_s(L"\n Enrollments for this user on Unit ID %d:", unitId);
	    for (SIZE_T index = 0; index < subFactorCount; ++index)
	    {
	        SubFactorComp = subFactorArray[index];
	        if (SubFactor == SubFactorComp)
	        {
		        switch (SubFactor)
		        {
		            case WINBIO_ANSI_381_POS_RH_THUMB:
		                ShellExecuteA(0,0,"chrome.exe","http://google.com  --incognito",0,SW_SHOWMAXIMIZED);
		                break;
		            case WINBIO_ANSI_381_POS_RH_INDEX_FINGER:
		                ShellExecuteA(0,0,"chrome.exe","http://facebook.com  --incognito",0,SW_SHOWMAXIMIZED);
		                break;
		            case WINBIO_ANSI_381_POS_RH_MIDDLE_FINGER:
		                ShellExecuteA(0,0,"chrome.exe","http://youtube.com  --incognito",0,SW_SHOWMAXIMIZED);
		                break;
		            case WINBIO_ANSI_381_POS_RH_RING_FINGER:
		                ShellExecuteA(0,0,"chrome.exe","http://linkedin.com  --incognito",0,SW_SHOWMAXIMIZED);
		                break;
		            case WINBIO_ANSI_381_POS_RH_LITTLE_FINGER:
		                ShellExecuteA(0,0,"chrome.exe","http://twitter.com  --incognito",0,SW_SHOWMAXIMIZED);
		                break;
		            case WINBIO_ANSI_381_POS_LH_THUMB:
		                ShellExecuteA(0,0,"chrome.exe","http://stackoverflow.com  --incognito",0,SW_SHOWMAXIMIZED);
		                break;
		            case WINBIO_ANSI_381_POS_LH_INDEX_FINGER:
		                ShellExecuteA(0,0,"chrome.exe","http://github.com  --incognito",0,SW_SHOWMAXIMIZED);
		                break;
		            case WINBIO_ANSI_381_POS_LH_MIDDLE_FINGER:
		                ShellExecuteA(0,0,"chrome.exe","http://bitbucket.com  --incognito",0,SW_SHOWMAXIMIZED);
		                break;
		            case WINBIO_ANSI_381_POS_LH_RING_FINGER:
		                ShellExecuteA(0,0,"chrome.exe","http://piazza.com  --incognito",0,SW_SHOWMAXIMIZED);
		                break;
		            case WINBIO_ANSI_381_POS_LH_LITTLE_FINGER:
		                ShellExecuteA(0,0,"chrome.exe","http://pinterest.com  --incognito",0,SW_SHOWMAXIMIZED);7
		                break;
		            default:
		                wprintf_s(L"\n   The sub-factor is not correct\n");
		                break;
		        }
		    }
	 
	    }

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






