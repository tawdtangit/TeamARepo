// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <Stdio.h>
#include <Conio.h>
#include <Winbio.h>
#include <Lmcons.h>
#include <map>
#include <vector>
#include <list>
#include<atlstr.h>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <tchar.h>
#include <locale.h>

using namespace std;

vector<string> BlockSetup(vector<string> curr_blocked)
{
    if (curr_blocked.size() != 0)
    {
        for (vector<string>::const_iterator iterator = curr_blocked.begin(); iterator != curr_blocked.end(); ++iterator)
        {
            // unblock everything here
        }
    }

    string input = "";
    vector<string> BLOCK_LIST;
    while (true)
    {
        cout << "Sites to block: ? (q to pass)" << endl;
        cin >> input;
        if (input == "s")
        {
            break;
        }
        if (strstr(input.c_str(), "http") == NULL)
        {
            input = "https://" + input + "/";
        }
        BLOCK_LIST.push_back(input);
    }

    if (BLOCK_LIST.size() != 0)
    {
        for (vector<string>::const_iterator iterator = BLOCK_LIST.begin(); iterator != BLOCK_LIST.end(); ++iterator)
        {
            // block everything here
        }
    }

    return BLOCK_LIST;
}

map<string, vector<string>> RunSetup()
{
    map<string, vector<string>> activities;
    string input = "";

    vector<string> RH_INDEX_FINGER;
    while (true)
    {
        cout << "RH INDEX FINGER: ? (s to proceed to next finger)" << endl;
        cin >> input;
        if (input == "s")
        {
            break;
        }
        if (strstr(input.c_str(), "http") == NULL)
        {
            input = "https://" + input + "/";
        }
        RH_INDEX_FINGER.push_back(input);
    }
    activities["RH_INDEX_FINGER"] = RH_INDEX_FINGER;

    vector<string> RH_MIDDLE_FINGER;
    while (true)
    {
        cout << "RH MIDDLE FINGER: ? (s to proceed to next finger) " << endl;
        cin >> input;
        if (input == "s")
        {
            break;
        }
        if (strstr(input.c_str(), "http") == NULL)
        {
            input = "https://" + input + "/";
        }
        RH_MIDDLE_FINGER.push_back(input);
    }
    activities["RH_MIDDLE_FINGER"] = RH_MIDDLE_FINGER;

    vector<string> RH_RING_FINGER;
    while (true)
    {
        cout << "RH RING FINGER: ? (s to proceed to next finger)" << endl;
        cin >> input;
        if (input == "s")
        {
            break;
        }
        if (strstr(input.c_str(), "http") == NULL)
        {
            input = "https://" + input + "/";
        }
        RH_RING_FINGER.push_back(input);
    }
    activities["RH_RING_FINGER"] = RH_RING_FINGER;

    vector<string> LH_INDEX_FINGER;
    while (true)
    {
        cout << "LH INDEX FINGER: ? (s to proceed to next finger)" << endl;
        cin >> input;
        if (input == "s")
        {
            break;
        }
        if (strstr(input.c_str(), "http") == NULL)
        {
            input = "https://" + input + "/";
        }
        LH_INDEX_FINGER.push_back(input);
    }
    activities["LH_INDEX_FINGER"] = LH_INDEX_FINGER;

    vector<string> LH_MIDDLE_FINGER;
    while (true)
    {
        cout << "LH MIDDLE FINGER: ? (s to proceed to next finger)" << endl;
        cin >> input;
        if (input == "s")
        {
            break;
        }
        if (strstr(input.c_str(), "http") == NULL)
        {
            input = "https://" + input + "/";
        }
        LH_MIDDLE_FINGER.push_back(input);
    }
    activities["LH_MIDDLE_FINGER"] = LH_MIDDLE_FINGER;

    vector<string> LH_RING_FINGER;
    while (true)
    {
        cout << "LH RING FINGER: ? (s to proceed to next finger)" << endl;
        cin >> input;
        if (input == "s")
        {
            break;
        }
        if (strstr(input.c_str(), "http") == NULL)
        {
            input = "https://" + input + "/";
        }
        LH_RING_FINGER.push_back(input);
    }
    activities["LH_RING_FINGER"] = LH_RING_FINGER;

    return activities;
}

