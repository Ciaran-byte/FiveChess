#include<vector>
#include "Chess.h"
#include "ChessPad.h"
#ifndef _ARTIFICIAL_INTELLIGENCE_H
#define _ARTIFICIAL_INTELLIGENCE_H


namespace myChess
{
	
	class Situation {//当前位置的形式，打分根据这个来打
	public:
		//构造函数
		Situation()
		{
			win5 = 0;//5连珠
			alive4 = 0;//活4
			die4 = 0;//死4
			lowdie4 = 0;//死4低级版本
			alive3 = 0;//活3
			tiao3 = 0;//跳3
			die3 = 0;//死3
			alive2 = 0;//活2
			lowalive2 = 0;//低级活2
			die2 = 0;//死2
			nothreat = 0;//没有威胁
		}

		//成员变量
		int win5;//5连珠
		int alive4;//活4
		int die4;//死4
		int lowdie4;//死4低级版本
		int alive3;//活3
		int tiao3;//跳3
		int die3;//死3
		int alive2;//活2
		int lowalive2;//低级活2
		int die2;//死2
		int nothreat;//没有威胁

	};
	class ArtificialIntelligence
{
public:
	//获取下的最佳位置
	cv::Point getPosition(const ChessPad&, int color); 
private:
	//01 成员变量
	//用来标记基本棋形的

	static const int WIN5 = 0;//0->5连珠
	static const int ALIVE4 = 1;//1->活4
	static const int DIE4 = 2;//2->死4
	static const int LOWDIE4 = 3;//3->死4的低级版本
	static const int ALIVE3 = 4;//3->活3
	static const int TIAO3 = 5;//5->跳3
	static const int DIE3 = 6;//6->死3
	static const int ALIVE2 = 7;//7->活2
	static const int LOWALIVE2 = 8;//8->低级活2
	static const int DIE2 = 9;//9->死2
	static const int NOTHREAT = 10;//10->没有威胁


	//打分等级
	static const int LevelOne = 100000;//成五
	static const int Leveltwo = 10000;//成活4 或 双死4 或 死4活3
	static const int Levelthree = 5000;//双活3
	static const int Levelfour = 1000;//死3高级活3
	static const int Levelfive = 500;//死四
	static const int Levelsix = 400;//低级死四
	static const int Levelseven = 100;//单活3
	static const int LevelEight = 90;//跳活3
	static const int LevelNight = 50;//双活2
	static const int LevelTen = 10;//活2
	static const int LevelEleven = 9;//低级活2
	static const int LevelTwelve = 5;//死3
	static const int LevelThirteen = 2;//死2
	static const int LevelFourteen = 1;//没有威胁
	static const int LevelFiveteen = 0;//不能下
	//02 工具函数
	//02-1 对给定棋子组合判断是哪一类基本棋形
	int JudgeType(const std::vector<int>&); //用来判断给定的棋子组合属于哪一类的基本棋形
	
	//02-2 在某点假定加入一个棋子，获取这个棋子的四个方向的棋子组合
	void getChess(
		std::vector<int>& chess,
		const ChessPad& chp,
		cv::Point p,
		int mycolor,
		int direction
		); //获取指定方向棋局
	//02-3 获取某一个方向的棋子，并且判断是什么基本棋形
	int getType(
		const ChessPad& chp,
		cv::Point p,
		int mycolor,
		int direction
	);

	//02-4 根据情况打分
	int giveScore(Situation situation);//根据形势，给分

	//02-5 综合四个方向进行判分
	int judgeChessSituation(const ChessPad&, cv::Point p, int color);

	
};

}

#endif

