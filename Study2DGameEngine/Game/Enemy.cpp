#include "Include.h"
void Enemy::init() {
	mTransform.mPos = Vector2D(550, 200);		// 초기위치
	mTransform.mSize = Vector2D(50, 50);
	mSprite.m_Texid = NULL;
	mSprite.mColor = Color4f(0.1, 0.1, 0.8, 0.5);
	
	
	mVelo = Vector2D(2, 2);
	gravity = 4;
	OnGround = false;
	OnCollide = false;
	mSprite.loadTexture();
}

void Enemy::Transform()
{
	mSprite.SquareArea(mTransform.mPos, mTransform.mSize);
}

void Enemy::Render()
{
	mSprite.RenderSquare(mTransform.mPos, mTransform.mSize);
}


bool Enemy::Collide(Player other)
{
	return mCollider.Collide(other.mSprite);
}


void Enemy::Move() 
{
	mTransform.mPos.y += gravity;
	mTransform.mPos.x -= mVelo.x;
}
