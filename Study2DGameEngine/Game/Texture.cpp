#define STB_IMAGE_IMPLEMENTATION
#include "Include.h"

Vector2D Texture::GetSize()
{
    return m_vSize;
}


void Texture::LoadImage(const char* texFile)
{
    // LoadMeshFromFile
    GLuint texture;
    int width, height;

    glGenTextures(1, &texture);
    FILE* fp = NULL;
    if (fopen_s(&fp, texFile, "rb"))
    {
        printf("ERROR : No %s. \n fail to bind %d\n", texFile, texture);
        return;
    }

    int channel;
    image = stbi_load_from_file(fp, &width, &height, &channel, 4);
    fclose(fp);

    if (image != NULL) 
    {
        // 상하 반전을 위해 이미지 데이터를 복사하여 처리합니다.
        unsigned char* flippedImage = new unsigned char[width * height * 4];
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                int index = (y * width + x) * 4;
                int flippedIndex = ((height - 1 - y) * width + x) * 4;

                flippedImage[flippedIndex + 0] = image[index + 0];
                flippedImage[flippedIndex + 1] = image[index + 1];
                flippedImage[flippedIndex + 2] = image[index + 2];
                flippedImage[flippedIndex + 3] = image[index + 3];
            }
        }

        glEnable(GL_TEXTURE_2D);
        glGenTextures(1, &m_gridTexture);
        glBindTexture(GL_TEXTURE_2D, m_gridTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, flippedImage);

        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        delete[] flippedImage;
        free(image);
    }
    else printf("Texture Load Fail");

}

void Texture::Release()
{
    glBindTexture(GL_TEXTURE_2D, m_gridTexture);
    glDeleteTextures(1, &m_gridTexture);
}

GLuint* Texture::GetTexture()
{
    if (image != NULL)
        return &m_gridTexture;
    else
        return NULL;
}
