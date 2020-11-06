#include "ChessPad.h"

void ChessPad::ReloadGrid(const cv::Mat& src)//��ȡ��������任�Ժ��ͼƬ����������������
{
	//��������ͼƬ
	this->src = src.clone();

	// ���¸����Ϣ
	float dx = (src.cols) / 9.0;
	float dy = (src.rows) / 9.0;
	

	for (int i = 0; i < 9; i++)
	{
		colPoint.push_back(dx / 2.0 + dx * i);
		rowPoint.push_back(dy / 2.0 + dy * i);
	}
	


}

cv::Point2f  ChessPad::P(int x, int y)//��ȡ���(x,y)��Ӧ�����ص�����
{
	return cv::Point2f(colPoint[x], rowPoint[y]);
}

bool ChessPad::addBlackList() //�����ɫ����
{
	//01 ����任�Ժ��ͼƬתתhsvͼƬ
	cv::Mat hsv;
	cv::cvtColor(src, hsv, CV_BGR2HSV);

	//02 ʶ�����(ʵ��ʹ�õ�����ɫ��)
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{

			int h, s, v; //��¼����hsvֵ
			int flag = 0; //�����ж��Ƿ��������μ�ⶼ����ɫ����
			for (int time = 0; time < 2; time++)
			{

				//��ȡ������hsvֵ��ʶ����ɫ���ӣ��������ǵ����ӡ��������̿��ܳ�����ʶ������ʶ����2�Σ���������2�ζ�����ɫ����
				//����Ϊ�������µ�����
				h = hsv.at<cv::Vec3b>(P(i,j))[0];
				s = hsv.at<cv::Vec3b>(P(i, j))[1];
				v = hsv.at<cv::Vec3b>(P(i, j))[2];

				if (h >= 110 && h <= 124 && s >= 43 && s <= 255 && v >= 43 && v <= 255)
				{

					flag++;
					if (flag == 2)
					{
						if (find(BlackList.begin(), BlackList.end(), cv::Point(i, j)) == BlackList.end())//������λ�õĺ��廹û�м������̣��ͼ���
						{
							chess.at<uchar>(j, i) = BLACK;
							BlackList.push_back(cv::Point(i, j));
							return  true; //�����в�������
						}
						

					}
				}
				else
				{
					break;
				}

			}
		}
	}
	return false;

}
bool ChessPad::addWhiteList() //�����ɫ����
{
	ArtificialIntelligence AI;
	cv::Point whiteP=AI.getPosition(this->chess, WHITE);
	chess.at<uchar>(whiteP.y, whiteP.x) = WHITE;
	WhiteList.push_back(whiteP);
	return true;

	
}
cv::Point ChessPad::GetLastBlack()//��ȡ��һ����ɫ���ӵ�λ��
{
	if (BlackList.empty())return cv::Point(-1, -1);
	else return BlackList[BlackList.size() - 1];

}
cv::Point ChessPad::GetLastWhite() //��ȡ��һ����ɫ���ӵ�λ��
{
	if (WhiteList.empty())return cv::Point(-1, -1);
	else return WhiteList[WhiteList.size() - 1];
	
}

string ChessPad::sendStr()
{
	int num =GetLastWhite().x * 10 + GetLastWhite().y;
	ostringstream s;
	s << num;
	return s.str();
}