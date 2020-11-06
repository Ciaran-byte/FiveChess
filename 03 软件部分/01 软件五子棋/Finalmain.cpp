#include<iostream>
#include<opencv2/opencv.hpp>
#include "game.h"
#include <functional>
using namespace std;
using namespace cv;


myChess::ResultDisplay  myChess::game::rd; //默认初始化，用于保存绘制输出的图
//需要的系统类

myChess::ChessPad  myChess::game::cp; //有默认初始化，用于保存存储数据
myChess::Judge  myChess::game::j;  //用于评判谁是当前棋手，并且用于判断棋局结果
myChess::ArtificialIntelligence myChess::game::ai;  //人机对战的时候提供棋子
myChess::Chesser  myChess::game::black; //黑棋
myChess::Chesser  myChess::game::white; //白棋



//定义对战模式的常量
const int  myChess::game::PP;
const int  myChess::game::PE;
const int  myChess::game::EE;

int  myChess::game::mode; //PP还是PE还是EE；

//定义先后手的常量
const int  myChess::game::PeopleFirst;
const int  myChess::game::ComputerFirst;
int  myChess::game::WhoIsFirst;

//定义游戏结束标志位
int  myChess::game::ok;
const int  myChess::game::GOON;
const int  myChess::game::OVER;

bool myChess::game::PEok;

int main()
{
	myChess::game g;
	g.gameInit();
	g.gameStart();
	

	return 0;
}

