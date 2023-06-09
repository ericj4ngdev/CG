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
	mGround1.SetmPos(100, 500);
	mGround2.SetmPos(150, 500);
	mGround3.SetmPos(200, 500);
	mGround4.SetmPos(250, 500);
	mGround5.SetmPos(300, 500);

	mPlatform1.SetmPos(250, 300);
	mPlatform2.SetmPos(300, 300);
	mPlatform3.SetmPos(350, 300);
	
	mGround1.init();
	mGround2.init();
	mGround3.init();
	mGround4.init();
	mGround5.init();
	mPlatform1.init();
	mPlatform2.init();
	mPlatform3.init();
}

void Stage::Release() 
{
	mPlayer.Release();
	mGround1.Release();
	mGround2.Release();
	mGround3.Release();
	mGround4.Release();
	mGround5.Release();
	mPlatform1.Release();
	mPlatform2.Release();
	mPlatform3.Release();
}

void Stage::Render() {
	mPlayer.Render();
	mGround1.Render();
	mGround2.Render();
	mGround3.Render();
	mGround4.Render();
	mGround5.Render();
	mPlatform1.Render();
	mPlatform2.Render();
	mPlatform3.Render();
}

void Stage::Transform() {
	mPlayer.Transform();
	mGround1.Transform();
	mGround2.Transform();
	mGround3.Transform();
	mGround4.Transform();
	mGround5.Transform();
	mPlatform1.Transform();
	mPlatform2.Transform();
	mPlatform3.Transform();
}

void Stage::Collide()
{
	mGround1.CollidebyVector(mPlayer);
	mGround2.CollidebyVector(mPlayer);
	mGround3.CollidebyVector(mPlayer);
	mGround4.CollidebyVector(mPlayer);
	mGround5.CollidebyVector(mPlayer);
	mPlatform1.CollidebyVector(mPlayer);
	mPlatform2.CollidebyVector(mPlayer);
	mPlatform3.CollidebyVector(mPlayer);
	// ¶¥ Ã¼Å©
	// mPlayer.IsGround(mGround1);
	// mPlayer.IsGround(mGround2);
	// mPlayer.IsGround(mGround3);
	// mPlayer.IsGround(mGround4);
	// mPlayer.IsGround(mGround5);
	// mPlayer.IsGround(mPlatform1);
	// mPlayer.IsGround(mPlatform2);
	// mPlayer.IsGround(mPlatform3);

}


	// if (mPlayer.Collide(mGround)) 
	// {
	// 	mPlayer.mColor = Color4f(1, 0, 1, 1);
	// }
	// else mPlayer.mColor = Color4f(1, 1, 1, 1);
	
	// mPlayer.CollidebyVector(mGround);

void Stage::FrameMove()
{
	mPlayer.Move();
}
