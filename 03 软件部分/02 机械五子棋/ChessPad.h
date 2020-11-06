#pragma once
#include<iostream>
#include<opencv2/opencv.hpp>
#include "ArtificialIntelligence.h"
#include<sstream>
using namespace std;
/*
名称:ChessPad.h
作用:ChessPad是储存数据的类，包括记录棋盘的格点信息，记录棋局信息，记录落子顺序信息。

*/

#ifndef _CHESS_PAD_H
#define _CHESS_PAD_H


class ChessPad
{
public:
	//函数
	ChessPad(){ chess = cv::Mat::zeros(cv::Size(9, 9), CV_8UC1); } //构造函数
	~ChessPad(){} //析构函数
	void ReloadGrid(const cv::Mat& src); //获取经过仿射变换以后的图片，更新网格线坐标
	cv::Point2f P(int x, int y); //获取格点(x,y)对应的像素点坐标
	bool addBlackList(); //加入黑色棋子
	bool addWhiteList(); //加入白色棋子
	cv::Point GetLastBlack();//获取上一个黑色棋子的位置
	cv::Point GetLastWhite(); //获取上一个白色棋子的位置
	string sendStr(); //送出上一个白色棋子的坐标
	//数据
	cv::Mat chess; //用来存放棋局信息
private:

	//保存仿射变换以后的图片
	cv::Mat src;
	//图片格点坐标储存
	vector<float> colPoint; //行格点坐标
	vector<float> rowPoint; //列格点坐标
	
	

	//棋子顺序数据
	vector<cv::Point> BlackList; //按顺序保存蓝色棋子
	vector<cv::Point> WhiteList; //按顺序保存红色棋子
};
#endif
