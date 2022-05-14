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

	MiniEngine2D miniEngine;
	MiniEngine2D::log("中文测试:%d %c %.2f", 123, 'c', 2.5);
	miniEngine.log(L"中文测试:%d %c %.2f", 123, 'c', 2.5);

	MACRO_Log(TEXT("中文测试: %d %c %.2f"), 123, 'c', 2.5);
	MACRO_LogA("中文测试: %d %c %.2f", 123, 'c', 2.5);
	MACRO_LogW(L"中文测试: %d %c %.2f", 123, 'c', 2.5);

	miniEngine.showWindow();

	system("pause");
	return 0;
}