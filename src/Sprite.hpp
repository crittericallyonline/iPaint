#ifndef SPRITE_HPP
#define SPRITE_HPP

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

class Sprite
{
private:
    GLuint id;
public:
    int width, height, channels;
    Sprite(const char *source);
    ~Sprite();
};

Sprite::Sprite(const char *source)
{
    glGenTextures(1, &id);
    unsigned char* pixel_data = stbi_load(source, &width, &height, &channels, STBI_rgb_alpha);

    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

    if (channels == 4)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel_data);
    }
    else {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixel_data);
    }


    glBindTexture(GL_TEXTURE_2D, 0);
    free(pixel_data);
}

Sprite::~Sprite()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    if(id > 0)
    {
        glDeleteTextures(1, &id);
        id = 0;
    }
}

#endif // SPRITE_HPP