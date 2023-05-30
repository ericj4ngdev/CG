#ifndef TEXTURE_H_
#define TEXTURE_H_

#pragma comment(lib,"FreeImage.lib")
#include "FreeImage.h"
#include "FreeImageLoader.h"

class Texture
{	
	FreeImage mLoader;
	FIBITMAP *Load;
	GLuint m_gridTexture;
	Vector2D m_vSize;

public:
	Vector2D GetSize();
	void Release();
	GLuint* GetTexture();
};

#endif