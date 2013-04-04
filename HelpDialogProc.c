#include "HelpDialogProc.h"

//////////////////////////////////////////////////////////////////////////

BOOL CALLBACK HelpDlgProc( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch( message )
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		switch( LOWORD(wParam) )
		{
		case IDC_BTN_OK:
			EndDialog( hDlg, 0 );
			return TRUE;
		}
		break;
	}
	return FALSE;
}