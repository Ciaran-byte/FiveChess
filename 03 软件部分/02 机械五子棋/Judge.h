#pragma once
#include<opencv2/opencv.hpp>
#ifndef _JUDGE_H_
#define _JUDGE_H_
/*
����:Judge.h
����:����ͨ����ǰ��֣��ƶϳ��Ƿ��������

*/
int JudgeResult(const cv::Mat& chess, cv::Point lastChess, int ChessColor); //���ڲþ���ǰ�����Ƿ�ȡ����ʤ��
#endif