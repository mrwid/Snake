#include "PlayingProc.h"
#include "map_data.h"

//////////////////////////////////////////////////////////////////////////

LRESULT PlayingProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen;
	HBRUSH hBrush;

	switch( message )
	{
	case WM_TIMER:
		switch( wParam )
		{
		case TMR_PLAYING_READY:
			SetTimer( hwnd, TMR_PLAYING_READY, 1000*60, NULL );			//调整定时器为60秒
			PlaySound( MAKEINTRESOURCE( IDR_READY ), (HINSTANCE)GetWindowLong( hwnd, GWL_HINSTANCE ), SND_RESOURCE | SND_ASYNC );
			KillTimer( hwnd, TMR_PLAYING_READY );
			SetTimer( hwnd, TMR_PLAYING_GO, 1500, NULL );				//启动游戏启动定时器
			break;

		case TMR_PLAYING_GO:
			KillTimer( hwnd, TMR_PLAYING_GO );
			PlaySound( MAKEINTRESOURCE( IDR_GO ), (HINSTANCE)GetWindowLong( hwnd, GWL_HINSTANCE ), SND_RESOURCE | SND_ASYNC );
			//MessageBox( hwnd, TEXT("游戏开始!"), TEXT("消息"), MB_OK );
			//游戏开始
			break;
		}
		return 0;

	case WM_PAINT:
		hdc = BeginPaint( hwnd, &ps );

		hPen = CreatePen( PS_SOLID, 3, RGB(128, 128, 128) );
		hBrush = CreateSolidBrush( RGB(192, 192, 192) );
		SelectObject( hdc, hPen );
		SelectObject( hdc, hBrush );
		
		InitPlayingMap( hwnd, hdc, (HINSTANCE)GetWindowLong( hwnd, GWL_HINSTANCE ) );
		DrawRandWall( hwnd, hdc, gm_map, 9 );

		DeleteObject( hPen );
		DeleteObject( hBrush );

		EndPaint( hwnd, &ps );
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc( hwnd, message, wParam, lParam );
}
