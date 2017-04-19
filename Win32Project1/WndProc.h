#pragma once

#include"AddDialogue.h"
#include"ErrorDialogue.h"
#include"Delete.h"
void paintMenu(HWND &hWnd, int &MenuWidth, int &MenuHight);
void tuneScroll(HWND &hDrawPanel, int &DrawWidth, int &DrawHight);


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	static HDC hdc;

	static HWND hDrawPanel;
	static int DrawWidth;
	static int DrawHight;

	static bool first = true;

	static int ScreenWidth;
	static int ScreenHight;
	static int MenuWidth;
	static int MenuHight;
	static int caption;
	static int ButtonWidth = 220, ButtonHight = 30;

	static TCHAR name[256] = _T("");;
	static OPENFILENAME file;
	std::ifstream in;
	std::ofstream out;

	static HWND hBtn[6];




	switch (message)
	{
	case WM_COMMAND:
	{

		if (wParam == ID_FILE_OPEN)
		{
			hdc = GetDC(hDrawPanel);
			file.lpstrTitle = _T("Открыть файл для чтения");
			file.Flags = OFN_HIDEREADONLY;
			if (!GetOpenFileName(&file)) return 1;
			in.open(name);
			std::vector<int> vec;
			while (!in.eof())
			{
				int value;
				in >> value;
				vec.push_back(value);
			}
			in.close();
			std::sort(vec.begin(), vec.end());
			//for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
				//tree.Add(*it, true);
			for (int i = 0; i < vec.size(); i++)
				tree.Add(vec[i], true);

			tuneScroll(hDrawPanel, DrawWidth, DrawHight);
			paintBackground(hDrawPanel, hdc, DrawWidth, DrawHight);
			tree.showGDI(hDrawPanel, ScreenWidth, ScreenHight);
			ReleaseDC(hDrawPanel, hdc);
		}
		if (wParam == ID_FILE_SAVE)
		{
			file.lpstrTitle = _T("Открыть файл для записи");
			file.Flags = OFN_NOTESTFILECREATE;
			if (!GetSaveFileName(&file)) return 1;
			out.open(name);
			tree.getAllElements();
			for (int i = 0; i < tree.elements.size(); i++)
			{
				out << tree.elements[i];
				if (i + 1 != tree.elements.size()) out << " ";
			}
			
			out.close();
		}
		if (wParam == ID_FILE_BACKUP)
		{
			hdc = GetDC(hDrawPanel);
			int val = MessageBox(hWnd, _T("Дерево будет полностью удалено"),
				_T("Предупреждение"), MB_YESNO | MB_ICONQUESTION);
			if (IDYES == val)
			{
				tree.deleteAll();
				in.open("backup.tree");

				while (!in.eof())
				{
					int value;
					in >> value;
					tree.Add(value, false);
				}
				in.close();
				
				tuneScroll(hDrawPanel, DrawWidth, DrawHight);
				paintBackground(hDrawPanel, hdc, DrawWidth, DrawHight);
				tree.showGDI(hDrawPanel, ScreenWidth, ScreenHight);
			}
			ReleaseDC(hDrawPanel, hdc);
		}
		if (wParam == ID_ADD)
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, AddDialog);
			if (tree.getHead())
			{
				paintBackground(hDrawPanel, hdc, DrawWidth, DrawHight);
				tuneScroll(hDrawPanel, DrawWidth, DrawHight);
				tree.showGDI(hDrawPanel, ScreenWidth, ScreenHight);
			}
		}
		if (wParam == ID_DELETE)
		{
			hdc = GetDC(hDrawPanel);
			try {
				tree.CheckIfEmpty();
			}
			catch (Tree::NullException) {
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ERROREMPTY), hWnd, Error);
				ReleaseDC(hDrawPanel, hdc);
				break;
			}
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DELETE), hWnd, Delete);
			tuneScroll(hDrawPanel, DrawWidth, DrawHight);
			if (tree.getNodeXY(tree.getEdgeLeftNode()).x > 0 && (tree.getNodeXY(tree.getEdgeRightNode()).x + tree.getResolutionOfNode().x) < DrawWidth)
			{
				SetScrollRange(hDrawPanel, SB_HORZ,0, 0, FALSE);
			}
			paintBackground(hDrawPanel, hdc, DrawWidth, DrawHight);
			tree.showGDI(hDrawPanel, ScreenWidth, ScreenHight);
			ReleaseDC(hDrawPanel, hdc);
		}
		if (wParam == ID_DELETE_ALL)
		{
			hdc = GetDC(hDrawPanel);
			try {
				tree.CheckIfEmpty();
			}
			catch (Tree::NullException) {
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, AddDialog);
				break;
			}
			if (IDYES == MessageBox(hWnd, _T("Дерево будет полностью удалено"),
				_T("Предупреждение"), MB_YESNO | MB_ICONQUESTION))
			{
				tree.deleteAll();
				if (tree.CheckIfEmpty(1))
				{
					SetScrollRange(hDrawPanel, SB_HORZ, 0, 0, TRUE);
					SetScrollRange(hDrawPanel, SB_VERT, 0, 0, TRUE);
				}
			}
			paintBackground(hDrawPanel, hdc, DrawWidth, DrawHight);
			tree.showGDI(hDrawPanel, ScreenWidth, ScreenHight);
			ReleaseDC(hDrawPanel, hdc);

		}
	}
	break;
	case WM_CREATE:
	{
		SetTimer(hWnd, 1, 100, NULL);
		file.lStructSize = sizeof(OPENFILENAME);
		file.hInstance = hInst;
		file.lpstrFilter = _T("Text\0*.tree");
		file.lpstrFile = name;
		file.nMaxFile = 256;
		file.lpstrInitialDir = _T(".\\");
		file.lpstrDefExt = _T("tree");
		tree.loadResourse();
		MyDrawPanelClass();
		hDrawPanel = CreateWindow(ChildClassName, NULL, WS_CHILD |
			WS_DLGFRAME | WS_HSCROLL | WS_VSCROLL | WS_VSCROLL | WS_VISIBLE, 0, 0, 0, 0, hWnd, NULL, hInst, NULL);
	}
	break;
	case WM_SIZE:
	{
		hdc = GetDC(hWnd);
		ScreenWidth = LOWORD(lParam);
		ScreenHight = HIWORD(lParam);
		MenuWidth = LOWORD(lParam) / 6;
		MenuHight = HIWORD(lParam);
		DrawWidth = ScreenWidth - MenuWidth;
		DrawHight = ScreenHight;
		ScrollParametres.left = 0;
		ScrollParametres.right = DrawWidth;
		ScrollParametres.top = 0;
		ScrollParametres.bottom = DrawHight;
		ButtonWidth = MenuWidth - 10;
		paintMenu(hWnd, MenuWidth, MenuHight);

		caption = GetSystemMetrics(SM_CYCAPTION);
		/*DRAW PANEL*/
		MoveWindow(hDrawPanel, MenuWidth, 0, DrawWidth, DrawHight, true);
		ReleaseDC(hWnd, hdc);
		hdc = GetDC(hDrawPanel);
		paintBackground(hDrawPanel, hdc, DrawWidth, DrawHight);

		if (tree.CheckIfEmpty(1))
		{
			SetScrollRange(hDrawPanel, SB_HORZ, 0, 0, FALSE);
			SetScrollRange(hDrawPanel, SB_VERT, 0, 0, FALSE);
		}
		else
		{
			tuneScroll(hDrawPanel, DrawWidth, DrawHight);
		}
		tree.setX(DrawWidth / 2);
		tree.showGDI(hDrawPanel, ScreenWidth, ScreenHight);
		ReleaseDC(hDrawPanel, hdc);
	}
	break;
	case WM_MOVE:
	{
		hdc = GetDC(hWnd);
		paintMenu(hWnd, MenuWidth, MenuHight);
		for (int i = 0; i < 6; i++)
			InvalidateRect(hBtn[i], 0, true);
		ReleaseDC(hWnd, hdc);
		/*DRAW PANEL*/
		hdc = GetDC(hDrawPanel);
		paintBackground(hDrawPanel, hdc, DrawWidth, DrawHight);
		tree.showGDI(hDrawPanel, ScreenWidth, ScreenHight);
		ReleaseDC(hDrawPanel, hdc);
	}
	break;
	case WM_TIMER:
	{
		if (first)
		{
			paintMenu(hWnd, MenuWidth, MenuHight);
			hBtn[0] = CreateWindow(_T("BUTTON"), _T("Новое дерево"), BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 5, ScreenHight / 2 - 5 * ButtonHight * 3 / 2, ButtonWidth, ButtonHight, hWnd, (HMENU)ID_DELETE_ALL, hInst, NULL);
			hBtn[1] = CreateWindow(_T("BUTTON"), _T("Добавить элемент"), BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 5, ScreenHight / 2, ButtonWidth, ButtonHight, hWnd, (HMENU)ID_ADD, hInst, NULL);
			hBtn[2] = CreateWindow(_T("BUTTON"), _T("Удалить элемент"), BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 5, ScreenHight / 2 + ButtonHight * 3 / 2, ButtonWidth, ButtonHight, hWnd, (HMENU)ID_DELETE, hInst, NULL);
			hBtn[3] = CreateWindow(_T("BUTTON"), _T("Добавить из файла"), BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 5, ScreenHight / 2 + 2 * ButtonHight * 3 / 2, ButtonWidth, ButtonHight, hWnd, (HMENU)ID_FILE_OPEN, hInst, NULL);
			hBtn[4] = CreateWindow(_T("BUTTON"), _T("Сохранить в файл"), BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 5, ScreenHight / 2 + 3 * ButtonHight * 3 / 2, ButtonWidth, ButtonHight, hWnd, (HMENU)ID_FILE_SAVE, hInst, NULL);
			hBtn[5] = CreateWindow(_T("BUTTON"), _T("Восстановить дерево"), BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 5, ScreenHight / 2 + 5 * ButtonHight * 3 / 2 - ButtonHight / 2, ButtonWidth, ButtonHight, hWnd, (HMENU)ID_FILE_BACKUP, hInst, NULL);
			first = false;
			hdc = GetDC(hDrawPanel);
			paintBackground(hDrawPanel, hdc, DrawWidth, DrawHight);



			tree.showGDI(hDrawPanel, DrawWidth, DrawHight);

			ReleaseDC(hDrawPanel, hdc);

		}
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		tree.getAllElements();
		if (tree.elements.size() > 0)
		{
			out.open("backup.tree");

			//for (std::vector<int>::iterator it = tree.elements.begin(); it != tree.elements.end(); it++)

			for (int i = 0; i < tree.elements.size(); i++)
			{
				out << tree.elements[i];
				if (i + 1 != tree.elements.size()) out << " ";
			}
			out.close();
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


void paintMenu(HWND &hWnd, int  &MenuWidth, int &MenuHight)
{
	HDC hdc = GetDC(hWnd);
	HRGN hrgnMenu;
	HBRUSH hBrush;
	HDC memDC;
	static HBITMAP hPicture;
	hPicture = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	hrgnMenu = CreateRectRgn(0, 0, MenuWidth, MenuHight);
	hBrush = CreateSolidBrush(RGB(130, 130, 130));
	FillRgn(hdc, hrgnMenu, hBrush);
	DeleteObject(hrgnMenu);
	DeleteObject(hBrush);
	memDC = CreateCompatibleDC(hdc);
	SelectObject(memDC, hPicture);
	BitBlt(hdc, 5, 65, 150, 150, memDC, 0, 0, SRCCOPY);
	DeleteDC(memDC);
	ReleaseDC(hWnd, hdc);
}

void tuneScroll(HWND &hDrawPanel, int &DrawWidth, int &DrawHight)
{
	tree.setX(DrawWidth / 2);
	if (tree.getNodeXY(tree.getEdgeLeftNode()).x < 0 || (tree.getNodeXY(tree.getEdgeRightNode()).x + tree.getResolutionOfNode().x) >= DrawWidth)
	{
		//int offset = abs(tree.getNodeXY(tree.getEdgeLeftNode()).x) - tree.getResolutionOfNode().x;
		int offset = max(abs(tree.getNodeXY(tree.getEdgeLeftNode()).x), tree.getNodeXY(tree.getEdgeRightNode()).x + tree.getResolutionOfNode().x);
			if (tree.getNodeXY(tree.getEdgeLeftNode()).x < 0)
				tree.offsetXY(offset, 0);
			else if ((tree.getNodeXY(tree.getEdgeRightNode()).x + tree.getResolutionOfNode().x) >= DrawWidth)
				tree.offsetXY(-offset, 0);
		treeRes.x = (tree.getNodeXY(tree.getEdgeRightNode()).x + tree.getResolutionOfNode().x);
		int centerX = (tree.getNodeXY(tree.getEdgeRightNode()).x + tree.getResolutionOfNode().x + abs(tree.getNodeXY(tree.getEdgeLeftNode()).x)) / DrawWidth;
		iHscrollPos = DrawWidth / 2;
		tree.offsetXY(-iHscrollPos*centerX, 0);
		tree.offsetXY(centerX * tree.getResolutionOfNode().x, 0);
		//iHscrollPos = 0;
		SetScrollRange(hDrawPanel, SB_HORZ, ScrollParametres.left, ScrollParametres.right, FALSE);
		SetScrollPos(hDrawPanel, SB_HORZ, iHscrollPos, TRUE);
		treeOffset.x = treeRes.x / ScrollParametres.right;
	}
	if (tree.getNodeXY(tree.getEdgeLeftNode()).y + tree.getResolutionOfNode().y >= DrawHight || tree.getNodeXY(tree.getEdgeRightNode()).y + tree.getResolutionOfNode().y >= DrawHight)
	{
		treeRes.y = max(tree.getNodeXY(tree.getEdgeLeftNode()).y + tree.getResolutionOfNode().y, tree.getNodeXY(tree.getEdgeRightNode()).y + tree.getResolutionOfNode().y);
		//if (tree.getNodeXY(tree.getEdgeLeftNode()).y + tree.getResolutionOfNode().y >= DrawHight) treeRes.y = (tree.getNodeXY(tree.getEdgeLeftNode()).y + tree.getResolutionOfNode().y);
		//if (tree.getNodeXY(tree.getEdgeRightNode()).y + tree.getResolutionOfNode().y > tree.getNodeXY(tree.getEdgeLeftNode()).y + tree.getResolutionOfNode().y) treeRes.y = tree.getNodeXY(tree.getEdgeRightNode()).y + tree.getResolutionOfNode().y;
		tree.setY(10);
		iVscrollPos = 0;
		SetScrollRange(hDrawPanel, SB_VERT, ScrollParametres.top, ScrollParametres.bottom, FALSE);
		SetScrollPos(hDrawPanel, SB_VERT, iVscrollPos, TRUE);
		treeOffset.y = treeRes.y / ScrollParametres.bottom;
	}
}