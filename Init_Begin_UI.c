#include "Init_Begin_UI.h"

//////////////////////////////////////////////////////////////////////////

void InitBeginUI( HDC hdc, HINSTANCE hInst )
{
	LOGFONT lf = {0};
	HFONT hFont;

	strcpy( lf.lfFaceName, "黑体" );
	lf.lfWidth			= 50;
	lf.lfHeight			= 100;
	lf.lfWeight			= FW_NORMAL;
	lf.lfCharSet		= GB2312_CHARSET;
	lf.lfPitchAndFamily = 35;

	hFont = CreateFontIndirect (&lf);
	SelectObject( hdc, hFont );
	SetBkColor( hdc, RGB(0, 0, 0) );
	SetTextCharacterExtra( hdc, 50 );
	SetTextColor( hdc, RGB(0, 170, 0) );

	TextOut( hdc, 200, 60, TEXT("贪吃蛇"), lstrlen("贪吃蛇") );

	DeleteObject( hFont );

	ShowGameMenu( hdc );
}

//////////////////////////////////////////////////////////////////////////

#define UNICODE

struct GameMenu
{
	int id;
	TCHAR szName[10];
	int xPos;
	int yPos;
}menu[] = {
	{ 1, TEXT("开始游戏"), 345, 250 },
	{ 2, TEXT("查看帮助"), 345, 300 },
	{ 3, TEXT("作者博客"), 345, 350 },
	{ 4, TEXT("退出游戏"), 345, 400 }
};

void ShowGameMenu( HDC hdc )
{
	int i = 0;

	HPEN hPen;
	HFONT hFont;
	HBRUSH hBrush;
	LOGFONT lf = {0};

	strcpy( lf.lfFaceName, "黑体" );
	lf.lfWidth		= 12;
	lf.lfHeight		= 25;
	lf.lfWeight			= FW_NORMAL;
	lf.lfCharSet		= GB2312_CHARSET;

	hPen = CreatePen( PS_SOLID, 5, RGB( 0, 0, 255 ) );
	hFont = CreateFontIndirect(&lf);
	hBrush = CreateSolidBrush( RGB(0, 0, 0) );

	SelectObject( hdc, hPen );
	SelectObject( hdc, hFont );
	SelectObject( hdc, hBrush );

	SetBkColor( hdc, RGB(0, 0, 0) );
	SetTextCharacterExtra( hdc, 3 );
	SetTextColor( hdc, RGB(255, 255, 255) );

	for( i; i < 4; i++ )
		TextOut( hdc, menu[i].xPos , menu[i].yPos, menu[i].szName, lstrlen(menu[i].szName) );

	DeleteObject(hPen);
	DeleteObject(hFont);
	DeleteObject(hBrush);
}