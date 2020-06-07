#include "Application.h"
#include "GameObj.h"

void GameObj::Update()
{
	if (mVel.x != 0 || mVel.y != 0)
	{
		sf::Vector2f pos{ mSprite.getPosition() };
		pos += mVel * Application::GetElapsedSecs();
		mSprite.setPosition(pos);
	}
}