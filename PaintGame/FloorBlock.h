#include "Play.h"

class FloorBlock
{
public:
	FloorBlock();
	~FloorBlock();

	float getX();
	float getY();
	void setX(float x);
	void setY(float y);
	void setPos(Point2D p);
	Point2D getPos();
	void setSpriteID(int i);
	int getSpriteID();

private:
	int spriteID;
	Point2D pos;
};