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
FloorBlock levelBlocks[10];

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
void InitPlayer();
void TranslateLevel();

// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );

	CreateLevel();
	InitPlayer();
}

void InitPlayer()
{
	player.setAccel(acceleration);
	player.setPos(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2);
	player.setVel(0.0f, 0.0f);
	player.setSpriteID(0);
	player.jump();
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	Play::ClearDrawingBuffer( Play::cGrey );
	
	if (Play::KeyDown(0x52) || player.getY() > DISPLAY_HEIGHT)
	{
		CreateLevel();
		InitPlayer();
	}

	ApplyPhysics();
	CheckBounds();
	TranslateLevel();

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

	if (player.getVelY() > 1.0f)
	{
		player.jump();
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
	
	
	//player.setPos(player.getX() + player.getVelX(), player.getY() + player.getVelY());
	player.setPosY(player.getY() + player.getVelY());
}

void TranslateLevel()
{
	//Point2D p = { 0.0f,0.0f };
	for (int x = 0; x < sizeof(levelBlocks) / sizeof(levelBlocks[0]); x++)
	{
		//p.x = levelBlocks[x].getX() - player.getVelX();
		//p.y = levelBlocks[x].getY() - player.getVelY();
		levelBlocks[x].setX(levelBlocks[x].getX() - player.getVelX());
	}
}

void CheckBounds()
{
	for (int x = 0; x < sizeof(levelBlocks) / sizeof(levelBlocks[0]); x++)
	{
		if (//bottom of player
			player.getY() + Play::GetSpriteHeight(player.getSpriteID()) > levelBlocks[x].getY() &&
			//top of player
			player.getY() < levelBlocks[x].getY() + Play::GetSpriteHeight(levelBlocks[x].getSpriteID()) &&
			//right of player
			player.getX() + Play::GetSpriteWidth(player.getSpriteID()) > levelBlocks[x].getX() &&
			//left of player
			player.getX() < levelBlocks[x].getX() + Play::GetSpriteWidth(levelBlocks[x].getSpriteID()))
		{
			player.setPosY(levelBlocks[x].getY() - Play::GetSpriteHeight(player.getSpriteID()));
			player.endJump();
		}
	}
}

void CreateLevel()
{

	for (int x = 0; x < sizeof(levelBlocks) / sizeof(levelBlocks[0]); x++)
	{
		levelBlocks[x].setSpriteID(1);
		levelBlocks[x].setX((DISPLAY_WIDTH * .333f + 75)*(x+1));
		if (x < 5)
		{
			levelBlocks[x].setY(DISPLAY_HEIGHT * .666f - (x * 25));
		}
		else
		{
			levelBlocks[x].setY(levelBlocks[x-1].getY() + ((x-5) * 25));
		}
	}
}

void CheckLevelCollision()
{

}