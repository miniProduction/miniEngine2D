#pragma once

// 项目GitHub地址  https://github.com/miniProduction/miniEngine2D
// 函数命名文档    https://github.com/miniProduction/miniEngine2D/wiki/MiniEngine-%E5%91%BD%E5%90%8D%E5%8F%8A%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84
//
//
//

#include <string>


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

struct MiniColor
{
	//a 通道 0是透明 255是不透明
	unsigned char b, g, r, a;
	MiniColor(int R, int G, int B, int A) :b(B), g(G), r(R), a(A) {};
	MiniColor(int R, int G, int B) :b(B), g(G), r(R), a(255) {};
	MiniColor() :b(0), g(0), r(0), a(255) {};

};

struct MiniImage
{
	int height, width;
	MiniColor* _data;
	MiniImage() :height(0), width(0), _data(nullptr) {};
	bool load(const char* filepath);
	bool makeRectImage(int width, int height, const MiniColor& color);
	MiniImage(const MiniImage& mImg)
	{
		height = mImg.height;
		width = mImg.width;
		_data = new MiniColor[height * width];
		for (int i = 0; i < height*width; i++)
		{
			_data[i] = mImg._data[i];
		}
	}
	~MiniImage() {
		if (_data != nullptr) {
			delete[]_data;
		}
	}

};

/// <summary>
/// 发生鼠标键盘事件时的事件类型
/// </summary>
enum EventType {
	/// <summary>
	/// KeyCode 对应的键被按下
	/// </summary>
	KeyDown,

	/// <summary>
	/// KeyCode 对应的键被抬起
	/// </summary>
	KeyUp
};

/// <summary>
/// 用于处理鼠标事件的函数类型
/// </summary>
/// <param name="eventType">发生事件的类型，有按下(EventType::KeyDown)和抬起(EventType::KeyUp)两种</param>
/// <param name="keyCode">发生事件的具体键。
/// VK_LBUTTON 0x01 //鼠标左键
/// VK_RBUTTON 0x02 //鼠标右键
/// VK_MBUTTON 0x04 //鼠标中键
/// </param>
/// <param name="x">发生事件所在客户区域的横坐标</param>
/// <param name="y">发生事件所在客户区域的纵坐标</param>
/// <returns></returns>
using PFuncMouseEvent = void(__cdecl *)(EventType eventType, int keyCode, int x, int y);

/// <summary>
/// 用于处理键盘事件的函数类型
/// </summary>
/// <param name="eventType">发生事件的类型，有按下(EventType::KeyDown)和抬起(EventType::KeyUp)两种</param>
/// <param name="keyCode">发生事件的具体键。与WinUser.h 中Virtual Keys, Standard Set定义一致</param>
/// <returns></returns>
using PFuncKeyboardEvent = void(__cdecl *)(EventType eventType, int keyCode);

enum KeyCode {
	MouseLeft = 1,
	MouseRight,

	//3 保留

	MouseMiddle = 4,

	//5,6,7保留

	Back = 0x08,
	Tab,

	//10,11保留

	Clear = 0x0C,
	Return,

	//0x0E - 0x0F : unassigned

	Shift = 0x10,
	Control,
	KC_Escape = 0x1B,
	Space = 0x20,
	Left = 0x25,
	Up,
	Right,
	Down,
	Select,
	Print,
	Execute,
	Snapshot,
	Insert,
	Delete,
	Help,
	_0,
	_1,
	_2,
	_3,
	_4,
	_5,
	_6,
	_7,
	_8,
	_9,

	//0x3A - 0x40 : unassigned

	A = 0x41,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	LeftWin,
	RightWin,
	APPs,
	KC_Sleep = 0x5F,
	NumPad0,
	NumPad1,
	NumPad2,
	NumPad3,
	NumPad4,
	NumPad5,
	NumPad6,
	NumPad7,
	NumPad8,
	NumPad9,
	Multiply,
	Add,
	Separator,
	Subtract,
	Decimal,
	Divide,
	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	F11,
	F12,
	F13,
	F14,
	F15,
	F16,
	F17,
	F18,
	F19,
	F20,
	F21,
	F22,
	F23,
	F24,
	NumLock = 0x90,
	Scroll
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
	void drawImage( int x, int y, const MiniImage&);
	void setFont(const std::string& fontName, int size);
	void setTitle(const char* title);


	MiniImage makeFontToMiniImage(std::string str, int size);
	
	/// <summary>
	/// 给MiniEngine添加一个用于处理鼠标事件的函数，在发生鼠标事件时，
	/// MiniEngine内部会先处理保留事件，处理完成之后会调用pfunc
	/// </summary>
	/// <param name="pfunc">处理函数</param>
	void addEventHook(PFuncMouseEvent pfunc);

	/// <summary>
	/// 给MiniEngine添加一个用于处理键盘事件的函数，在发生键盘事件时，
	/// MiniEngine内部会先处理保留事件，处理完成之后会调用pfunc
	/// </summary>
	/// <param name="pfunc">处理函数</param>
	void addEventHook(PFuncKeyboardEvent pfunc);

	/// <summary>
	/// 检测keyCode是否按下
	/// </summary>
	/// <param name="keyCode">
	/// 发生事件的具体键,与WinUser.h 中Virtual Keys, Standard Set定义一致,补充鼠标键定义如下:
	/// VK_LBUTTON 0x01 //鼠标左键 
	/// VK_RBUTTON 0x02 //鼠标右键 
	/// VK_MBUTTON 0x04 //鼠标中键 
	/// </param>
	/// <returns>
	/// true keyCode按下
	/// false keyCode未按下
	/// </returns>
	bool isKeyDown(int keyCode);

	/// <summary>
	/// 检测keyCode是否抬起
	/// </summary>
	/// <param name="keyCode">与isKeyDown定义一致不再赘述</param>
	/// <returns>
	/// true keyCode抬起
	/// false keyCode未抬起
	/// </returns>
	bool isKeyUp(int keyCode);

	/// <summary>
	/// 获取鼠标当前点击事件发生时的位置，只有当isKeyDown(VK_*BUTTON)为真时才有效
	/// </summary>
	/// <returns>返回一个(x,y)数对</returns>
	std::pair<int, int> getMousePosition();

	static int __cdecl log(char const* const _Format, ...);
	static int __cdecl log(wchar_t const* const _Format, ...);
	static int __cdecl log(int obj);
	static int __cdecl log(unsigned long obj);
	static int __cdecl log(float obj);
	static int __cdecl log(double obj);
	static int __cdecl logDetail(char const* const _Format, ...);
	static int __cdecl logDetail(wchar_t const* const _Format, ...);
	static void exportLogToFile(const std::string logFilePath);

};

#include "Trace.h"
#include "Graphics.h"


