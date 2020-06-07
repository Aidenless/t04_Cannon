#include "Gun.h"
#include "Game.h"
#include "Application.h"

void Gun::Update(CannonBall& mBall)
{
	SetPos(Vec2f{ GDC::SCREEN_RES.x / 2.f, GDC::SCREEN_RES.y / 2.f });

	if (mWaitSecs <= 0)
	{
		//here we don't want windowsOS keys, with initial delays and repeat rate delays and all that rubbish
		//so just access the keyboard directly for instant response
		float inc = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			inc = -GDC::PLAY_SPIN_SPD;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			inc = GDC::PLAY_SPIN_SPD;
		//a bit of physics degress per seconds X seconds for smooth predictable rate of rotation
		SetDegrees(GetDegrees() + inc * Application::GetElapsedSecs());
	}
	else
		mWaitSecs -= Application::GetElapsedSecs();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		//fire the ball here
		mBall.active = true;

		mBall.SetPos(Vec2f{ GetPos().x, GetPos().y + 150 });
		mBall.SetVel(Vec2f{ -cosf((GetDegrees() + mBall.angleOffest) * (PI / 180)) * mBall.speed, -sinf((GetDegrees() + mBall.angleOffest) * (PI / 180)) * mBall.speed });

		mWaitSecs = GDC::FIRE_DELAY;
	}
}