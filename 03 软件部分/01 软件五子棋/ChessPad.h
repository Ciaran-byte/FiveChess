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
		//��Ԫ
		friend std::ostream& operator<<(std::ostream& os, const ChessPad& rhs);
		friend class ResultDisplay;
		//01 ���캯������������

		//Ĭ�Ϲ���
		ChessPad();
		

		//��������
		ChessPad(const cv::Mat& m);

		//�ƶ�����
		ChessPad(cv::Mat&& m)noexcept;

		//��������
		~ChessPad();

		//02 ���������
		//������ֵ
		ChessPad& operator=(const ChessPad&);

		//03 ���ܺ���

		//�����ӵ�ʱ�򣬸������̵�״̬
		bool addChess(const Chess&);

		////��ѯ�����Ͼ���ĳ�����״̬
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