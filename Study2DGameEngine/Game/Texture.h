#ifndef TEXTURE_H_
#define TEXTURE_H_

class Texture
{
public:
	unsigned char* image;
	GLuint m_gridTexture;
	Vector2D m_vSize;
public:
	Vector2D GetSize();
	void LoadImage(const char *texFile);
	void Release();
	GLuint* GetTexture();
};

#endif