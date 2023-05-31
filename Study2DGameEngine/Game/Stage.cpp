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
	mGround.init();
}

void Stage::Release() 
{
	mPlayer.Release();
	mGround.Release();
}

void Stage::Render() {
	mPlayer.Render();
	mGround.Render();
}

void Stage::Collide() {
	if (mPlayer.Collide(mGround)) 
	{
		mPlayer.mColor = Color4f(1, 0, 1, 1);
	}
	else mPlayer.mColor = Color4f(1, 1, 1, 1);
}

void Stage::FrameMove() 
{
	mPlayer.Move();
}
