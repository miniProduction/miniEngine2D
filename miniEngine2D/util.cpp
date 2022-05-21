#include"util.h"

MiniImage makeRectImage(int width, int height, const MiniColor& color)
{
	MiniImage ret;


	ret.width = width;
	ret.height = height;
	ret._data = (MiniColor*)malloc(sizeof(MiniColor) * width * height);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			ret._data[i * width + j] = color;
		}
	}
	return ret;


}