#include "Include.h"

Stage::Stage() 
{

}

Stage::~Stage() 
{

}

void Stage::init() 
{
	m_Sprite.init();
}

void Stage::Release() 
{
	m_Sprite.Release();
}

void Stage::Render() {
	m_Sprite.Render();
}

void Stage::FrameMove() {
	if (KeyDown(VK_LEFT) || KeyDown('A') || KeyDown('a'))
	{
		m_Sprite.mPos.x--;
	}

	if (KeyDown(VK_RIGHT) || KeyDown('D') || KeyDown('d'))
	{
		m_Sprite.mPos.x++;
	}

	if (KeyDown(VK_UP) || KeyDown('W') || KeyDown('w'))
	{
		m_Sprite.mPos.y--;
	}

	if (KeyDown(VK_DOWN) || KeyDown('S') || KeyDown('s'))
	{
		m_Sprite.mPos.y++;
	}
}
