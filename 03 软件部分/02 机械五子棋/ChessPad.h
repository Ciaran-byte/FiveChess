#pragma once
#include<iostream>
#include<opencv2/opencv.hpp>
#include "ArtificialIntelligence.h"
#include<sstream>
using namespace std;
/*
����:ChessPad.h
����:ChessPad�Ǵ������ݵ��࣬������¼���̵ĸ����Ϣ����¼�����Ϣ����¼����˳����Ϣ��

*/

#ifndef _CHESS_PAD_H
#define _CHESS_PAD_H


class ChessPad
{
public:
	//����
	ChessPad(){ chess = cv::Mat::zeros(cv::Size(9, 9), CV_8UC1); } //���캯��
	~ChessPad(){} //��������
	void ReloadGrid(const cv::Mat& src); //��ȡ��������任�Ժ��ͼƬ����������������
	cv::Point2f P(int x, int y); //��ȡ���(x,y)��Ӧ�����ص�����
	bool addBlackList(); //�����ɫ����
	bool addWhiteList(); //�����ɫ����
	cv::Point GetLastBlack();//��ȡ��һ����ɫ���ӵ�λ��
	cv::Point GetLastWhite(); //��ȡ��һ����ɫ���ӵ�λ��
	string sendStr(); //�ͳ���һ����ɫ���ӵ�����
	//����
	cv::Mat chess; //������������Ϣ
private:

	//�������任�Ժ��ͼƬ
	cv::Mat src;
	//ͼƬ������괢��
	vector<float> colPoint; //�и������
	vector<float> rowPoint; //�и������
	
	

	//����˳������
	vector<cv::Point> BlackList; //��˳�򱣴���ɫ����
	vector<cv::Point> WhiteList; //��˳�򱣴��ɫ����
};
#endif
