#include "Init_Playing_Map.h"

//////////////////////////////////////////////////////////////////////////

void InitPlayingMap( HWND hwnd, HDC hdc, HINSTANCE hInst )
{
	DrawBrickWall( hwnd, hdc );
}

//////////////////////////////////////////////////////////////////////////

//»­×©¿é
void DrawBrickWall( HWND hwnd, HDC hdc )
{
	int x = 0, y = 0;

	RECT rect = {0};

	HPEN hPen;
	HBRUSH hBrush;

	hPen = CreatePen( PS_SOLID, 3, RGB(128, 128, 128) );
	hBrush = CreateSolidBrush( RGB(192, 192, 192) );

	SelectObject( hdc, hPen );
	SelectObject( hdc, hBrush );

	GetClientRect( hwnd, &rect );

	for( x; x < rect.right / 10 + 1; x++ )
	{
		RoundRect( hdc, x*10, 0, x*10+10, 10, 3, 3 );
		RoundRect( hdc, x*10, rect.bottom-10, x*10+10, rect.bottom, 3, 3 );
	}
	
	for( y; y < rect.bottom / 10 + 1; y++ )
	{
		RoundRect( hdc, 0, y*10, 10, y*10+10, 3, 3 );
		RoundRect( hdc, rect.right-10, y*10, rect.right, y*10+10, 3, 3 );
	}

	DeleteObject( hPen );
	DeleteObject( hBrush );
}

//³õÊ¼»¯Ëæ»úÇ½±Ú×ø±ê
void InitRandWallPos( HWND hwnd, POINT *pt )
{
	RECT rect = {0};
	GetClientRect( hwnd, &rect );
	
	srand( (unsigned)time( NULL ) );
	
	pt[0].x = rand() % (rect.right - 60);
	pt[0].y = rand() % (rect.bottom - 60);

	pt[1].x = rand() % (rect.right - 60);
	pt[1].y = rand() % (rect.bottom - 60);
}

//»­Ëæ»úÇ½
void DrawRandWall( HWND hwnd, HDC hdc, POINT *pt )
{
	int i = 0, xPos = 0, yPos = 0, length = 0;

	HPEN hPen;
	HBRUSH hBrush;

	hPen = CreatePen( PS_SOLID, 3, RGB(128, 128, 128) );
	hBrush = CreateSolidBrush( RGB(192, 192, 192) );

	SelectObject( hdc, hPen );
	SelectObject( hdc, hBrush );
	
	//»æÖÆËæ»úÇ½±Ú
	/*
	xPos = pt[0].x;		yPos = pt[0].y;
	length = (int)sqrt( (pt[1].x - pt[0].x)*(pt[1].x - pt[0].x) + (pt[1].y - pt[0].y)*(pt[1].y - pt[0].y) );
	for( i; i < abs(length); i+=10 )
	{
		RoundRect( hdc, xPos, yPos, xPos+10, yPos+10, 3, 3 );
		xPos += 10;		yPos += 10;
	}
	*/

	DeleteObject( hPen );
	DeleteObject( hBrush );
}