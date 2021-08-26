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
FloorBlock levelBlocks[1];

const float gravity = .6f;
const float friction = .25f;
const float acceleration = .7f;
const float sprintBonus = 5.0f;
const float maxVelX = 10.0f;
const float maxVelY = 11.0f;
const float jumpHeight = 15.0f;

void ApplyPhysics();
void CheckBounds();
void CreateLevel();
void CheckLevelCollision();

// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );

	CreateLevel();

	player.setAccel(acceleration);
	player.setPos(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2);
	player.setSpriteID(1);
	player.jump();
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
	for (int x = 0; x < sizeof(levelBlocks) / sizeof(levelBlocks[0]); x++)
	{
		Play::DrawSprite(levelBlocks[x].getSpriteID(), levelBlocks[x].getPos(), 0);
	}

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
	if (player.getVelY() > maxVelY)
	{
		player.setVelY(maxVelY);
	}

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

	if (Play::KeyPressed(VK_SPACE) && !player.isJumped())
	{
		player.setVelY(-jumpHeight);
		player.jump();
	}
	else if (!Play::KeyDown(VK_SPACE) && player.isJumped() && player.getVelY() < 0)
	{
		player.setVelY(0);
	}
	
	player.setPos(player.getX() + player.getVelX(), player.getY() + player.getVelY());
}

void CheckBounds()
{
	if (player.getY() > levelBlocks[0].getY() - Play::GetSpriteHeight(player.getSpriteID()) &&
		player.getX() + Play::GetSpriteWidth(player.getSpriteID()) > levelBlocks[0].getX() &&
		player.getX() < levelBlocks[0].getX() + Play::GetSpriteWidth(levelBlocks[0].getSpriteID()))
	{
		player.setPosY(levelBlocks[0].getY() - Play::GetSpriteHeight(player.getSpriteID()));
		player.endJump();
	}
}

void CreateLevel()
{
	levelBlocks[0].setSpriteID(0);
	levelBlocks[0].setX(DISPLAY_WIDTH * .333f);
	levelBlocks[0].setY(DISPLAY_HEIGHT * .666f);
}

void CheckLevelCollision()
{

}