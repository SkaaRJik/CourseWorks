// OpenFile.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "OpenFile.h"

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
    LoadStringW(hInstance, IDC_OPENFILE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OPENFILE));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OPENFILE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_OPENFILE);
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW ,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

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
	HDC hdc;
	static TCHAR name[256] = _T("");;
	static OPENFILENAME file;
	std::ifstream in;
	std::ofstream out;
	static std::vector<std::string> v;
	std::vector<std::string>::iterator it;
	std::string st;
	int y, k;
	static int n, length, sx, sy, cx, iVscrollPos, iHscrollPos, COUNT, MAX_WIDTH;
	static SIZE size = { 8, 16 }; //Ширина и высота символа
	switch (message)
	{
	case WM_CREATE:
		file.lStructSize = sizeof(OPENFILENAME);
		file.hInstance = hInst;
		file.lpstrFilter = _T("Text\0*.txt");
		file.lpstrFile = name;
		file.nMaxFile = 256;
		file.lpstrInitialDir = _T(".\\");
		file.lpstrDefExt = _T("txt");
		break;
	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		k = n - sy / size.cy;
		if (k > 0) COUNT = k; else COUNT = iVscrollPos = 0;
		SetScrollRange(hWnd, SB_VERT, 0, COUNT, FALSE);
		SetScrollPos(hWnd, SB_VERT, iVscrollPos, TRUE);
		k = length - sx / size.cx;
		if (k > 0) MAX_WIDTH = k; else MAX_WIDTH = iHscrollPos = 0;
		SetScrollRange(hWnd, SB_HORZ, 0, MAX_WIDTH, FALSE);
		SetScrollPos(hWnd, SB_HORZ, iHscrollPos, TRUE);
		break;
	case WM_VSCROLL:
		switch (LOWORD(wParam))
		{
		case SB_LINEUP: iVscrollPos--; break;
		case SB_LINEDOWN: iVscrollPos++; break;
		case SB_PAGEUP: iVscrollPos -= sy / size.cy; break;
		case SB_PAGEDOWN: iVscrollPos += sy / size.cy; break;
		case SB_THUMBPOSITION: iVscrollPos = HIWORD(wParam); break;
		}
		iVscrollPos = max(0, min(iVscrollPos, COUNT));
		if (iVscrollPos != GetScrollPos(hWnd, SB_VERT))
		{
			SetScrollPos(hWnd, SB_VERT, iVscrollPos, TRUE);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	case WM_HSCROLL:
		switch (LOWORD(wParam))
		{
		case SB_LINEUP: iHscrollPos--; break;
		case SB_LINEDOWN: iHscrollPos++; break;
		case SB_PAGEUP: iHscrollPos -= 8; break;
		case SB_PAGEDOWN: iHscrollPos += 8; break;
		case SB_THUMBPOSITION: iHscrollPos = HIWORD(wParam); break;
		}
		iHscrollPos = max(0, min(iHscrollPos, MAX_WIDTH));
		if (iHscrollPos != GetScrollPos(hWnd, SB_HORZ))
		{
			SetScrollPos(hWnd, SB_HORZ, iHscrollPos, TRUE);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_FILE_NEW:
			if (!v.empty()) std::vector<std::string>().swap(v);
			n = length = 0;
			SendMessage(hWnd, WM_SIZE, 0, sy << 16 | sx);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_FILE_OPEN:
			file.lpstrTitle = _T("Открыть файл для чтения");
			file.Flags = OFN_HIDEREADONLY;
			if (!GetOpenFileName(&file)) return 1;
			in.open(name);
			while (getline(in, st))
			{
				if (length < st.length()) length = st.length();
				v.push_back(st);
			}
			in.close();
			n = v.size();
			SendMessage(hWnd, WM_SIZE, 0, sy << 16 | sx);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_FILE_SAVE:
			file.lpstrTitle = _T("Открыть файл для записи");
			file.Flags = OFN_NOTESTFILECREATE;
			if (!GetSaveFileName(&file)) return 1;
			out.open(name);

			//for (it = v.begin(); it != v.end(); ++it) out << *it << '\n';

			out.close();
			break;
		case IDM_EXIT: DestroyWindow(hWnd); break;
		default: return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		for (y = 0, it = v.begin() + iVscrollPos; it != v.end() && y<sy; ++it, y += size.cy)
			if (iHscrollPos < it->length())
				TabbedTextOutA(hdc, 0, y, it->data() + iHscrollPos, it->length() -
					iHscrollPos, 0, NULL, 0);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
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
