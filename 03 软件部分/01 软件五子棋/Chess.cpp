#include "Chess.h"

namespace myChess
{


	std::ostream& operator<<(std::ostream& os, const Point& p) //Point类流运算符重载
	{
		os << "x = " << p.x << std::endl;
		os << "y = " << p.y << std::endl;
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const Chess& rhs) //Chess类流运算符重载
{
	os << rhs.p;
	os << rhs._color << std::endl;
	return os;
}


}
