#include "ArtificialIntelligence.h"


int ArtificialIntelligence::JudgeType(const std::vector<int>& chess) //判断棋形的
{
	int mycolor = chess[4]; //记录位于中间的棋子颜色
	int hiscolor;   //记录对手棋子的颜色
	int left, right;  //左边断色棋子和右边断色棋子位置
	int leftColor, rightColor; //左边断色棋子和右边断色棋子颜色
	int count = 1;

	//01 用来判断己方和对方棋子的颜色
	if (mycolor == BLACK)
	{
		hiscolor = WHITE;
	}
	else
	{
		hiscolor = BLACK;
	}

	//02 判断棋子连接情况

	//02-1 判断左边棋子的连接情况
	for (int i = 1; i <= 4; i++)
	{
		if (chess[4 - i] == mycolor)
		{
			count++;
		}
		else
		{
			left = 4 - i;
			leftColor = chess[4 - i];
			break;
		}
	}

	//02-2 判断右边棋子的连接情况
	for (int i = 1; i <= 4; i++)
	{
		if (chess[4 + i] == mycolor)
		{
			count++;
		}
		else
		{
			right = 4 + i;
			rightColor = chess[4 + i];
			break;
		}
	}
	//03 根据棋子连接数和左右端棋子的颜色，判断基本形
	if (count == 5)
	{
		return WIN5; //连无
	}
	if (count == 4)
	{
		if (leftColor == NOTHING && rightColor == NOTHING)
		{
			return ALIVE4;  //4连珠并且左右均空，说明是活四棋形
		}
		else if (leftColor == hiscolor && rightColor == hiscolor)
		{
			return NOTHREAT; //没有威胁
		}
		else if (leftColor == NOTHING || rightColor == NOTHING)
		{
			return DIE4; //死四
		}
	}

	if (count == 3)
	{
		int colorleft1 = chess[left - 1];
		int colorright1 = chess[right + 1];
		if (leftColor == NOTHING && rightColor == NOTHING)
		{
			if (colorleft1 == hiscolor && colorright1 == hiscolor)//均为对手棋子
				return DIE3;
			else if (colorleft1 == mycolor || colorright1 == mycolor)//只要一个为自己的棋子
				return LOWDIE4;
			else if (colorleft1 == NOTHING || colorright1 == NOTHING)//只要有一个空
				return ALIVE3;
		}
		else if (leftColor == hiscolor && rightColor == hiscolor)//两边断开位置均非空
		{
			return NOTHREAT;//没有威胁
		}

		else if (leftColor == NOTHING || rightColor == NOTHING)
		{

			if (leftColor == hiscolor) {//左边被对方堵住
				if (colorright1 == hiscolor)//右边也被对方堵住
					return NOTHREAT;
				if (colorright1 == NOTHING)//右边均空
					return DIE3;
				if (colorright1 == mycolor)
					return LOWDIE4;

			}
			if (rightColor == hiscolor) {//右边被对方堵住
				if (colorleft1 == hiscolor)//左边也被对方堵住
					return NOTHREAT;
				if (colorleft1 == NOTHING)//左边均空
					return DIE3;
				if (colorleft1 == mycolor)//左边还有自己的棋子
					return LOWDIE4;
			}
		}


	}

	if (count == 2)
	{
		int leftcolor1 = chess[left - 1];
		int leftcolor2 = chess[left - 2];
		int rightcolor1 = chess[right + 1];
		int rightcolor2 = chess[right + 2];
		if (leftColor == NOTHING && rightColor == NOTHING)
		{
			if ((rightcolor1 == NOTHING && rightcolor2 == mycolor) || (leftcolor1 == NOTHING && leftcolor2 == mycolor))
			{
				return DIE3;
			}
			else if (leftcolor1 == NOTHING && rightcolor1 == NOTHING)
				return ALIVE2;//活2
			if ((rightcolor1 == mycolor && rightcolor2 == hiscolor) ||
				(leftcolor1 == mycolor && leftcolor2 == hiscolor))
				return DIE3;//死3

			if ((rightcolor1 == mycolor && rightcolor2 == mycolor) ||
				(leftcolor1 == mycolor && leftcolor2 == mycolor))
				return LOWDIE4;//死4

			if ((rightcolor1 == mycolor && rightcolor2 == NOTHING) ||
				(leftcolor1 == mycolor && leftcolor2 == NOTHING))
				return TIAO3;//跳活3
			//其他情况在下边返回NOTHREAT
		}
		else if (leftColor == hiscolor && rightColor == hiscolor)//两边断开位置均非空
		{
			return NOTHREAT;
		}
		else if (leftColor == NOTHING || rightColor == NOTHING)//两边断开位置只有一个空
		{
			if (leftColor == hiscolor) {//左边被对方堵住
				if (rightcolor1 == hiscolor || rightcolor2 == hiscolor) {//只要有对方的一个棋子
					return NOTHREAT;//没有威胁
				}
				else if (rightcolor1 == NOTHING && rightcolor2 == NOTHING) {//均空
					return DIE2;//死2
				}
				else if (rightcolor1 == mycolor && rightcolor2 == mycolor) {//均为自己的棋子
					return LOWDIE4;//死4
				}
				else if (rightcolor1 == mycolor || rightcolor2 == mycolor) {//只有一个自己的棋子
					return DIE3;//死3
				}
			}
			if (rightColor == hiscolor) {//右边被对方堵住
				if (leftcolor1 == hiscolor || leftcolor2 == hiscolor) {//只要有对方的一个棋子
					return NOTHREAT;//没有威胁
				}
				else if (leftcolor1 == NOTHING && leftcolor2 == NOTHING) {//均空
					return DIE2;//死2
				}
				else if (leftcolor1 == mycolor && leftcolor2 == mycolor) {//均为自己的棋子
					return LOWDIE4;//死4
				}
				else if (leftcolor1 == mycolor || leftcolor2 == mycolor) {//只有一个自己的棋子
					return DIE3;//死3
				}
			}
		}
	}

	if (count == 1) {//中心线1连
		int colorleft1 = chess[left - 1];
		int colorright1 = chess[right + 1];
		int colorleft2 = chess[left - 2];
		int colorright2 = chess[right + 2];
		int colorleft3 = chess[left - 3];
		int colorright3 = chess[right + 3];

		if (leftColor == NOTHING && colorleft1 == mycolor &&
			colorleft2 == mycolor && colorleft3 == mycolor)
			return LOWDIE4;
		if (rightColor == NOTHING && colorright1 == mycolor &&
			colorright2 == mycolor && colorright3 == mycolor)
			return LOWDIE4;

		if (leftColor == NOTHING && colorleft1 == mycolor &&
			colorleft2 == mycolor && colorleft3 == NOTHING && rightColor == NOTHING)
			return TIAO3;
		if (rightColor == NOTHING && colorright1 == mycolor &&
			colorright2 == mycolor && colorright3 == NOTHING && leftColor == NOTHING)
			return TIAO3;

		if (leftColor == NOTHING && colorleft1 == mycolor &&
			colorleft2 == mycolor && colorleft3 == hiscolor && rightColor == NOTHING)
			return DIE3;
		if (rightColor == NOTHING && colorright1 == mycolor &&
			colorright2 == mycolor && colorright3 == hiscolor && leftColor == NOTHING)
			return DIE3;

		if (leftColor == NOTHING && colorleft1 == NOTHING &&
			colorleft2 == mycolor && colorleft3 == mycolor)
			return DIE3;
		if (rightColor == NOTHING && colorright1 == NOTHING &&
			colorright2 == mycolor && colorright3 == mycolor)
			return DIE3;

		if (leftColor == NOTHING && colorleft1 == mycolor &&
			colorleft2 == NOTHING && colorleft3 == mycolor)
			return DIE3;
		if (rightColor == NOTHING && colorright1 == mycolor &&
			colorright2 == NOTHING && colorright3 == mycolor)
			return DIE3;

		if (leftColor == NOTHING && colorleft1 == mycolor &&
			colorleft2 == NOTHING && colorleft3 == NOTHING && rightColor == NOTHING)
			return LOWALIVE2;
		if (rightColor == NOTHING && colorright1 == mycolor &&
			colorright2 == NOTHING && colorright3 == NOTHING && leftColor == NOTHING)
			return LOWALIVE2;

		if (leftColor == NOTHING && colorleft1 == NOTHING &&
			colorleft2 == mycolor && colorleft3 == NOTHING && rightColor == NOTHING)
			return LOWALIVE2;
		if (rightColor == NOTHING && colorright1 == NOTHING &&
			colorright2 == mycolor && colorright3 == NOTHING && leftColor == NOTHING)
			return LOWALIVE2;

		//其余在下边返回没有威胁

	}
	return NOTHREAT;//返回没有威胁

}


