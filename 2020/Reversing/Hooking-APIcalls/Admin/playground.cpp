// koohing.cpp : Defines the entry point for the application.
#include "framework.h"
#include "koohing.h"
#include <string>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <winternl.h>
#include <string>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#define MAX_LOADSTRING 100
static HWND hButton0, hButton1, hButton2;
#define CHECK = 10;

#pragma data_seg(."kooh")
char mxp1[8][8];
char mxp2[8][8];
char mxc1[8][8];
char mxc2[8][8];
char one[8][8];
char st_p1[65] = { '9', 'i', 'b', 'P', 'w', 'R', '3', 'k', 'e', 'j', 'Z', 'O', 'p', 'd', '_', 'r', 'c', 'N', '!', 'n', 'K', '6', 'A', 'F', '7', '4', 'I', 'M', '2', 'B', 'H', '1', 'h', 'f', 'T', 'V', 'Q', 'L', 'a', 'q', 'z', '5', 'u', 'U', 'G', 'l', '8', 'm', 't', 'o', 'E', 'x', 'S', 'J', 'D', 'W', 'g', 'C', 's', 'Y', 'X', 'y', '0', 'v' };
char st_c1[65] = { 'U', 'H', 'F', 'B', '6', 'l', 'g', '7', 'f', 'n', 'S', 'P', '_', 'J', 's', '!', 'k', 'r', 'Y', 'E', '3', 'i', '2', 'e', 'q', 'u', 'N', 'O', 'L', 'c', '4', 't', 'D', 'x', 'M', '5', 'b', 'w', 'W', 'K', 'X', 'm', 'd', 'h', 'T', 'o', 'C', '0', 'R', 'z', 'Z', 'p', 'Q', 'j', 'G', 'I', 'y', '8', '1', 'V', 'v', 'a', '9', 'A' };
char st_c2[65] = { '8', 'W', 'm', 'L', 'b', 'z', 'F', 'q', 'e', 'k', '6', 'u', 'I', 'V', 'H', '5', 'l', 'O', 'E', '7', 'g', '9', 'd', 'C', 'y', 'S', 'G', 's', 'T', 'j', 'w', 'X', 'n', 'Q', 'o', 'Y', 'v', 'J', 'r', 'K', 'M', '4', '2', '_', 'i', 'R', 'N', '!', 'h', 'B', 'D', '1', 'A', '0', 'f', '3', 'p', 'U', 'x', 'a', 't', 'P', 'Z', 'c' };
char st_p2[65] = { '4', '1', 'R', '5', 's', 'o', '7', 'z', '!', '9', '3', 'p', 'c', 'g', 'T', 'n', 'S', 'I', 'b', 'v', 'i', 'W', 'O', 'x', '_', 'e', 'G', 'u', 'f', 'D', 'h', 'Q', 'V', 'J', '0', 'd', '2', 'F', 'j', 'U', 'y', 'L', '8', 'M', 'r', 'q', 'A', 'Z', '6', 'E', 'B', 'Y', 'a', 'C', 'N', 'K', 'w', 'k', 'X', 'l', 'H', 'P', 't', 'm' };
long int last[56] = { 4194304 ,16384 ,2 ,262144 ,8192 ,1 ,2048 ,64 ,65536 ,256 ,524288 ,33554432 ,262144 ,32768 ,65536 ,33554432 ,4096 ,2048 ,512 ,16384 ,32 ,512 ,256 ,16384 ,65536 ,2097152 ,524288 ,262144 ,128 ,8388608 ,2048 ,32768 ,8 ,64 ,8192 ,262144 ,1024 ,512 ,8192 ,32 ,8192 ,65536 ,4194304 ,8 ,16 ,32 ,512 ,65536 ,1 ,33554432 ,16777216 ,32768 ,262144 ,8388608 ,8192 ,2097152 };
char en1[57];
long int ar[56];
int mat[63][26];
char f[57];
int x[56] = { 57, 39, 27, 25, 40, 23, 62, 63, 64, 48, 44, 61, 63, 65, 66, 75, 92, 9, 12, 5, 60, 4, 7, 9, 32, 41, 56, 24, 58, 1, 43, 9, 49, 16, 24, 71, 15, 18, 61, 20, 42, 34, 48, 29, 41, 23, 32, 23, 3, 18, 54, 19, 82, 29, 95, 19 };
char fflag[64];
int ar2[7] = { 101, 89, 106, 126, 77, 38, 95 };
int ar1[7] = { 12,55,9,10,43,93,34 };
#pragma runtime_checks( "su", off )
using hookMessageBox = int (WINAPI*)(HWND hWnd, LPCSTR lpstext, LPCSTR lpcaption, UINT utype);
hookMessageBox trueMesgBox = MessageBoxA;
#pragma data_seg()
int a1[56];
int ans2[56] = { 122,45,110,107,93,109,110,86,51,89,87,98,108,100,118,82,122,101,57,101,133,50,101,3,99,110,29,50,79,106,122,90,109,96,118,83,123,90,123,105,127,106,125,101,134,104,139,88,136,76,131,106,131,99,19,82 };
int func1();
int lets_do();
int lets_do2();
int lets_do3();
int lets_undo();
int function_false1(HWND hWnd, LPCSTR lpstext, LPCSTR lpcaption, UINT utype);
int function_false2(HWND hWnd, LPCSTR lpstext, LPCSTR lpcaption, UINT utype);
int function_false3(HWND hWnd, LPCSTR lpstext, LPCSTR lpcaption, UINT utype);
int function_false4(HWND hWnd, LPCSTR lpstext, LPCSTR lpcaption, UINT utype);
char  szInput[64];
int k;
long int check[2];
void flase_exit();
void wrong_len();
void wrong_format();

