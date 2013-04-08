#include "DealBeginMenuMsg.h"

//////////////////////////////////////////////////////////////////////////

LRESULT DealBeginMenuMsg( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	static HINSTANCE hInst;

	static int menuID = 0;
	static int oldMenuID = 0;

	HDC			hdc;
	PAINTSTRUCT ps;

	switch( message )
	{
	case WM_CREATE:
		hInst =(HINSTANCE) GetWindowLong( hwnd, GWL_HINSTANCE );
		PostMessage( hwnd, CM_GAME_READY, 0, 0 );
		return 0;

	case WM_PAINT:
		hdc = BeginPaint( hwnd, &ps );
		InitBeginUI( hdc, hInst );
		EndPaint( hwnd, &ps );
		return 0;

	case CM_GAME_READY:
		SetTimer( hwnd, TMR_BEGIN, 60, NULL );
		PlaySound( MAKEINTRESOURCE( IDR_GAME_START ), (HINSTANCE)GetWindowLong( hwnd, GWL_HINSTANCE ), SND_RESOURCE | SND_ASYNC | SND_LOOP );
		return 0;

	case CM_START_GAME:
		InvalidateRect( hwnd, NULL, TRUE );
		SetWindowLong( hwnd, GWL_WNDPROC, (long)PlayingProc );
		SetTimer( hwnd, TMR_PLAYING_READY, 500, NULL );			//开启游戏准备音效定时器
		PlaySound( NULL, NULL, SND_FILENAME );					//终止当前音效
		return CM_START_GAME;

	case WM_KEYDOWN:
		switch( wParam )
		{
		case VK_RETURN:
			//预留处理
			break;
		}
		return 0;

	case WM_TIMER:
		switch( wParam )
		{
		case TMR_BEGIN:
			menuID = DealMouseMove( hwnd );
			if( menuID != oldMenuID && menuID > 0 )
			{
				DrawSelectedBox( hwnd, 240 + (menuID-1) * 50 );
				oldMenuID = menuID;
			}	
			break;
		}
		return 0;

	case WM_LBUTTONDOWN:
		//PlaySound( MAKEINTRESOURCE( IDR_EATING ), hInst , SND_RESOURCE | SND_ASYNC );
		DealMenuClick( DealMouseMove(hwnd), hwnd, hInst );
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc( hwnd, message, wParam, lParam );
}

//////////////////////////////////////////////////////////////////////////

//处理鼠标消息
int DealMouseMove( HWND hwnd )
{
	POINT pt;

	GetCursorPos(&pt) ;
	ScreenToClient( hwnd, &pt ) ;

	if( pt.x < 340 )	return 0;
	if( pt.x > 450 )	return 0;
	if( pt.y < 245 )	return 0;
	if( pt.y > 435 )	return 0;

	if( pt.y > 250 && pt.y < 285 )
		return 1;

	if( pt.y > 300 && pt.y < 335 )
		return 2;

	if( pt.y > 350 && pt.y < 385 )
		return 3;

	if( pt.y > 400 && pt.y < 435 )
		return 4;

	return 0;
}

//////////////////////////////////////////////////////////////////////////

//绘制菜单选中外框
void drawGreenBox( HWND hwnd, int yPos );
void drawBlackBox( HWND hwnd, int yPos );

void DrawSelectedBox( HWND hwnd, int yPos )
{
	int i = 0;
	for( i; i < 4; i++ )
	{
		drawBlackBox( hwnd, 240 + i * 50 );
	}
	drawGreenBox( hwnd, yPos );
}

//////////////////////////////////////////////////////////////////////////

//绘制一个绿色的边框
void drawGreenBox( HWND hwnd, int yPos )
{
	HDC hdc;
	HPEN hPen;
	POINT apn[5] = { {335, yPos}, {460, yPos}, {460, yPos+45}, {335, yPos+45}, {335, yPos} } ;        //坐标组

	hdc = GetDC( hwnd );
	hPen = CreatePen( PS_SOLID, 3, RGB(0, 128, 0) );
	SelectObject( hdc, hPen );
	Polyline( hdc, apn, 5 );

	ReleaseDC( hwnd, hdc );
}

//绘制黑色边框
void drawBlackBox( HWND hwnd, int yPos )
{
	HDC hdc;
	HPEN hPen;
	POINT apn[5] = { {335, yPos}, {460, yPos}, {460, yPos+45}, {335, yPos+45}, {335, yPos} } ;        //坐标组

	hdc = GetDC( hwnd );
	hPen = CreatePen( PS_SOLID, 3, RGB(0, 0, 0) );
	SelectObject( hdc, hPen );
	Polyline( hdc, apn, 5 );

	ReleaseDC( hwnd, hdc );
}

//处理鼠标点击消息
void DealMenuClick( int menuID, HWND hwnd, HINSTANCE hInst )
{
	switch( menuID )
	{
	case 1:
		//MessageBox( NULL, "start", "", 0 );
		KillTimer( hwnd, TMR_BEGIN );
		PostMessage( hwnd, CM_START_GAME, 0, 0 );
		return;
	case 2:
		DialogBox( hInst, MAKEINTRESOURCE(IDD_HELP_FORM), hwnd, HelpDlgProc );
		return;
	case 3:
		ShellExecute( NULL, "open", "http://www.cnblogs.com/mr-wid/", NULL, NULL, SW_SHOW );
		return;
	case 4:
		PostQuitMessage(0);
		return;
	}
}
