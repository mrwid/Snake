#include "PlayingProc.h"
#include "map_data.h"

//////////////////////////////////////////////////////////////////////////

void testImpace( HWND hwnd );

static GM_STATUS APP = {
	TEXT("贪吃蛇"),
	0,
	{0},
	{0},
	0,
	0
};

//////////////////////////////////////////////////////////////////////////

LRESULT PlayingProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen;
	HBRUSH hBrush;
	POINT pt = {0};

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
			//SetTimer( hwnd, TMR_IMPACE_TEST, 0, NULL );	//碰撞检测正确性测试
			//MessageBox( hwnd, TEXT("游戏开始!"), TEXT("消息"), MB_OK );
			//游戏开始
			break;

		//case TMR_IMPACE_TEST:
		//	testImpace( hwnd );
		//	break;
		}
		return 0;

	case WM_PAINT:
		hdc = BeginPaint( hwnd, &ps );

		hPen = CreatePen( PS_SOLID, 3, RGB(128, 128, 128) );
		hBrush = CreateSolidBrush( RGB(192, 192, 192) );
		SelectObject( hdc, hPen );
		SelectObject( hdc, hBrush );
		
		InitPlayingMap( hwnd, hdc, (HINSTANCE)GetWindowLong( hwnd, GWL_HINSTANCE ) );
		//APP.level = 7;
		DrawRandWall( hwnd, hdc, gm_map, APP.level );

	//APP.pt.x = 100;
	//APP.pt.y = 100;
		//PointImpaceTest( hwnd, APP.pt );

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

//////////////////////////////////////////////////////////////////////////

void getWallLineRect( int, RECT *, RECT * );	//获取地图障碍物i在窗口中的实际位置
BOOL borderImpace( RECT, POINT );			//边缘碰撞检测

//点障碍物的碰撞检测
BOOL PointImpaceTest( HWND hwnd, POINT pt )
{
	int i = 0;
	RECT rect = {0};
	RECT line = {0};

	GetClientRect( hwnd, &rect );

	if( borderImpace(rect, pt) )		//边缘碰撞
		return TRUE;

	for( i; i < 5; i++ )
	{
		getWallLineRect( i, &rect, &line );
		if( line.right - line.left == 0 )		//垂直障碍物
			if( pt.x > line.left && pt.x < line.left + 10 && pt.y > line.top && pt.y < line.bottom )
				return TRUE;

		if( line.bottom - line.top == 0 )		//水平障碍物
			if( pt.x > line.left && pt.x < line.right && pt.y > line.top && pt.y < line.top + 10 )
				return TRUE;
	}

	return FALSE;
}

//获取地图障碍物i在窗口中的实际位置
void getWallLineRect( int i, RECT *rect, RECT *line )
{
	//获取地图数据在窗口中的映射位置
	line->left   = (int)(gm_map[APP.level].line[i].x1 * rect->right);		//x1
	line->top    = (int)(gm_map[APP.level].line[i].y1 * rect->bottom);		//y1
	line->right  = (int)(gm_map[APP.level].line[i].x2 * rect->right);		//x2
	line->bottom = (int)(gm_map[APP.level].line[i].y2 * rect->bottom);		//y2

	//添加偏移坐标
	line->left	 += 10 - line->left % 10;
	line->top	 += 10 - line->top % 10;
	line->right	 += 10 - line->right % 10;
	line->bottom += 10 - line->bottom % 10;
}

//边缘碰撞检测
BOOL borderImpace( RECT rect, POINT pt )
{
	if( pt.x > rect.right-10 || pt.x < rect.left+10 )
		return TRUE;

	if( pt.y > rect.bottom-10 || pt.y < rect.top+10 )
		return TRUE;

	return FALSE;
}

/*
//检测碰撞正确性测试 - 测试结果: 正确
void testImpace( HWND hwnd )
{
	int i = 0;
	POINT pt = {0};
	HDC hdc;

	TCHAR szBuffer[28] = {0};
	wsprintf( szBuffer, "%s %i %s", TEXT("第"), APP.level+1, TEXT("关障碍物碰撞检测") );
	SetWindowText( hwnd, szBuffer );

	SetTimer( hwnd, TMR_IMPACE_TEST, 0, NULL );
	if( APP.level == 9 )
	{
		SetWindowText( hwnd, TEXT("贪吃蛇 - 碰撞检测正确性测试完毕") );
		KillTimer( hwnd, TMR_IMPACE_TEST );
	}
	hdc = GetDC(hwnd);
		
	for( pt.x = 0; pt.x < 800; pt.x++ )
		for( pt.y = 0; pt.y < 600; pt.y++ )
			if( !PointImpaceTest(hwnd, pt) )
				SetPixel( hdc, pt.x, pt.y, RGB(0, 128, 0) );

	Sleep(2000);
	APP.level ++;
	InvalidateRect( hwnd, NULL, TRUE );

	ReleaseDC( hwnd, hdc );
}
*/
