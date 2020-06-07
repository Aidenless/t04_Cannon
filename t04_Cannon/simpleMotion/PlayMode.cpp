#include <assert.h>
#include <string.h>
#include "Game.h"
#include "Application.h"

//******************************************************************
//a mini playable game (sort of)
void PlayMode::Init(Game *pG)
{
	mpGame = pG;
	if (!mCannonTex.loadFromFile("../bin/data/cannon.png"))
		assert(false);
	mCannonTex.setSmooth(true); //it will look gnarly when it turns otherwise, try it. Probably using anisotropic sub pixel sampling with blur (look it up)
	mGun.SetTexture(mCannonTex, sf::IntRect(0, 0, 156, 138));
	mGun.SetOrigin(Vec2f{ 73, 68 });

	if (!mBallTex.loadFromFile("../bin/data/cannon.png"))
		assert(false);
	mBallTex.setSmooth(true);
	mBall.SetTexture(mCannonTex, sf::IntRect(4, 147, 38, 38));
	mBall.SetOrigin(Vec2f{ 23, 166 });
	mBall.SetPos(Vec2f{ 500, 500 });

	if (!mWallTex.loadFromFile("../bin/data/TiledWall.png"))
		assert(false);
	mWallTex.setRepeated(true);
	mWallTex.setSmooth(true);

	//resolution independant with the sprite scaled up/down as necessary
	//the texture is set to wrap and uses a 'tilable' brick pattern so it can grow to any size
	mWalls[Wall::TOP].SetTexture(mWallTex, sf::IntRect{ 0,0,(int)(GDC::SCREEN_RES.x*(1 - GDC::WALL_WDITH * 2)), (int)(GDC::SCREEN_RES.y*GDC::WALL_WDITH) });
	mWalls[Wall::TOP].SetPos(Vec2f{ GDC::SCREEN_RES.x*GDC::WALL_WDITH,0 });
	mWalls[Wall::TOP].SetOrigin(Vec2f{ 0,0 });
	mWalls[Wall::TOP].Init(Wall::TOP);

	mWalls[Wall::BOTTOM].SetTexture(mWallTex, sf::IntRect{ 0,0,(int)(GDC::SCREEN_RES.x*(1 - GDC::WALL_WDITH * 2)), (int)(GDC::SCREEN_RES.y*GDC::WALL_WDITH) });
	mWalls[Wall::BOTTOM].SetPos(Vec2f{ GDC::SCREEN_RES.x*GDC::WALL_WDITH,GDC::SCREEN_RES.y*(1 - GDC::WALL_WDITH) });
	mWalls[Wall::BOTTOM].SetOrigin(Vec2f{ 0,0 });
	mWalls[Wall::BOTTOM].Init(Wall::BOTTOM);

	mWalls[Wall::LEFT].SetTexture(mWallTex, sf::IntRect{ 0,0,(int)(GDC::SCREEN_RES.x*GDC::WALL_WDITH), (int)(GDC::SCREEN_RES.y*(1 - GDC::WALL_WDITH * 2)) });
	mWalls[Wall::LEFT].SetPos(Vec2f{ 0,GDC::SCREEN_RES.y*GDC::WALL_WDITH });
	mWalls[Wall::LEFT].SetOrigin(Vec2f{ 0,0 });
	mWalls[Wall::LEFT].Init(Wall::LEFT);

	mWalls[Wall::RIGHT].SetOrigin(Vec2f{ 0,0 });
	mWalls[Wall::RIGHT].SetPos(Vec2f{ GDC::SCREEN_RES.x*(1 - GDC::WALL_WDITH),GDC::SCREEN_RES.y*GDC::WALL_WDITH });
	mWalls[Wall::RIGHT].SetTexture(mWallTex, sf::IntRect{ 0,0,(int)(GDC::SCREEN_RES.x*GDC::WALL_WDITH), (int)(GDC::SCREEN_RES.y*(1 - GDC::WALL_WDITH * 2)) });
	mWalls[Wall::RIGHT].Init(Wall::RIGHT);

}

void PlayMode::Update()
{
	assert(mpGame);

	mGun.Update(mBall);

	if (mBall.active) {
		mBall.Update();
	}

	for (int i = 0; i < Wall::MAX_WALLS; ++i)
		mWalls[i].Update(mBall);
}

void PlayMode::Render()
{
	//the instructions
	assert(mpGame);
	GD& gd = mpGame->GetData();
	std::string mssg = gd.playerName;
	mssg += ", press left or right arrow to spin, space to fire, ESC to quit";
	sf::Text txt(mssg, gd.font, 20);
	txt.setPosition(GDC::SCREEN_RES.x*0.15f, GDC::SCREEN_RES.y*0.15f);
	gd.pWindow->draw(txt);
	
	if (mBall.active) {
		mBall.Render(*gd.pWindow);
	}
	
	mGun.Render(*gd.pWindow);
	
	for (int i = 0; i < Wall::MAX_WALLS; ++i)
		mWalls[i].Render(*gd.pWindow);
}
