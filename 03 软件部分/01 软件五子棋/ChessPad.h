#include<iostream>
#include<opencv2/opencv.hpp>
# include "Chess.h"


#ifndef _CHESS_PAD_H
#define _CHESS_PAD_H

namespace myChess
{
	
	class ChessPad
	{
	public:
		//友元
		friend std::ostream& operator<<(std::ostream& os, const ChessPad& rhs);
		friend class ResultDisplay;
		//01 构造函数和析构函数

		//默认构造
		ChessPad();
		

		//拷贝构造
		ChessPad(const cv::Mat& m);

		//移动构造
		ChessPad(cv::Mat&& m)noexcept;

		//析构函数
		~ChessPad();

		//02 运算符重载
		//拷贝赋值
		ChessPad& operator=(const ChessPad&);

		//03 功能函数

		//当落子的时候，更新棋盘的状态
		bool addChess(const Chess&);

		////查询棋盘上具体某个点的状态
		int getChessPadState(int x,int y)const;
		int getChessPadState(Point p)const;
		int getChessPadState(cv::Point p)const;

		int getLastRow()const
		{
			return last_row;
		}
		int getLastCol()const
		{
			return last_col;
		}
		int getLastColor()const
		{
			return getChessPadState(last_col, last_row);
		}
	
	private:
		 const int row=16;
		 const int col=16;
		cv::Mat ChessPadState;
		int last_row;
		int last_col;

	};
	
	
}


#endif