
#include "Chesser.h"
namespace myChess
{
	//peopleChesser��
	Chesser::Chesser(int color, const std::string& name):color(color),name(name){}
	 Chess Chesser::getNextChess(const ChessPad& cp,int x,int y) //��ȡ���ֵ���һ����
	{
		
			 return Chess(x, y, color);
		 
		
	}

}
