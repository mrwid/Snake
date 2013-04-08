#include <windows.h>

#include "GameWndProc.h"
#include "resource.h"

//////////////////////////////////////////////////////////////////////////

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow )
{
	static TCHAR szGameName[] = TEXT( "Snake" );

	HWND		hwnd;
	RECT		rect;
	MSG			msg;
	WNDCLASS	wndclass;

	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hbrBackground	= (HBRUSH) GetStockObject( BLACK_BRUSH );
	wndclass.hCursor		= LoadCursor( NULL, IDC_ARROW );
	wndclass.hIcon			= LoadIcon( hInstance, MAKEINTRESOURCE(IDI_ICON_GAME) );
	wndclass.hInstance		= hInstance;
	wndclass.lpfnWndProc	= WndProc;
	wndclass.lpszClassName	= szGameName;
	wndclass.lpszMenuName	= NULL;
	wndclass.style			= CS_HREDRAW | CS_VREDRAW;

	if( !RegisterClass(&wndclass) )
	{
		MessageBox( NULL, TEXT("¥∞ø⁄¿‡◊¢≤· ß∞‹!"), TEXT("”¶”√≥Ã–Ú¥ÌŒÛ"), MB_OK | MB_ICONERROR );
		return 0;
	}

	rect.left = 0;	rect.top = 0;
	rect.right  = 800 + GetSystemMetrics(SM_CXFRAME);
	rect.bottom = 600 + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CXFRAME);
	AdjustWindowRect( &rect, WS_CAPTION, FALSE );

	hwnd = CreateWindow(
		szGameName, TEXT("Ã∞≥‘…ﬂ"),
		WS_CAPTION | WS_SYSMENU,
		(int)((GetSystemMetrics(SM_CXSCREEN)-rect.right) /2),
		(int)((GetSystemMetrics(SM_CYSCREEN)-rect.bottom)/2),
		rect.right, rect.bottom,
		NULL, NULL, hInstance, NULL
	);

	ShowWindow( hwnd, iCmdShow );
	UpdateWindow( hwnd );

	while( GetMessage( &msg, NULL, 0, 0 ) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}

	return msg.wParam;
}

//////////////////////////////////////////////////////////////////////////