void ArtificialIntelligence::getChess(  //获取各个方向的可能构成连珠的棋子
	std::vector<int>& chess,
	const cv::Mat& chp, //Mat应该是CV_8UC1类型的棋盘
	cv::Point p,
	int mycolor,
	int direction
)//获取指定方向棋局
{
	int hiscolor;
	if (mycolor == BLACK)
	{
		hiscolor = WHITE;
	}
	else
	{
		hiscolor = BLACK;
	}
	int last_row = chp.rows; //棋盘的最后一行
	int last_col = chp.cols; //棋盘的最后一列
	int x = p.x; //点的横坐标
	int y = p.y; //
	
	chess[4] = mycolor;
	int time1 = 0; //用于判断边界点的，边界点出界第一点认为是hiscolor，其余认为是nothing，判断左边边界
	int time2 = 0; //判断右边边界
	switch (direction)
	{
	case(0): //横向
	{
		
		for (int j = 1; j <= 4; j++) //左侧四个点赋值
		{

			if (x - j < 0)
			{
				time1++;
				if (time1 == 1)
				{
					chess[4 - j] = hiscolor;
				}
				else
				{
					chess[4 - j] = NOTHING;
				}
				
			}
			else
			{
				chess[4 - j] = chp.at<uchar>(y, x - j);
			}


		}
		
		for (int j = 1; j <= 4; j++) //右侧四个点赋值
		{
		
			if (x + j >= last_col)
			{
				time2++;
				if (time2 == 1)
				{
					chess[4 + j] = hiscolor;
				}
				else
				{
					chess[4 + j] = NOTHING;

				}
				
			}
			else
			{
				chess[4 + j] = chp.at<uchar>(y, x + j);
			}
			
		}
		
		break;
	}
	case(1): //纵向
	{
		for (int j = 1; j <= 4; j++) //上面四个点赋值
		{

			if (y - j < 0)
			{
				time1++;
				if (time1 == 1)
				{
					chess[4 - j] = hiscolor;
				}
				else
				{
					chess[4 - j] = NOTHING;
				}
				
			}
			else
			{
				chess[4 - j] = chp.at<uchar>(y - j, x);
			}


		}

		for (int j = 1; j <= 4; j++) //右侧四个点赋值
		{

			if (y + j >= last_row)
			{
				time2++;
				if (time2 == 1)
				{
					chess[4 + j] = hiscolor;
				}
				else
				{
					chess[4 + j] = NOTHING;

				}
			}
			else
			{
				chess[4 + j] = chp.at<uchar>(y + j, x);
			}


		}
		break;
	}
	case(2): //左上到右下
	{
		for (int j = 1; j <= 4; j++) //往左上角搜索
		{
			if (x - j < 0 || y - j < 0)
			{
				time1++;
				if (time1 == 1)
				{
					chess[4 - j] = hiscolor;
				}
				else
				{
					chess[4 - j] = NOTHING;
				}

			}
			else
			{
				chess[4 - j] = chp.at<uchar>(y - j, x - j);
			}
		}

		for (int j = 1; j <= 4; j++) //往右下角搜索
		{
			if (x + j >= last_row || y + j >= last_row)
			{
				time2++;
				if (time2 == 1)
				{
					chess[4 + j] = hiscolor;
				}
				else
				{
					chess[4 + j] = NOTHING;

				}
			}
			else
			{
				chess[4 + j] = chp.at<uchar>(y + j, x + j);
			}
		}

		break;
	}

	case(3): //左下到右上
	{
		for (int j = 1; j <= 4; j++) //往左下搜索
		{
			if (x - j < 0 || y + j>=last_row)
			{
				time1++;
				if (time1 == 1)
				{
					chess[4 - j] = hiscolor;
				}
				else
				{
					chess[4 - j] = NOTHING;
				}
			}
			else
			{
				chess[4 - j] = chp.at<uchar>(y+j, x - j);
			}
		}
		for (int j = 1; j <= 4; j++) //往右上搜索
		{
			if (x+j >= last_col || y - j < 0)
			{
				time2++;
				if (time2 == 1)
				{
					chess[4 + j] = hiscolor;
				}
				else
				{
					chess[4 + j] = NOTHING;

				}
					;
			}
			else
			{
				chess[4 + j] = chp.at<uchar>(y - j, x + j);
			}
		}
		break;
	}

	}
}

