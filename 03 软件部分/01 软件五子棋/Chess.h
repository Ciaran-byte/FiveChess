#include<iostream>

#ifndef _myChess_H
#define _myChess_H


namespace myChess
{
	const int BLACK = 1;
	const int WHITE = 2;
	const int NOTHING = 0;
	//Point类，实现棋子位置的存储
	class Point
	{

	//友元
		friend std::ostream& operator<<(std::ostream& os, const Point& p);
		
	public:
		//01 构造函数与析构函数
		 Point() = default; //默认构造函数
		 Point(int x, int y) :x(x), y(y) {} //构造函数
		 Point(const Point& p) //拷贝构造函数
		{
			x = p.x;
			y = p.y;
		}
		 Point(Point&& p)noexcept //移动构造函数
		{
			x = p.x;
			y = p.y;
		}
		 ~Point() {} //析构函数
		//02 功能函数
		 void getPoint(int& x, int& y)const //设置点
		{
			x = this->x;
			y = this->y;

		}
		 void setPoint(int x, int y) //设置点
		{
			this->x = x;
			this->y = y;
		}

		//03 运算符重载

		 Point& operator=(const Point& p) //拷贝赋值函数
		{
			x = p.x;
			y = p.y;
			return *this;
		}
		
		 bool operator==(const Point& p) //等号重载
		{
			if (x == p.x && y == p.y)
			{
				return true;
			}
			return false;
		}
	private:
		int x;
		int y;
	};


	

	//Chess类，实现棋子的存储
	class Chess
	{
	//友元
		
	public:
		friend std::ostream& operator<<(std::ostream& os, const Chess& rhs);
		//01 构造函数和析构函数
		Chess() = default;//默认构造函数
		Chess(int x, int y,int color) :p(x, y), _color(color) {} //构造函数
		Chess(Point p, int color) :p(p), _color(color) {}  //重载的构造函数
		Chess(const Chess& rhs)  //拷贝构造
		{
			p = rhs.p;
			_color = rhs._color;
		}
		Chess(Chess&& rhs)noexcept  //移动构造
		{
			p = rhs.p;
			_color = rhs._color;
		}

		

		~Chess() {}

		//02 运算符重载
		Chess& operator=(const Chess& rhs) //赋值函数
		{
			p = rhs.p;
			_color = rhs._color;
		}

		//03 功能函数
		void getPoint(int& row,int& col)const //获取棋子的坐标
		{
			this->p.getPoint(row, col);

		}
		int  getColor()const //获取棋子的颜色
		{
			return _color;
		}
		void setPoint(const Point& p) //设置棋子的坐标
		{
			this->p = p;
		}
		void setPoint(int x, int y) //设置棋子的坐标
		{
			this->p = Point(x, y);
		}
		void setColor(int color) //设置棋子的颜色
		{
			this->_color = color;
		}

	private:
		Point p;
		 int _color;
	};
	
	
}



#endif
