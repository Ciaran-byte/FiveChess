#include "Processor.h"


//----------------------------------工具函数----------------------------------------------------
void Rotation(cv::Mat& src, double angle, double scale)//通过设置角度和缩放比例，调整图片大小
{
	cv::Point center(src.cols / 2, src.rows / 2); //旋转中心

	cv::Mat rotMat = getRotationMatrix2D(center, angle, scale);
	cv::warpAffine(src, src, rotMat, src.size());

}

void GetGreenPixel(const cv::Mat& src, cv::Mat& GreenPixel) //获取图片的绿色掩膜
{
	//01 hsv色彩空间变换
	cv::Mat hsv; //储存hsv图片
	cvtColor(src, hsv, cv::COLOR_BGR2HSV); //变换到hsv色彩空间进行颜色提取
	//02 从hsv中提取绿色边框

	int iLowH = 38;  //绿色的范围是 H 38-77  S 30-255   V 30-255
	int iLowS = 43;  //青色的范围 78 - 99 
	int iLowV = 46;
	int iHighH = 77;

	int iHighS = 255;
	int iHighV = 255;

	cv::Mat mask; //通过inRange函数，将符合范围的设置为255，构成掩膜
	inRange(hsv, cv::Scalar(iLowH, iLowS, iLowV), cv::Scalar(iHighH, iHighS, iHighV), mask);

	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
	morphologyEx(mask, mask, cv::MORPH_OPEN, element);//通过开操作能够去除白色小斑点
	morphologyEx(mask, mask, cv::MORPH_CLOSE, element, cv::Point(-1, -1), 3); //通过闭操作能够连接区域

	bitwise_and(src, src, GreenPixel, mask); //通过掩膜，与原图做位运算，获取相应的绿色像素
}
bool GetRectPoint(const cv::Mat src, vector<cv::Point2f>& rect_Point)//通过绿色像素点图，识别轮廓四个点
{
	//01 提取原图中的绿色像素点图
	cv::Mat GreenPixel;
	GetGreenPixel(src, GreenPixel); 

	//02 像素点图转灰度图，不然没法轮廓识别和拟合
	cvtColor(GreenPixel, GreenPixel, cv::COLOR_BGR2GRAY);

	//03 提取轮廓信息
	vector<vector<cv::Point>> contours; //提取轮廓信息
	vector<cv::Vec4i> hierarchy;//储存层次信息
	findContours(GreenPixel, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0)); //轮廓信息

	//04 多边形拟合

		//对03得到的轮廓进行多边形拟合，得到需要的四边形
	vector<vector<cv::Point>> contours_poly(contours.size()); //用来储存对外轮廓进行的多边形拟合的边界点

	for (int i = 0; i < contours.size(); i++)
	{
		cv::approxPolyDP(cv::Mat(contours[i]), contours_poly[i], 80, true); //对所有轮廓进行多边形拟合，因为只有外轮廓，所以没筛选最大轮廓

	}
	//05 拟合得到的四边形取最大的那个
	if (contours_poly.size() > 1) //有拟合的多边形，就找到最大的那个
	{
		for (int i = contours_poly.size() - 1; i > 0; i--) {
			if (contourArea(contours_poly[i]) > contourArea(contours_poly[i - 1])) {
				contours_poly[i - 1] = contours_poly[i];
			}
		}
	}
	//06 如果拟合得到的最大图案不是四边形，返回去，重新找
	if (contours_poly[0].size() != 4)return false;

	//07 如果是四边形，可以提取四个边点了
	vector<cv::Point> outer = contours_poly[0];
	//拟合的轮廓是逆时针的
	// 按逆时针方向提取四个边点
	if ((contours_poly[0][0].x + contours_poly[0][0].y) <
		(contours_poly[0][1].x + contours_poly[0][1].y))
	{
		rect_Point.push_back(outer[0]);
		rect_Point.push_back(outer[1]);
		rect_Point.push_back(outer[2]);
		rect_Point.push_back(outer[3]);
	}
	else
	{
		rect_Point.push_back(outer[1]);
		rect_Point.push_back(outer[2]);
		rect_Point.push_back(outer[3]);
		rect_Point.push_back(outer[0]);
	}

	return true; //如果拟合图形是四边形，提取到了四个边界点，返回true

}

void warp(cv::Mat& src, const vector<cv::Point2f>& rect_Point) //通过仿射变换矫正图片
{
	vector<cv::Point2f> rect_Point2; //记录仿射变换后四个顶点的信息

	rect_Point2.push_back(cv::Point2f(0, 0));	//----------------------------------------------仿射变换前的准备
	rect_Point2.push_back(cv::Point2f(rect_Point2[0].x, rect_Point2[0].y + src.rows)); //按逆时针顺序准备四个点
	rect_Point2.push_back(cv::Point2f(rect_Point2[1].x + src.cols, rect_Point2[1].y));
	rect_Point2.push_back(cv::Point2f(rect_Point2[2].x, rect_Point2[0].y));
	cv::Mat elementTransf(3, 3, CV_32FC1); //与原来四个点一一匹配，并生成3x3的变换矩阵
	elementTransf = getPerspectiveTransform(rect_Point, rect_Point2); //使用变换矩阵进行图形变换

	//对要绘制网格的和要进行颜色提取的图片都进行仿射变换，让他们正起来
	warpPerspective(src, src, elementTransf, src.size()); //仿射变换
	
}
//----------------------------------功能函数----------------------------------------------------
bool ImageProcessor(cv::Mat& src)
{
	// 一、图片旋转
	Rotation(src);
	
	//二、高斯滤波
	cv::GaussianBlur(src, src, cv::Size(3, 3), 0);

	//三、提取轮廓边界点
	vector<cv::Point2f> rect_Point;
	if (!GetRectPoint(src, rect_Point))return false; //如果没有提取边界点成功，返回false
	

	//四、放射变换
	warp(src, rect_Point);



	return true;
	

}