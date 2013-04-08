#include "PlayingProc.h"
#include "GameWndProc.h"
#include "map_data.h"

//////////////////////////////////////////////////////////////////////////

void testImpace( HWND hwnd );
void testFoodPlace( HWND hwnd );

static GM_STATUS APP = {
	TEXT("贪吃蛇"),
	0,
	{ {20, 20} },
	{-10, -10},
	DR_RIGHT,
	5,
	0
};

//////////////////////////////////////////////////////////////////////////

LRESULT PlayingProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	HDC hdc;
	PAINTSTRUCT ps;
	POINT pt = {0};

	switch( message )
	{
	case WM_TIMER:
		switch( wParam )
		{
		case TMR_PLAYING_READY:
			srand( (unsigned int)time(0) );
			SetTimer( hwnd, TMR_PLAYING_READY, 1000*60, NULL );			//调整定时器为60秒
			PlaySound( MAKEINTRESOURCE( IDR_READY ), (HINSTANCE)GetWindowLong( hwnd, GWL_HINSTANCE ), SND_RESOURCE | SND_ASYNC );
			KillTimer( hwnd, TMR_PLAYING_READY );
			SetTimer( hwnd, TMR_PLAYING_GO, 1500, NULL );				//启动游戏启动定时器
			GetRandomFoodPlace( hwnd, &APP.food );
			break;

		case TMR_PLAYING_GO:
			KillTimer( hwnd, TMR_PLAYING_GO );
			PlaySound( MAKEINTRESOURCE( IDR_GO ), (HINSTANCE)GetWindowLong( hwnd, GWL_HINSTANCE ), SND_RESOURCE | SND_ASYNC );
			//游戏开始
			PostMessage( hwnd, CM_START_GAME, 0, 0 );
			SetTimer( hwnd, TMR_START_MOVE, 200, 0 );
			break;
		}
		return 0;

	case WM_PAINT:
		hdc = BeginPaint( hwnd, &ps );
		InitPlayingMap( hwnd, hdc, APP.food, gm_map, APP.level );
		EndPaint( hwnd, &ps );
		return 0;

	case CM_START_GAME:
		SetWindowLong( hwnd, GWL_WNDPROC, (long)StartPlaying );
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	
	return DefWindowProc( hwnd, message, wParam, lParam );
}

//////////////////////////////////////////////////////////////////////////

void getWallLineRect( int, RECT *, RECT *, int );	//获取地图障碍物i在窗口中的实际位置
BOOL borderImpace( RECT, POINT, int );				//边缘碰撞检测

//点障碍物的碰撞检测
BOOL PointImpaceTest( HWND hwnd, POINT pt, int exc )
{
	int i = 0;
	RECT rect = {0};
	RECT line = {0};

	GetClientRect( hwnd, &rect );

	if( borderImpace(rect, pt, exc) )		//边缘碰撞
		return TRUE;

	for( i = 0; i < 5; i++ )
	{
		getWallLineRect( i, &rect, &line, exc );
		if( line.right - line.left == 0 )		//垂直障碍物
			if( pt.x >= line.left - exc && pt.x < line.left + 10 + exc && \
				pt.y >= line.top - exc  && pt.y < line.bottom + exc )
				return TRUE;
			
		if( line.bottom - line.top == 0 )		//水平障碍物
			if( pt.x >= line.left - exc && pt.x < line.right + exc && \
				pt.y >= line.top - exc  && pt.y < line.top + 10 + exc )
				return TRUE;
	}

	return FALSE;
}

//////////////////////////////////////////////////////////////////////////

//获取地图障碍物i在窗口中的实际位置
void getWallLineRect( int i, RECT *rect, RECT *line, int exc )
{
	//获取地图数据在窗口中的映射位置
	line->left   = (int)(gm_map[APP.level].line[i].x1 * rect->right);		//x1
	line->top    = (int)(gm_map[APP.level].line[i].y1 * rect->bottom);		//y1
	line->right  = (int)(gm_map[APP.level].line[i].x2 * rect->right);		//x2
	line->bottom = (int)(gm_map[APP.level].line[i].y2 * rect->bottom);		//y2

	//添加偏移坐标
	if( line->left )
	{
		line->left	 += (10 - line->left   % 10);
		line->top	 += (10 - line->top	   % 10);
		line->right	 += (10 - line->right  % 10);
		line->bottom += (10 - line->bottom % 10);
	}
}

//////////////////////////////////////////////////////////////////////////

//边缘碰撞检测
BOOL borderImpace( RECT rect, POINT pt, int exc )
{
	if( pt.x > rect.right-20-exc || pt.x < rect.left+10 )
		return TRUE;

	if( pt.y > rect.bottom-20-exc || pt.y < rect.top+10 )
		return TRUE;

	return FALSE;
}

//////////////////////////////////////////////////////////////////////////

