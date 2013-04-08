#include "GameOverDlgProc.h"
#include "MacroDefine.h"

//////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK GameOverProc( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
	HWND hStatic;
	LOGFONT lf = {0};
	HFONT hFont;

	strcpy( lf.lfFaceName, "ËÎÌו" );
	lf.lfWidth			= 30;
	lf.lfHeight			= 50;
	lf.lfWeight			= FW_NORMAL;
	lf.lfCharSet		= GB2312_CHARSET;
	lf.lfPitchAndFamily = 35;

	hFont = CreateFontIndirect (&lf);
	
	switch( message )
	{
	case WM_INITDIALOG:
		hStatic = CreateWindow( TEXT("static"), TEXT("GAME OVER !"), WS_CHILD | WS_VISIBLE, 25, 50, 400, 50, hDlg, NULL, NULL, NULL );
		SendMessage( hStatic, WM_SETFONT, (WPARAM)hFont, 0 );
		return TRUE;

	case WM_COMMAND:
		switch( LOWORD(wParam) )
		{
		case IDC_EXIT_GAME:
			EndDialog( hDlg, GAME_EXIT );
			return TRUE;
			
		case IDC_GAME_AGAIN:
			EndDialog( hDlg, GAME_AGAIN );
			return TRUE;
	
		case IDC_RETURN_MAIN:
			EndDialog( hDlg, GAME_MAIN );
			return TRUE;
		}
		break;
	}
	return 0;
}
