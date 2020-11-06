#include "ResultDisplay.h"


namespace myChess
{

	//01 Map��
	Map::Map(int before_x,int before_y)
	{
		after_x = before_x * 40 + xShift;
		after_y = before_y * 40 + yShift;
	}
	cv::Point Map::pt()
	
		{
			return cv::Point(after_x, after_y);
		}
	
	//02 ReMap��
	ReMap::ReMap(int before_x, int before_y)
	{
		after_x = (before_x - xShift) / 40;
		after_y = (before_y - yShift) / 40;
	}
	cv::Point ReMap::pt()

	{
		return cv::Point(after_x, after_y);
	}
	//03 ResultDisplay��
	//���캯��

	//���캯����������ʼ��������
	 ResultDisplay::ResultDisplay()
	{
		 
		 init();
	}

	 ResultDisplay::ResultDisplay(const ResultDisplay& rd)
	 {
		 pad = (rd.pad).clone();
	 }
	 ResultDisplay& ResultDisplay:: operator=(const ResultDisplay& rd)
	 {
		 pad = (rd.pad).clone();
		 return *this;
	 }
	
	 //���ܺ���������ChessPad����¼���������ݣ������ƽ��
	 void  ResultDisplay::display(const ChessPad& cp)
	 {
		 
		 for (int i = 0; i < 16; i++)
		 {
			 for (int j = 0; j < 16; j++)
			 {
				 if ((cp.ChessPadState).at<int>(j,i) == 1)
				 {
					 cv::circle(pad, Map(i, j).pt(), 10, cv::Scalar(0, 0, 0), -1);
				 }
				 if ((cp.ChessPadState).at<int>(j, i) == 2)
				 {
					 cv::circle(pad, Map(i, j).pt(), 10, cv::Scalar(255, 255, 255), -1);
				 }
			 }
		 }

	 }
//���ߺ���
	 void ResultDisplay::init()
	 {
		 pad = cv::Mat(Width, Height, CV_8UC3, cv::Scalar(0, 255, 255));
		 cv::rectangle(pad, cv::Point(xShift, yShift), cv::Point(Width - 2 * xShift, Height - 2 * yShift),
			 cv::Scalar(0, 0, 0), 4);
		 for (int i = 1; i <= 14; i++)
		 {
			 cv::line(
				 pad,
				 cv::Point(xShift + i * 40, yShift),
				 cv::Point(xShift + i * 40, Height - 2 * yShift),
				 cv::Scalar(0, 0, 0),
				 2
			 );
		 }

		 for (int i = 1; i <= 14; i++)
		 {
			 cv::line(
				 pad,
				 cv::Point(xShift, yShift + i * 40),
				 cv::Point(Width - 2 * xShift, yShift + i * 40),
				 cv::Scalar(0, 0, 0),
				 2
			 );
		 }
		 cv::circle(pad, Map(3, 3).pt(), 6, cv::Scalar(0, 0, 0), 2);
		 cv::circle(pad, Map(3, 12).pt(), 6, cv::Scalar(0, 0, 0), 2);
		 cv::circle(pad, Map(12, 3).pt(), 6, cv::Scalar(0, 0, 0), 2);
		 cv::circle(pad, Map(12, 12).pt(), 6, cv::Scalar(0, 0, 0), 2);
	 }

	 //04 ��ͼУ��
	 void Calibration(int& x, int& y)
	 {
		 x -= 50;
		 y -= 50;
		 int devideX =x / 40;
		 int modX = x % 40;

		 if (modX <= 20)
		 {
			 x = devideX * 40;
		 }
		 else
		 {
			 x = (devideX + 1) * 40;
		 }
		 int devideY = y / 40;
		 int modY = y % 40;
		 if (modY <= 20)
		 {
			 y = devideY * 40;
		 }
		 else
		 {
			 y = (devideY + 1) * 40;
		 }
		 x += 50;
		 y += 50;

	 }

}