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
	
	for (int i = 0; i < 14; i++)
	{
		arrground[i].SetmPos(i * 50, 500);
		arrground[i].init();
	}
	for (int i = 0; i < 8; i++)
	{
		arrPlatform1[i].SetmPos(150 + i * 50, 300);
		arrPlatform1[i].init();
	}
	for (int i = 0; i < 10; i++)
	{
		arrPlatform2[i].SetmPos(230 + i * 50, 100);
		arrPlatform2[i].init();
	}

}

void Stage::Release() 
{
	mPlayer.Release();

	for (int i = 0; i < 14; i++)
	{
		arrground[i].Release();
	}
	for (int i = 0; i < 8; i++)
	{
		arrPlatform1[i].Release();
	}
	for (int i = 0; i < 10; i++)
	{
		arrPlatform2[i].Release();
	}

}

void Stage::Render() {
	mPlayer.Render();
	for (int i = 0; i < 14; i++)
	{
		arrground[i].Render();
	}
	for (int i = 0; i < 8; i++)
	{
		arrPlatform1[i].Render();
	}
	for (int i = 0; i < 10; i++)
	{
		arrPlatform2[i].Render();
	}

}

void Stage::Transform() {
	mPlayer.Transform();
	for (int i = 0; i < 14; i++)
	{
		arrground[i].Transform();
	}
	for (int i = 0; i < 8; i++)
	{
		arrPlatform1[i].Transform();
	}
	for (int i = 0; i < 10; i++)
	{
		arrPlatform2[i].Transform();
	}
}

void Stage::Collide()
{
	for (int i = 0; i < 14; i++)
	{
		arrground[i].CollidebyVector(mPlayer);
	}
	for (int i = 0; i < 8; i++)
	{
		arrPlatform1[i].CollidebyVector(mPlayer);
	}

	for (int i = 0; i < 10; i++)
	{
		arrPlatform2[i].CollidebyVector(mPlayer);
	}

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
