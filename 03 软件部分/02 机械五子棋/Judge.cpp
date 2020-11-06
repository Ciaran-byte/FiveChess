#include "Judge.h"

//���ڲþ���ǰ�����Ƿ�ȡ����ʤ��
int JudgeResult(const cv::Mat& chess, cv::Point lastChess, int ChessColor)
{
	//01 �ж��Ƿ�Ϊ����
	//ȫ�����������˻�û�з��أ����Ǻ���
	int flag;
	int i, j; //�кź��к�
	int xmin, xmax; //�����
	int ymin, ymax;
	int count; //���ڼ����ģ��������Ӯ
	for (j = 0; j < chess.rows; j++)
	{
		for (i = 0; i < chess.cols; i++)
		{
			if (chess.at<uchar>(j, i) == 0)
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
	if (j == chess.rows && i == chess.cols)
	{
		return 3; //����
	}

	////02 �ж�����Ƿ�û��ʼ
	flag = 0;
	for (j = 0; j < chess.rows; j++)
	{
		for (i = 0; i < chess.cols; i++)
		{
			if (chess.at<uchar>(j, i) != 0)
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
	if (j == chess.rows && i == chess.rows)
	{
		return 0; //û��ʼ
	}


	////03 �жϺ�����û��ʤ����
	////��ʼ������������Χ


	xmin = lastChess.x - 4 < 0 ? 0 : lastChess.x - 4;
	xmax = lastChess.x + 4 > chess.cols - 1 ? chess.cols - 1 : lastChess.x + 4;




	count = 0;//����Ϊ0
	for (i = xmin, j = lastChess.y; i <= xmax; i++)
	{
		if (chess.at<uchar>(j, i) == ChessColor)
		{
			count++;
		}
		else
		{
			count = 0;
		}
		if (count == 5)
		{
			return ChessColor;
		}
	}


	////04 ����������û��ʤ����

	ymin = lastChess.y - 4 < 0 ? 0 : lastChess.y - 4;
	ymax = lastChess.y + 4 > chess.rows - 1 ? chess.rows - 1 : lastChess.y + 4;

	count = 0;//����Ϊ0
	for (i = lastChess.x, j = ymin; j <= ymax; j++)
	{
		if (chess.at<uchar>(j, i) == ChessColor)
		{
			count++;
		}
		else
		{
			count = 0;
		}
		if (count == 5)
		{
			return ChessColor;
		}
	}


	////05 ����б����û��ʤ����(���ϵ�����)
	count = 0;
	xmin = lastChess.x - 4;
	ymin = lastChess.y - 4;
	if (xmin < 0 || ymin < 0)
	{
		if (lastChess.x < lastChess.y)
		{
			xmin = 0;
			ymin = lastChess.y - lastChess.x;

		}
		else
		{
			ymin = 0;
			xmin = lastChess.x - lastChess.y;
		}
	}
	xmax = lastChess.x + 4;
	ymax = lastChess.y + 4;
	if (xmax > chess.cols - 1 || ymax > chess.rows - 1)
	{
		if (lastChess.x > lastChess.y)
		{
			xmax = chess.cols - 1;
			ymax = lastChess.y + chess.rows - 1 - lastChess.x;
		}
		else
		{
			ymax = chess.rows - 1;
			xmax = lastChess.x + chess.cols - 1 - lastChess.y;
		}
	}

	for (i = xmin, j = ymin; i <= xmax; i++, j++)
	{
		if (chess.at<uchar>(j, i) == ChessColor)
		{
			count++;
		}
		else
		{
			count = 0;
		}
		if (count == 5)
		{
			return ChessColor;
		}
	}


	////06 ����б����û��ʤ����(���µ�����)
	count = 0;
	xmin = lastChess.x - 4;
	ymax = lastChess.y + 4;
	if (xmin < 0 || ymax>chess.rows - 1)
	{
		if (lastChess.x - 0 < chess.rows - 1 - lastChess.y)
		{
			xmin = 0;
			ymax = lastChess.y + lastChess.x;
		}
		else
		{
			ymax = chess.rows - 1;
			xmin = lastChess.x - (chess.rows - 1 - lastChess.y);
		}
	}

	xmax = lastChess.x + 4;
	ymin = lastChess.y - 4;
	if (xmax > chess.cols - 1 || ymin < 0)
	{
		if (chess.cols - 1 - lastChess.x > lastChess.y - 0)
		{
			ymin = 0;
			xmax = lastChess.x + lastChess.y - 0;
		}
		else
		{

			xmax = chess.cols - 1;
			ymin = lastChess.y - (chess.cols - 1 - lastChess.x);
		}
	}
	for (i = xmin, j = ymax; i <= xmax; i++, j--)
	{
		if (chess.at<uchar>(j, i) == ChessColor)
		{
			count++;
		}
		else
		{
			count = 0;
		}
		if (count == 5)
		{
			return ChessColor;
		}

	}


	return 0; //ʤ��δ��
}