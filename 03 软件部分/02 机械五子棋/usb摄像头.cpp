//#include<iostream>
//#include<opencv2/opencv.hpp>
//
//using namespace std;
//using namespace cv;
//
//int main()
//{
//    VideoCapture capture;
//    capture.open(0);           //open the default camera -1����Ĭ���������3���ҵ�USBCaemra��
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
//        Mat frame; //����һ��Mat���������ڴ洢ÿһ֡��ͼ��
//        capture >> frame; //��ȡ��ǰ֡
//        if (frame.empty()) //�жϵ�ǰ֡�Ƿ�׽�ɹ� **�ⲽ����Ҫ
//        {
//            cout << "can't get picture" << endl;
//        }
//       
//        
//        imshow("b", frame);
//        
//        waitKey(30); //��ʱ30����
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
