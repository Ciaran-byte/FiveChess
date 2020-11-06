#include "Chess.h"
#include "ChessPad.h"
#include "Chesser.h"
#include "ResultDisplay.h"
#include "Judge.h"
#include "ArtificialIntelligence.h"
#ifndef _GAME_H
#define _GMAE_H



namespace myChess
{
	
	class game
	{
	public:
		static void gameInit();//用于设定系统是人人对战还是人机对战，会初始化棋手等的信息
		static void gameStart();


		
		

		
	private:
		//需要的系统类
		
		static ChessPad cp; //有默认初始化，用于保存存储数据
		static Judge j;  //用于评判谁是当前棋手，并且用于判断棋局结果
		static ArtificialIntelligence ai;  //人机对战的时候提供棋子
		static Chesser black; //黑棋
		static Chesser white; //白棋
		static ResultDisplay rd; //默认初始化，用于保存绘制输出的图
		

		//定义对战模式的常量
		static const int PP = 0;
		static const int PE = 1;
		static const int EE = 2;
		static int mode; //PP还是PE；

		//定义先后手的常量
		static const int PeopleFirst = 0;
		static const int ComputerFirst = 1;
		static int WhoIsFirst;

		//定义游戏结束标志位
		static int ok;
		static const int GOON = 0;
		static const int OVER = 1;


		//需要的工具函数，也就是选择人机还是选择人人的回调函数
		static int getWhoIsFirst() { return WhoIsFirst; }
		static void PPMouseCallBack(int event, int x, int y, int flags, void* param); //人人的回调函数
		static void PEMouseCallBack(int event, int x, int y, int flags, void* param); //人机的回调函数
		static void EEMouseCallBack(int event, int x, int y, int flags, void* param); //机机的回调函数
		//
		static bool PEok;
	};


}

#endif

