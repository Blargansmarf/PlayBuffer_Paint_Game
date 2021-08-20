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

void FloorBlock::setX(float x)
{
	xPos = x;
}

void FloorBlock::setY(float y)
{
	yPos = y;
}

float FloorBlock::getW()
{
	return FloorBlock::width;
}

float FloorBlock::getH()
{
	return FloorBlock::height;
}