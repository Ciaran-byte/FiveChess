#include<iostream>
#include"Processor.h"
#include "ChessPad.h"
#include "WZSerialPort.h"
#include "draw.h"
#include "Judge.h"
using namespace std;


int main()
{
	//������ͷ
	cv::VideoCapture capture;
	capture.open(0);           //open the default camera -1����Ĭ�������
	if (capture.isOpened())cout << "camera open!!!";

	//����ɼ�ͼƬ��������������
	cv::Mat src;
	ChessPad chp;

	//���崮������
	WZSerialPort w;
	while (1)
	{
		//01 ��ȡͼƬ
		
		capture >> src;
		//�жϵ�ǰ֡�Ƿ�׽�ɹ� 
		if (src.empty()) cout << "can't get picture" << endl;
		

		//02 ����任����ͼƬ
		if (!ImageProcessor(src))continue;
		
		//03 ��ʼ����������
		chp.ReloadGrid(src);
		
		//04 �ڼ�������̺�ʵ�������м�������
		if (chp.addBlackList()) //������壬���Һ������ɹ���ʱ��Ż�������
		{
			if (JudgeResult(chp.chess, chp.GetLastBlack(), BLACK) != BLACK) //�������û��Ӯ���Ż���ذ���
			{


				chp.addWhiteList();
				if (w.open("\\\\.\\COM12"))
				{
					cout << "���ڴ򿪳ɹ�" << endl;
					w.send(chp.sendStr());
					Sleep(500);
					w.close();
				}
				else
				{
					cout << "���ڴ�ʧ��" << endl;
				}
				//�������Ӯ�ˣ����˳�
				if (JudgeResult(chp.chess, chp.GetLastWhite(), WHITE) == WHITE)
				{
					cout << "white win" << endl;
					break;
				}
				

			}
			else //�������Ӯ�ˣ��˳�
			{
				cout << "black win" << endl;
				break;
			}
		}

		//05 ��ͼ
		drawPicture(src, chp);
		cv::imshow("1", src);
		cv::waitKey(30);
	}

	//�������ʤ���ˣ���������ͼ
	drawPicture(src, chp);
	cv::imshow("1", src);
	cv::waitKey(0);
	return 0;
}