//获取某一个方向的棋子，并判断是什么棋形


int ArtificialIntelligence::getType(
	const cv::Mat& chp,
	cv::Point p,
	int mycolor,
	int direction)
{
	std::vector<int> chess(9, 0);
	
	getChess(chess, chp, p, mycolor, direction);
	
	int type = JudgeType(chess);
	return type;
}

int ArtificialIntelligence::giveScore(Situation situation)
{

	int die4 = situation.die4 + situation.lowdie4;
	int alive3 = situation.alive3 + situation.tiao3;
	int alive2 = situation.alive2 + situation.lowalive2;

	if (situation.win5 >= 1)
		return LevelOne;//赢5

	if (situation.alive4 >= 1 || die4 >= 2 || (die4 >= 1 && alive3 >= 1))
		return Leveltwo;//活4 双死4 死4活3

	if (alive3 >= 2)
		return Levelthree;//双活3

	if (situation.die3 >= 1 && situation.alive3 >= 1)
		return Levelfour;//死3高级活3

	if (situation.die4 >= 1)
		return Levelfive;//高级死4

	if (situation.lowdie4 >= 1)
		return Levelsix;//低级死4

	if (situation.alive3 >= 1)
		return Levelseven;//单活3

	if (situation.tiao3 >= 1)
		return LevelEight;//跳活3

	if (alive2 >= 2)
		return LevelNight;//双活2

	if (situation.alive2 >= 1)
		return LevelTen;//活2

	if (situation.lowalive2 >= 1)
		return LevelEleven;//低级活2

	if (situation.die3 >= 1)
		return LevelTwelve;//死3

	if (situation.die2 >= 1)
		return LevelThirteen;//死2

	return LevelFourteen;//没有威胁
}