HINSTANCE hInst;                                
WCHAR szTitle[MAX_LOADSTRING];                  
WCHAR szWindowClass[MAX_LOADSTRING];            

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_KOOHING, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KOOHING));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}


//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KOOHING));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_KOOHING);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    wcex.hbrBackground = GetSysColorBrush(COLOR_ACTIVEBORDER);
    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, CW_USEDEFAULT, 590, 200, nullptr, nullptr, hInstance, nullptr);
   lets_do();
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}
//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_OK:
                GetWindowTextA(hButton2, (szInput), 64);
                szInput[63] = 0;
                func1();
                
                
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_CREATE:
        hButton0 = CreateWindowW(L"button", L"Enter the Flag", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 120, 10, 300, 20, hWnd, 0, hInst, NULL);
        hButton2 = CreateWindowW(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 40, 40, 500, 20, hWnd, 0, hInst, 0);
        hButton1 = CreateWindow(L"button", L"OK", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 240, 70, 50, 40, hWnd, (HMENU)IDM_OK, hInst, NULL);
       
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

int lets_do() {
    LPVOID imageBase = GetModuleHandleA(NULL);
    PIMAGE_DOS_HEADER dosheader = (PIMAGE_DOS_HEADER)imageBase;
    PIMAGE_NT_HEADERS ntHeaders = (PIMAGE_NT_HEADERS)((DWORD_PTR)imageBase + dosheader->e_lfanew);
    PIMAGE_IMPORT_DESCRIPTOR importDescriptor = NULL;
    IMAGE_DATA_DIRECTORY importsDirectory = ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    importDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)(importsDirectory.VirtualAddress + (DWORD_PTR)imageBase);
    LPCSTR libraryName = NULL;
    HMODULE library = NULL;
    PIMAGE_IMPORT_BY_NAME functionName = NULL;

    while (importDescriptor->Name != NULL)
    {
        libraryName = (LPCSTR)importDescriptor->Name + (DWORD_PTR)imageBase;
        library = LoadLibraryA(libraryName);

        if (library)
        {
            PIMAGE_THUNK_DATA originalFirstThunk = NULL, firstThunk = NULL;
            originalFirstThunk = (PIMAGE_THUNK_DATA)((DWORD_PTR)imageBase + importDescriptor->OriginalFirstThunk);
            firstThunk = (PIMAGE_THUNK_DATA)((DWORD_PTR)imageBase + importDescriptor->FirstThunk);
            while (originalFirstThunk->u1.AddressOfData != NULL)
            {
                functionName = (PIMAGE_IMPORT_BY_NAME)((DWORD_PTR)imageBase + originalFirstThunk->u1.AddressOfData);
                if (std::string(functionName->Name).compare("MessageBoxA") == 0)
                {
                    SIZE_T bytesWritten = 0;
                    DWORD oldProtect = 0;
                    DWORD oldProtect2 = 0;
                    VirtualProtect((LPVOID)(&firstThunk->u1.Function), 8, PAGE_READWRITE, &oldProtect);
                    firstThunk->u1.Function = (DWORD_PTR)function_false1;
                    VirtualProtect((LPVOID)(&firstThunk->u1.Function), sizeof(LPDWORD), PAGE_READONLY, &oldProtect);
                    break;
                }
                ++originalFirstThunk;
                ++firstThunk;
            }
        }

        importDescriptor++;
    }

    return 1;
}
int lets_do2() {
    LPVOID imageBase = GetModuleHandleA(NULL);
    PIMAGE_DOS_HEADER dosheader = (PIMAGE_DOS_HEADER)imageBase;
    PIMAGE_NT_HEADERS ntHeaders = (PIMAGE_NT_HEADERS)((DWORD_PTR)imageBase + dosheader->e_lfanew);
    PIMAGE_IMPORT_DESCRIPTOR importDescriptor = NULL;
    IMAGE_DATA_DIRECTORY importsDirectory = ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    importDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)(importsDirectory.VirtualAddress + (DWORD_PTR)imageBase);
    LPCSTR libraryName = NULL;
    HMODULE library = NULL;
    PIMAGE_IMPORT_BY_NAME functionName = NULL;

    while (importDescriptor->Name != NULL)
    {
        libraryName = (LPCSTR)importDescriptor->Name + (DWORD_PTR)imageBase;
        library = LoadLibraryA(libraryName);

        if (library)
        {
            PIMAGE_THUNK_DATA originalFirstThunk = NULL, firstThunk = NULL;
            originalFirstThunk = (PIMAGE_THUNK_DATA)((DWORD_PTR)imageBase + importDescriptor->OriginalFirstThunk);
            firstThunk = (PIMAGE_THUNK_DATA)((DWORD_PTR)imageBase + importDescriptor->FirstThunk);
            while (originalFirstThunk->u1.AddressOfData != NULL)
            {
                functionName = (PIMAGE_IMPORT_BY_NAME)((DWORD_PTR)imageBase + originalFirstThunk->u1.AddressOfData);
                if (std::string(functionName->Name).compare("MessageBoxA") == 0)
                {
                    SIZE_T bytesWritten = 0;
                    DWORD oldProtect = 0;
                    DWORD oldProtect2 = 0;
                    VirtualProtect((LPVOID)(&firstThunk->u1.Function), 8, PAGE_READWRITE, &oldProtect);
                    firstThunk->u1.Function = (DWORD_PTR)function_false2;
                    VirtualProtect((LPVOID)(&firstThunk->u1.Function), sizeof(LPDWORD), PAGE_READONLY, &oldProtect);
                    break;
                }
                ++originalFirstThunk;
                ++firstThunk;
            }
        }

        importDescriptor++;
    }

    return 1;
}
int lets_do3() {
    LPVOID imageBase = GetModuleHandleA(NULL);
    PIMAGE_DOS_HEADER dosheader = (PIMAGE_DOS_HEADER)imageBase;
    PIMAGE_NT_HEADERS ntHeaders = (PIMAGE_NT_HEADERS)((DWORD_PTR)imageBase + dosheader->e_lfanew);
    PIMAGE_IMPORT_DESCRIPTOR importDescriptor = NULL;
    IMAGE_DATA_DIRECTORY importsDirectory = ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    importDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)(importsDirectory.VirtualAddress + (DWORD_PTR)imageBase);
    LPCSTR libraryName = NULL;
    HMODULE library = NULL;
    PIMAGE_IMPORT_BY_NAME functionName = NULL;

    while (importDescriptor->Name != NULL)
    {
        libraryName = (LPCSTR)importDescriptor->Name + (DWORD_PTR)imageBase;
        library = LoadLibraryA(libraryName);

        if (library)
        {
            PIMAGE_THUNK_DATA originalFirstThunk = NULL, firstThunk = NULL;
            originalFirstThunk = (PIMAGE_THUNK_DATA)((DWORD_PTR)imageBase + importDescriptor->OriginalFirstThunk);
            firstThunk = (PIMAGE_THUNK_DATA)((DWORD_PTR)imageBase + importDescriptor->FirstThunk);
            while (originalFirstThunk->u1.AddressOfData != NULL)
            {
                functionName = (PIMAGE_IMPORT_BY_NAME)((DWORD_PTR)imageBase + originalFirstThunk->u1.AddressOfData);
                if (std::string(functionName->Name).compare("MessageBoxA") == 0)
                {
                    SIZE_T bytesWritten = 0;
                    DWORD oldProtect = 0;
                    DWORD oldProtect2 = 0;
                    VirtualProtect((LPVOID)(&firstThunk->u1.Function), 8, PAGE_READWRITE, &oldProtect);
                    firstThunk->u1.Function = (DWORD_PTR)function_false3;
                    VirtualProtect((LPVOID)(&firstThunk->u1.Function), sizeof(LPDWORD), PAGE_READONLY, &oldProtect);
                    break;
                }
                ++originalFirstThunk;
                ++firstThunk;
            }
        }

        importDescriptor++;
    }

    return 1;
}
int lets_do4() {
    LPVOID imageBase = GetModuleHandleA(NULL);
    PIMAGE_DOS_HEADER dosheader = (PIMAGE_DOS_HEADER)imageBase;
    PIMAGE_NT_HEADERS ntHeaders = (PIMAGE_NT_HEADERS)((DWORD_PTR)imageBase + dosheader->e_lfanew);
    PIMAGE_IMPORT_DESCRIPTOR importDescriptor = NULL;
    IMAGE_DATA_DIRECTORY importsDirectory = ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    importDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)(importsDirectory.VirtualAddress + (DWORD_PTR)imageBase);
    LPCSTR libraryName = NULL;
    HMODULE library = NULL;
    PIMAGE_IMPORT_BY_NAME functionName = NULL;

    while (importDescriptor->Name != NULL)
    {
        libraryName = (LPCSTR)importDescriptor->Name + (DWORD_PTR)imageBase;
        library = LoadLibraryA(libraryName);

        if (library)
        {
            PIMAGE_THUNK_DATA originalFirstThunk = NULL, firstThunk = NULL;
            originalFirstThunk = (PIMAGE_THUNK_DATA)((DWORD_PTR)imageBase + importDescriptor->OriginalFirstThunk);
            firstThunk = (PIMAGE_THUNK_DATA)((DWORD_PTR)imageBase + importDescriptor->FirstThunk);
            while (originalFirstThunk->u1.AddressOfData != NULL)
            {
                functionName = (PIMAGE_IMPORT_BY_NAME)((DWORD_PTR)imageBase + originalFirstThunk->u1.AddressOfData);
                if (std::string(functionName->Name).compare("MessageBoxA") == 0)
                {
                    SIZE_T bytesWritten = 0;
                    DWORD oldProtect = 0;
                    DWORD oldProtect2 = 0;
                    VirtualProtect((LPVOID)(&firstThunk->u1.Function), 8, PAGE_READWRITE, &oldProtect);
                    firstThunk->u1.Function = (DWORD_PTR)function_false4;
                    VirtualProtect((LPVOID)(&firstThunk->u1.Function), sizeof(LPDWORD), PAGE_READONLY, &oldProtect);
                    break;
                }
                ++originalFirstThunk;
                ++firstThunk;
            }
        }

        importDescriptor++;
    }

    return 1;
}
int lets_undo() {

    LPVOID imageBase = GetModuleHandleA(NULL);
    PIMAGE_DOS_HEADER dosheader = (PIMAGE_DOS_HEADER)imageBase;
    PIMAGE_NT_HEADERS ntHeaders = (PIMAGE_NT_HEADERS)((DWORD_PTR)imageBase + dosheader->e_lfanew);
    PIMAGE_IMPORT_DESCRIPTOR importDescriptor = NULL;
    IMAGE_DATA_DIRECTORY importsDirectory = ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    importDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)(importsDirectory.VirtualAddress + (DWORD_PTR)imageBase);
    LPCSTR libraryName = NULL;
    HMODULE library = NULL;
    PIMAGE_IMPORT_BY_NAME functionName = NULL;

    while (importDescriptor->Name != NULL)
    {
        libraryName = (LPCSTR)importDescriptor->Name + (DWORD_PTR)imageBase;
        library = LoadLibraryA(libraryName);

        if (library)
        {
            PIMAGE_THUNK_DATA originalFirstThunk = NULL, firstThunk = NULL;
            originalFirstThunk = (PIMAGE_THUNK_DATA)((DWORD_PTR)imageBase + importDescriptor->OriginalFirstThunk);
            firstThunk = (PIMAGE_THUNK_DATA)((DWORD_PTR)imageBase + importDescriptor->FirstThunk);

            while (originalFirstThunk->u1.AddressOfData != NULL)
            {
                functionName = (PIMAGE_IMPORT_BY_NAME)((DWORD_PTR)imageBase + originalFirstThunk->u1.AddressOfData);
                if (strcmp(functionName->Name, "MessageBoxA") == 0)
                {
                    SIZE_T bytesWritten = 0;
                    DWORD oldProtect = 0;
                    VirtualProtect((LPVOID)(&firstThunk->u1.Function), 8, PAGE_READWRITE, &oldProtect);
                    firstThunk->u1.Function = (DWORD_PTR)trueMesgBox;
                    VirtualProtect((LPVOID)(&firstThunk->u1.Function), sizeof(LPDWORD), PAGE_EXECUTE_READ, &oldProtect);
                    break;
                }
                ++originalFirstThunk;
                ++firstThunk;
            }
        }
        importDescriptor++;
    }
    return 0;
}
void flase_exit() {
    MessageBoxW(NULL, L"Wrong......!!!",L"Failed", 0);
    exit(0);
}
void wrong_len() {
    MessageBoxW(NULL, L"Please check Length", L"Failed", 0);
    exit(0);
}
void wrong_format() {
    MessageBoxW(NULL, L"Please check format!!!", L"Failed", 0);
    exit(0);
}

