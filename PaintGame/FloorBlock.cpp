#include "FloorBlock.h"

FloorBlock::FloorBlock(float x, float y, float w, float h)
{
	FloorBlock::xPos = x;
	FloorBlock::yPos = y;
	FloorBlock::width = w;
	FloorBlock::height = h;
}

FloorBlock::~FloorBlock()
{

}

float FloorBlock::getX()
{
	return FloorBlock::xPos;
}

float FloorBlock::getY()
{
	return FloorBlock::yPos;
}

float FloorBlock::getW()
{
	return FloorBlock::width;
}

float FloorBlock::getH()
{
	return FloorBlock::height;
}