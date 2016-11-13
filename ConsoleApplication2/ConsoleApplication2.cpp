// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <Stdio.h>
#include <Conio.h>
#include <Winbio.h>
#include <Lmcons.h>
#include <map>

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

using namespace std;

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

HRESULT RunScript(const char* username, std::map activites)
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
                            case WINBIO_ANSI_381_POS_RH_THUMB: //default
                                for (std::vector<T>::const_iterator iterator = activities["RH_THUMB"].begin(); iterator != activities["RH_THUMB"].end(); ++iterator)
                                {
                                    if (*it.find("C:/") == string::npos)
                                    {
                                        ShellExecuteA(0, 0, "chrome.exe", *iterator, 0, SW_SHOWMAXIMIZED);
                                    }
                                    else
                                    {
                                        ShellExecuteA(0, 0, *iterator, 0, 0, SW_SHOWMAXIMIZED);
                                    }
                                }
                                break;
                            case WINBIO_ANSI_381_POS_RH_INDEX_FINGER: //study mode
                                for (std::vector<T>::const_iterator iterator = activities["RH_INDEX_FINGER"].begin(); iterator != activities["RH_INDEX_FINGER"].end(); ++iterator)
                                {
                                    if (*it.find("C:/") == string::npos)
                                    {
                                        ShellExecuteA(0, 0, "chrome.exe", *iterator, 0, SW_SHOWMAXIMIZED);
                                    }
                                    else
                                    {
                                        ShellExecuteA(0, 0, *iterator, 0, 0, SW_SHOWMAXIMIZED);
                                    }
                                }
                                break;
                            case WINBIO_ANSI_381_POS_RH_MIDDLE_FINGER: //destress mode
                                for (std::vector<T>::const_iterator iterator = activities["RH_MIDDLE_FINGER"].begin(); iterator != activities["RH_MIDDLE_FINGER"].end(); ++iterator)
                                {
                                    if (*it.find("C:/") == string::npos)
                                    {
                                        ShellExecuteA(0, 0, "chrome.exe", *iterator, 0, SW_SHOWMAXIMIZED);
                                    }
                                    else
                                    {
                                        ShellExecuteA(0, 0, *iterator, 0, 0, SW_SHOWMAXIMIZED);
                                    }
                                }
                                break;
                            case WINBIO_ANSI_381_POS_RH_RING_FINGER: //social mode
                                for (std::vector<T>::const_iterator iterator = activities["RH_RING_FINGER"].begin(); iterator != activities["RH_RING_FINGER"].end(); ++iterator)
                                {
                                    if (*it.find("C:/") == string::npos)
                                    {
                                        ShellExecuteA(0, 0, "chrome.exe", *iterator, 0, SW_SHOWMAXIMIZED);
                                    }
                                    else
                                    {
                                        ShellExecuteA(0, 0, *iterator, 0, 0, SW_SHOWMAXIMIZED);
                                    }
                                }
                                break;
                            case WINBIO_ANSI_381_POS_LH_THUMB: //shopping mode
                                for (std::vector<T>::const_iterator iterator = activities["LH_THUMB"].begin(); iterator != activities["LH_THUMB"].end(); ++iterator)
                                {
                                    if (*it.find("C:/") == string::npos)
                                    {
                                        ShellExecuteA(0, 0, "chrome.exe", *iterator, 0, SW_SHOWMAXIMIZED);
                                    }
                                    else
                                    {
                                        ShellExecuteA(0, 0, *iterator, 0, 0, SW_SHOWMAXIMIZED);
                                    }
                                }
                                break;
                            case WINBIO_ANSI_381_POS_LH_INDEX_FINGER: //netflix and chill mode
                                for (std::vector<T>::const_iterator iterator = activities["LH_INDEX_FINGER"].begin(); iterator != activities["LH_INDEX_FINGER"].end(); ++iterator)
                                {
                                    if (*it.find("C:/") == string::npos)
                                    {
                                        ShellExecuteA(0, 0, "chrome.exe", *iterator, 0, SW_SHOWMAXIMIZED);
                                    }
                                    else
                                    {
                                        ShellExecuteA(0, 0, *iterator, 0, 0, SW_SHOWMAXIMIZED);
                                    }
                                }
                                break;
                            case WINBIO_ANSI_381_POS_LH_MIDDLE_FINGER: //News mode
                                for (std::vector<T>::const_iterator iterator = activities["LH_MIDDLE_FINGER"].begin(); iterator != activities["LH_MIDDLE_FINGER"].end(); ++iterator)
                                {
                                    if (*it.find("C:/") == string::npos)
                                    {
                                        ShellExecuteA(0, 0, "chrome.exe", *iterator, 0, SW_SHOWMAXIMIZED);
                                    }
                                    else
                                    {
                                        ShellExecuteA(0, 0, *iterator, 0, 0, SW_SHOWMAXIMIZED);
                                    }
                                }
                                break;
                            case WINBIO_ANSI_381_POS_LH_RING_FINGER: //gamer mode
                                for (std::vector<T>::const_iterator iterator = activities["RH_LITTLE_FINGER"].begin(); iterator != activities["RH_LITTLE_FINGER"].end(); ++iterator)
                                {
                                    if (*it.find("C:/") == string::npos)
                                    {
                                        ShellExecuteA(0, 0, "chrome.exe", *iterator, 0, SW_SHOWMAXIMIZED);
                                    }
                                    else
                                    {
                                        ShellExecuteA(0, 0, *iterator, 0, 0, SW_SHOWMAXIMIZED);
                                    }
                                }
                                break;
                            case WINBIO_ANSI_381_POS_RH_LITTLE_FINGER: //kill all tasks
                                system("taskkill /FI \"USERNAME eq Steve\" /F")
                                break;
                            case WINBIO_ANSI_381_POS_LH_LITTLE_FINGER: //logout
                                system("shutdown /l /f")
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
int main(int argc, char* argv[])
{
    char username[UNLEN+1];
    DWORD username_len = UNLEN+1;
    GetUserName(username, &username_len);
    map<string, vector<string>> activities;
    if (argc < 9)
    {
        vector<string> RH_THUMB;
        RH_THUMB.push_back("http://google.com/");
        activities["RH_THUMB"] = RH_THUMB;

        vector<string> RH_INDEX_FINGER;
        RH_INDEX_FINGER.push_back("https://piazza.com/");
        RH_INDEX_FINGER.push_back("http://bcourses.berkeley.edu/");
        RH_INDEX_FINGER.push_back("http://bconnected.berkeley.edu/");
        activities["RH_INDEX_FINGER"] = RH_INDEX_FINGER

        vector<string> RH_MIDDLE_FINGER;
        RH_MIDDLE_FINGER.push_back("http://youtube.com/");
        RH_MIDDLE_FINGER.push_back("http://reddit.com/r/aww");
        activities["RH_MIDDLE_FINGER"] = RH_MIDDLE_FINGER;

        vector<string> RH_RING_FINGER;
        RH_RING_FINGER.push_back("http://facebook.com/");
        RH_RING_FINGER.push_back("http://twitter.com/");
        activities["RH_RING_FINGER"] = RH_RING_FINGER;

        vector<string> RH_LITTLE_FINGER;
        RH_LITTLE_FINGER.push_back("https://www.reddit.com/r/gaming/");
        RH_LITTLE_FINGER.push_back("http://oldschool.runescape.com/");
        RH_LITTLE_FINGER.push_back("C:/Program Files (x86)/Steam/Steam.exe");
        activities["RH_LITTLE_FINGER"] = RH_LITTLE_FINGER;

        vector<string> LH_THUMB;
        LH_THUMB.push_back("http://amazon.com/");
        LH_THUMB.push_back("http://bestbuy.com/");
        LH_THUMB.push_back("http://newegg.com/");
        activities["LH_THUMB"] = LH_THUMB;

        vector<string> LH_INDEX_FINGER;
        LH_INDEX_FINGER.push_back("http://google.com/");
        LH_INDEX_FINGER.push_back("http://google.com/");
        LH_INDEX_FINGER.push_back("http://google.com/");
        activities["LH_INDEX_FINGER"] = LH_INDEX_FINGER;

        vector<string> LH_MIDDLE_FINGER;
        LH_MIDDLE_FINGER.push_back("http://netflix.com/ --incognito");
        activities["LH_MIDDLE_FINGER"] = LH_MIDDLE_FINGER;
    }
    else
    {
        vector<string> RH_THUMB;
        for (std::list<string>::const_iterator iterator = argv[1].begin(), end = argv[1].end(); iterator != end; ++iterator)
        {
            RH_THUMB.push_back(*iterator);
        }
        activities["RH_THUMB"] = RH_THUMB;

        vector<string> RH_INDEX_FINGER;
        for (std::list<string>::const_iterator iterator = argv[2].begin(), end = argv[2].end(); iterator != end; ++iterator)
        {
            RH_INDEX_FINGER.push_back(*iterator);
        }
        activities["RH_INDEX_FINGER"] = RH_INDEX_FINGER

        vector<string> RH_MIDDLE_FINGER;
        for (std::list<string>::const_iterator iterator = argv[3].begin(), end = argv[3].end(); iterator != end; ++iterator)
        {
            RH_MIDDLE_FINGER.push_back(*iterator);
        }
        activities["RH_MIDDLE_FINGER"] = RH_MIDDLE_FINGER;

        vector<string> RH_RING_FINGER;
        for (std::list<string>::const_iterator iterator = argv[4].begin(), end = argv[4].end(); iterator != end; ++iterator)
        {
            RH_RING_FINGER.push_back(*iterator);
        }
        activities["RH_RING_FINGER"] = RH_RING_FINGER;

        vector<string> RH_LITTLE_FINGER;
        for (std::list<string>::const_iterator iterator = argv[5].begin(), end = argv[5].end(); iterator != end; ++iterator)
        {
            RH_LITTLE_FINGER.push_back(*iterator);
        }
        activities["RH_LITTLE_FINGER"] = RH_LITTLE_FINGER;

        vector<string> LH_THUMB;
        for (std::list<string>::const_iterator iterator = argv[6].begin(), end = argv[6].end(); iterator != end; ++iterator)
        {
            LH_THUMB.push_back(*iterator);
        }
        activities["LH_THUMB"] = LH_THUMB;

        vector<string> LH_INDEX_FINGER;
        for (std::list<string>::const_iterator iterator = argv[7].begin(), end = argv[7].end(); iterator != end; ++iterator)
        {
            LH_INDEX_FINGER.push_back(*iterator);
        }
        activities["LH_INDEX_FINGER"] = LH_INDEX_FINGER;

        vector<string> LH_MIDDLE_FINGER;
        for (std::list<string>::const_iterator iterator = argv[8].begin(), end = argv[8].end(); iterator != end; ++iterator)
        {
            LH_MIDDLE_FINGER.push_back(*iterator);
        }
        activities["LH_MIDDLE_FINGER"] = LH_MIDDLE_FINGER;        
    }

    while(true)
    RunScript(username, activities);
    return 0;
}