//生成随机食物坐标
void GetRandomFoodPlace( HWND hwnd, POINT *ptFood )
{
	int i = 0, x = 0, y = 0;
	RECT rect = {0}, line = {0};
	POINT pt = {0};

	ptFood->x = ptFood->y = 0;

	GetClientRect( hwnd, &rect );
	while( PointImpaceTest( hwnd, *ptFood, 10 ) )
	{
		x = rand()%rect.right;		y = rand()%rect.bottom;
		ptFood->x = x - x%10;		ptFood->y = y - y%10;
	}
}

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

int dealKeywordMsg( HWND hwnd, WPARAM );	//处理键盘消息
void moveSnake( );							//移动蛇身
void eraseNode( HWND, POINT );				//擦除一个蛇身节点
void drawSnakeBody( HWND );					//绘制蛇身
BOOL testEating( HWND );					//检测食物是否被吃掉
void updateGameInfo( HWND );				//更新游戏标题栏信息
void resetGameStatus();						//重置游戏状态
void nextLevel( HWND );						//下一关
BOOL testEatSelf( HWND );					//测试是否吃到自己
void gameOver( HWND );						//游戏结束
void gameAgain( HWND );						//再来一局

void startSnakeMove( HWND );				//蛇开始移动(封装移动方法)
//////////////////////////////////////////////////////////////////////////

