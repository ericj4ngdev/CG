#ifndef TEXTURE_H_
#define TEXTURE_H_

class Texture
{	
	GLuint m_gridTexture;
	Vector2D m_vSize;

public:
	Vector2D GetSize();
	void Release();
};

#endif