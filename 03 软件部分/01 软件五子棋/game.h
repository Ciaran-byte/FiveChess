#include "Chess.h"
#include "ChessPad.h"
#include "Chesser.h"
#include "ResultDisplay.h"
#include "Judge.h"
#include "ArtificialIntelligence.h"
#ifndef _GAME_H
#define _GMAE_H



namespace myChess
{
	
	class game
	{
	public:
		static void gameInit();//�����趨ϵͳ�����˶�ս�����˻���ս�����ʼ�����ֵȵ���Ϣ
		static void gameStart();


		
		

		
	private:
		//��Ҫ��ϵͳ��
		
		static ChessPad cp; //��Ĭ�ϳ�ʼ�������ڱ���洢����
		static Judge j;  //��������˭�ǵ�ǰ���֣����������ж���ֽ��
		static ArtificialIntelligence ai;  //�˻���ս��ʱ���ṩ����
		static Chesser black; //����
		static Chesser white; //����
		static ResultDisplay rd; //Ĭ�ϳ�ʼ�������ڱ�����������ͼ
		

		//�����սģʽ�ĳ���
		static const int PP = 0;
		static const int PE = 1;
		static const int EE = 2;
		static int mode; //PP����PE��

		//�����Ⱥ��ֵĳ���
		static const int PeopleFirst = 0;
		static const int ComputerFirst = 1;
		static int WhoIsFirst;

		//������Ϸ������־λ
		static int ok;
		static const int GOON = 0;
		static const int OVER = 1;


		//��Ҫ�Ĺ��ߺ�����Ҳ����ѡ���˻�����ѡ�����˵Ļص�����
		static int getWhoIsFirst() { return WhoIsFirst; }
		static void PPMouseCallBack(int event, int x, int y, int flags, void* param); //���˵Ļص�����
		static void PEMouseCallBack(int event, int x, int y, int flags, void* param); //�˻��Ļص�����
		static void EEMouseCallBack(int event, int x, int y, int flags, void* param); //�����Ļص�����
		//
		static bool PEok;
	};


}

#endif

