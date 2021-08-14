class FloorBlock
{
public:
	FloorBlock(float x, float y, float w, float h);
	~FloorBlock();

	float getX();
	float getY();
	float getW();
	float getH();

private:
	float xPos, yPos;
	float width, height;
};