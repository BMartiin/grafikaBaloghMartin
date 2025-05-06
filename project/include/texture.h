#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/gl.h>

#ifdef __cplusplus
extern "C" {
#endif

// általános ismétlődő textúra betöltése
GLuint loadTexture(const char* filename);

// clamp (a szélén megáll) textúra betöltése
GLuint loadTextureClamp(const char* filename);

#ifdef __cplusplus
}
#endif

#endif // TEXTURE_H
