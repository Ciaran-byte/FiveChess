#include<vector>
#include "Chess.h"
#include "ChessPad.h"
#ifndef _ARTIFICIAL_INTELLIGENCE_H
#define _ARTIFICIAL_INTELLIGENCE_H


namespace myChess
{
	
	class Situation {//��ǰλ�õ���ʽ����ָ����������
	public:
		//���캯��
		Situation()
		{
			win5 = 0;//5����
			alive4 = 0;//��4
			die4 = 0;//��4
			lowdie4 = 0;//��4�ͼ��汾
			alive3 = 0;//��3
			tiao3 = 0;//��3
			die3 = 0;//��3
			alive2 = 0;//��2
			lowalive2 = 0;//�ͼ���2
			die2 = 0;//��2
			nothreat = 0;//û����в
		}

		//��Ա����
		int win5;//5����
		int alive4;//��4
		int die4;//��4
		int lowdie4;//��4�ͼ��汾
		int alive3;//��3
		int tiao3;//��3
		int die3;//��3
		int alive2;//��2
		int lowalive2;//�ͼ���2
		int die2;//��2
		int nothreat;//û����в

	};
	class ArtificialIntelligence
{
public:
	//��ȡ�µ����λ��
	cv::Point getPosition(const ChessPad&, int color); 
private:
	//01 ��Ա����
	//������ǻ������ε�

	static const int WIN5 = 0;//0->5����
	static const int ALIVE4 = 1;//1->��4
	static const int DIE4 = 2;//2->��4
	static const int LOWDIE4 = 3;//3->��4�ĵͼ��汾
	static const int ALIVE3 = 4;//3->��3
	static const int TIAO3 = 5;//5->��3
	static const int DIE3 = 6;//6->��3
	static const int ALIVE2 = 7;//7->��2
	static const int LOWALIVE2 = 8;//8->�ͼ���2
	static const int DIE2 = 9;//9->��2
	static const int NOTHREAT = 10;//10->û����в


	//��ֵȼ�
	static const int LevelOne = 100000;//����
	static const int Leveltwo = 10000;//�ɻ�4 �� ˫��4 �� ��4��3
	static const int Levelthree = 5000;//˫��3
	static const int Levelfour = 1000;//��3�߼���3
	static const int Levelfive = 500;//����
	static const int Levelsix = 400;//�ͼ�����
	static const int Levelseven = 100;//����3
	static const int LevelEight = 90;//����3
	static const int LevelNight = 50;//˫��2
	static const int LevelTen = 10;//��2
	static const int LevelEleven = 9;//�ͼ���2
	static const int LevelTwelve = 5;//��3
	static const int LevelThirteen = 2;//��2
	static const int LevelFourteen = 1;//û����в
	static const int LevelFiveteen = 0;//������
	//02 ���ߺ���
	//02-1 �Ը�����������ж�����һ���������
	int JudgeType(const std::vector<int>&); //�����жϸ������������������һ��Ļ�������
	
	//02-2 ��ĳ��ٶ�����һ�����ӣ���ȡ������ӵ��ĸ�������������
	void getChess(
		std::vector<int>& chess,
		const ChessPad& chp,
		cv::Point p,
		int mycolor,
		int direction
		); //��ȡָ���������
	//02-3 ��ȡĳһ����������ӣ������ж���ʲô��������
	int getType(
		const ChessPad& chp,
		cv::Point p,
		int mycolor,
		int direction
	);

	//02-4 ����������
	int giveScore(Situation situation);//�������ƣ�����

	//02-5 �ۺ��ĸ���������з�
	int judgeChessSituation(const ChessPad&, cv::Point p, int color);

	
};

}

#endif

