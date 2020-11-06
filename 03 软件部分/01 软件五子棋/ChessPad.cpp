#include "ChessPad.h"
#pragma once
namespace myChess
{
	//ChessPad类

	//01构造函数
	ChessPad::ChessPad(const cv::Mat& m)
	{
		this->ChessPadState = m.clone();
	}

	ChessPad::ChessPad(cv::Mat&& m)noexcept
	{
		this->ChessPadState = m.clone();
	}
	ChessPad::ChessPad():last_row(0),last_col(0)
	{
		ChessPadState = cv::Mat::zeros(cv::Size(row, col), CV_32SC1);
	}
	ChessPad::~ChessPad(){}
	//02 运算符重载
	ChessPad& ChessPad::operator=(const ChessPad& rhs)
	{
		this->ChessPadState = rhs.ChessPadState.clone();
		this->last_col = rhs.last_col;
		this->last_row = rhs.last_row;
		

		return *this;
	}

	std::ostream& operator<<(std::ostream& os, const ChessPad& rhs)
	{
		os << rhs.ChessPadState;
		return os;
	}

	//03 功能函数
	bool ChessPad::addChess(const Chess& chs)
	{
		int x, y;
		chs.getPoint(x,y);
		
		if (this->ChessPadState.at<int>(y, x) ==0) //说明为空，可以下入棋子
		{
			
			this->ChessPadState.at<int>(y, x) = chs.getColor();
			last_row = y;
			last_col = x;
			return true;
		}
		return false;
	}
	int  ChessPad::getChessPadState(int x, int y)const
	{
		return this->ChessPadState.at<int>(y, x);
	}
	int ChessPad::getChessPadState(Point p)const
	{
		int x, y;
		p.getPoint(x, y);
		return ChessPadState.at<int>(y, x);
	}
	int ChessPad::getChessPadState(cv::Point p)const
	{
		int x = p.x;
		int y = p.y;
		return ChessPadState.at<int>(y, x);
	}
}