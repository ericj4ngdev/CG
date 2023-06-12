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
	mEnemy.init();
	mobject.mSprite.init();

	for (int i = 0; i < 14; i++)
	{
		arrground[i].SetmPos(i * 50, 450);
		arrground[i].init();
	}
	for (int i = 0; i < 8; i++)
	{
		arrPlatform1[i].SetmPos(250 + i * 50, 250);
		arrPlatform1[i].init();
	}
	// for (int i = 0; i < 10; i++)
	// {
	// 	arrPlatform2[i].SetmPos(230 + i * 50, 100);
	// 	arrPlatform2[i].init();
	// }

}

void Stage::Release() 
{
	// mPlayer.Release();
	mEnemy.Release();

	mobject.mSprite.Release();

	for (int i = 0; i < 14; i++)
	{
		arrground[i].Release();
	}
	for (int i = 0; i < 8; i++)
	{
		arrPlatform1[i].Release();
	}
	// for (int i = 0; i < 10; i++)
	// {
	// 	arrPlatform2[i].Release();
	// }
}

void Stage::Render() {
	mPlayer.Render();
	mEnemy.Render();
	
	mobject.mSprite.Render();

	for (int i = 0; i < 14; i++)
	{
		arrground[i].Render();
	}
	for (int i = 0; i < 8; i++)
	{
		arrPlatform1[i].Render();
	}
	// for (int i = 0; i < 10; i++)
	// {
	// 	arrPlatform2[i].Render();
	// }

}

void Stage::Transform() {
	mPlayer.Transform();
	mEnemy.Transform();
	for (int i = 0; i < 14; i++)
	{
		arrground[i].Transform();
	}
	for (int i = 0; i < 8; i++)
	{
		arrPlatform1[i].Transform();
	}
	// for (int i = 0; i < 10; i++)
	// {
	// 	arrPlatform2[i].Transform();
	// }
}

void Stage::Collide()
{
	for (int i = 0; i < 14; i++)
	{
		// arrground[i].CollidebyVector(mPlayer);
		arrground[i].CollidebyVector(mEnemy);
	}
	for (int i = 0; i < 8; i++)
	{
		// arrPlatform1[i].CollidebyVector(mPlayer);
		arrPlatform1[i].CollidebyVector(mEnemy);
	}

	// for (int i = 0; i < 10; i++)
	// {
	// 	arrPlatform2[i].CollidebyVector(mPlayer);
	// 	arrPlatform2[i].CollidebyVector(mEnemy);
	// }

}

void Stage::FrameMove()
{
	// printf("%d\n", mPlayer.OnGround);
	mPlayer.Move();
	mEnemy.Move();
}