int func1() {
    int i, k, j;

    memcpy(fflag, szInput, sizeof(char) * 63);
    if (strlen(fflag) != 63) {
        wrong_len();
    }

    for (i = 0; i < 6; i++) {
        if ((int)((int)(fflag[i]) ^ ar1[i]) != ar2[i]) {
            wrong_format();
        }
    }
    if ((int)((int)(fflag[62]) ^ ar1[i]) != ar2[i]) {
        wrong_format();
    }

    MessageBoxA(NULL, "Thanks for your input", "Gratitude", 0); 

    MessageBoxA(NULL, "Checking phase ....", "Baby steps", 0);
    Sleep(2);
    for (i = 6; i < strlen(fflag) - 1; i++) {
        a1[i - 6] = (int)(fflag[i]) ^ (i + 4);
    }
    
    MessageBoxA(NULL, "Checking phase ....", "Rechecking for safety ", 0);
     
    for (i = 0; i < 56; i++) {
        if ((i % 2) == 0) {
            a1[i] = (a1[i] + 12);
        }
        else {
            a1[i] = (a1[i] - 14);
        }
    }

    MessageBoxA(NULL, "Cross ur fingers", "Final",  0); 

    for (i = 0; i < 56; i++) {
        if (a1[i] != ans2[i]) {
            MessageBoxA(NULL, "definatly its wrong!!!", "INCORRECT", 0);
            exit(0);
        }
    }

    MessageBoxA(NULL, "You are missing something vital", "naaahhhh!!!", 0);

    return 1;
}

