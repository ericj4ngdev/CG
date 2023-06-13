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
	
	for (int i = 0; i < 96; i++)
	{
		arrground[i].SetmPos(25 + i * 50, 925);
		arrground[i].init();
	}
	for (int i = 0; i < 3; i++)
	{
		arrPlatform1[i].SetmPos(25 + 50*(16*3-5) + i * 50, 925 - 50 * 4);
		arrPlatform1[i].init();
	}
	for (int i = 0; i < 10; i++)
	{
		arrPlatform2[i].SetmPos(25 + 50 * (16 * 3 - 1) + i * 50, 925 - 50 * 6);
		arrPlatform2[i].init();
	}
	for (int i = 0; i < 6; i++)
	{
		arrPlatform3[i].SetmPos(25 + 50 * (16 * 4 - 6) + i * 50, 925 - 50 * 4);
		arrPlatform3[i].init();
	}
	for (int i = 0; i < 9; i++)
	{
		arrPlatform4[i].SetmPos(25 + 50 * (16 * 6 - 9) + i * 50, 925 - 50 * 6);
		arrPlatform4[i].init();
	}
}

void Stage::Release() 
{
	mPlayer.Release();
	mEnemy.Release();
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
	mEnemy.Render();
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
	mEnemy.Transform();
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
		arrground[i].CollidebyVector(mEnemy);
	}
	for (int i = 0; i < 3; i++)
	{
		arrPlatform1[i].CollidebyVector(mPlayer);
		arrPlatform1[i].CollidebyVector(mEnemy);
	}
	for (int i = 0; i < 10; i++)
	{
		arrPlatform2[i].CollidebyVector(mPlayer);
		arrPlatform2[i].CollidebyVector(mEnemy);
	}
	for (int i = 0; i < 6; i++)
	{
		arrPlatform3[i].CollidebyVector(mPlayer);
		arrPlatform3[i].CollidebyVector(mEnemy);
	}
	for (int i = 0; i < 9; i++)
	{
		arrPlatform4[i].CollidebyVector(mPlayer);
		arrPlatform4[i].CollidebyVector(mEnemy);
	}
}

void Stage::FrameMove()
{	
	printf("%d\n", mPlayer.OnGround);
	mPlayer.Move();
	mPlayer.mVelo.x = 2;
	// 화면 절반 넘으면 맵이 이동
	if (mPlayer.mPos.x > (int)g_Extern.WINDOWSIZE_WIDTH / 2)
	{
		if (KeyDown(VK_RIGHT))
		{
			mPlayer.mVelo.x = 0;			// 플레이어 속도 죽이기
			for (int i = 0; i < 96; i++)
			{
				arrground[i].mPos.x -= 2;
			}	
			for (int i = 0; i < 3; i++)
			{
				arrPlatform1[i].mPos.x -= 2;
			}
			for (int i = 0; i < 10; i++)
			{
				arrPlatform2[i].mPos.x -= 2;
			}
			for (int i = 0; i < 6; i++)
			{
				arrPlatform3[i].mPos.x -= 2;
			}
			for (int i = 0; i < 9; i++)
			{
				arrPlatform4[i].mPos.x -= 2;
			}
		}		
	}
	else if(mPlayer.mPos.x < (int)g_Extern.WINDOWSIZE_WIDTH / 2)
	{
		if (KeyDown(VK_LEFT))
		{
			mPlayer.mVelo.x = 0;			// 플레이어 속도 죽이기
			for (int i = 0; i < 96; i++)
			{
				arrground[i].mPos.x += 2;
			}
			for (int i = 0; i < 3; i++)
			{
				arrPlatform1[i].mPos.x += 2;
			}
			for (int i = 0; i < 10; i++)
			{
				arrPlatform2[i].mPos.x += 2;
			}
			for (int i = 0; i < 6; i++)
			{
				arrPlatform3[i].mPos.x += 2;
			}
			for (int i = 0; i < 9; i++)
			{
				arrPlatform4[i].mPos.x += 2;
			}
		}
	}
	
	mEnemy.Move();
}
