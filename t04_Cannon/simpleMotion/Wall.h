#pragma once

#include "GameObj.h"
#include "CannonBall.h"

//cannon balls bounce off walls
class Wall : public GameObj
{
public:
	static const int MAX_WALLS = 4;				//a wall on each side of the screen
	enum WallType { LEFT, RIGHT, TOP, BOTTOM };	//identify where each wall is

	Wall()
		:GameObj(), mType(LEFT)
	{}
	void Init(WallType wtype) {
		mType = wtype;
	}
	void Update(CannonBall& mBall);
private:
	WallType mType; //where does this instance fit on screen
};