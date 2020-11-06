#include "Judge.h"

//用于裁决当前棋子是否取得了胜利
int JudgeResult(const cv::Mat& chess, cv::Point lastChess, int ChessColor)
{
	//01 判断是否为和棋
	//全部棋子下满了还没有返回，就是和棋
	int flag;
	int i, j; //行号和列好
	int xmin, xmax; //定界的
	int ymin, ymax;
	int count; //用于计数的，满五个就赢
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
		return 3; //和棋
	}

	////02 判断棋局是否还没开始
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
		return 0; //没开始
	}


	////03 判断横向有没有胜利者
	////初始化横向搜索范围


	xmin = lastChess.x - 4 < 0 ? 0 : lastChess.x - 4;
	xmax = lastChess.x + 4 > chess.cols - 1 ? chess.cols - 1 : lastChess.x + 4;




	count = 0;//计数为0
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


	////04 查找纵向有没有胜利者

	ymin = lastChess.y - 4 < 0 ? 0 : lastChess.y - 4;
	ymax = lastChess.y + 4 > chess.rows - 1 ? chess.rows - 1 : lastChess.y + 4;

	count = 0;//计数为0
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


	////05 查找斜向有没有胜利者(左上到右下)
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


	////06 查找斜向有没有胜利者(左下到右上)
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


	return 0; //胜负未定
}