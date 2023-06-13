#ifndef TEXTURE_H_
#define TEXTURE_H_

#pragma comment(lib,"Freeimage/FreeImage.lib")
#include "Freeimage/FreeImage.h"
#include "Freeimage/FreeImageLoader.h"

class Texture
{
public:
	FreeImage m_Loader;
	// FIBITMAP* Load;
	GLuint m_gridTexture;
	Vector2D m_vSize;

public:
	
	Vector2D GetSize();
	// void LoadImage(const char* filename);
	void Release();
	GLuint* GetTexture();
};

#endif