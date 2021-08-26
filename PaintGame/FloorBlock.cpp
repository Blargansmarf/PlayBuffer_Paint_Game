#include "FloorBlock.h"

FloorBlock::FloorBlock()
{
	
}

FloorBlock::~FloorBlock()
{

}

float FloorBlock::getX()
{
	return pos.x;
}

float FloorBlock::getY()
{
	return pos.y;
}

void FloorBlock::setX(float x)
{
	pos.x = x;
}

void FloorBlock::setY(float y)
{
	pos.y = y;
}

void FloorBlock::setPos(Point2D p)
{
	pos = p;
}

Point2D FloorBlock::getPos()
{
	return pos;
}

void FloorBlock::setSpriteID(int i)
{
	spriteID = i;
}

int FloorBlock::getSpriteID()
{
	return spriteID;
}