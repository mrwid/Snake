#pragma once

//////////////////////////////////////////////////////////////////////////

#include <windows.h>

#include "Init_Begin_UI.h"
#include "HelpDialogProc.h"
#include "MacroDefine.h"
#include "PlayingProc.h"
#include "resource.h"

//////////////////////////////////////////////////////////////////////////

LRESULT DealBeginMenuMsg( HWND, UINT, WPARAM, LPARAM );

//////////////////////////////////////////////////////////////////////////

//处理鼠标消息
int DealMouseMove( HWND );

//绘制菜单选中外框
void DrawSelectedBox( HWND, int );

//处理菜单点击消息
void DealMenuClick( int, HWND, HINSTANCE );
