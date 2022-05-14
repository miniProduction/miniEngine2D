#pragma once
#include "Trace.h"


class MiniEngine2D {
public:
	MiniEngine2D();
	~MiniEngine2D();
	void showWindow();

	void gameLoop();
	

	static int __cdecl log(char const* const _Format, ...);
	static int __cdecl log(wchar_t const* const _Format, ...);
private:


};