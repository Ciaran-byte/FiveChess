#include<iostream>
#include "Chess.h"
#include "ChessPad.h"
#ifndef _JUDGE_H
#define _JUDGE_H

namespace myChess
{

	class Judge //������
	{
	public:
		Judge()
		{
			CurrentChesser = 1;
		}
		
		int JudgeResult(const ChessPad&);
		//�������ս����0ʤ��δ����1����ʤ��2����ʤ��3 ����
		int nextChesser()
		{
			if (CurrentChesser == 0)
			{
				CurrentChesser = 1;
			}
			else
			{
				CurrentChesser = 0;
			 }
		return CurrentChesser;
		}
		int &getCurrentChesser()
		{
			return CurrentChesser;
		}
	private:
		int CurrentChesser;
		//0 �ڷ�
		//1 �׷�

	};
}


#endif