int ArtificialIntelligence::judgeChessSituation(const cv::Mat& chp, cv::Point p, int color)
{

	Situation situation;
	
	if (chp.at<uchar>(p.y,p.x)!= NOTHING)
	{
		return LevelFiveteen;//有棋子，不能下
	}
	
	for (int direction = 0; direction < 4; direction++) {//四个方向,0横，1竖，2左上右下，3右上左下
		int type;
		
		type = getType(chp, p, color, direction);//取得类型（死四，活四等）
		
		switch (type) {//根据类型对situation设置
		case WIN5:
			situation.win5++;
			break;
		case ALIVE4:
			situation.alive4++;
			break;
		case DIE4:
			situation.die4++;
			break;
		case LOWDIE4:
			situation.lowdie4++;
			break;
		case ALIVE3:
			situation.alive3++;
			break;
		case TIAO3:
			situation.tiao3++;
			break;
		case DIE3:
			situation.die3++;
			break;
		case ALIVE2:
			situation.alive2++;
			break;
		case LOWALIVE2:
			situation.lowalive2++;
			break;
		case DIE2:
			situation.die2++;
			break;
		case NOTHREAT:
			situation.nothreat++;
			break;
		default:
			//差错控制
			break;
		}
	}
	
	return giveScore(situation);//根据形势得出分数
}



