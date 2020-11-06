#pragma once
#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
#ifndef _PROCESSOR_H_
#define _PROCESSOR_H_
/*
名称:Processor.h
作用:处理摄像头获得的图片，经过仿射变换后，获得一张标准棋盘图片
示例:
	if(!ImageProcessor(src))continue;

*/

//工具函数
void Rotation(cv::Mat& src, double angle=90, double scale=0.8);//通过设置角度和缩放比例，调整图片大小
void GetGreenPixel(const cv::Mat& src, cv::Mat& GreenPixel); //提取绿色像素点图
bool GetRectPoint(cv::Mat GreenPixel, vector<cv::Point2f>& rect_Point); //通过绿色像素点图，识别轮廓四个点
void warp(cv::Mat& src, const vector<cv::Point2f>& rect_Point); //通过仿射变换矫正图片

//功能函数
bool ImageProcessor(cv::Mat& src);//把图片处理为标准图片


#endif
