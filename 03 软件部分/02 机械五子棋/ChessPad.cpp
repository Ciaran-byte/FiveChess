#include "ChessPad.h"

void ChessPad::ReloadGrid(const cv::Mat& src)//获取经过仿射变换以后的图片，更新网格线坐标
{
	//更新棋盘图片
	this->src = src.clone();

	// 更新格点信息
	float dx = (src.cols) / 9.0;
	float dy = (src.rows) / 9.0;
	

	for (int i = 0; i < 9; i++)
	{
		colPoint.push_back(dx / 2.0 + dx * i);
		rowPoint.push_back(dy / 2.0 + dy * i);
	}
	


}

cv::Point2f  ChessPad::P(int x, int y)//获取格点(x,y)对应的像素点坐标
{
	return cv::Point2f(colPoint[x], rowPoint[y]);
}

bool ChessPad::addBlackList() //加入黑色棋子
{
	//01 仿射变换以后的图片转转hsv图片
	cv::Mat hsv;
	cv::cvtColor(src, hsv, CV_BGR2HSV);

	//02 识别黑棋(实际使用的是蓝色的)
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{

			int h, s, v; //记录格点的hsv值
			int flag = 0; //用于判断是否连续两次检测都是蓝色棋子
			for (int time = 0; time < 2; time++)
			{

				//获取网格点的hsv值，识别蓝色棋子，这是我们的棋子。但是棋盘可能出现误识别，所以识别了2次，必须连续2次都是蓝色，才
				//被认为是我们下的棋子
				h = hsv.at<cv::Vec3b>(P(i,j))[0];
				s = hsv.at<cv::Vec3b>(P(i, j))[1];
				v = hsv.at<cv::Vec3b>(P(i, j))[2];

				if (h >= 110 && h <= 124 && s >= 43 && s <= 255 && v >= 43 && v <= 255)
				{

					flag++;
					if (flag == 2)
					{
						if (find(BlackList.begin(), BlackList.end(), cv::Point(i, j)) == BlackList.end())//如果这个位置的黑棋还没有加入棋盘，就加入
						{
							chess.at<uchar>(j, i) = BLACK;
							BlackList.push_back(cv::Point(i, j));
							return  true; //本次有插入棋子
						}
						

					}
				}
				else
				{
					break;
				}

			}
		}
	}
	return false;

}
bool ChessPad::addWhiteList() //加入白色棋子
{
	ArtificialIntelligence AI;
	cv::Point whiteP=AI.getPosition(this->chess, WHITE);
	chess.at<uchar>(whiteP.y, whiteP.x) = WHITE;
	WhiteList.push_back(whiteP);
	return true;

	
}
cv::Point ChessPad::GetLastBlack()//获取上一个黑色棋子的位置
{
	if (BlackList.empty())return cv::Point(-1, -1);
	else return BlackList[BlackList.size() - 1];

}
cv::Point ChessPad::GetLastWhite() //获取上一个白色棋子的位置
{
	if (WhiteList.empty())return cv::Point(-1, -1);
	else return WhiteList[WhiteList.size() - 1];
	
}

string ChessPad::sendStr()
{
	int num =GetLastWhite().x * 10 + GetLastWhite().y;
	ostringstream s;
	s << num;
	return s.str();
}