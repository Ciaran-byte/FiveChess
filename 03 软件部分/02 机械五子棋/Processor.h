#pragma once
#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
#ifndef _PROCESSOR_H_
#define _PROCESSOR_H_
/*
����:Processor.h
����:��������ͷ��õ�ͼƬ����������任�󣬻��һ�ű�׼����ͼƬ
ʾ��:
	if(!ImageProcessor(src))continue;

*/

//���ߺ���
void Rotation(cv::Mat& src, double angle=90, double scale=0.8);//ͨ�����ýǶȺ����ű���������ͼƬ��С
void GetGreenPixel(const cv::Mat& src, cv::Mat& GreenPixel); //��ȡ��ɫ���ص�ͼ
bool GetRectPoint(cv::Mat GreenPixel, vector<cv::Point2f>& rect_Point); //ͨ����ɫ���ص�ͼ��ʶ�������ĸ���
void warp(cv::Mat& src, const vector<cv::Point2f>& rect_Point); //ͨ������任����ͼƬ

//���ܺ���
bool ImageProcessor(cv::Mat& src);//��ͼƬ����Ϊ��׼ͼƬ


#endif
