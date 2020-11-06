#include<iostream>
#include"Processor.h"
#include "ChessPad.h"
#include "WZSerialPort.h"
#include "draw.h"
#include "Judge.h"
using namespace std;


int main()
{
	//打开摄像头
	cv::VideoCapture capture;
	capture.open(0);           //open the default camera -1才是默认摄像机
	if (capture.isOpened())cout << "camera open!!!";

	//定义采集图片和棋盘数据类型
	cv::Mat src;
	ChessPad chp;

	//定义串口类型
	WZSerialPort w;
	while (1)
	{
		//01 获取图片
		
		capture >> src;
		//判断当前帧是否捕捉成功 
		if (src.empty()) cout << "can't get picture" << endl;
		

		//02 仿射变换处理图片
		if (!ImageProcessor(src))continue;
		
		//03 初始化棋盘网格
		chp.ReloadGrid(src);
		
		//04 在计算机棋盘和实际棋盘中加入棋子
		if (chp.addBlackList()) //加入黑棋，并且黑棋加入成功的时候才会加入白棋
		{
			if (JudgeResult(chp.chess, chp.GetLastBlack(), BLACK) != BLACK) //如果黑棋没有赢，才会加载白棋
			{


				chp.addWhiteList();
				if (w.open("\\\\.\\COM12"))
				{
					cout << "串口打开成功" << endl;
					w.send(chp.sendStr());
					Sleep(500);
					w.close();
				}
				else
				{
					cout << "串口打开失败" << endl;
				}
				//如果白棋赢了，就退出
				if (JudgeResult(chp.chess, chp.GetLastWhite(), WHITE) == WHITE)
				{
					cout << "white win" << endl;
					break;
				}
				

			}
			else //如果黑棋赢了，退出
			{
				cout << "black win" << endl;
				break;
			}
		}

		//05 绘图
		drawPicture(src, chp);
		cv::imshow("1", src);
		cv::waitKey(30);
	}

	//如果有人胜利了，保存最后的图
	drawPicture(src, chp);
	cv::imshow("1", src);
	cv::waitKey(0);
	return 0;
}