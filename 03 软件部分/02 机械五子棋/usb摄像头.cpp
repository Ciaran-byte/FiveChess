//#include<iostream>
//#include<opencv2/opencv.hpp>
//
//using namespace std;
//using namespace cv;
//
//int main()
//{
//    VideoCapture capture;
//    capture.open(0);           //open the default camera -1才是默认摄像机，3是我的USBCaemra的
//    if (capture.isOpened())
//    {
//
//       cout << "camera open!!!";
//    }
//    Mat edges;
//   
//    while (1)
//    {
//    string str = ".jpg";
//   while(1)
//    {
//
//    
//        Mat frame; //定义一个Mat变量，用于存储每一帧的图像
//        capture >> frame; //读取当前帧
//        if (frame.empty()) //判断当前帧是否捕捉成功 **这步很重要
//        {
//            cout << "can't get picture" << endl;
//        }
//       
//        
//        imshow("b", frame);
//        
//        waitKey(30); //延时30毫秒
//    }
//    }
//        
//       
//  
//      
//
//    
//
//
//}