//开始游戏
LRESULT CALLBACK StartPlaying( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	HDC hdc;
	PAINTSTRUCT ps;
	
	switch( message )
	{
	case WM_PAINT:
		hdc = BeginPaint( hwnd, &ps );
		InitPlayingMap( hwnd, hdc, APP.food, gm_map, APP.level );
		EndPaint( hwnd, &ps );
		return 0;

	case WM_TIMER:
		switch( wParam )
		{
			case TMR_START_MOVE:
				startSnakeMove( hwnd );
				break;
		}
		return 0;
			
	case CM_GAME_OVER:
		gameOver( hwnd );
		break;

	case CM_GAME_NEXT:
		nextLevel( hwnd );
		break;

	case CM_GAME_SUCCEED:
		MessageBox( NULL, "ok", "", 0 );
		break;

	case WM_KEYDOWN:
		dealKeywordMsg( hwnd, wParam );
		return 0;
		
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	
	return DefWindowProc( hwnd, message, wParam, lParam );
}

//////////////////////////////////////////////////////////////////////////

//处理键盘消息
int dealKeywordMsg( HWND hwnd, WPARAM wParam )
{
	switch( wParam )
	{
	case VK_UP:
	case 'W':
		if(APP.direction != DR_DOWN)	APP.direction = DR_UP;		break;

	case VK_DOWN:
	case 'S':
		if(APP.direction != DR_UP)		APP.direction = DR_DOWN;	break;

	case VK_LEFT:
	case 'A':
		if(APP.direction != DR_RIGHT)	APP.direction = DR_LEFT;	break;

	case VK_RIGHT:
	case 'D':
		if(APP.direction != DR_LEFT)	APP.direction = DR_RIGHT;	break;

	case VK_CONTROL:
		PostMessage( hwnd, WM_TIMER, TMR_START_MOVE, 0 );
		break;

	case VK_ESCAPE:
		if ( MessageBox( NULL, TEXT("游戏正在运行, 确定退出吗?"), \
			TEXT("确认"), MB_OKCANCEL | MB_ICONQUESTION ) == IDOK )
			PostQuitMessage(0);
		break;
	}
	return 0;
}

//移动蛇身
void moveSnake( )
{
	int i = APP.len;
	for( i; i > 0; i-- )
		APP.body[i] = APP.body[i-1];
	
	switch( APP.direction )
	{
	case DR_UP:
		APP.body[0].y -= 10;	break;

	case DR_DOWN:
		APP.body[0].y += 10;	break;

	case DR_LEFT:
		APP.body[0].x -= 10;	break;

	case DR_RIGHT:
		APP.body[0].x += 10;	break;
	}
}

//擦除蛇身的一个节点
void eraseNode( HWND hwnd, POINT ptNode )
{
	HDC hdc;
	HPEN hPen;
	HBRUSH hBrush;

	hdc = GetDC( hwnd );
	hPen = CreatePen( PS_SOLID, 3, RGB(0, 0, 0) );
	hBrush = CreateSolidBrush( RGB(0, 0, 0) );
	SelectObject( hdc, hPen );
	SelectObject( hdc, hBrush );

	Rectangle( hdc, ptNode.x, ptNode.y, ptNode.x+10, ptNode.y+10 );

	DeleteObject( hBrush );
	ReleaseDC( hwnd, hdc );
}

//绘制蛇身
void drawSnakeBody( HWND hwnd )
{
	int i = 0;
	HDC hdc;
	HPEN hPen;
	HBRUSH hBrush;
	
	hdc = GetDC( hwnd );
	hPen = CreatePen( PS_SOLID, 3, RGB(0, 128, 0) );
	hBrush = CreateSolidBrush( RGB(0, 255, 0) );
	SelectObject( hdc, hPen );
	SelectObject( hdc, hBrush );
	
	for( i; i <= APP.len; i++ )
		RoundRect( hdc, APP.body[i].x, APP.body[i].y, APP.body[i].x+10, APP.body[i].y+10, 3, 3 );
	eraseNode( hwnd, APP.body[APP.len] );

	DeleteObject( hPen );
	DeleteObject( hBrush );
	ReleaseDC( hwnd, hdc );
}

//检测食物是否被吃掉
BOOL testEating( HWND hwnd )
{
	if( APP.food.x == APP.body[0].x && APP.food.y == APP.body[0].y )
	{
		PlaySound( MAKEINTRESOURCE( IDR_EATING ), (HINSTANCE)GetWindowLong( hwnd, GWL_HINSTANCE ), SND_RESOURCE | SND_ASYNC );
		APP.len += 2;
		APP.score += 10;
		if( (APP.level == APP.score / 100-1) && (APP.level < 9) )
		{
			APP.level++;
			PostMessage( hwnd, CM_GAME_NEXT, 0, 0 );
		}

		GetRandomFoodPlace( hwnd, &APP.food );
		return TRUE;
	}

	return FALSE;
}

//更新游戏信息
void updateGameInfo( HWND hwnd )
{
	if( APP.score < 1000 )
		wsprintf( APP.szGameTitle, "贪吃蛇  第 %d 关  得分: %d  进度: %d/10",
		APP.level + 1, APP.score, APP.score/10%10 );
	else		//第十关以后的无尽模式统计方案
		wsprintf( APP.szGameTitle, "贪吃蛇  第 %d 关  得分: %d  进度: %d/10",
		APP.level + 1, APP.score, (APP.score-1000)/10 );
	SetWindowText( hwnd, APP.szGameTitle );
}

//重置游戏状态
void resetGameStatus()
{
	int i = APP.len;
	APP.direction = DR_RIGHT;
	
	APP.body[0].x = 10;		APP.body[0].y = 20;
	APP.food.x = -10;		APP.food.y = -10;

	for( i; i > 0; i-- )
	{
		APP.body[i].x = APP.body[0].x;
		APP.body[i].y = APP.body[0].y;
	}
}

//下一关
void nextLevel( HWND hwnd )
{
	PlaySound( MAKEINTRESOURCE( IDR_NEXT ), (HINSTANCE)GetWindowLong( hwnd, GWL_HINSTANCE ), SND_RESOURCE | SND_ASYNC );
	resetGameStatus();
	InvalidateRect( hwnd, NULL, TRUE );
}

//测试是否吃到自己
BOOL testEatSelf( HWND hwnd )
{
	int i = APP.len;
	for( i; i > 0; i-- )
		if( APP.body[0].x == APP.body[i].x && APP.body[0].y == APP.body[i].y )
		{
			PostMessage( hwnd, CM_GAME_OVER, 0, 0 );
			return TRUE;
		}

	return FALSE;
}

//游戏结束
void gameOver( HWND hwnd )
{
	int menuID = 0;

	KillTimer( hwnd, TMR_START_MOVE );
	PlaySound( MAKEINTRESOURCE( IDR_GAME_OVER ), (HINSTANCE)GetWindowLong( hwnd, GWL_HINSTANCE ), SND_RESOURCE );
	InvalidateRect( hwnd, NULL, TRUE );
	
	menuID = DialogBox(
		(HINSTANCE)GetWindowLong( hwnd, GWL_HINSTANCE ),
		MAKEINTRESOURCE(IDD_GAMEOVER_DLG),
		hwnd, GameOverProc
	);
	
	switch( menuID )
	{
	case GAME_AGAIN:
		gameAgain( hwnd );
		break;
		
	case GAME_MAIN:
		SetWindowLong( hwnd, GWL_WNDPROC, (long)DealBeginMenuMsg );
		PostMessage( hwnd, CM_GAME_READY, 0, 0 );
		resetGameStatus();
		APP.level = 0;		APP.score = 0;
		InvalidateRect( hwnd, NULL, TRUE );
		SetWindowText( hwnd, TEXT("贪吃蛇") );
		return ;
		
	case GAME_EXIT:
		PostMessage( hwnd, WM_DESTROY, 0, 0 );
		return ;
	}
}

//再来一局
void gameAgain( HWND hwnd )
{
	resetGameStatus();
	APP.level = 0;
	APP.score = 0;

	SetWindowLong( hwnd, GWL_WNDPROC, (long)PlayingProc );
	PostMessage( hwnd, WM_TIMER, TMR_PLAYING_READY, 0 );
	InvalidateRect( hwnd, NULL, TRUE );
}

//////////////////////////////////////////////////////////////////////////

//蛇开始移动 (封装移动方法)
void startSnakeMove( HWND hwnd )
{
	if( PointImpaceTest(hwnd, APP.body[0], 0) )
	{
		PostMessage( hwnd, CM_GAME_OVER, 0, 0 );
		return ;
	}
	testEating( hwnd );
	drawSnakeBody( hwnd );
	moveSnake( );
	testEatSelf( hwnd );
	updateGameInfo( hwnd );
	InvalidateRect( hwnd, NULL, FALSE );
}