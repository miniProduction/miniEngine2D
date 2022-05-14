#pragma once
void showWindow();

struct MiniColor
{
	char b, g, r, a;
};


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

extern MiniColor BUFFER[SCREEN_HEIGHT* SCREEN_WIDTH];

struct MiniImage
{
	int height, width;
	MiniColor* _data;
};

void update();

void putBufferToScreen();

void clearScreen();