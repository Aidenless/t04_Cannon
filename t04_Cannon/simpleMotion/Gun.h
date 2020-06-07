#pragma once

#include "GameObj.h"
#include "CannonBall.h"

//cannon spins around and can fire one cannon ball
class Gun : public GameObj
{
public:
	Gun()
		:GameObj(), mWaitSecs(0)
	{}
	void Update(CannonBall& mBall);
private:
	float mWaitSecs;	//delay after firing beforeo you can move/fire
};