//HRESULT RunScript(string username, map<string, vector<string>> activities)
map<string, vector<string>> RunScript(string username, map<string, vector<string>> activities)
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
    vector<string> blocked_sites;


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
                    case WINBIO_ANSI_381_POS_RH_INDEX_FINGER:
                        for (vector<string>::const_iterator iterator = activities["RH_INDEX_FINGER"].begin(); iterator != activities["RH_INDEX_FINGER"].end(); ++iterator)
                        {
                            if (strstr((*iterator).c_str(), "C:/") != NULL)
                            {
                                ShellExecuteA(0, 0, "chrome.exe", (*iterator).c_str(), 0, SW_SHOWMAXIMIZED);
                            }
                            else
                            {
                                ShellExecuteA(0, 0, (*iterator).c_str(), 0, 0, SW_SHOWMAXIMIZED);
                            }
                        }
                        break;
                    case WINBIO_ANSI_381_POS_RH_MIDDLE_FINGER:
                        for (vector<string>::const_iterator iterator = activities["RH_MIDDLE_FINGER"].begin(); iterator != activities["RH_MIDDLE_FINGER"].end(); ++iterator)
                        {
                            if (strstr((*iterator).c_str(), "C:/") != NULL)
                            {
                                ShellExecuteA(0, 0, "chrome.exe", (*iterator).c_str(), 0, SW_SHOWMAXIMIZED);
                            }
                            else
                            {
                                ShellExecuteA(0, 0, (*iterator).c_str(), 0, 0, SW_SHOWMAXIMIZED);
                            }
                        }
                        break;
                    case WINBIO_ANSI_381_POS_RH_RING_FINGER:
                        for (vector<string>::const_iterator iterator = activities["RH_RING_FINGER"].begin(); iterator != activities["RH_RING_FINGER"].end(); ++iterator)
                        {
                            if (strstr((*iterator).c_str(), "C:/") != NULL)
                            {
                                ShellExecuteA(0, 0, "chrome.exe", (*iterator).c_str(), 0, SW_SHOWMAXIMIZED);
                            }
                            else
                            {
                                ShellExecuteA(0, 0, (*iterator).c_str(), 0, 0, SW_SHOWMAXIMIZED);
                            }
                        }
                        break;
                    case WINBIO_ANSI_381_POS_LH_INDEX_FINGER:
                        for (vector<string>::const_iterator iterator = activities["LH_INDEX_FINGER"].begin(); iterator != activities["LH_INDEX_FINGER"].end(); ++iterator)
                        {
                            if (strstr((*iterator).c_str(), "C:/") != NULL)
                            {
                                ShellExecuteA(0, 0, "chrome.exe", (*iterator).c_str(), 0, SW_SHOWMAXIMIZED);
                            }
                            else
                            {
                                ShellExecuteA(0, 0, (*iterator).c_str(), 0, 0, SW_SHOWMAXIMIZED);
                            }
                        }
                        break;
                    case WINBIO_ANSI_381_POS_LH_MIDDLE_FINGER:
                        for (vector<string>::const_iterator iterator = activities["LH_MIDDLE_FINGER"].begin(); iterator != activities["LH_MIDDLE_FINGER"].end(); ++iterator)
                        {
                            if (strstr((*iterator).c_str(), "C:/") != NULL)
                            {
                                ShellExecuteA(0, 0, "chrome.exe", (*iterator).c_str(), 0, SW_SHOWMAXIMIZED);
                            }
                            else
                            {
                                ShellExecuteA(0, 0, (*iterator).c_str(), 0, 0, SW_SHOWMAXIMIZED);
                            }
                        }
                        break;
                    case WINBIO_ANSI_381_POS_LH_RING_FINGER:
                        for (vector<string>::const_iterator iterator = activities["RH_LITTLE_FINGER"].begin(); iterator != activities["RH_LITTLE_FINGER"].end(); ++iterator)
                        {
                            if (strstr((*iterator).c_str(), "C:/") != NULL)
                            {
                                ShellExecuteA(0, 0, "chrome.exe", (*iterator).c_str(), 0, SW_SHOWMAXIMIZED);
                            }
                            else
                            {
                                ShellExecuteA(0, 0, (*iterator).c_str(), 0, 0, SW_SHOWMAXIMIZED);
                            }
                        }
                        break;
                    case WINBIO_ANSI_381_POS_RH_THUMB:
                        blocked_sites = BlockSetup(blocked_sites);
                        break;
                    case WINBIO_ANSI_381_POS_LH_THUMB:
                        return RunSetup();
                        break;
                    case WINBIO_ANSI_381_POS_RH_LITTLE_FINGER:
                        ShellExecuteA(0, 0, "C:/Users/Todd/Documents/Visual Studio 2015/Projects/ConsoleApplication2/ConsoleApplication2/killall.bat", 0, 0, SW_SHOWMAXIMIZED);
                        break;
                    case WINBIO_ANSI_381_POS_LH_LITTLE_FINGER:
                        system("shutdown /l /f");
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
    return activities;
    // return hr;
}
int main(int argc, char* argv[])
{
    TCHAR username[UNLEN + 1];
    DWORD username_len = UNLEN + 1;
    GetUserName(username, &username_len);
    wstring temp(&username[0]);
    string name(temp.begin(), temp.end());
    map<string, vector<string>> activities;

    vector<string> RH_INDEX_FINGER;
    RH_INDEX_FINGER.push_back("https://piazza.com/");
    RH_INDEX_FINGER.push_back("http://bcourses.berkeley.edu/");
    RH_INDEX_FINGER.push_back("http://bconnected.berkeley.edu/");
    activities["RH_INDEX_FINGER"] = RH_INDEX_FINGER;

    vector<string> RH_MIDDLE_FINGER;
    RH_MIDDLE_FINGER.push_back("http://youtube.com/");
    RH_MIDDLE_FINGER.push_back("http://reddit.com/r/aww");
    activities["RH_MIDDLE_FINGER"] = RH_MIDDLE_FINGER;

    vector<string> RH_RING_FINGER;
    RH_RING_FINGER.push_back("http://facebook.com/");
    RH_RING_FINGER.push_back("http://twitter.com/");
    activities["RH_RING_FINGER"] = RH_RING_FINGER;

    vector<string> LH_INDEX_FINGER;
    LH_INDEX_FINGER.push_back("http://google.com/");
    LH_INDEX_FINGER.push_back("http://google.com/");
    LH_INDEX_FINGER.push_back("http://google.com/");
    activities["LH_INDEX_FINGER"] = LH_INDEX_FINGER;

    vector<string> LH_MIDDLE_FINGER;
    LH_MIDDLE_FINGER.push_back("http://netflix.com/ --incognito");
    activities["LH_MIDDLE_FINGER"] = LH_MIDDLE_FINGER;

    vector<string> LH_RING_FINGER;
    LH_RING_FINGER.push_back("https://www.reddit.com/r/gaming/");
    LH_RING_FINGER.push_back("http://oldschool.runescape.com/");
    LH_RING_FINGER.push_back("C:/Program Files (x86)/Steam/Steam.exe");
    activities["LH_RING_FINGER"] = LH_RING_FINGER;

    cout << "Default settings loaded!" << endl;
    cout << "Scan LH THUMB to set or reset settings." << endl;
    cout << "Scan RH THUMB to set or reset blocked sites" << endl;

    while (true)
        activities = RunScript(name, activities);
    return 0;
}