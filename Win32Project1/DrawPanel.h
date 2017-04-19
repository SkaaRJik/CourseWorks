#pragma once


LRESULT CALLBACK DrawPanelProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	static int DrawWidth;
	static int DrawHight;

	switch (message)
	{
	case WM_CREATE:

		break;
	case WM_SIZE:
		DrawWidth = LOWORD(lParam);
		DrawHight = HIWORD(lParam);

		break;
	case WM_HSCROLL:
	{
		hdc = GetDC(hWnd);
		//int buf = (tree.getNodeXY(tree.getEdgeRightNode()).x + tree.getResolutionOfNode().x + abs(tree.getNodeXY(tree.getEdgeLeftNode()).x));
		//int treeOffset.x = (treeRes.x / (ScrollParametres.right));
		switch (LOWORD(wParam))
		{
			case SB_LINEUP:
			{
				//iHscrollPos -= tree.getResolutionOfNode().x / 2;
				//iHscrollPos -= buf % ScrollParametres.right;

				iHscrollPos--;
				if (iHscrollPos >= ScrollParametres.left)
				{
					tree.offsetXY(+treeOffset.x, 0);
				}
				else
				{
					iHscrollPos = ScrollParametres.left;
				}
				break;
			}
			case SB_LINEDOWN:
			{
				//iHscrollPos += tree.getResolutionOfNode().x / 2; 
				iHscrollPos++;

				if (iHscrollPos <= ScrollParametres.right)
				{
					tree.offsetXY(-treeOffset.x, 0);
				}
				else
				{
					iHscrollPos = ScrollParametres.right;
				}
				break;
			}
			case SB_PAGEUP:
			{
				iHscrollPos -= tree.getResolutionOfNode().x;

				if (iHscrollPos >= ScrollParametres.left)
				{
					tree.offsetXY(treeOffset.x*tree.getResolutionOfNode().x, 0);
				}
				else
				{
					iHscrollPos = ScrollParametres.left;
				}
				break;
			}
			case SB_PAGEDOWN:
			{
				iHscrollPos += tree.getResolutionOfNode().x;
				if (iHscrollPos <= ScrollParametres.right)
				{
					tree.offsetXY(-treeOffset.x*tree.getResolutionOfNode().x, 0);
				}
				else
				{
					iHscrollPos = ScrollParametres.right;
				}
				break;
			}
			case SB_THUMBPOSITION:
			case SB_THUMBTRACK:
				int offseting = iHscrollPos;
				iHscrollPos = HIWORD(wParam);
				offseting = iHscrollPos - abs(offseting);
				if (iHscrollPos >= ScrollParametres.left || iHscrollPos <= ScrollParametres.right)
				{
					tree.offsetXY(-treeOffset.x*offseting, 0);
				}
				else if (iHscrollPos <= ScrollParametres.left)
				{
					iHscrollPos = ScrollParametres.left;
				}
				else if (iHscrollPos >= ScrollParametres.right)
				{
					iHscrollPos = ScrollParametres.right;
				}
		}
		//iHscrollPos = max(0, min (iHscrollPos, tree.getNodeXY(tree.getEdgeRightNode()).x+tree.getResolutionOfNode().x));
		paintBackground(hWnd, hdc, DrawWidth, DrawHight);
		tree.showGDI(hWnd, DrawWidth, DrawHight);
		//tree.Show(hWnd, hdc);
		if (iHscrollPos != GetScrollPos(hWnd, SB_HORZ))
		{
			SetScrollPos(hWnd, SB_HORZ, iHscrollPos, TRUE);
		}
		ReleaseDC(hWnd, hdc);
	}
	break;

	case WM_VSCROLL:
	{
		hdc = GetDC(hWnd);
		
		//int offset = (treeRes.y / (ScrollParametres.bottom));
		switch (LOWORD(wParam))
		{
		case SB_LINEUP:
		{
			
			iVscrollPos--;
			if (iVscrollPos >= ScrollParametres.top)
			{
				tree.offsetXY(0, treeOffset.y);
			}
			else
			{
				iVscrollPos = ScrollParametres.top;
			}
			break;
		}
		case SB_LINEDOWN:
		{
			
			iVscrollPos++;

			if (iVscrollPos <= ScrollParametres.bottom)
			{
				tree.offsetXY(0, -treeOffset.y);
			}
			else
			{
				iVscrollPos = ScrollParametres.bottom;
			}
			break;
		}
		case SB_PAGEUP:
		{
			iVscrollPos -= tree.getResolutionOfNode().y;

			if (iVscrollPos >= ScrollParametres.top)
			{
				tree.offsetXY(0, treeOffset.y*tree.getResolutionOfNode().y);
			}
			else
			{
				iVscrollPos = ScrollParametres.top;
			}
			break;
		}
		case SB_PAGEDOWN:
		{
			iVscrollPos += tree.getResolutionOfNode().y;
			if (iVscrollPos <= ScrollParametres.bottom)
			{
				tree.offsetXY(0, -treeOffset.y*tree.getResolutionOfNode().y);
			}
			else
			{
				iVscrollPos = ScrollParametres.bottom;
			}
			break;
		}
		case SB_THUMBPOSITION:
		case SB_THUMBTRACK:
			int offseting = iVscrollPos;
			iVscrollPos = HIWORD(wParam);
			offseting = iVscrollPos - abs(offseting);
			if (iVscrollPos >= ScrollParametres.top || iVscrollPos <= ScrollParametres.bottom)
			{
				tree.offsetXY(0, -treeOffset.y*offseting);
			}
			else if (iVscrollPos <= ScrollParametres.top)
			{
				iVscrollPos = ScrollParametres.top;
			}
			else if (iVscrollPos >= ScrollParametres.bottom)
			{
				iVscrollPos = ScrollParametres.bottom;
			}
		}
		
		paintBackground(hWnd, hdc, DrawWidth, DrawHight);
		tree.showGDI(hWnd, DrawWidth, DrawHight);
		
		if (iVscrollPos != GetScrollPos(hWnd, SB_VERT))
		{
			SetScrollPos(hWnd, SB_VERT, iVscrollPos, TRUE);
		}
		ReleaseDC(hWnd, hdc);
	}
	break;

	case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
		//Фоновая закраска окна
		break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void paintBackground(HWND hWnd, HDC hdc, int ScreenWidth, int ScreenHight)
{
	hdc = GetDC(hWnd);
	HRGN hrgnMenu;
	HBRUSH hBrush;
	hrgnMenu = CreateRectRgn(0, 0, ScreenWidth, ScreenHight);
	hBrush = CreateSolidBrush(RGB(10, 10, 10));
	FillRgn(hdc, hrgnMenu, hBrush);
	DeleteObject(hrgnMenu);
	DeleteObject(hBrush);
	ReleaseDC(hWnd, hdc);
}