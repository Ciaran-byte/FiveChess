#include<iostream>
#include<opencv2/opencv.hpp>
#include "game.h"
#include <functional>
using namespace std;
using namespace cv;


myChess::ResultDisplay  myChess::game::rd; //Ĭ�ϳ�ʼ�������ڱ�����������ͼ
//��Ҫ��ϵͳ��

myChess::ChessPad  myChess::game::cp; //��Ĭ�ϳ�ʼ�������ڱ���洢����
myChess::Judge  myChess::game::j;  //��������˭�ǵ�ǰ���֣����������ж���ֽ��
myChess::ArtificialIntelligence myChess::game::ai;  //�˻���ս��ʱ���ṩ����
myChess::Chesser  myChess::game::black; //����
myChess::Chesser  myChess::game::white; //����



//�����սģʽ�ĳ���
const int  myChess::game::PP;
const int  myChess::game::PE;
const int  myChess::game::EE;

int  myChess::game::mode; //PP����PE����EE��

//�����Ⱥ��ֵĳ���
const int  myChess::game::PeopleFirst;
const int  myChess::game::ComputerFirst;
int  myChess::game::WhoIsFirst;

//������Ϸ������־λ
int  myChess::game::ok;
const int  myChess::game::GOON;
const int  myChess::game::OVER;

bool myChess::game::PEok;

int main()
{
	myChess::game g;
	g.gameInit();
	g.gameStart();
	

	return 0;
}

