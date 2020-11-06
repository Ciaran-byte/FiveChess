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
	class Map //����ͼ����ʾͼ
	{
	public:
		Map(int before_x, int before_y);
		int after_x;
		int after_y;
		cv::Point pt();
		
	};
	class ReMap //��ʾͼ������ͼ
	{
	public:
		ReMap(int before_x, int before_y);
		int after_x;
		int after_y;
		cv::Point pt();
	};
	class ResultDisplay //�洢��ͼ�����
	{
	public:

		//��Ա����
		//01 ���ƺ���
		ResultDisplay();
		ResultDisplay(const ResultDisplay& rd);
		ResultDisplay& operator=(const ResultDisplay& rd);
		

		//02 ���������

			//03 ���ܺ���
		void display(const ChessPad&);
		
		
		//04 ���ߺ���
		void init(); //��pad���г�ʼ��

		//��Ա����
		cv::Mat pad;
		
	};

	//��ͼ��У��
	void Calibration(int& x, int& y);
	

}


#endif