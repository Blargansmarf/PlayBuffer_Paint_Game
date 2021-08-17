#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Player.h"
#include "FloorBlock.h"

const int DISPLAY_WIDTH = 1280;
const int DISPLAY_HEIGHT = 720;
const int DISPLAY_SCALE = 1;

Player player;
Point2D playerPos;

const float gravity = .1f;
const float maxVelX = 9.0f;
const float maxVelY = 11.0f;

void ApplyPhysics();

// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );

	player.setAccel(.5f);
	player.setPos(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2);
	player.setSpriteID(Play::GetSpriteId("Data//Sprites//WhiteSquare.png"));
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	Play::ClearDrawingBuffer( Play::cCyan );
	
	ApplyPhysics();
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
	player.setPos(player.getX() + player.getVelX(), player.getY() + player.getVelY() + gravity);
}