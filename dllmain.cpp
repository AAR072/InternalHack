// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "iostream"
#include <TlHelp32.h>
#include <Windows.h>
#include "mem.h"
#include "proc.h"


struct Vector3 {
    float x, y, z;
};


// Created with ReClass.NET 1.2 by KN4CK3R

class base
{
public:
    char pad_0000[8]; //0x0000
    class offset1* offset1ptr; //0x0008
}; //Size: 0x000C

class offset1
{
public:
    char pad_0000[1780]; //0x0000
    class offset2* offset2; //0x06F4
}; //Size: 0x06F8

class playerent
{
public:
    Vector3 Headposition; //0x0004
    char pad_0010[36]; //0x0010
    Vector3 Lookangles; //0x0034
    char pad_0040[172]; //0x0040
    int32_t Health; //0x00EC
    int32_t armour; //0x00F0
    char pad_00F4[56]; //0x00F4
    int32_t mk77ammo; //0x012C
    char pad_0130[16]; //0x0130
    int32_t mtp57ammo; //0x0140
    char pad_0144[193]; //0x0144
    char name[16]; //0x0205
    char pad_0215[339]; //0x0215
    class weapon* currentweapon; //0x0368
    char pad_036C[40]; //0x036C

    virtual void Function0();
    virtual void Function1();
    virtual void Function2();
    virtual void Function3();
    virtual void Function4();
    virtual void Function5();
    virtual void Function6();
    virtual void Function7();
    virtual void Function8();
    virtual void Function9();
}; //Size: 0x0394

class offset2
{
public:
    char pad_0000[2024]; //0x0000
    class playerent playerinstance; //0x07E8
    char pad_0B7C[912]; //0x0B7C
}; //Size: 0x0F0C

class weapon
{
public:
    char pad_0000[8]; //0x0000
    class playerent* weaponOwnerPtr; //0x0008
    class weaponconstdata* weaponconstptr; //0x000C
    class weapondata* gundataptr; //0x0010
    char pad_0014[8]; //0x0014
    int32_t sprayshotcount; //0x001C
    char pad_0020[1016]; //0x0020
}; //Size: 0x0418

class weapondata
{
public:
    int32_t magammocount; //0x0000
    char pad_0004[32]; //0x0004
    int32_t clipammocount; //0x0024
    char pad_0028[732]; //0x0028
}; //Size: 0x0304

class weaponconstdata
{
public:
    char pad_0000[94]; //0x0000
    int16_t Recoilseed1; //0x005E
    int16_t Recoilseed2; //0x0060
    char pad_0062[590]; //0x0062
}; //Size: 0x02B0

void clear_screen(char fill = ' ') {
    COORD tl = { 0,0 };
    CONSOLE_SCREEN_BUFFER_INFO s;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(console, &s);
    DWORD written, cells = s.dwSize.X * s.dwSize.Y;
    FillConsoleOutputCharacter(console, fill, cells, tl, &written);
    FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
    SetConsoleCursorPosition(console, tl);
}
DWORD WINAPI HackThread(HMODULE hModule) {
    // create console
    AllocConsole();
    FILE * f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    SetConsoleTitle(TEXT("Lifty Client"));
    std::cout << "STARTED CLIENT\n";
    bool stateChanged = true;

    // get mod base
    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"ac_client.exe");


    bool bHealth = false, bAmmo = false, bRecoil = false;
    

    playerent* localPlayer = *(playerent**)(moduleBase + 0x18AC00);

//    char* tempPtr = reinterpret_cast<char*>(localPlayer);
//    tempPtr += 0x7E8;
//    localPlayer = reinterpret_cast<playerent*>(tempPtr);



    std::cout << "Local Player Address: " << localPlayer << "\n";
    std::cout << "Health Val: " << localPlayer->Health << "\n";

    // hack loop
    while (true)
    {

        if (GetAsyncKeyState(VK_ESCAPE) & 1) {
            break;
        }

        if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
            bHealth = !bHealth;
            stateChanged = true;

        }

        if (GetAsyncKeyState(VK_NUMPAD2) & 1) {
            bAmmo = !bAmmo;
            stateChanged = true;
            if (bAmmo) {
                mem::Nop((BYTE*)(moduleBase + 0x0C73EF), 2);
            }
            else {
                std::cout << "Infinite Ammo: Off";
                clear_screen();
                mem::Patch((BYTE*)(moduleBase + 0x0C73EF), (BYTE*)"\xFF\x08", 2);
            }
        }

        if (GetAsyncKeyState(VK_NUMPAD3) & 1) {
            bRecoil = !bRecoil;
            stateChanged = true;
            if (bRecoil) 
            {
                mem::Patch((BYTE*)(moduleBase + 0xC8BA0), (BYTE*)"\xC2\x08\x00", 3);
            }
        }
        if (bHealth)
        {
            localPlayer->Health = 133;

        }
        if (stateChanged) {
            clear_screen();
            std::cout << "Health Toggle: " << (bHealth ? "On" : "Off") << "\n";
            std::cout << "Ammo Toggle: " << (bAmmo ? "On" : "Off") << "\n";
            std::cout << "Recoil Toggle: " << (bRecoil ? "On" : "Off") << "\n";
            std::cout << "Current Health: " << localPlayer->Health << "\n";
            stateChanged = false; // Reset state change flag
        }
        Sleep(5);
 
        
        
    }
    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;


}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

