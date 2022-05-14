#pragma once

// 项目GitHub地址  https://github.com/miniProduction/miniEngine2D
// 函数命名文档    https://github.com/miniProduction/miniEngine2D/wiki/MiniEngine-%E5%91%BD%E5%90%8D%E5%8F%8A%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84
//
//
//

#include "Trace.h"

struct MiniColor
{
	char b, g, r, a;
};

struct MiniImage
{
	int height, width;
	MiniColor* _data;
};


class MiniEngine2D {
public:
	MiniEngine2D();
	~MiniEngine2D();

	void showWindow();
	void gameLoop();
	void update();
	void clearScreen();
	void drawPoint(int x, int y, const MiniColor&);
	void drawLine(int x0, int y0, int x1, int y1, const MiniColor&);
	void drawRect(int x, int y, int width, int height, const MiniColor&);
	void drawCircle(int x, int y, double r, const MiniColor&);
	

	static int __cdecl log(char const* const _Format, ...);
	static int __cdecl log(wchar_t const* const _Format, ...);
private:


};