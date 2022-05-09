/*
//该文件用于测试MiniEngine

*/
#include "MiniEngine2D.h"
#include <iostream>
using namespace std;

int main()
{
	system("chcp 65001 ");
	cout << "Hello World!" << endl;
	cout << "中文测试" << endl;
	cout << u8"中文测试" << endl;

	MiniEngine2D miniEngine;
	miniEngine.log(u8"中文测试:%d %c %.2f", 123, 'c', 2.5);
	MACRO_Log("中文测试: %d %c %.2f", 123, 'c', 2.5);

	miniEngine.showWindow();

	//u8"中文测试:%d %c %.2f"u8"中文";

	return 0;
}