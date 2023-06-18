#include "Include.h"

Stage::Stage() 
{
	groundSpeed = 3;
}

Stage::~Stage() 
{

}

void Stage::init() 
{
	mPlayer.initTexture("Game/Image/castlevania3.png");
	
	mZombie.SetmPos(550, 850 / 2);
	mZombie.initTexture("Game/Image/Zombie1.png");
	mLeopard.SetmPos(25 + 50 * (16 * 3 - 5) + 2 * 50, 462.5 - 50 * 6 + 25);
	mLeopard.initTexture("Game/Image/Black Leopard.png");

	for (int i = 0; i < 96; i++)
	{
		arrground[i].SetmPos(25 + i * 50, 925/2);
		arrground[i].initTexture("Game/Image/block.png");
	}
	for (int i = 0; i < 3; i++)
	{
		arrPlatform1[i].SetmPos(25 + 50 * (16 * 3 - 5) + i * 50, 925 / 2 - 50 * 4);
		arrPlatform1[i].initTexture("Game/Image/block.png");
	}
	for (int i = 0; i < 10; i++)
	{
		arrPlatform2[i].SetmPos(25 + 50 * (16 * 3 - 1) + i * 50, 925/2 - 50 * 6);
		arrPlatform2[i].initTexture("Game/Image/block.png");
	}
	for (int i = 0; i < 6; i++)
	{
		arrPlatform3[i].SetmPos(25 + 50 * (16 * 4 - 6) + i * 50, 925/2 - 50 * 4);
		arrPlatform3[i].initTexture("Game/Image/block.png");
	}
	for (int i = 0; i < 9; i++)
	{
		arrPlatform4[i].SetmPos(25 + 50 * (16 * 6 - 9) + i * 50, 925/2 - 50 * 6);
		arrPlatform4[i].initTexture("Game/Image/block.png");
	}
}

void Stage::Release() 
{
	mPlayer.Release();
	mZombie.Release();
	mLeopard.Release();

	for (int i = 0; i < 96; i++)
	{
		arrground[i].Release();
	}
	for (int i = 0; i < 3; i++)
	{
		arrPlatform1[i].Release();
	}
	for (int i = 0; i < 10; i++)
	{
		arrPlatform2[i].Release();
	}
	for (int i = 0; i < 6; i++)
	{
		arrPlatform3[i].Release();
	}
	for (int i = 0; i < 9; i++)
	{
		arrPlatform4[i].Release();
	}
}

void Stage::Render() {
	mPlayer.Render();
	mZombie.Render();
	mLeopard.Render();

	for (int i = 0; i < 96; i++)
	{
		arrground[i].Render();
	}
	for (int i = 0; i < 3; i++)
	{
		arrPlatform1[i].Render();
	}
	for (int i = 0; i < 10; i++)
	{
		arrPlatform2[i].Render();
	}
	for (int i = 0; i < 6; i++)
	{
		arrPlatform3[i].Render();
	}
	for (int i = 0; i < 9; i++)
	{
		arrPlatform4[i].Render();
	}
}

void Stage::Transform() {
	mPlayer.Transform();
	mZombie.Transform();
	mLeopard.Transform();

	for (int i = 0; i < 96; i++)
	{
		arrground[i].Transform();
	}
	for (int i = 0; i < 3; i++)
	{
		arrPlatform1[i].Transform();
	}
	for (int i = 0; i < 10; i++)
	{
		arrPlatform2[i].Transform();
	}
	for (int i = 0; i < 6; i++)
	{
		arrPlatform3[i].Transform();
	}
	for (int i = 0; i < 9; i++)
	{
		arrPlatform4[i].Transform();
	}
}

void Stage::Collide()
{
	for (int i = 0; i < 96; i++)
	{
		arrground[i].CollidebyVector(mPlayer);
		arrground[i].CollidebyVector(mZombie);
		arrground[i].CollidebyVector(mLeopard);
	}
	for (int i = 0; i < 3; i++)
	{
		arrPlatform1[i].CollidebyVector(mPlayer);
		arrPlatform1[i].CollidebyVector(mZombie);
		arrPlatform1[i].CollidebyVector(mLeopard);
	}
	for (int i = 0; i < 10; i++)
	{
		arrPlatform2[i].CollidebyVector(mPlayer);
		arrPlatform2[i].CollidebyVector(mZombie);
		arrPlatform2[i].CollidebyVector(mLeopard);
	}
	for (int i = 0; i < 6; i++)
	{
		arrPlatform3[i].CollidebyVector(mPlayer);
		arrPlatform3[i].CollidebyVector(mZombie);
		arrPlatform3[i].CollidebyVector(mLeopard);
	}
	for (int i = 0; i < 9; i++)
	{
		arrPlatform4[i].CollidebyVector(mPlayer);
		arrPlatform4[i].CollidebyVector(mZombie);
		arrPlatform4[i].CollidebyVector(mLeopard);
	}
}

void Stage::FrameMove()
{	
	// printf("%d\n", mPlayer.OnGround);
	mPlayer.Move();
	mPlayer.Controller();
	mPlayer.mVelo.x = 3;
	// 화면 절반 넘으면 맵이 이동
	if (mPlayer.mPos.x > (int)g_Extern.WINDOWSIZE_WIDTH / 2)
	{
		if (KeyDown(VK_RIGHT))
		{
			mPlayer.mVelo.x = 0;			// 플레이어 속도 죽이기
			mLeopard.mPos.x -= groundSpeed;
			for (int i = 0; i < 96; i++)
			{
				arrground[i].mPos.x -= groundSpeed;
			}	
			for (int i = 0; i < 3; i++)
			{
				arrPlatform1[i].mPos.x -= groundSpeed;
			}
			for (int i = 0; i < 10; i++)
			{
				arrPlatform2[i].mPos.x -= groundSpeed;
			}
			for (int i = 0; i < 6; i++)
			{
				arrPlatform3[i].mPos.x -= groundSpeed;
			}
			for (int i = 0; i < 9; i++)
			{
				arrPlatform4[i].mPos.x -= groundSpeed;
			}
		}		
	}
	else if(mPlayer.mPos.x < (int)g_Extern.WINDOWSIZE_WIDTH / 2)
	{
		if (KeyDown(VK_LEFT))
		{
			mPlayer.mVelo.x = 0;			// 플레이어 속도 죽이기
			mLeopard.mPos.x += groundSpeed;
			for (int i = 0; i < 96; i++)
			{
				arrground[i].mPos.x += groundSpeed;
			}
			for (int i = 0; i < 3; i++)
			{
				arrPlatform1[i].mPos.x += groundSpeed;
			}
			for (int i = 0; i < 10; i++)
			{
				arrPlatform2[i].mPos.x += groundSpeed;
			}
			for (int i = 0; i < 6; i++)
			{
				arrPlatform3[i].mPos.x += groundSpeed;
			}
			for (int i = 0; i < 9; i++)
			{
				arrPlatform4[i].mPos.x += groundSpeed;
			}
		}
	}
	
	mZombie.Move();
	// mLeopard.Move();
}
