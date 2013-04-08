#pragma once

//////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "DealBeginMenuMsg.h"
#include "GameOverDlgProc.h"
#include "Init_Playing_Map.h"
#include "MacroDefine.h"
#include "cu_map.h"
#include "resource.h"

//////////////////////////////////////////////////////////////////////////

typedef struct GameStatus
{
	TCHAR	szGameTitle[256];		//标题栏内容
	int		level;					//当前游戏关数
	POINT	body[512];				//蛇身坐标
	POINT	food;					//食物所在坐标
	int		direction;				//当前行动方向
	int		len;					//蛇身长度
	int		score;					//游戏得分
}GM_STATUS;

//////////////////////////////////////////////////////////////////////////

LRESULT PlayingProc( HWND, UINT, WPARAM, LPARAM );

BOOL PointImpaceTest( HWND, POINT, int );		//点与障碍物的碰撞检测

void GetRandomFoodPlace( HWND, POINT* );		//生成随机食物坐标

LRESULT CALLBACK StartPlaying( HWND, UINT, WPARAM, LPARAM );		//开始游戏

