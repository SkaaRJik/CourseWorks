#pragma once
INT_PTR CALLBACK AddDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int dlgWidth;
	static int dlgHight;

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_SIZE:
		dlgWidth = LOWORD(lParam);
		dlgHight = HIWORD(lParam);
		break;
	case WM_INITDIALOG:
		return(INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			EndDialog(hDlg, LOWORD(wParam));
			TCHAR value[6];
			GetDlgItemText(hDlg, IDC_EDIT, value, 6);
			int valueInt = _wtoi(value);
			tree.Add(valueInt, true);
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