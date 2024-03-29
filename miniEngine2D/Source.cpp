/*
//该文件用于测试MiniEngine

*/
#include "MiniEngine2D.h"
#include"util.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>
using namespace std;

int main()
{
	system("chcp");
	cout << u8"中文测试" << endl;
	cout << "中文测试" << endl;
	wcout << L"中文测试" << endl;

	MiniEngine2D m;
	MiniEngine2D::log("%d", 1234);
	m.log("中文测试:%d %c %.2f", 123, 'c', 2.5);
	m.log(L"中文测试:%d %c %.2f", 123, 'c', 2.5);
	m.log(1234);
	m.log(12.34f);
	m.log(56.78);
	m.logDetail("中文测试:%d %c %.2f", 123, 'c', 2.5);
	m.logDetail(L"中文测试:%d %c %.2f", 123, 'c', 2.5);

	//MACRO_Log(TEXT("中文测试: %d %c %.2f"), 123, 'c', 2.5);
	//MACRO_LogA("中文测试: %d %c %.2f", 123, 'c', 2.5);
	//MACRO_LogW(L"中文测试: %d %c %.2f", 123, 'c', 2.5);
	
	m.addEventHook([](EventType eventType, int keyCode, int x, int y) {
		MiniEngine2D::log("Mouse: EventType %d KeyCode %d (%d,%d)",eventType, keyCode,x,y);
		//throw std::exception("I am SORRY!");
	});
	m.addEventHook([](EventType eventType, int keyCode){
		MiniEngine2D::log("Keyboard: EventType %d KeyCode %d", eventType, keyCode);
		//while (1);
	});
	//取消注册事件
	//m.addEventHook((PFuncKeyboardEvent)NULL);

	m.log("miniColorSize %d\n", sizeof(MiniColor));

	m.showWindow();

	bool isGameOver = false;

	MiniColor black, MIZUASAGI;
	black.r = 0; black.g = 0; black.b = 0; black.a = 255;
	MIZUASAGI.r = 102; MIZUASAGI.g = 186; MIZUASAGI.b = 183; MIZUASAGI.a = 255;

	MiniImage image;
	image.makeRectImage(300, 300, MIZUASAGI);

	MiniImage image1;
	image1.load("raw.jpg");

	m.setFont("微软雅黑", 50);
	m.update();

	MiniImage WordImage= m.makeFontToMiniImage("miniEngine2D", 50);

	double nowPosX = 0, nowPosY = 400;
	int fx = 1;

	while (!isGameOver) {
		m.clearScreen();

		//测试基础的绘制图像函数
		m.drawPoint(50, 50, black);
		m.drawLine(0, 0, 100, 300, MIZUASAGI);
		m.drawRect(1000, 500, 100, 100, black);
		m.drawCircle(500, 500, 50, black);
		m.drawImage(nowPosX, nowPosY, image);
		m.drawImage(nowPosX, nowPosY, WordImage);
		m.drawImage(nowPosX+300, nowPosY - 300, image1);
		nowPosX += fx*0.5;
		if (nowPosX > SCREEN_WIDTH - image.width) {
			fx *= -1;
			nowPosX = SCREEN_WIDTH - image.width;
		}
		if (nowPosX < 0) {
			fx *= -1;
			nowPosX = 0; 0x5a;
		}
		/*if (m.isKeyDown(KeyCode::MouseLeft)) {
			auto pos = m.getMousePosition();
			m.log("Left mouse down (%d,%d)", pos.first, pos.second);
		}
		if (m.isKeyUp(KeyCode::MouseRight)) {
			auto pos = m.getMousePosition();
			m.log("Right mouse up (%d,%d)", pos.first, pos.second);
		}
		if (m.isKeyUp(KeyCode::A)) {
			m.log("A up");
		}
		if (m.isKeyDown(KeyCode::A)) {
			m.log("A down");
		}*/
		m.update();
	}

	system("pause");
	return 0;
}