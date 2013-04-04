#pragma once

//////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <windows.h>

#include "Init_Playing_Map.h"
#include "MacroDefine.h"
#include "cu_map.h"
#include "resource.h"

//////////////////////////////////////////////////////////////////////////

typedef struct GameStatus
{
	TCHAR	szGameTitle[256];		//标题栏内容
	int		level;					//当前游戏关数
	POINT	head;					//蛇头部所在坐标
	POINT	food;					//食物所在坐标
	int		len;					//蛇身长度
	int		score;					//游戏得分
}GM_STATUS;

//////////////////////////////////////////////////////////////////////////

LRESULT PlayingProc( HWND, UINT, WPARAM, LPARAM );

BOOL PointImpaceTest( HWND, POINT );			//点与障碍物的碰撞检测
