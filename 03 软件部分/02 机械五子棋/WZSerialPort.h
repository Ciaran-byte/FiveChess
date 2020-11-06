#pragma once
#ifndef _WZSERIALPORT_H
#define _WZSERIALPORT_H
#include<Windows.h>
#include<iostream>
#include<string>
using namespace std;
/*
	类名：WZSerialPort
	用途：串口读写
	示例：
		WZSerialPort w;
		if(w.open("COM1",9600，0，8，1))
		{
			w.send("helloworld");
			char buf[1024];
			w.receive(buf,1024);
		}
*/

/*windows端运行常见的问题
1. 在Windows上，要打开COM10以后的串口（包括COM10），串口名称不再是“COM10”，
而是“\\.\COM10”，因此在open函数中，如果是COM10及以后的串口，串口名（假设当前要打开COM10）
应该写“\\\\.\\COM10”，其中“\\\\.\\”为“\\.\”的转义。

2.	在visual studio的项目中，编译报错，错误指向WzSerialPort.cpp的157行、211行的问题：
157|    m_osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, L"WriteEvent");
211|    m_osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, L"ReadEvent");
   导致这个编译报错的其实是VS的字符集设置所导致的。
   ①将字符集改为“使用Unicode字符集”即可，
   ②或者将 L"WriteEvent" 和 L"ReadEvent" 前面的 L 删除掉也可以。 总而言之吧，这是微软的要求，
   字符集设置为 “使用Unicode字符集” 时需要加在字符串前加 L 先将 char* 转为 wchar_t* 再转为 LPCWSTR，
   字符集设置为 “使用多字节字符集” 时，则无需将 char* 转为 wchar_t* ，可直接转为LPCWSTR，因此无需加 L
3. 与opencv出现命名冲突的问题，opencv不要把命名空间开放
*/


class WZSerialPort
{
public:
	WZSerialPort(){}
	~WZSerialPort(){}

	// 打开串口,成功返回true，失败返回false
	// portname(串口名): 在Windows下是"COM1""COM2"等，在Linux下是"/dev/ttyS1"等
	// baudrate(波特率): 9600、19200、38400、43000、56000、57600、115200 
	// parity(校验位): 0为无校验，1为奇校验，2为偶校验，3为标记校验
	// databit(数据位): 4-8，通常为8位
	// stopbit(停止位): 1为1位停止位，2为2位停止位,3为1.5位停止位
	// synchronizable(同步、异步): 0为异步，1为同步
	bool open(const char* portname, int baudrate = 9600, char parity = 0, char databit = 8, char stopbit = 1, char synchronizeflag = 0);

	//关闭串口，参数待定
	void close();

	//发送数据或写数据，成功返回发送数据长度，失败返回0
	int send(string dat);

	//接受数据或读数据，成功返回读取实际数据的长度，失败返回0
	string receive();

private:
	int pHandle[16];
	char synchronizeflag;
};



#endif