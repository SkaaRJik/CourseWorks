#pragma once
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
			int valueInt = _wtoi(value);
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