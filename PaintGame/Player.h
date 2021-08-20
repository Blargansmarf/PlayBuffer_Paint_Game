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
	void jump();
	void endJump();
	
	int getSpriteID();
	float getX();
	float getY();
	float getVelX();
	float getVelY();
	float getAccel();
	float getW();
	float getH();
	bool isJumped();
		
private:
	float xPos, yPos;
	float xVel, yVel;
	float acceleration;
	float width, height;
	bool jumped;
	int spriteID;
};