cv::Point ArtificialIntelligence::getPosition(const cv::Mat& chp, int color)
{
	int myColor = color;
	int hisColor;
	int last_row = chp.rows;
	
	int last_col = chp.cols;
	if (myColor == BLACK)
	{
		hisColor = WHITE;
	}
	else
	{
		hisColor = BLACK;
	}


	std::vector<cv::Point> myMaxPoint;
	std::vector<cv::Point> hisMaxPoint;

	int myMaxScore = 0;
	int hisMaxScore = 0;
	
	//判断是不是第一手
	int ret = 0;
	int m, n;
	for (m = 0; m < last_row; m++)
	{
		for (n = 0; n <last_col; n++)
		{
			if (chp.at<uchar>(m,n) != NOTHING)
			{
				ret = 1;
				break;
			}
		}
		if (ret == 1)
			break;
	}
	if (m == last_row && n == last_col)
	{
		return cv::Point(last_col/2, last_row/2);
	}
	
	//判断我方最大值点组
	int myscore = 0;
	for (int i = 0; i < last_row; i++)
	{
		for (int j = 0; j < last_col; j++)
		{
			myscore = judgeChessSituation(chp, cv::Point(j, i), myColor);
			
			

			if (myscore == myMaxScore)
			{
				myMaxPoint.push_back(cv::Point(j, i));
			}
			if (myscore > myMaxScore)
			{
				myMaxScore = myscore;
				myMaxPoint.clear();
				myMaxPoint.push_back(cv::Point(j, i));
			}
		}
	}

	
	//判断对方最大值点
	int hisscore = 0;
	for (int i = 0; i < last_row; i++)
	{
		for (int j = 0; j < last_col; j++)
		{
			hisscore = judgeChessSituation(chp, cv::Point(j, i), hisColor);
			if (hisscore == hisMaxScore)
			{
				hisMaxPoint.push_back(cv::Point(j, i));
			}
			if (hisscore > hisMaxScore)
			{
				hisMaxScore = hisscore;
				hisMaxPoint.clear();
				hisMaxPoint.push_back(cv::Point(j, i));
			}
		}
	}







	//进攻
	cv::Point position(0, 0);
	int temp = 0;
	if (myMaxScore > hisMaxScore)
	{
		std::vector<cv::Point>::iterator it = myMaxPoint.begin();
		std::vector<cv::Point>::iterator end = myMaxPoint.end();
		for (; it != end; it++)
		{
			int hisScore = judgeChessSituation(chp, *it, hisColor);
			if (hisScore > temp)
			{
				temp = hisScore;
				position.x = (*it).x;
				position.y = (*it).y;
			}
		}
		return position;
	}

	else //防守
	{
		std::vector<cv::Point>::iterator it = hisMaxPoint.begin();
		std::vector<cv::Point>::iterator end = hisMaxPoint.end();
		for (; it != end; it++)
		{
			int myScore = judgeChessSituation(chp, *it, myColor);
			if (myScore > temp)
			{
				temp = myScore;
				position.x = (*it).x;
				position.y = (*it).y;
			}
		}
		return position;
	}

}

