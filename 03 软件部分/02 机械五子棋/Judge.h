#pragma once
#include<opencv2/opencv.hpp>
#ifndef _JUDGE_H_
#define _JUDGE_H_
/*
名称:Judge.h
作用:用于通过当前棋局，推断出是否下棋结束

*/
int JudgeResult(const cv::Mat& chess, cv::Point lastChess, int ChessColor); //用于裁决当前棋子是否取得了胜利
#endif