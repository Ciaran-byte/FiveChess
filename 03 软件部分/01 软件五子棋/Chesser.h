
#include "Chess.h"
#include "ChessPad.h"


#ifndef CHESSER_H
#define CHESSER_H

namespace myChess
{
	class Chesser  //派生自抽象类Chesser
	{
	public:
		Chesser() = default;
		Chesser(int color, const std::string& s);
		Chess getNextChess(const ChessPad& cp,int x,int y);
		 ~Chesser(){}
		int& getColor() { return color; }
		std::string& getName() { return name; }
	private:
		int color;
		std::string name;
	};
}

#endif