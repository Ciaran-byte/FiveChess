#include "Judge.h"

namespace myChess
{
	int x, y;
	int i, j;
	int count, result;
	int xmin, xmax, ymin, ymax;


	int flag = 0;
	int Judge::JudgeResult(const ChessPad& cp)
	{
		//01 判断是否为和棋
		//全部棋子下满了还没有返回，就是和棋
		for (i = 0; i < 16; i++)
		{
			for (j = 0; j < 16; j++)
			{
				if (cp.getChessPadState(i, j) == 0)
				{
					flag = 1;
					break;
				}
			}
			if (flag)
			{
				break;
			}
		}
		if (i == 16 && j == 16)
		{
			return 3; //和棋
		}

		////02 判断棋局是否还没开始
		flag = 0;
		for (i = 0; i < 16; i++)
		{
			for (j = 0; j < 16; j++)
			{
				if (cp.getChessPadState(i, j) != 0)
				{
					flag = 1;
					break;
				}
				if (flag)
				{
					break;
				}
			}
		}
		if (i == 16 && j == 16)
		{
			return 0; //没开始
		}

		x = cp.getLastCol();
		y = cp.getLastRow();
		result = cp.getChessPadState(x, y);//查找最后一次落子方棋子什么色
		////03 判断横向有没有胜利者
		////初始化横向搜索范围

		xmin = x - 4 < 0 ? 0 : x - 4;
		xmax = x + 4 > 15 ? 15 : x + 4;




		count = 0;//计数为0
		for (i = xmin, j = y; i <= xmax; i++)
		{
			if (cp.getChessPadState(i, j) == result)
			{
				count++;
			}
			else
			{
				count = 0;
			}
			if (count == 5)
			{
				return result;
			}
		}
		

		////04 查找纵向有没有胜利者

		ymin = y - 4 < 0 ? 0 : y - 4;
		ymax = y + 4 > 15 ? 15 : y + 4;

		count = 0;//计数为0
		for (i = x, j = ymin; j <= ymax; j++)
		{
			if (cp.getChessPadState(i, j) == result)
			{
				count++;
			}
			else
			{
				count = 0;
			}
			if (count == 5)
			{
				return result;
			}
		}
		

		////05 查找斜向有没有胜利者(左上到右下)
		count = 0;
		xmin = x - 4;
		ymin = y - 4;
		if (xmin < 0 || ymin < 0)
		{
			if (x < y)
			{
				xmin = 0;
				ymin = y - x;

			}
			else
			{
				ymin = 0;
				xmin = x - y;
			}
		}
		xmax = x + 4;
		ymax = y + 4;
		if (xmax > 15 || ymax > 15)
		{
			if (x > y)
			{
				xmax = 15;
				ymax = y + 15 - x;
			}
			else
			{
				ymax = 15;
				xmax = x + 15 - y;
			}
		}

		for (i = xmin, j = ymin; i <= xmax; i++, j++)
		{
			if (cp.getChessPadState(i, j) == result)
			{
				count++;
			}
			else
			{
				count = 0;
			}
			if (count == 5)
			{
				return result;
			}
		}
		

		////06 查找斜向有没有胜利者(左下到右上)
		count = 0;
		xmin = x - 4;
		ymax = y + 4;
		if (xmin < 0 || ymax>15)
		{
			if (x - 0 < 15 - y)
			{
				xmin = 0;
				ymax = y + x;
			}
			else
			{
				ymax = 15;
				xmin = x - (15 - y);
			}
		}

		xmax = x + 4;
		ymin = y - 4;
		if (xmax > 15 || ymin < 0)
		{
			if (15 - x > y - 0)
			{
				ymin = 0;
				xmax = x + y - 0;
			}
			else
			{
				
				xmax = 15;
				ymin = y - (15 - x);
			}
		}
		for (i = xmin, j = ymax; i <= xmax; i++, j--)
		{
			if (cp.getChessPadState(i, j) == result)
			{
				count++;
			}
			else
			{
				count = 0;
			}
			if (count == 5)
			{
				return result;
			}

		}

		
		return 0; //胜负未定
	}
}