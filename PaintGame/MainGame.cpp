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
const float wallJumpHeight = 9.0f;
const float wallJumpWidth = 6.0f;
const float slideResist = 6.0f;

void ApplyPhysics();
void CheckBounds();
void CreateLevel();
void CheckLevelCollision();
void InitPlayer();
void TranslateLevel();
void SetTop(int levelIndex);
void SetBot(int levelIndex);
void SetLeft(int levelIndex);
void SetRight(int levelIndex);

// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );

	Play::ColourSprite(Play::GetSpriteName(1), Play::cBlack);
	Play::ColourSprite(Play::GetSpriteName(2), Play::cBlack);
	Play::ColourSprite(Play::GetSpriteName(3), Play::cBlack);
	Play::ColourSprite(Play::GetSpriteName(4), Play::cBlack);

	CreateLevel();
	InitPlayer();
}

void InitPlayer()
{
	player.setAccel(acceleration);
	player.setPos(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2);
	player.setVel(0.0f, 0.0f);
	player.setSlideResist(slideResist);
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

	if (player.isSliding() && player.getVelY() > player.getSlideResist())
	{
		player.setVelY(player.getSlideResist());
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
			if (player.getBlockFace() == 2 && player.isSliding())
			{
				player.endSlide();
			}
			player.setVelX(player.getVelX() + player.getAccel()*1.5f);
			if (player.getVelX() > maxVelX + sprintBonus)
			{
				player.setVelX(maxVelX + sprintBonus);
			}
		}
		else if (Play::KeyDown(VK_LEFT))
		{
			if (player.getBlockFace() == 4 && player.isSliding())
			{
				player.endSlide();
			}
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
			if (player.getBlockFace() == 2 && player.isSliding())
			{
				player.endSlide();
			}
			player.setVelX(player.getVelX() + player.getAccel());
			if (player.getVelX() > maxVelX)
			{
				player.setVelX(maxVelX);
			}
		}
		else if(Play::KeyDown(VK_LEFT))
		{
			if (player.getBlockFace() == 4 && player.isSliding())
			{
				player.endSlide();
			}
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

	if (Play::KeyPressed(VK_SPACE))
	{
		if (!player.isJumped())
		{
			player.setVelY(-jumpHeight);
			player.jump();
		}
		else if (player.isSliding())
		{
			//left side
			if (player.getBlockFace() == 4)
			{
				player.setVelX(-wallJumpWidth);
			}
			//right side
			else if(player.getBlockFace() == 2)
			{
				player.setVelX(wallJumpWidth);
			}
				
			player.setVelY(-wallJumpHeight);
		}
		player.endSlide();
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
	//p1 = top left
	//p2 = top right
	//p3 = bot left
	//p4 = bot right
	Point2D p1 = { player.getX(), player.getY() };
	Point2D p2 = { player.getX() + Play::GetSpriteWidth(player.getSpriteID()), player.getY() };
	Point2D p3 = { player.getX(), player.getY() + Play::GetSpriteHeight(player.getSpriteID()) };
	Point2D p4 = { player.getX() + Play::GetSpriteWidth(player.getSpriteID()), player.getY() + Play::GetSpriteHeight(player.getSpriteID()) };
	
	Point2D r1;
	Point2D r2;
	Point2D r3;
	Point2D r4;

	for (int x = 0; x < sizeof(levelBlocks) / sizeof(levelBlocks[0]); x++)
	{
		r1 = { levelBlocks[x].getX(), levelBlocks[x].getY() };
		r2 = { levelBlocks[x].getX() + Play::GetSpriteWidth(levelBlocks[x].getSpriteID()), levelBlocks[x].getY() };
		r3 = { levelBlocks[x].getX(), levelBlocks[x].getY() + Play::GetSpriteHeight(levelBlocks[x].getSpriteID()) };
		r4 = { levelBlocks[x].getX() + Play::GetSpriteWidth(levelBlocks[x].getSpriteID()), levelBlocks[x].getY() + Play::GetSpriteHeight(levelBlocks[x].getSpriteID()) };

		if (p3.y > r1.y &&
			p3.x > r1.x &&
			p4.x < r2.x &&
			p1.y < r1.y)
		{
			//set top
			SetTop(x);
			break;
		}
		if (p1.y < r3.y &&
			p3.x > r1.x &&
			p4.x < r2.x &&
			p3.y > r3.y)
		{
			//set bot
			SetBot(x);
			break;
		}
		if (p2.x > r1.x &&
			p2.y > r1.y &&
			p4.y < r3.y &&
			p1.x < r1.x)
		{
			//set left
			SetLeft(x);
			break;
		}
		if (p1.x < r2.x &&
			p2.y > r1.y &&
			p4.y < r3.y &&
			p2.x > r2.x)
		{
			//set right
			SetRight(x);
			break;
		}
		if (p2.x > r3.x &&
			p2.y < r3.y &&
			p1.x < r3.x &&
			p4.y > r3.y)
		{
			if (abs(p2.x - r3.x) <= abs(p2.y - r3.y))
			{
				//set left
				SetLeft(x);
			}
			else
			{
				//set bot
				SetBot(x);
			}
			break;
		}
		if (p4.x > r1.x &&
			p4.y > r1.y &&
			p2.y < r1.y &&
			p3.x < r1.x)
		{
			if (abs(p4.x - r1.x) <= abs(p4.y - r1.y))
			{
				SetLeft(x);
			}
			else
			{
				SetTop(x);
			}
			break;
		}
		if (p1.x < r4.x &&
			p1.y < r4.y &&
			p2.x > r4.x &&
			p3.y > r4.y)
		{
			if (abs(p1.x - r4.x) <= abs(p1.y - r4.y))
			{
				SetRight(x);
			}
			else
			{
				SetBot(x);
			}
			break;
		}
		if (p3.x < r2.x &&
			p3.y > r2.y &&
			p1.y < r2.y &&
			p4.x > r2.x)
		{
			if (abs(p3.x - r2.x) <= abs(p3.y - r2.y))
			{
				SetRight(x);
			}
			else
			{
				SetTop(x);
			}
			break;
		}
	}
}

void CreateLevel()
{
	levelBlocks[0].setSpriteID(4);
	levelBlocks[0].setX((DISPLAY_WIDTH * .333f + 75));
	levelBlocks[0].setY(DISPLAY_HEIGHT * .666f);

	levelBlocks[1].setSpriteID(4);
	levelBlocks[1].setX((DISPLAY_WIDTH * .333f - 300));
	levelBlocks[1].setY(DISPLAY_HEIGHT * .666f - 220);

	levelBlocks[2].setSpriteID(4);
	levelBlocks[2].setX((DISPLAY_WIDTH * .333f + 425));
	levelBlocks[2].setY(DISPLAY_HEIGHT * .666f - 220);

	levelBlocks[3].setSpriteID(2);
	levelBlocks[3].setX((DISPLAY_WIDTH * .75f + 245));
	levelBlocks[3].setY(DISPLAY_HEIGHT * .5f - 200);

	levelBlocks[4].setSpriteID(2);
	levelBlocks[4].setX((DISPLAY_WIDTH * .25f - 325));
	levelBlocks[4].setY(DISPLAY_HEIGHT * .5f - 200);

	levelBlocks[5].setSpriteID(3);
	levelBlocks[5].setX((DISPLAY_WIDTH * .5f));
	levelBlocks[5].setY(DISPLAY_HEIGHT * .5f - 200);

	levelBlocks[6].setSpriteID(3);
	levelBlocks[6].setX((DISPLAY_WIDTH * .5f));
	levelBlocks[6].setY(DISPLAY_HEIGHT * .5f - 300);

	for (int x = 7; x < sizeof(levelBlocks) / sizeof(levelBlocks[0]); x++)
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

void SetTop(int levelIndex)
{
	player.setPosY(levelBlocks[levelIndex].getY() - Play::GetSpriteHeight(player.getSpriteID()));
	player.setVelY(0);
	player.endJump();
	player.setBlockFace(1);
}

void SetBot(int levelIndex)
{
	player.setPosY(levelBlocks[levelIndex].getY() + Play::GetSpriteHeight(levelBlocks[levelIndex].getSpriteID()));
	if (player.getVelY() < 0)
	{
		player.setVelY(0);
	}
	player.setBlockFace(3);
}

void SetLeft(int levelIndex)
{
	//adjust for velocity so camera doesn't drift
	float rev = player.getX();
	rev = (levelBlocks[levelIndex].getX() - Play::GetSpriteWidth(player.getSpriteID())) - rev;
	player.setVelX(rev);
	TranslateLevel();
	//set player pos/vel
	player.setPosX(levelBlocks[levelIndex].getX() - Play::GetSpriteWidth(player.getSpriteID()));
	player.setVelX(0);
	player.setBlockFace(4);
	player.slide();
}

void SetRight(int levelIndex)
{
	//adjust for velocity so camera doesn't drift
	float rev = player.getX();
	rev = rev - (levelBlocks[levelIndex].getX() + Play::GetSpriteWidth(levelBlocks[levelIndex].getSpriteID()));
	player.setVelX(-rev);
	TranslateLevel();
	//set player pos/vel
	player.setPosX(levelBlocks[levelIndex].getX() + Play::GetSpriteWidth(levelBlocks[levelIndex].getSpriteID()));
	player.setVelX(0);
	player.setBlockFace(2);
	player.slide();
}