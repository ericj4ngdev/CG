#ifndef OBJECT_H_
#define OBJECT_H_
class cObject
{
private:
	

// ������Ʈ
public:
	Transform mTransform;
	Sprite mSprite;
	Collider mCollider;
	// virtual bool Collide(cObject* other) = 0;
};

#endif