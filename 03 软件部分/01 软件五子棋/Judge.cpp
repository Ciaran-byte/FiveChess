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
		//01 �ж��Ƿ�Ϊ����
		//ȫ�����������˻�û�з��أ����Ǻ���
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
			return 3; //����
		}

		////02 �ж�����Ƿ�û��ʼ
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
			return 0; //û��ʼ
		}

		x = cp.getLastCol();
		y = cp.getLastRow();
		result = cp.getChessPadState(x, y);//�������һ�����ӷ�����ʲôɫ
		////03 �жϺ�����û��ʤ����
		////��ʼ������������Χ

		xmin = x - 4 < 0 ? 0 : x - 4;
		xmax = x + 4 > 15 ? 15 : x + 4;




		count = 0;//����Ϊ0
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
		

		////04 ����������û��ʤ����

		ymin = y - 4 < 0 ? 0 : y - 4;
		ymax = y + 4 > 15 ? 15 : y + 4;

		count = 0;//����Ϊ0
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
		

		////05 ����б����û��ʤ����(���ϵ�����)
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
		

		////06 ����б����û��ʤ����(���µ�����)
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

		
		return 0; //ʤ��δ��
	}
}