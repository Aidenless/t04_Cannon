#pragma once
/*
Mini game example demonstrates static binding - compile time inheritance and
introduces some simple physics to get things moving. For students to modify
*/


#include <string>

#include "SFML/Graphics.hpp"
#include "GameObj.h"
#include "Gun.h"
#include "Wall.h"
#include "CannonBall.h"


const float PI = 3.14159265358979323846f;
inline float Deg2Rad(float deg) {
	return deg * (PI/180.f);
}

//a namespace is just another type of box with a label where we can group things together
//GDC="GameDataConstants" - a box for all your magic numbers
//especially those that a designer might need to tweak to balance the game
namespace GDC
{
	const Vec2i SCREEN_RES{ 1200,800 };	//desired resolution
	const char ESCAPE_KEY{ 27 };		//ASCII code
	const char ENTER_KEY{ 13 };
	const sf::Uint32 ASCII_RANGE{ 127 };//google an ASCII table, after 127 we don't care
	const float PLAY_SPIN_SPD{ 200.f };	//how fast to spin
	const float WALL_WDITH{ 0.1f };		//the walls skirt the edge of the screen
	const float GUN_LENGTH{ 70.f };		//from the centre to the end of the barrel
	const float BALL_SPEED{ 400.f };	//ball speed in units per sec
	const float FIRE_DELAY{ 0.25f };	//stop on firing for this time in secs
	const float CANNON_ROT_OFFSET{ 115 };	//when rotating the cannon, the barrel points at a specific angle (rotate anti-clockwise from horizontal)
}

//keep important shared information "GameData" in one accessible object and pass it around
//note - structs are like classes but everything is always public, so best kept just for data
struct GD
{
	sf::Font font;				//a shared font to use everywhere
	sf::RenderWindow *pWindow;	//can't render anything without this
	std::string playerName;			//the player's name is needed by different objects
};

class Game;

//in this mode we want the player's name, like a game's frontend menu screens
class NameMode
{
public:
	NameMode() :mpGame(nullptr) {}
	//setup
	void Init(Game*);
	//handle any logic
	void Update() {};
	//display
	void Render();
	//process windows text messages
	void TextEntered(char);
private:
	Game* mpGame;	//the only way to communicate with the rest of the game
};

class PlayMode
{
public:
	PlayMode() : mpGame(nullptr) {}
	void Init(Game*);
	void Update();
	void Render();
private:
	Game* mpGame; //for communication

	sf::Texture mCannonTex;			//cannon and ball
	sf::Texture mBallTex;
	sf::Texture mWallTex;			//walls
	Wall mWalls[Wall::MAX_WALLS];	//four walls
	Gun mGun;		//cannon
	CannonBall mBall;
};

//manage the game's different behaviours
class Game
{
public:
	//control what the game is doing 
	enum class StateMachine {
		WAITING_INIT,	//not in a safe state yet
		GET_NAME,		//what's your name?
		PLAY			//let's play!!
	};

	Game();
	//setup
	void Initialise(sf::RenderWindow&);
	//logic
	void Update();
	//display
	void Render();
	//input from windows
	void TextEntered(char);

	//accessors
	StateMachine& GetState() { return mState; }
	void SetState(StateMachine nState) { mState = nState; }

	GD& GetData() { return mGD; }
private:
	GD mGD;				//shared game data, be careful here we are breaking rules of encapsulation
	StateMachine mState;//contols what's going on in the 
	PlayMode mPMode;	//object used for playing the game (like a mini game)
	NameMode mNMode;	//object used for getting the player's name (like a mini frontend)
};

