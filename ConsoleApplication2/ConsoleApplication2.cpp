// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <Stdio.h>
#include <Conio.h>
#include <Winbio.h>

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

std::string exec(const char* cmd) {
	char buffer[128];
	std::string result = "";
	std::shared_ptr<FILE> pipe(_popen(cmd, "r"), _pclose);
	if (!pipe) throw std::runtime_error("popen() failed!");
	while (!feof(pipe.get())) {
		if (fgets(buffer, 128, pipe.get()) != NULL)
			result += buffer;
	}
	return result;
}
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
	    hr = WinBioLogonIdentifiedUser(sessionHandle);

		switch (hr)
		{
			case S_FALSE:
				hr = WinBioEnumEnrollments( 
		            sessionHandle,              // Session handle
		            UnitId,                     // Biometric unit ID
		            &Identity,                  // Template ID
		            &subFactorArray,            // Subfactors
		            &subFactorCount             // Count of subfactors
		            );
		    	if (FAILED(hr))
			    {
			        wprintf_s(L"\n WinBioEnumEnrollments failed. hr = 0x%x\n", hr);
			        goto e_Exit;
			    }

			    wprintf_s(L"\n Enrollments for this user on Unit ID %d:", UnitId);
			    for (SIZE_T index = 0; index < subFactorCount; ++index)
			    {
			        SubFactorComp = subFactorArray[index];
			        if (SubFactor == SubFactorComp)
			        {
						
				        switch (SubFactor)
				        {
				            case WINBIO_ANSI_381_POS_RH_THUMB:	//switch user account
								//std::string command = ;
								//exec("wmic useraccount where sid = " + Identity + " get name");
								
				                //ShellExecuteA(0,0,"chrome.exe","http://google.com  --incognito",0,SW_SHOWMAXIMIZED);
				                break;
				            case WINBIO_ANSI_381_POS_RH_INDEX_FINGER:	//study mode
				                ShellExecuteA(0,0,"chrome.exe","https://piazza.com/ --incognito",0,SW_SHOWMAXIMIZED);
								ShellExecuteA(0, 0, "chrome.exe", "https://bcourses.berkeley.edu/ --incognito", 0, SW_SHOWMAXIMIZED);
								ShellExecuteA(0, 0, "chrome.exe", "https://bconnected.berkeley.edu/  --incognito", 0, SW_SHOWMAXIMIZED);
				                break;
				            case WINBIO_ANSI_381_POS_RH_MIDDLE_FINGER: //destress mode
				                ShellExecuteA(0,0,"chrome.exe","http://youtube.com  --incognito",0,SW_SHOWMAXIMIZED);
								ShellExecuteA(0, 0, "chrome.exe", "https://www.reddit.com/r/aww/  --incognito", 0, SW_SHOWMAXIMIZED);
								ShellExecute(0, 0, L"C:/Users/Todd/AppData/Roaming/Spotify/Spotify.exe", 0, 0, SW_SHOW);
				                break;
				            case WINBIO_ANSI_381_POS_RH_RING_FINGER:	//social mode
				                ShellExecuteA(0,0,"chrome.exe","http://facebook.com  --incognito",0,SW_SHOWMAXIMIZED);
								ShellExecuteA(0, 0, "chrome.exe", "http://twitter.com  --incognito", 0, SW_SHOWMAXIMIZED);
								//ShellExecute(0, 0, L"INSERT PATH NAME HERE", 0, 0, SW_SHOW);
								
				                break;
				            case WINBIO_ANSI_381_POS_RH_LITTLE_FINGER: //gamer mode
								ShellExecute(0, 0, L"C:/Program Files (x86)/Steam/Steam.exe", 0, 0, SW_SHOW);
								ShellExecuteA(0, 0, "chrome.exe", "https://www.reddit.com/r/gaming/  --incognito", 0, SW_SHOWMAXIMIZED);
								ShellExecuteA(0, 0, "chrome.exe", "http://oldschool.runescape.com  --incognito", 0, SW_SHOWMAXIMIZED);
								break;
				            case WINBIO_ANSI_381_POS_LH_THUMB: //shopping mode
				                ShellExecuteA(0,0,"chrome.exe","http://amazon.com  --incognito",0,SW_SHOWMAXIMIZED);
								ShellExecuteA(0, 0, "chrome.exe", "http://bestbuy.com  --incognito", 0, SW_SHOWMAXIMIZED);
								ShellExecuteA(0, 0, "chrome.exe", "http://newegg.com  --incognito", 0, SW_SHOWMAXIMIZED);
								break;
				            case WINBIO_ANSI_381_POS_LH_INDEX_FINGER: //netflix and chill mode
				                ShellExecuteA(0,0,"chrome.exe","http://netflix.com  --incognito",0,SW_SHOWMAXIMIZED);
				                break;
				            case WINBIO_ANSI_381_POS_LH_MIDDLE_FINGER: //News mode
				                ShellExecuteA(0,0,"chrome.exe","http://yahoo.com/news/  --incognito",0,SW_SHOWMAXIMIZED);
								ShellExecuteA(0, 0, "chrome.exe", "http://cnn.com  --incognito", 0, SW_SHOWMAXIMIZED);
								ShellExecuteA(0, 0, "chrome.exe", "http://bbc.com  --incognito", 0, SW_SHOWMAXIMIZED);
				                break;
				            case WINBIO_ANSI_381_POS_LH_RING_FINGER: //close all
				                break;
				            case WINBIO_ANSI_381_POS_LH_LITTLE_FINGER: //logout
				                break;
				            default:
				                wprintf_s(L"\n   The sub-factor is not correct\n");
				                break;
				        }
				    }
				}
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






