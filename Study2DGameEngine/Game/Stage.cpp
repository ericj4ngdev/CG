#include "Include.h"

Stage::Stage() 
{

}

Stage::~Stage() 
{

}

void Stage::init() 
{
	mPlayer.init();
	mGround.init(1);
}

void Stage::Release() 
{
	mPlayer.Release();
	mGround.Release();
}

void Stage::Render() {
	mPlayer.Render();
	mGround.Render(1);
}

void Stage::Collide() {
	if (mPlayer.Collide(mGround)) {
		mPlayer.mColor = Color4f(1, 0, 1, 1);
	}
	else mPlayer.mColor = Color4f(1, 1, 1, 1);
}

void Stage::FrameMove() 
{
	int moveSpeed = 2;
	if (KeyDown(VK_LEFT) || KeyDown('A') || KeyDown('a'))
	{
		mPlayer.mPos.x -= moveSpeed;
	}

	if (KeyDown(VK_RIGHT) || KeyDown('D') || KeyDown('d'))
	{
		mPlayer.mPos.x += moveSpeed;
	}

	if (KeyDown(VK_UP) || KeyDown('W') || KeyDown('w'))
	{
		mPlayer.mPos.y -= moveSpeed;
	}

	if (KeyDown(VK_DOWN) || KeyDown('S') || KeyDown('s'))
	{
		mPlayer.mPos.y += moveSpeed;
	}
}
