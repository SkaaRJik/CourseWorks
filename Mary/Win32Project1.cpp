// Win32Project1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32Project1.h"

#define MAX_LOADSTRING 100



// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK Error(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK Delete(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

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
    LoadStringW(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32PROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


#include <iostream>
#include <stdlib.h>
#include "Tree.h"

int WcharToInt(TCHAR *value);
void Background(HWND hWnd, HDC hdc, int ScreenWidth, int ScreenHight, int MenuHight, bool onlyBack);

Tree tree;

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	static HDC hdc;

	static bool first = true;

	static int ScreenWidth;
	static int ScreenHight;
	static int MenuHight;
	static int caption;
	static int ButtonWidth = 220, ButtonHight = 30;

	
	
	static HWND hBtn[2];
	

    switch (message)
    {
    case WM_COMMAND:
        {
			if (wParam == ID_ADD)
			{
				hdc=GetDC(hWnd);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				Background(hWnd, hdc, ScreenWidth, ScreenHight, MenuHight, false);
				tree.Show(hWnd, hdc);
				ReleaseDC(hWnd, hdc);
			}
			if (wParam == ID_DELETE)
			{
				hdc = GetDC(hWnd);
				try {
					tree.IsEmpty();
				}
				catch (Tree::NullException) {
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ERROREMPTY), hWnd, Error);
					break;
				}
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DELETE), hWnd, Delete);
				Background(hWnd, hdc, ScreenWidth, ScreenHight, MenuHight, false);
				tree.Show(hWnd, hdc);
				ReleaseDC(hWnd, hdc);
			}
        }
        break;
	case WM_CREATE:
		{
			SetTimer(hWnd, 1, 100, NULL);
		}
		break;
		case WM_SIZE:
		{
			ScreenWidth = LOWORD(lParam);
			ScreenHight = HIWORD(lParam);
			MenuHight = HIWORD(lParam)/10;
			ButtonWidth = ScreenWidth / 5;
			tree.GiveXY(ScreenWidth / 2, MenuHight+5);
			caption = GetSystemMetrics(SM_CYCAPTION);
		}
		break;
		case WM_TIMER:
		{
			if(first) 
			{
				hdc = GetDC(hWnd);
				Background(hWnd, hdc, ScreenWidth, ScreenHight, MenuHight, true);
				tree.Show(hWnd, hdc);
				hBtn[0] = CreateWindow(_T("BUTTON"), _T("Добавить элемент"), BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, ScreenWidth/2-ButtonWidth-50, MenuHight/2-ButtonHight/2, ButtonWidth, ButtonHight, hWnd, (HMENU)ID_ADD, hInst, NULL);
				hBtn[1] = CreateWindow(_T("BUTTON"), _T("Удалить элемент"), BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, ScreenWidth / 2 + 50, MenuHight / 2 - ButtonHight / 2, ButtonWidth, ButtonHight, hWnd, (HMENU)ID_DELETE, hInst, NULL);
				first = false;
			}
			else { 
			//hdc = GetDC(hWnd); 
				
			//ReleaseDC(hWnd, hdc); 
			}
		}
    case WM_PAINT:
        {
            hdc = BeginPaint(hWnd, &ps);
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
        if (LOWORD(wParam) == IDOK)
        {
            EndDialog(hDlg, LOWORD(wParam));
			TCHAR value[100];
			GetDlgItemText(hDlg, IDC_EDIT, value, 100);
			int valueInt = WcharToInt(value);
			tree.Add(valueInt);
			return (INT_PTR)TRUE;
        }
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
        break;
    }
    return (INT_PTR)FALSE;
}

int WcharToInt(TCHAR *value)
{
	unsigned int idx = 0;
	
	int result = 0;
	while (value[idx] >= '0' && value[idx] <= '9')
	{
		result = result * 10 + (value[idx] - '0');

		++idx;
	}
	return result;
}

void Background(HWND hWnd, HDC hdc, int ScreenWidth, int ScreenHight, int MenuHight, bool onlyBack )
{
	hdc = GetDC(hWnd);
	HRGN hrgnMenu;
	HBRUSH hBrush;
	if (onlyBack) {
		hrgnMenu = CreateRectRgn(0, 0, ScreenWidth, MenuHight);
		hBrush = CreateSolidBrush(RGB(0, 60, 255));
		FillRgn(hdc, hrgnMenu, hBrush);
		DeleteObject(hrgnMenu);
		DeleteObject(hBrush);
	}
	hrgnMenu = CreateRectRgn(0, MenuHight, ScreenWidth, ScreenHight);
	hBrush = CreateSolidBrush(RGB(0, 255, 0));
	FillRgn(hdc, hrgnMenu, hBrush);
	DeleteObject(hrgnMenu);
	DeleteObject(hBrush);
	ReleaseDC(hWnd, hdc);
}

INT_PTR CALLBACK Error(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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

INT_PTR CALLBACK Delete(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			EndDialog(hDlg, LOWORD(wParam));
			TCHAR value[100];
			GetDlgItemText(hDlg, IDC_EDIT, value, 100);
			int valueInt = WcharToInt(value);
			try { tree.Delete(valueInt); }
			catch (Tree::NullException) {
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ERROREMPTY), hDlg, Error);
			}
			catch (Tree::NotFoundException) {
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ERRORNOTFOUND), hDlg, Error);
			}
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}