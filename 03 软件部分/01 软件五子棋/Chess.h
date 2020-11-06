#include<iostream>

#ifndef _myChess_H
#define _myChess_H


namespace myChess
{
	const int BLACK = 1;
	const int WHITE = 2;
	const int NOTHING = 0;
	//Point�࣬ʵ������λ�õĴ洢
	class Point
	{

	//��Ԫ
		friend std::ostream& operator<<(std::ostream& os, const Point& p);
		
	public:
		//01 ���캯������������
		 Point() = default; //Ĭ�Ϲ��캯��
		 Point(int x, int y) :x(x), y(y) {} //���캯��
		 Point(const Point& p) //�������캯��
		{
			x = p.x;
			y = p.y;
		}
		 Point(Point&& p)noexcept //�ƶ����캯��
		{
			x = p.x;
			y = p.y;
		}
		 ~Point() {} //��������
		//02 ���ܺ���
		 void getPoint(int& x, int& y)const //���õ�
		{
			x = this->x;
			y = this->y;

		}
		 void setPoint(int x, int y) //���õ�
		{
			this->x = x;
			this->y = y;
		}

		//03 ���������

		 Point& operator=(const Point& p) //������ֵ����
		{
			x = p.x;
			y = p.y;
			return *this;
		}
		
		 bool operator==(const Point& p) //�Ⱥ�����
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


	

	//Chess�࣬ʵ�����ӵĴ洢
	class Chess
	{
	//��Ԫ
		
	public:
		friend std::ostream& operator<<(std::ostream& os, const Chess& rhs);
		//01 ���캯������������
		Chess() = default;//Ĭ�Ϲ��캯��
		Chess(int x, int y,int color) :p(x, y), _color(color) {} //���캯��
		Chess(Point p, int color) :p(p), _color(color) {}  //���صĹ��캯��
		Chess(const Chess& rhs)  //��������
		{
			p = rhs.p;
			_color = rhs._color;
		}
		Chess(Chess&& rhs)noexcept  //�ƶ�����
		{
			p = rhs.p;
			_color = rhs._color;
		}

		

		~Chess() {}

		//02 ���������
		Chess& operator=(const Chess& rhs) //��ֵ����
		{
			p = rhs.p;
			_color = rhs._color;
		}

		//03 ���ܺ���
		void getPoint(int& row,int& col)const //��ȡ���ӵ�����
		{
			this->p.getPoint(row, col);

		}
		int  getColor()const //��ȡ���ӵ���ɫ
		{
			return _color;
		}
		void setPoint(const Point& p) //�������ӵ�����
		{
			this->p = p;
		}
		void setPoint(int x, int y) //�������ӵ�����
		{
			this->p = Point(x, y);
		}
		void setColor(int color) //�������ӵ���ɫ
		{
			this->_color = color;
		}

	private:
		Point p;
		 int _color;
	};
	
	
}



#endif
