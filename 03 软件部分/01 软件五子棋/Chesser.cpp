
#include "Chesser.h"
namespace myChess
{
	//peopleChesser类
	Chesser::Chesser(int color, const std::string& name):color(color),name(name){}
	 Chess Chesser::getNextChess(const ChessPad& cp,int x,int y) //获取棋手的下一手棋
	{
		
			 return Chess(x, y, color);
		 
		
	}

}
