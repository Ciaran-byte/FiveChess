#include "draw.h"

void drawPicture(cv::Mat& src, ChessPad& chp)//Õ˘srcÕºœÒ…œªÊ÷∆Õº∆¨
{
	

	for (int i = 0; i < 9; i++)
	{
		cv::line(src, chp.P(i, 0), chp.P(i, 8), cv::Scalar(0, 0, 255), 2, 8);
		cv::line(src, chp.P(0, i), chp.P(8, i), cv::Scalar(0, 0, 255), 2, 8);
	}
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (chp.chess.at<uchar>(i, j) == 1)
			{
				cv::circle(src, chp.P(j, i), 5, cv::Scalar(255, 0, 0), -1);
			}
			else if (chp.chess.at<uchar>(i, j) == 2)
			{
				cv::circle(src, chp.P(j, i), 20, cv::Scalar(0, 255, 0), 2);
			}
			cv::Point lb = chp.GetLastBlack();
			cv::Point lw = chp.GetLastWhite();
			if (lb != cv::Point(-1, -1) && lw != cv::Point(-1, -1))
			{
				circle(src, chp.P(chp.GetLastBlack().x, chp.GetLastBlack().y), 5, cv::Scalar(0, 0, 255), 2);
				circle(src, chp.P(chp.GetLastWhite().x, chp.GetLastWhite().y), 5, cv::Scalar(0, 0, 255), 2);
			}

		}
	}
	
}