#ifndef WEAPON_H_
#define WEAPON_H_
class cWeapon : public cObject
{
public:
	Sprite mSprite;
	Collider mCollider;
private:
	float length;
};

#endif
