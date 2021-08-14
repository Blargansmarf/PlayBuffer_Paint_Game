#include "Player.h"

Player::Player()
{
	Player::xPos = 0.0f;
	Player::yPos = 0.0f;
	Player::xVel = 0.0f;
	Player::yVel = 0.0f;
	Player::acceleration = 0.0f;
	Player::width = 10.0f;
	Player::height = 10.0f;
	Player::jumped = false;
}

Player::Player(float w, float h)
{
	Player::xPos = 0.0f;
	Player::yPos = 0.0f;
	Player::xVel = 0.0f;
	Player::yVel = 0.0f;
	Player::acceleration = 0.0f;
	Player::width = w;
	Player::height = h;
	Player::jumped = false;
}

Player::~Player()
{

}

void Player::setDim(float w, float h)
{
	Player::width = w;
	Player::height = h;
}

void Player::setPos(float x, float y)
{
	Player::xPos = x;
	Player::yPos = y;
}

void Player::setVel(float x, float y)
{
	Player::xVel = x;
	Player::yVel = y;
}

void Player::setAccel(float a)
{
	Player::acceleration = a;
}

float Player::getX()
{
	return Player::xPos;
}

float Player::getY()
{
	return Player::yPos;
}

float Player::getVelX()
{
	return Player::xVel;
}

float Player::getVelY()
{
	return Player::yVel;
}

float Player::getAccel()
{
	return Player::acceleration;
}

float Player::getW()
{
	return Player::width;
}

float Player::getH()
{
	return Player::height;
}