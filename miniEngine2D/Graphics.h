#pragma once
void showWindow();

struct Color
{
	char r, g, b, a;
};


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

Color BUFFER[SCREEN_HEIGHT* SCREEN_WIDTH];