int function_false1(HWND hWnd, LPCSTR lpstext, LPCSTR lpcaption, UINT utype) {

    int i, j;
    char a, b;
    int x1, y1, x2, y2 = 0;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            mxp1[i][j] = st_p1[i * 8 + j];
            mxp2[i][j] = st_p2[i * 8 + j];
            mxc1[i][j] = st_c1[i * 8 + j];
            mxc2[i][j] = st_c2[i * 8 + j];
        }

    }

    for (i = 6; i < strlen(fflag) - 1; i = i + 2) {
        a = fflag[i];
        b = fflag[i + 1];

        for (j = 0; j < 8; j++) {
            for (k = 0; k < 8; k++) {
                if ((int)mxp1[j][k] == a) {
                    x1 = j;
                    y2 = k;
                }
            }
        }

        for (j = 0; j < 8; j++) {
            for (k = 0; k < 8; k++) {
                if ((int)mxp2[j][k] == b) {
                    y1 = k;
                    x2 = j;
                }
            }
        }

        en1[i - 6] = (char)mxc1[x1][y1];
        en1[i + 1 - 6] = (char)mxc2[x2][y2];

    }
    en1[i - 6] = 0;
    check[0] = 67108864;
    lets_do2();
    return trueMesgBox(hWnd, lpstext, lpcaption, utype);
}

