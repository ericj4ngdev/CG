#ifndef BACKGR_H_
#define BACKGR_H_	
class BackGround : public Sprite
{
public:
	void initTexture(const char* name) override;
	void Transform() override;
	void Render() override;
};
#endif
