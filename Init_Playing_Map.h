#pragma once

//////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>

#include "cu_map.h"

#include "MacroDefine.h"

//////////////////////////////////////////////////////////////////////////

void InitPlayingMap( HWND, HDC, POINT, CMAP *, int );

//////////////////////////////////////////////////////////////////////////

void DrawBrickWall( HWND, HDC );				//绘制四周砖块

void DrawRandWall( HWND, HDC, CMAP*, int );		//绘制随机障碍物

void DrawRandomFood( HDC, POINT );				//绘制食物


