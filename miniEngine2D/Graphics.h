#pragma once
void showWindow();

struct Color
{
	char b, g, r, a;
};


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

extern Color BUFFER[SCREEN_HEIGHT* SCREEN_WIDTH];

void update();

void putBufferToScreen();

void clearScreen();