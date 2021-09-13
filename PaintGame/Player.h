class Player
{
public:
	Player();
	Player(float w, float h);
	~Player();

	void setDim(float w, float h);
	void setPos(float x, float y);
	void setPosX(float x);
	void setPosY(float y);
	void setVel(float x, float y);
	void setVelX(float x);
	void setVelY(float y);
	void setAccel(float a);
	void setSpriteID(int id);
	void setSlideResist(float s);
	void jump();
	void endJump();
	void slide();
	void endSlide();
	void setBlockFace(int x);
	
	int getSpriteID();
	int getBlockFace();
	float getX();
	float getY();
	float getVelX();
	float getVelY();
	float getAccel();
	float getW();
	float getH();
	float getSlideResist();
	bool isJumped();
	bool isSliding();
		
private:
	float xPos, yPos;
	float xVel, yVel;
	float acceleration;
	float width, height;
	float slideResist;
	bool jumped;
	bool wallJumped;
	bool sliding;
	int spriteID;
	int blockFace;
};