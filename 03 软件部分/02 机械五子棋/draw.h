#pragma once
#include<iostream>
#include<opencv2/opencv.hpp>
#include "ChessPad.h"
using namespace std;

#ifndef _DRAW_H_
#define _DRAW_H_
/*
名称:draw.h
作用:draw.h用来绘制棋盘现状的库


*/

void drawPicture(cv::Mat& src, ChessPad& chp); //往src图像上绘制图片
#endif