int function_false2(HWND hWnd, LPCSTR lpstext, LPCSTR lpcaption, UINT utype) {
    int i, j, k;

    for (i = strlen(en1) - 1; i >= 0; i--) {
        for (j = 0; j < 26; j++) {
            mat[i][j] = 0;
        }
    }
   
    for (i = 0; i < strlen(en1); i++) {
        f[i] = en1[i] ^ x[i];
    }
    f[i] = 0;   

    for (i = strlen(f) - 1; i >= 0; i--) {
        for (j = 0; j < 26; j++) {
            if ((int(f[i]) - 97) % 26 == j)
            {
                mat[i][j] = 1;
            }
            else
            {
                mat[i][j] = 0;
            }
        }
    }

    for (i = 0; i < strlen(f); i++) {
        long int k = 0;
        for (j = 25; j >= 0; j--) {
            k = k + pow(2, j) * mat[i][j];
        }

        ar[i] = k;
    }
    

    lets_do3();

    return trueMesgBox(hWnd, lpstext, lpcaption, utype);
}

int function_false3(HWND hWnd, LPCSTR lpstext, LPCSTR lpcaption, UINT utype) {

    int  i;
    for (i = 0; i < strlen(f); i++) {
        if( (ar[i] ^ last[i])!= 0) {
            check[1] = 0;
            return trueMesgBox(hWnd, lpstext, lpcaption, utype);
        }
    }
    check[1] = 67108864;

    lets_do4();

    trueMesgBox(hWnd, lpstext, lpcaption, utype);
}

int function_false4(HWND hWnd, LPCSTR lpstext, LPCSTR lpcaption, UINT utype) {
    if (check[0] == check[1]) {
        trueMesgBox(NULL, "YO!!", lpcaption, utype);
    }
    lets_undo();
    exit(0);
    return trueMesgBox(hWnd, lpstext, lpcaption, utype);
}