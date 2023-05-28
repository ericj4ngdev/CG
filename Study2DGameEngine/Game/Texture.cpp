#include "Include.h"

Vector2D Texture::GetSize(){ return m_vSize; }

void Texture::Release()
{
	glDeleteTextures(1, &m_gridTexture);
}