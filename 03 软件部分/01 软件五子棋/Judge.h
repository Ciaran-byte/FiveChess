#include<iostream>
#include "Chess.h"
#include "ChessPad.h"
#ifndef _JUDGE_H
#define _JUDGE_H

namespace myChess
{

	class Judge //²ÃÅĞÀà
	{
	public:
		Judge()
		{
			CurrentChesser = 1;
		}
		
		int JudgeResult(const ChessPad&);
		//ÆÀÅĞ×îÖÕ½á¹û¡£0Ê¤¸ºÎ´¶¨£¬1ºÚÆåÊ¤£¬2°×ÆåÊ¤£¬3 ºÍÆå
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
		//0 ºÚ·½
		//1 °×·½

	};
}


#endif
