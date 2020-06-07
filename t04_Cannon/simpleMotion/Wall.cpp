#include "Wall.h"

void Wall::Update(CannonBall& mBall)
{
	//add ball collision code here
	if (mType == RIGHT) {
		if (mBall.GetPos().x + 10 > GetPos().x) {
			mBall.SetVel(Vec2f{ mBall.GetVel().x * -1, mBall.GetVel().y });
		}
	}

	if (mType == LEFT) {
		if (mBall.GetPos().x - 140 < GetPos().x) {
			mBall.SetVel(Vec2f{ mBall.GetVel().x * -1, mBall.GetVel().y });
		}
	}

	if (mType == TOP) {
		if (mBall.GetPos().y - 240 < GetPos().y) {
			mBall.SetVel(Vec2f{ mBall.GetVel().x, mBall.GetVel().y * -1 });
		}
	}

	if (mType == BOTTOM) {
		if (mBall.GetPos().y - 130 > GetPos().y) {
			mBall.SetVel(Vec2f{ mBall.GetVel().x, mBall.GetVel().y * -1 });
		}
	}

}