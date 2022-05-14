/*
//该文件用于测试MiniEngine

*/
#include "MiniEngine2D.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>
using namespace std;

int main()
{
	//system("chcp");
	//system("chcp 65001 ");
	system("chcp 437 ");
	//system("chcp 936");
	cout << u8"中文测试" << endl;
	cout << "中文测试" << endl;
	wcout << L"中文测试" << endl;

	MiniEngine2D m;
	MiniEngine2D::log("中文测试:%d %c %.2f", 123, 'c', 2.5);
	m.log(L"中文测试:%d %c %.2f", 123, 'c', 2.5);

	MACRO_Log(TEXT("中文测试: %d %c %.2f"), 123, 'c', 2.5);
	MACRO_LogA("中文测试: %d %c %.2f", 123, 'c', 2.5);
	MACRO_LogW(L"中文测试: %d %c %.2f", 123, 'c', 2.5);

	m.showWindow();

	bool isGameOver = false;

	MiniColor black, MIZUASAGI;
	black.r = 0; black.g = 0; black.b = 0;
	MIZUASAGI.r = 102; MIZUASAGI.g = 186; MIZUASAGI.b = 183;

	while (!isGameOver) {
		m.clearScreen();

		//测试基础的绘制图像函数
		m.drawPoint(50, 50, black);
		m.drawLine(0, 0, 100, 300, black);
		m.drawRect(1000, 500, 100, 100, black);
		m.drawCircle(500, 500, 50, black);

		m.update();
	}

	system("pause");
	return 0;
}