#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <stdio.h>
#include "texture.h"

GLuint loadTexture(const char* filename) {
    SDL_Surface* surface = IMG_Load(filename);
    if (!surface) {
        fprintf(stderr, "Nem sikerült betölteni a képet: %s\n", IMG_GetError());
        return 0;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    GLenum format = (surface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, format,
                 surface->w, surface->h, 0,
                 format, GL_UNSIGNED_BYTE, surface->pixels);

    // 🔁 Ismétlődő wrap mód beállítása
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // 🔍 Szűrési mód beállítása
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SDL_FreeSurface(surface);
    return textureID;
}

