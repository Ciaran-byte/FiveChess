#include "game.h"

namespace myChess
{
	//��Ϸ��ʼ������
	void game::gameInit()
	{
		//01 �趨��Ϸģʽ
		ok = GOON; //�趨��Ϸ��־λΪ������Ϸ
		PEok = true; //��ֹ�˻���ʱ���´�����
		std::cout << "��ӭ��������������磡" << std::endl;
		std::cout << "��0������" << std::endl;
		std::cout << "��1���˻�" << std::endl;
		std::cout << "��2������" << std::endl;

		while (std::cin >> mode)
		{

			if (mode == PP || mode == PE||mode==EE)
			{
				system("cls");
				break;
			}

			else
			{
				system("cls");
				std::cout << "������ѡ����Ϸģʽ:" << std::endl;
				std::cout << "��0������" << std::endl;
				std::cout << "��1���˻�" << std::endl;
				std::cout << "��2������" << std::endl;
			}
		}

		//02 ��������ˣ��趨���������ֵ�����
		if (mode == PP)
		{
			system("cls");
			std::cout << "��Ϊ������������" << std::endl;
			std::cout << "����: ";
			std::string name;
			std::cin >> name;
			black.getColor() = BLACK;
			black.getName() = name;

			std::cout << "����: ";
			std::cin >> name;
			white.getColor() = WHITE;
			white.getName() = name;
			WhoIsFirst = -1;
			system("cls");



		}
		//03 ������˻�����Ҫ�趨��˭��˭��
		else if (mode == PE)
		{
			system("cls");
			std::cout << "����ִ���廹�ǰ���:" << std::endl;
			std::cout << "��0������" << std::endl;
			std::cout << "��1������" << std::endl;
			while (std::cin >> WhoIsFirst)
			{
				if (WhoIsFirst == PeopleFirst || WhoIsFirst == ComputerFirst)
				{
					system("cls");
					break;
				}
				else
				{
					system("cls");
					std::cout << "������ѡ���Ⱥ�˳��:" << std::endl;
					std::cout << "��0������" << std::endl;
					std::cout << "��1������" << std::endl;
				}
			}
			if (WhoIsFirst == PeopleFirst)
			{
				black.getName() = "People";
				black.getColor() = BLACK;
				white.getName() = "Computer";
				white.getColor() = WHITE;
			}
			else if (WhoIsFirst == ComputerFirst)
			{
				black.getName() = "Computer";
				black.getColor() = BLACK;
				white.getName() = "People";
				white.getColor() = WHITE;
			}


		}
		else if (mode == EE)
		{
			black.getColor() = BLACK;
			black.getName() = "computer1";
			white.getColor() =WHITE;
			white.getName() = "computer2";
			WhoIsFirst = -1;
			system("cls");
		}

		std::cout << "��Ϸ��ʼ��" << std::endl;
		std::cout << "�ڷ�: " << black.getName() << std::endl;
		std::cout << "�׷�: " << white.getName() << std::endl;
	}

	//���˶�ս�Ļص�����
	void game::PPMouseCallBack(int event, int x, int y, int flags, void* param)

	{


		if (x >= 30 && x <= 670 && y >= 30 && y <= 670)//������������Χ�ڲŴ���
		{
			switch (event)
			{
			case(cv::EVENT_LBUTTONDOWN): //��������������µ��¼�
			{

				if (ok == GOON)//�ж���Ϸ�Ƿ������
				{
					if (j.nextChesser() == 0)//�����һ���ú�������
					{
						Calibration(x, y); //У�����������
						cv::Point p = myChess::ReMap(x, y).pt();//ת��Ϊ��ͼ���ĵ�
						if (cp.addChess(black.getNextChess(cp, p.x, p.y)))//����ܹ�������������
						{
							circle(rd.pad, cv::Point(x, y), 10, cv::Scalar(0, 0, 0), -1);//����
						}
						else
						{
							j.getCurrentChesser() = 1;//���û�ɹ�����һ���ڻ��Ǻ���
						}
					}


					else //����ð�������
					{
						Calibration(x, y);
						cv::Point p = myChess::ReMap(x, y).pt();

						if (cp.addChess(white.getNextChess(cp, p.x, p.y)))
						{
							circle(rd.pad, cv::Point(x, y), 10, cv::Scalar(255, 255, 255), -1);
						}
						else
						{
							j.getCurrentChesser() = 0;//���û�ɹ�����һ�ֻ��ǰ���
						}




					}
				}
			}

			case(CV_EVENT_RBUTTONUP):
			{
				system("cls");
				std::cout << "��ǰ����:" << std::endl;
				std::cout << cp << std::endl;
				int y = cp.getLastRow();
				int x = cp.getLastCol();
				if (cp.getLastColor() == BLACK)
				{
					std::cout << "������" << black.getName() << "������" << "(" << x << "," << y << ")" << std::endl;
				}
				if (cp.getLastColor() == WHITE)
				{
					std::cout << "������" << white.getName() << "������" << "(" << x << "," << y << ")" << std::endl;
				}
				int rst = j.JudgeResult(cp);

				if (rst == 1)
				{
					std::cout << "��ʤ" << std::endl;
					ok = OVER;
				}
				else if (rst == 2)
				{
					std::cout << "��ʤ" << std::endl;
					ok = OVER;
				}
				else if (rst == 3)
				{
					std::cout << "����" << std::endl;
					ok = OVER;
				}
			}
			}

		}


	}

