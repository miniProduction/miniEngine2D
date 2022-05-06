/*
//该文件用于测试MiniEngine

*/
#include "MiniEngine2D.h"
#include <iostream>
using namespace std;

int main()
{
	cout << "Hello World!" << endl;
	MiniEngine2D miniEngine;
	miniEngine.log("中文测试:%d %c %.2f", 123, 'c', 2.5);
	return 0;
}