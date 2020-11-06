#include<iostream>
#include<opencv2/opencv.hpp>
#include "Chess.h"
#include "ChessPad.h"
#include<vector>

#ifndef _RESULT_DISPLAY_H
#define _RESULT_DISPLAY_H


namespace myChess
{
	const int Width = 750;
	const int Height = 750;
	const int xShift = 50;
	const int yShift = 50;
	const int PointNum = 16;
	class Map //数据图到显示图
	{
	public:
		Map(int before_x, int before_y);
		int after_x;
		int after_y;
		cv::Point pt();
		
	};
	class ReMap //显示图到数据图
	{
	public:
		ReMap(int before_x, int before_y);
		int after_x;
		int after_y;
		cv::Point pt();
	};
	class ResultDisplay //存储绘图的情况
	{
	public:

		//成员函数
		//01 控制函数
		ResultDisplay();
		ResultDisplay(const ResultDisplay& rd);
		ResultDisplay& operator=(const ResultDisplay& rd);
		

		//02 运算符重载

			//03 功能函数
		void display(const ChessPad&);
		
		
		//04 工具函数
		void init(); //对pad进行初始化

		//成员变量
		cv::Mat pad;
		
	};

	//绘图点校正
	void Calibration(int& x, int& y);
	

}


#endif