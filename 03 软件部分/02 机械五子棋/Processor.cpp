#include "Processor.h"


//----------------------------------���ߺ���----------------------------------------------------
void Rotation(cv::Mat& src, double angle, double scale)//ͨ�����ýǶȺ����ű���������ͼƬ��С
{
	cv::Point center(src.cols / 2, src.rows / 2); //��ת����

	cv::Mat rotMat = getRotationMatrix2D(center, angle, scale);
	cv::warpAffine(src, src, rotMat, src.size());

}

void GetGreenPixel(const cv::Mat& src, cv::Mat& GreenPixel) //��ȡͼƬ����ɫ��Ĥ
{
	//01 hsvɫ�ʿռ�任
	cv::Mat hsv; //����hsvͼƬ
	cvtColor(src, hsv, cv::COLOR_BGR2HSV); //�任��hsvɫ�ʿռ������ɫ��ȡ
	//02 ��hsv����ȡ��ɫ�߿�

	int iLowH = 38;  //��ɫ�ķ�Χ�� H 38-77  S 30-255   V 30-255
	int iLowS = 43;  //��ɫ�ķ�Χ 78 - 99 
	int iLowV = 46;
	int iHighH = 77;

	int iHighS = 255;
	int iHighV = 255;

	cv::Mat mask; //ͨ��inRange�����������Ϸ�Χ������Ϊ255��������Ĥ
	inRange(hsv, cv::Scalar(iLowH, iLowS, iLowV), cv::Scalar(iHighH, iHighS, iHighV), mask);

	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
	morphologyEx(mask, mask, cv::MORPH_OPEN, element);//ͨ���������ܹ�ȥ����ɫС�ߵ�
	morphologyEx(mask, mask, cv::MORPH_CLOSE, element, cv::Point(-1, -1), 3); //ͨ���ղ����ܹ���������

	bitwise_and(src, src, GreenPixel, mask); //ͨ����Ĥ����ԭͼ��λ���㣬��ȡ��Ӧ����ɫ����
}
bool GetRectPoint(const cv::Mat src, vector<cv::Point2f>& rect_Point)//ͨ����ɫ���ص�ͼ��ʶ�������ĸ���
{
	//01 ��ȡԭͼ�е���ɫ���ص�ͼ
	cv::Mat GreenPixel;
	GetGreenPixel(src, GreenPixel); 

	//02 ���ص�ͼת�Ҷ�ͼ����Ȼû������ʶ������
	cvtColor(GreenPixel, GreenPixel, cv::COLOR_BGR2GRAY);

	//03 ��ȡ������Ϣ
	vector<vector<cv::Point>> contours; //��ȡ������Ϣ
	vector<cv::Vec4i> hierarchy;//��������Ϣ
	findContours(GreenPixel, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0)); //������Ϣ

	//04 ��������

		//��03�õ����������ж������ϣ��õ���Ҫ���ı���
	vector<vector<cv::Point>> contours_poly(contours.size()); //������������������еĶ������ϵı߽��

	for (int i = 0; i < contours.size(); i++)
	{
		cv::approxPolyDP(cv::Mat(contours[i]), contours_poly[i], 80, true); //�������������ж������ϣ���Ϊֻ��������������ûɸѡ�������

	}
	//05 ��ϵõ����ı���ȡ�����Ǹ�
	if (contours_poly.size() > 1) //����ϵĶ���Σ����ҵ������Ǹ�
	{
		for (int i = contours_poly.size() - 1; i > 0; i--) {
			if (contourArea(contours_poly[i]) > contourArea(contours_poly[i - 1])) {
				contours_poly[i - 1] = contours_poly[i];
			}
		}
	}
	//06 �����ϵõ������ͼ�������ı��Σ�����ȥ��������
	if (contours_poly[0].size() != 4)return false;

	//07 ������ı��Σ�������ȡ�ĸ��ߵ���
	vector<cv::Point> outer = contours_poly[0];
	//��ϵ���������ʱ���
	// ����ʱ�뷽����ȡ�ĸ��ߵ�
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

	return true; //������ͼ�����ı��Σ���ȡ�����ĸ��߽�㣬����true

}

void warp(cv::Mat& src, const vector<cv::Point2f>& rect_Point) //ͨ������任����ͼƬ
{
	vector<cv::Point2f> rect_Point2; //��¼����任���ĸ��������Ϣ

	rect_Point2.push_back(cv::Point2f(0, 0));	//----------------------------------------------����任ǰ��׼��
	rect_Point2.push_back(cv::Point2f(rect_Point2[0].x, rect_Point2[0].y + src.rows)); //����ʱ��˳��׼���ĸ���
	rect_Point2.push_back(cv::Point2f(rect_Point2[1].x + src.cols, rect_Point2[1].y));
	rect_Point2.push_back(cv::Point2f(rect_Point2[2].x, rect_Point2[0].y));
	cv::Mat elementTransf(3, 3, CV_32FC1); //��ԭ���ĸ���һһƥ�䣬������3x3�ı任����
	elementTransf = getPerspectiveTransform(rect_Point, rect_Point2); //ʹ�ñ任�������ͼ�α任

	//��Ҫ��������ĺ�Ҫ������ɫ��ȡ��ͼƬ�����з���任��������������
	warpPerspective(src, src, elementTransf, src.size()); //����任
	
}
//----------------------------------���ܺ���----------------------------------------------------
bool ImageProcessor(cv::Mat& src)
{
	// һ��ͼƬ��ת
	Rotation(src);
	
	//������˹�˲�
	cv::GaussianBlur(src, src, cv::Size(3, 3), 0);

	//������ȡ�����߽��
	vector<cv::Point2f> rect_Point;
	if (!GetRectPoint(src, rect_Point))return false; //���û����ȡ�߽��ɹ�������false
	

	//�ġ�����任
	warp(src, rect_Point);



	return true;
	

}