	//�˻��Ļص�����
	void game::PEMouseCallBack(int event, int x, int y, int flags, void* param)

	{


		if (x >= 30 && x <= 670 && y >= 30 && y <= 670)//������������Χ�ڲŴ���
		{
			switch (event)
			{
			case(cv::EVENT_LBUTTONDOWN): //��������������µ��¼�
			{
				if (ok == GOON) //�����Ϸ����
				{

					if (WhoIsFirst == PeopleFirst && j.nextChesser() == 0)//�����һ���ú�������
					{
						Calibration(x, y); //У�����������
						cv::Point p = myChess::ReMap(x, y).pt();//ת��Ϊ��ͼ���ĵ�
						if (cp.addChess(black.getNextChess(cp, p.x, p.y)))//����ܹ�������������
						{
							circle(rd.pad, cv::Point(x, y), 10, cv::Scalar(0, 0, 0), -1);//����
							PEok = true;
						}
						else
						{
							PEok = false;
						}
						
					}

					if (WhoIsFirst == ComputerFirst && j.nextChesser() == 1)//�����һ���ð�������
					{
						Calibration(x, y); //У�����������
						cv::Point p = myChess::ReMap(x, y).pt();//ת��Ϊ��ͼ���ĵ�
						if (cp.addChess(white.getNextChess(cp, p.x, p.y)))//����ܹ�������������
						{
							circle(rd.pad, cv::Point(x, y), 10, cv::Scalar(255, 255, 255), -1);//����
							PEok = true;
						}
						else
						{
							PEok = false;
						}
						
					}

					//�����ǰ���ƺ���һ������������
					system("cls");
					
					int y = cp.getLastRow();
					int x = cp.getLastCol();
					if (cp.getLastColor() == BLACK)
					{
						std::cout << "������" << black.getName() << "������" << "(" << x << "," << y << ")" << std::endl;
					}
					if (cp.getLastColor() == WHITE)
					{
						std::cout << "������" << white.getName() << "������" << "(" << x << "," << y << ")" << std::endl;
					}
					
					//�жϽ��
					int rst = j.JudgeResult(cp);

					if (rst == 1)
					{
						std::cout << "��ʤ" << std::endl;
						ok = OVER;
					}
					else if (rst == 2)
					{
						std::cout << "��ʤ" << std::endl;
						ok = OVER;
					}
					else if (rst == 3)
					{
						std::cout << "����" << std::endl;
						ok = OVER;
					}



				}

			case(CV_EVENT_RBUTTONUP):
			{
				if (ok == GOON) //�����Ϸ����
				{

					if (WhoIsFirst == ComputerFirst && j.nextChesser() == 0&&PEok)//�����һ���ú�������
					{
						cv::Point dataP = ai.getPosition(cp, black.getColor());
						if (cp.addChess(black.getNextChess(cp, dataP.x, dataP.y)))
						{
							cv::circle(rd.pad, Map(dataP.x, dataP.y).pt(), 10, cv::Scalar(0, 0, 0), -1);
						}
						
						
					}
					if (WhoIsFirst == PeopleFirst && j.nextChesser() == 1&& PEok)//�����һ���ð�������
					{
						cv::Point dataP = ai.getPosition(cp, white.getColor());
						if (cp.addChess(white.getNextChess(cp, dataP.x, dataP.y)))
						{
							cv::circle(rd.pad, Map(dataP.x, dataP.y).pt(), 10, cv::Scalar(255, 255, 255), -1);
						}
						
					}

					//�����ǰ���ƺ���һ������������
					
					
					int y = cp.getLastRow();
					int x = cp.getLastCol();
					if (cp.getLastColor() == BLACK)
					{
						std::cout << "������" << black.getName() << "������" << "(" << x << "," << y << ")" << std::endl;
					}
					if (cp.getLastColor() == WHITE)
					{
						std::cout << "������" << white.getName() << "������" << "(" << x << "," << y << ")" << std::endl;
					}
					std::cout << "��ǰ����:" << std::endl;
					std::cout << cp << std::endl;
					//������
					int rst = j.JudgeResult(cp);
					if (rst == 1)
					{
						std::cout << "��ʤ" << std::endl;
						ok = OVER;
					}
					else if (rst == 2)
					{
						std::cout << "��ʤ" << std::endl;
						ok = OVER;
					}
					else if (rst == 3)
					{
						std::cout << "����" << std::endl;
						ok = OVER;
					}

				}



			}


			
			}

			}


		}
	}

