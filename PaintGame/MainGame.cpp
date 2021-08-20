#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Player.h"
#include "FloorBlock.h"

const int DISPLAY_WIDTH = 1280;
const int DISPLAY_HEIGHT = 720;
const int DISPLAY_SCALE = 1;

Player player;
Point2D playerPos(0, 0);

const float gravity = .1f;
const float friction = .2f;
const float sprintBonus = 5.0f;
const float maxVelX = 9.0f;
const float maxVelY = 11.0f;

void ApplyPhysics();
void CheckBounds();

// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );

	player.setAccel(.5f);
	player.setPos(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2);
	player.setSpriteID(0);
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	Play::ClearDrawingBuffer( Play::cGrey );
	
	ApplyPhysics();
	CheckBounds();
	playerPos.x = player.getX();
	playerPos.y = player.getY();
	Play::DrawSprite(player.getSpriteID(), playerPos, 0);

	Play::PresentDrawingBuffer();
	return Play::KeyDown( VK_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}

void ApplyPhysics()
{
	player.setVelY(player.getVelY() + gravity);
	if (player.getVelX() > 0)
	{
		if (player.getVelX() > friction)
		{
			player.setVelX(player.getVelX() - friction);
		}
		else
		{
			player.setVelX(0.0f);
		}
	}
	else if (player.getVelX() < 0)
	{
		if (player.getVelX() < -friction)
		{
			player.setVelX(player.getVelX() + friction);
		}
		else
		{
			player.setVelX(0.0f);
		}
	}

	if (Play::KeyDown(VK_LSHIFT))
	{
		if (Play::KeyDown(VK_RIGHT))
		{
			player.setVelX(player.getVelX() + player.getAccel()*1.5f);
			if (player.getVelX() > maxVelX + sprintBonus)
			{
				player.setVelX(maxVelX + sprintBonus);
			}
		}
		else if (Play::KeyDown(VK_LEFT))
		{
			player.setVelX(player.getVelX() - player.getAccel()*1.5f);
			if (player.getVelX() < -maxVelX - sprintBonus)
			{
				player.setVelX(-maxVelX - sprintBonus);
			}
		}
	}
	else
	{
		if (Play::KeyDown(VK_RIGHT))
		{
			player.setVelX(player.getVelX() + player.getAccel());
			if (player.getVelX() > maxVelX)
			{
				player.setVelX(maxVelX);
			}
		}
		else if(Play::KeyDown(VK_LEFT))
		{
			player.setVelX(player.getVelX() - player.getAccel());
			if (player.getVelX() < -maxVelX)
			{
				player.setVelX(-maxVelX);
			}
		}
	}
	

	player.setPos(player.getX() + player.getVelX(), player.getY() + player.getVelY());
}

void CheckBounds()
{
	if (player.getY() > (DISPLAY_HEIGHT * .666f))
	{
		player.setPosY(DISPLAY_HEIGHT * .666f);
	}
}