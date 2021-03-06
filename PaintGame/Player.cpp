#include "Player.h"

Player::Player()
{
	xPos = 0.0f;
	yPos = 0.0f;
	xVel = 0.0f;
	yVel = 0.0f;
	acceleration = 0.0f;
	width = 0.0f;
	height = 0.0f;
	jumped = false;
	sliding = false;
	slideResist = 0.0f;
	blockFace = 0;
}

Player::~Player()
{

}

void Player::setSpriteID(int id)
{
	spriteID = id;
}

void Player::setDim(float w, float h)
{
	width = w;
	height = h;
}

void Player::setPos(float x, float y)
{
	xPos = x;
	yPos = y;
}

void Player::setPosX(float x)
{
	xPos = x;
}

void Player::setPosY(float y)
{
	yPos = y;
}

void Player::setVel(float x, float y)
{
	xVel = x;
	yVel = y;
}

void Player::setVelX(float x)
{
	xVel = x;
}

void Player::setVelY(float y)
{
	yVel = y;
}

void Player::setAccel(float a)
{
	acceleration = a;
}

float Player::getX()
{
	return xPos;
}

float Player::getY()
{
	return yPos;
}

float Player::getVelX()
{
	return xVel;
}

float Player::getVelY()
{
	return yVel;
}

float Player::getAccel()
{
	return acceleration;
}

float Player::getW()
{
	return width;
}

float Player::getH()
{
	return height;
}

int Player::getSpriteID()
{
	return spriteID;
}

void Player::jump()
{
	jumped = true;
}

void Player::endJump()
{
	jumped = false;
}

bool Player::isJumped()
{
	return jumped;
}

bool Player::isSliding()
{
	return sliding;
}

void Player::slide()
{
	sliding = true;
}

void Player::endSlide()
{
	sliding = false;
}

void Player::setSlideResist(float s)
{
	slideResist = s;
}

float Player::getSlideResist()
{
	return slideResist;
}

void Player::setBlockFace(int x)
{
	blockFace = x;
}

int Player::getBlockFace()
{
	return blockFace;
}