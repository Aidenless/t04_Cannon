#pragma once

#include "GameObj.h"

struct CannonBall : public GameObj 
{
public:
	CannonBall()
		:GameObj()
	{}

	bool active = false;
	float speed = 200;
	float angleOffest = 20;
};