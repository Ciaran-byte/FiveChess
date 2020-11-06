#include "game.h"

namespace myChess
{
	//游戏初始化函数
	void game::gameInit()
	{
		//01 设定游戏模式
		ok = GOON; //设定游戏标志位为继续游戏
		PEok = true; //防止人机的时候下错棋子
		std::cout << "欢迎来到五子棋的世界！" << std::endl;
		std::cout << "【0】人人" << std::endl;
		std::cout << "【1】人机" << std::endl;
		std::cout << "【2】机机" << std::endl;

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
				std::cout << "请重新选择游戏模式:" << std::endl;
				std::cout << "【0】人人" << std::endl;
				std::cout << "【1】人机" << std::endl;
				std::cout << "【2】机机" << std::endl;
			}
		}

		//02 如果是人人，设定好两个棋手的名字
		if (mode == PP)
		{
			system("cls");
			std::cout << "请为两个棋手命名" << std::endl;
			std::cout << "黑棋: ";
			std::string name;
			std::cin >> name;
			black.getColor() = BLACK;
			black.getName() = name;

			std::cout << "白棋: ";
			std::cin >> name;
			white.getColor() = WHITE;
			white.getName() = name;
			WhoIsFirst = -1;
			system("cls");



		}
		//03 如果是人机，需要设定好谁先谁后
		else if (mode == PE)
		{
			system("cls");
			std::cout << "您想执黑棋还是白棋:" << std::endl;
			std::cout << "【0】黑棋" << std::endl;
			std::cout << "【1】白棋" << std::endl;
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
					std::cout << "请重新选择先后顺序:" << std::endl;
					std::cout << "【0】黑棋" << std::endl;
					std::cout << "【1】白棋" << std::endl;
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

		std::cout << "游戏开始！" << std::endl;
		std::cout << "黑方: " << black.getName() << std::endl;
		std::cout << "白方: " << white.getName() << std::endl;
	}

	//人人对战的回调函数
	void game::PPMouseCallBack(int event, int x, int y, int flags, void* param)

	{


		if (x >= 30 && x <= 670 && y >= 30 && y <= 670)//输入在正常范围内才处理
		{
			switch (event)
			{
			case(cv::EVENT_LBUTTONDOWN): //如果是鼠标左键按下的事件
			{

				if (ok == GOON)//判断游戏是否结束了
				{
					if (j.nextChesser() == 0)//如果下一步该黑棋走了
					{
						Calibration(x, y); //校正输入点坐标
						cv::Point p = myChess::ReMap(x, y).pt();//转换为绘图区的点
						if (cp.addChess(black.getNextChess(cp, p.x, p.y)))//如果能够正常加入棋盘
						{
							circle(rd.pad, cv::Point(x, y), 10, cv::Scalar(0, 0, 0), -1);//画上
						}
						else
						{
							j.getCurrentChesser() = 1;//如果没成功，下一手期还是黑棋
						}
					}


					else //如果该白棋下了
					{
						Calibration(x, y);
						cv::Point p = myChess::ReMap(x, y).pt();

						if (cp.addChess(white.getNextChess(cp, p.x, p.y)))
						{
							circle(rd.pad, cv::Point(x, y), 10, cv::Scalar(255, 255, 255), -1);
						}
						else
						{
							j.getCurrentChesser() = 0;//如果没成功，下一手还是白棋
						}




					}
				}
			}

			case(CV_EVENT_RBUTTONUP):
			{
				system("cls");
				std::cout << "当前形势:" << std::endl;
				std::cout << cp << std::endl;
				int y = cp.getLastRow();
				int x = cp.getLastCol();
				if (cp.getLastColor() == BLACK)
				{
					std::cout << "黑棋手" << black.getName() << "下在了" << "(" << x << "," << y << ")" << std::endl;
				}
				if (cp.getLastColor() == WHITE)
				{
					std::cout << "白棋手" << white.getName() << "下在了" << "(" << x << "," << y << ")" << std::endl;
				}
				int rst = j.JudgeResult(cp);

				if (rst == 1)
				{
					std::cout << "黑胜" << std::endl;
					ok = OVER;
				}
				else if (rst == 2)
				{
					std::cout << "白胜" << std::endl;
					ok = OVER;
				}
				else if (rst == 3)
				{
					std::cout << "和棋" << std::endl;
					ok = OVER;
				}
			}
			}

		}


	}

	//人机的回调函数
	void game::PEMouseCallBack(int event, int x, int y, int flags, void* param)

	{


		if (x >= 30 && x <= 670 && y >= 30 && y <= 670)//输入在正常范围内才处理
		{
			switch (event)
			{
			case(cv::EVENT_LBUTTONDOWN): //如果是鼠标左键按下的事件
			{
				if (ok == GOON) //如果游戏继续
				{

					if (WhoIsFirst == PeopleFirst && j.nextChesser() == 0)//如果下一步该黑棋走了
					{
						Calibration(x, y); //校正输入点坐标
						cv::Point p = myChess::ReMap(x, y).pt();//转换为绘图区的点
						if (cp.addChess(black.getNextChess(cp, p.x, p.y)))//如果能够正常加入棋盘
						{
							circle(rd.pad, cv::Point(x, y), 10, cv::Scalar(0, 0, 0), -1);//画上
							PEok = true;
						}
						else
						{
							PEok = false;
						}
						
					}

					if (WhoIsFirst == ComputerFirst && j.nextChesser() == 1)//如果下一步该白棋走了
					{
						Calibration(x, y); //校正输入点坐标
						cv::Point p = myChess::ReMap(x, y).pt();//转换为绘图区的点
						if (cp.addChess(white.getNextChess(cp, p.x, p.y)))//如果能够正常加入棋盘
						{
							circle(rd.pad, cv::Point(x, y), 10, cv::Scalar(255, 255, 255), -1);//画上
							PEok = true;
						}
						else
						{
							PEok = false;
						}
						
					}

					//输出当前局势和上一步的棋子在哪
					system("cls");
					
					int y = cp.getLastRow();
					int x = cp.getLastCol();
					if (cp.getLastColor() == BLACK)
					{
						std::cout << "黑棋手" << black.getName() << "下在了" << "(" << x << "," << y << ")" << std::endl;
					}
					if (cp.getLastColor() == WHITE)
					{
						std::cout << "白棋手" << white.getName() << "下在了" << "(" << x << "," << y << ")" << std::endl;
					}
					
					//判断结果
					int rst = j.JudgeResult(cp);

					if (rst == 1)
					{
						std::cout << "黑胜" << std::endl;
						ok = OVER;
					}
					else if (rst == 2)
					{
						std::cout << "白胜" << std::endl;
						ok = OVER;
					}
					else if (rst == 3)
					{
						std::cout << "和棋" << std::endl;
						ok = OVER;
					}



				}

			case(CV_EVENT_RBUTTONUP):
			{
				if (ok == GOON) //如果游戏继续
				{

					if (WhoIsFirst == ComputerFirst && j.nextChesser() == 0&&PEok)//如果下一步该黑棋走了
					{
						cv::Point dataP = ai.getPosition(cp, black.getColor());
						if (cp.addChess(black.getNextChess(cp, dataP.x, dataP.y)))
						{
							cv::circle(rd.pad, Map(dataP.x, dataP.y).pt(), 10, cv::Scalar(0, 0, 0), -1);
						}
						
						
					}
					if (WhoIsFirst == PeopleFirst && j.nextChesser() == 1&& PEok)//如果下一步该白棋走了
					{
						cv::Point dataP = ai.getPosition(cp, white.getColor());
						if (cp.addChess(white.getNextChess(cp, dataP.x, dataP.y)))
						{
							cv::circle(rd.pad, Map(dataP.x, dataP.y).pt(), 10, cv::Scalar(255, 255, 255), -1);
						}
						
					}

					//输出当前局势和上一步的棋子在哪
					
					
					int y = cp.getLastRow();
					int x = cp.getLastCol();
					if (cp.getLastColor() == BLACK)
					{
						std::cout << "黑棋手" << black.getName() << "下在了" << "(" << x << "," << y << ")" << std::endl;
					}
					if (cp.getLastColor() == WHITE)
					{
						std::cout << "白棋手" << white.getName() << "下在了" << "(" << x << "," << y << ")" << std::endl;
					}
					std::cout << "当前形势:" << std::endl;
					std::cout << cp << std::endl;
					//输出结果
					int rst = j.JudgeResult(cp);
					if (rst == 1)
					{
						std::cout << "黑胜" << std::endl;
						ok = OVER;
					}
					else if (rst == 2)
					{
						std::cout << "白胜" << std::endl;
						ok = OVER;
					}
					else if (rst == 3)
					{
						std::cout << "和棋" << std::endl;
						ok = OVER;
					}

				}



			}


			
			}

			}


		}
	}

	//机机对战回调函数
	void game::EEMouseCallBack(int event, int x, int y, int flags, void* param)
	{
		switch (event)
		{
		case(cv::EVENT_LBUTTONDOWN): //如果是鼠标左键按下的事件
		{
			if (ok == GOON) //如果游戏继续
			{

				
					cv::Point dataP = ai.getPosition(cp, black.getColor());
					if (cp.addChess(black.getNextChess(cp, dataP.x, dataP.y)))
					{
						cv::circle(rd.pad, Map(dataP.x, dataP.y).pt(), 10, cv::Scalar(0, 0, 0), -1);
					}


				



				//输出当前局势和上一步的棋子在哪
				system("cls");

				int y = cp.getLastRow();
				int x = cp.getLastCol();
				
				std::cout << "黑棋手" << black.getName() << "下在了" << "(" << x << "," << y << ")" << std::endl;
				

				//判断结果
				int rst = j.JudgeResult(cp);

				if (rst == 1)
				{
					std::cout << "黑胜" << std::endl;
					ok = OVER;
				}
				else if (rst == 2)
				{
					std::cout << "白胜" << std::endl;
					ok = OVER;
				}
				else if (rst == 3)
				{
					std::cout << "和棋" << std::endl;
					ok = OVER;
				}



			}
		}

		case(CV_EVENT_RBUTTONUP):
		{
			if (ok == GOON) //如果游戏继续
			{

				cv::Point dataP = ai.getPosition(cp, white.getColor());
				if (cp.addChess(white.getNextChess(cp, dataP.x, dataP.y)))
				{
					cv::circle(rd.pad, Map(dataP.x, dataP.y).pt(), 10, cv::Scalar(255, 255, 255), -1);
				}


				//输出当前局势和上一步的棋子在哪


				int y = cp.getLastRow();
				int x = cp.getLastCol();
				
				
				std::cout << "白棋手" << white.getName() << "下在了" << "(" << x << "," << y << ")" << std::endl;
				
				std::cout << "当前形势:" << std::endl;
				std::cout << cp << std::endl;
				//输出结果
				int rst = j.JudgeResult(cp);
				if (rst == 1)
				{
					std::cout << "黑胜" << std::endl;
					ok = OVER;
				}
				else if (rst == 2)
				{
					std::cout << "白胜" << std::endl;
					ok = OVER;
				}
				else if (rst == 3)
				{
					std::cout << "和棋" << std::endl;
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
		cv::setMouseCallback("m", myChess::game::PPMouseCallBack, (void*)(0)); //鼠标函数
		cv::imshow("m", rd.pad);
		while (1)
		{
			cv::imshow("m", rd.pad);

			if (cv::waitKey(10) == 27)break;//按ESC键退出
		}

		cv::waitKey(0);
		}

		if (mode == PE)
		{
			if (getWhoIsFirst() == ComputerFirst && j.nextChesser() == 0)//如果下一步该黑棋走了
			{
				cv::Point dataP = ai.getPosition(cp, black.getColor());
				cp.addChess(black.getNextChess(cp, dataP.x, dataP.y));
				cv::circle(rd.pad, myChess::Map(dataP.x, dataP.y).pt(), 10, cv::Scalar(0, 0, 0), -1);
			}
			cv::setMouseCallback("m", myChess::game::PEMouseCallBack, (void*)(0)); //鼠标函数
			cv::imshow("m", rd.pad);
			while (1)
			{
				cv::imshow("m", rd.pad);

				if (cv::waitKey(10) == 27)break;//按ESC键退出
			}

			cv::waitKey(0);
		}

		if (mode == EE)
		{

			cv::setMouseCallback("m", myChess::game::EEMouseCallBack, (void*)(0)); //鼠标函数
			cv::imshow("m", rd.pad);
			while (1)
			{
				cv::imshow("m", rd.pad);

				if (cv::waitKey(10) == 27)break;//按ESC键退出
			}

			cv::waitKey(0);
		}
		
	}
}
