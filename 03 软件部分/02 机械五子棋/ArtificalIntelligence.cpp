#include "ArtificialIntelligence.h"


int ArtificialIntelligence::JudgeType(const std::vector<int>& chess) //�ж����ε�
{
	int mycolor = chess[4]; //��¼λ���м��������ɫ
	int hiscolor;   //��¼�������ӵ���ɫ
	int left, right;  //��߶�ɫ���Ӻ��ұ߶�ɫ����λ��
	int leftColor, rightColor; //��߶�ɫ���Ӻ��ұ߶�ɫ������ɫ
	int count = 1;

	//01 �����жϼ����ͶԷ����ӵ���ɫ
	if (mycolor == BLACK)
	{
		hiscolor = WHITE;
	}
	else
	{
		hiscolor = BLACK;
	}

	//02 �ж������������

	//02-1 �ж�������ӵ��������
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

	//02-2 �ж��ұ����ӵ��������
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
	//03 �������������������Ҷ����ӵ���ɫ���жϻ�����
	if (count == 5)
	{
		return WIN5; //����
	}
	if (count == 4)
	{
		if (leftColor == NOTHING && rightColor == NOTHING)
		{
			return ALIVE4;  //4���鲢�����Ҿ��գ�˵���ǻ�������
		}
		else if (leftColor == hiscolor && rightColor == hiscolor)
		{
			return NOTHREAT; //û����в
		}
		else if (leftColor == NOTHING || rightColor == NOTHING)
		{
			return DIE4; //����
		}
	}

	if (count == 3)
	{
		int colorleft1 = chess[left - 1];
		int colorright1 = chess[right + 1];
		if (leftColor == NOTHING && rightColor == NOTHING)
		{
			if (colorleft1 == hiscolor && colorright1 == hiscolor)//��Ϊ��������
				return DIE3;
			else if (colorleft1 == mycolor || colorright1 == mycolor)//ֻҪһ��Ϊ�Լ�������
				return LOWDIE4;
			else if (colorleft1 == NOTHING || colorright1 == NOTHING)//ֻҪ��һ����
				return ALIVE3;
		}
		else if (leftColor == hiscolor && rightColor == hiscolor)//���߶Ͽ�λ�þ��ǿ�
		{
			return NOTHREAT;//û����в
		}

		else if (leftColor == NOTHING || rightColor == NOTHING)
		{

			if (leftColor == hiscolor) {//��߱��Է���ס
				if (colorright1 == hiscolor)//�ұ�Ҳ���Է���ס
					return NOTHREAT;
				if (colorright1 == NOTHING)//�ұ߾���
					return DIE3;
				if (colorright1 == mycolor)
					return LOWDIE4;

			}
			if (rightColor == hiscolor) {//�ұ߱��Է���ס
				if (colorleft1 == hiscolor)//���Ҳ���Է���ס
					return NOTHREAT;
				if (colorleft1 == NOTHING)//��߾���
					return DIE3;
				if (colorleft1 == mycolor)//��߻����Լ�������
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
				return ALIVE2;//��2
			if ((rightcolor1 == mycolor && rightcolor2 == hiscolor) ||
				(leftcolor1 == mycolor && leftcolor2 == hiscolor))
				return DIE3;//��3

			if ((rightcolor1 == mycolor && rightcolor2 == mycolor) ||
				(leftcolor1 == mycolor && leftcolor2 == mycolor))
				return LOWDIE4;//��4

			if ((rightcolor1 == mycolor && rightcolor2 == NOTHING) ||
				(leftcolor1 == mycolor && leftcolor2 == NOTHING))
				return TIAO3;//����3
			//����������±߷���NOTHREAT
		}
		else if (leftColor == hiscolor && rightColor == hiscolor)//���߶Ͽ�λ�þ��ǿ�
		{
			return NOTHREAT;
		}
		else if (leftColor == NOTHING || rightColor == NOTHING)//���߶Ͽ�λ��ֻ��һ����
		{
			if (leftColor == hiscolor) {//��߱��Է���ס
				if (rightcolor1 == hiscolor || rightcolor2 == hiscolor) {//ֻҪ�жԷ���һ������
					return NOTHREAT;//û����в
				}
				else if (rightcolor1 == NOTHING && rightcolor2 == NOTHING) {//����
					return DIE2;//��2
				}
				else if (rightcolor1 == mycolor && rightcolor2 == mycolor) {//��Ϊ�Լ�������
					return LOWDIE4;//��4
				}
				else if (rightcolor1 == mycolor || rightcolor2 == mycolor) {//ֻ��һ���Լ�������
					return DIE3;//��3
				}
			}
			if (rightColor == hiscolor) {//�ұ߱��Է���ס
				if (leftcolor1 == hiscolor || leftcolor2 == hiscolor) {//ֻҪ�жԷ���һ������
					return NOTHREAT;//û����в
				}
				else if (leftcolor1 == NOTHING && leftcolor2 == NOTHING) {//����
					return DIE2;//��2
				}
				else if (leftcolor1 == mycolor && leftcolor2 == mycolor) {//��Ϊ�Լ�������
					return LOWDIE4;//��4
				}
				else if (leftcolor1 == mycolor || leftcolor2 == mycolor) {//ֻ��һ���Լ�������
					return DIE3;//��3
				}
			}
		}
	}

	if (count == 1) {//������1��
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

		//�������±߷���û����в

	}
	return NOTHREAT;//����û����в

}


void ArtificialIntelligence::getChess(  //��ȡ��������Ŀ��ܹ������������
	std::vector<int>& chess,
	const cv::Mat& chp, //MatӦ����CV_8UC1���͵�����
	cv::Point p,
	int mycolor,
	int direction
)//��ȡָ���������
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
	int last_row = chp.rows; //���̵����һ��
	int last_col = chp.cols; //���̵����һ��
	int x = p.x; //��ĺ�����
	int y = p.y; //
	
	chess[4] = mycolor;
	int time1 = 0; //�����жϱ߽��ģ��߽������һ����Ϊ��hiscolor��������Ϊ��nothing���ж���߽߱�
	int time2 = 0; //�ж��ұ߽߱�
	switch (direction)
	{
	case(0): //����
	{
		
		for (int j = 1; j <= 4; j++) //����ĸ��㸳ֵ
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
		
		for (int j = 1; j <= 4; j++) //�Ҳ��ĸ��㸳ֵ
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
	case(1): //����
	{
		for (int j = 1; j <= 4; j++) //�����ĸ��㸳ֵ
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

		for (int j = 1; j <= 4; j++) //�Ҳ��ĸ��㸳ֵ
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
	case(2): //���ϵ�����
	{
		for (int j = 1; j <= 4; j++) //�����Ͻ�����
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

		for (int j = 1; j <= 4; j++) //�����½�����
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

	case(3): //���µ�����
	{
		for (int j = 1; j <= 4; j++) //����������
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
		for (int j = 1; j <= 4; j++) //����������
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

//��ȡĳһ����������ӣ����ж���ʲô����


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
		return LevelOne;//Ӯ5

	if (situation.alive4 >= 1 || die4 >= 2 || (die4 >= 1 && alive3 >= 1))
		return Leveltwo;//��4 ˫��4 ��4��3

	if (alive3 >= 2)
		return Levelthree;//˫��3

	if (situation.die3 >= 1 && situation.alive3 >= 1)
		return Levelfour;//��3�߼���3

	if (situation.die4 >= 1)
		return Levelfive;//�߼���4

	if (situation.lowdie4 >= 1)
		return Levelsix;//�ͼ���4

	if (situation.alive3 >= 1)
		return Levelseven;//����3

	if (situation.tiao3 >= 1)
		return LevelEight;//����3

	if (alive2 >= 2)
		return LevelNight;//˫��2

	if (situation.alive2 >= 1)
		return LevelTen;//��2

	if (situation.lowalive2 >= 1)
		return LevelEleven;//�ͼ���2

	if (situation.die3 >= 1)
		return LevelTwelve;//��3

	if (situation.die2 >= 1)
		return LevelThirteen;//��2

	return LevelFourteen;//û����в
}





int ArtificialIntelligence::judgeChessSituation(const cv::Mat& chp, cv::Point p, int color)
{

	Situation situation;
	
	if (chp.at<uchar>(p.y,p.x)!= NOTHING)
	{
		return LevelFiveteen;//�����ӣ�������
	}
	
	for (int direction = 0; direction < 4; direction++) {//�ĸ�����,0�ᣬ1����2�������£�3��������
		int type;
		
		type = getType(chp, p, color, direction);//ȡ�����ͣ����ģ����ĵȣ�
		
		switch (type) {//�������Ͷ�situation����
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
			//������
			break;
		}
	}
	
	return giveScore(situation);//�������Ƶó�����
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
	
	//�ж��ǲ��ǵ�һ��
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
	
	//�ж��ҷ����ֵ����
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

	
	//�ж϶Է����ֵ��
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







	//����
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

	else //����
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

