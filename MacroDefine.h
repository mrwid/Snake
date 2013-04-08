#pragma once

//////////////////////////////////////////////////////////////////////////

//游戏状态
#define			CM_UN_START				0					//停留在起始界面
#define			CM_START_ED				1					//正在进行游戏

//////////////////////////////////////////////////////////////////////////

#define			CM_READY_GAME			(WM_USER + 100)		//准备游戏消息
#define			CM_START_GAME			(WM_USER + 101)		//开始游戏消息
#define			CM_MOVE_SNAKE			(WM_USER + 102)		//移动蛇身
#define			CM_GAME_OVER			(WM_USER + 103)		//游戏结束
#define			CM_GAME_NEXT			(WM_USER + 104)		//下一关
#define			CM_GAME_SUCCEED			(WM_USER + 105)		//全关成功
#define			CM_GAME_READY			(WM_USER + 106)		//游戏准备

//////////////////////////////////////////////////////////////////////////

#define			TMR_BEGIN				10000				//开始界面定时器
#define			TMR_PLAYING_READY		10001				//播放准备音效
#define			TMR_PLAYING_GO			10002				//播放开始音效
#define			TMR_IMPACE_TEST			10003				//碰撞检测正确性测试

#define			TMR_START_MOVE			10004				//移动蛇身

//////////////////////////////////////////////////////////////////////////

#define			DR_UP					20000				//上移动
#define			DR_DOWN					20001				//下移动
#define			DR_LEFT					20002				//左移动
#define			DR_RIGHT				20003				//右移动

//////////////////////////////////////////////////////////////////////////

#define			GAME_AGAIN				30000				//再来一局
#define			GAME_MAIN				30001				//回主菜单
#define			GAME_EXIT				30003				//退出游戏
