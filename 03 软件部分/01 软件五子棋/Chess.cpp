#include "Chess.h"

namespace myChess
{


	std::ostream& operator<<(std::ostream& os, const Point& p) //Point�������������
	{
		os << "x = " << p.x << std::endl;
		os << "y = " << p.y << std::endl;
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const Chess& rhs) //Chess�������������
{
	os << rhs.p;
	os << rhs._color << std::endl;
	return os;
}


}