	//������ս�ص�����
	void game::EEMouseCallBack(int event, int x, int y, int flags, void* param)
	{
		switch (event)
		{
		case(cv::EVENT_LBUTTONDOWN): //��������������µ��¼�
		{
			if (ok == GOON) //�����Ϸ����
			{

				
					cv::Point dataP = ai.getPosition(cp, black.getColor());
					if (cp.addChess(black.getNextChess(cp, dataP.x, dataP.y)))
					{
						cv::circle(rd.pad, Map(dataP.x, dataP.y).pt(), 10, cv::Scalar(0, 0, 0), -1);
					}


				



				//�����ǰ���ƺ���һ������������
				system("cls");

				int y = cp.getLastRow();
				int x = cp.getLastCol();
				
				std::cout << "������" << black.getName() << "������" << "(" << x << "," << y << ")" << std::endl;
				

				//�жϽ��
				int rst = j.JudgeResult(cp);

				if (rst == 1)
				{
					std::cout << "��ʤ" << std::endl;
					ok = OVER;
				}
				else if (rst == 2)
				{
					std::cout << "��ʤ" << std::endl;
					ok = OVER;
				}
				else if (rst == 3)
				{
					std::cout << "����" << std::endl;
					ok = OVER;
				}



			}
		}

		case(CV_EVENT_RBUTTONUP):
		{
			if (ok == GOON) //�����Ϸ����
			{

				cv::Point dataP = ai.getPosition(cp, white.getColor());
				if (cp.addChess(white.getNextChess(cp, dataP.x, dataP.y)))
				{
					cv::circle(rd.pad, Map(dataP.x, dataP.y).pt(), 10, cv::Scalar(255, 255, 255), -1);
				}


				//�����ǰ���ƺ���һ������������


				int y = cp.getLastRow();
				int x = cp.getLastCol();
				
				
				std::cout << "������" << white.getName() << "������" << "(" << x << "," << y << ")" << std::endl;
				
				std::cout << "��ǰ����:" << std::endl;
				std::cout << cp << std::endl;
				//������
				int rst = j.JudgeResult(cp);
				if (rst == 1)
				{
					std::cout << "��ʤ" << std::endl;
					ok = OVER;
				}
				else if (rst == 2)
				{
					std::cout << "��ʤ" << std::endl;
					ok = OVER;
				}
				else if (rst == 3)
				{
					std::cout << "����" << std::endl;
					ok = OVER;
				}

			}



		}
		}
	}


	 void game::gameStart()
	{

		cv::namedWindow("m");

		if (mode == PP)
		{
		cv::setMouseCallback("m", myChess::game::PPMouseCallBack, (void*)(0)); //��꺯��
		cv::imshow("m", rd.pad);
		while (1)
		{
			cv::imshow("m", rd.pad);

			if (cv::waitKey(10) == 27)break;//��ESC���˳�
		}

		cv::waitKey(0);
		}

		if (mode == PE)
		{
			if (getWhoIsFirst() == ComputerFirst && j.nextChesser() == 0)//�����һ���ú�������
			{
				cv::Point dataP = ai.getPosition(cp, black.getColor());
				cp.addChess(black.getNextChess(cp, dataP.x, dataP.y));
				cv::circle(rd.pad, myChess::Map(dataP.x, dataP.y).pt(), 10, cv::Scalar(0, 0, 0), -1);
			}
			cv::setMouseCallback("m", myChess::game::PEMouseCallBack, (void*)(0)); //��꺯��
			cv::imshow("m", rd.pad);
			while (1)
			{
				cv::imshow("m", rd.pad);

				if (cv::waitKey(10) == 27)break;//��ESC���˳�
			}

			cv::waitKey(0);
		}

		if (mode == EE)
		{

			cv::setMouseCallback("m", myChess::game::EEMouseCallBack, (void*)(0)); //��꺯��
			cv::imshow("m", rd.pad);
			while (1)
			{
				cv::imshow("m", rd.pad);

				if (cv::waitKey(10) == 27)break;//��ESC���˳�
			}

			cv::waitKey(0);
		}
		
	}
}
