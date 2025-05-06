#ifndef GROUND_H
#define GROUND_H

#include <GL/gl.h>

// padló, falak és plafon rajzolása különböző textúrákkal
void drawGroundPlane(float radius, GLuint groundTexture, GLuint wallTexture, GLuint backWallTexture, GLuint ceilingTexture);

#endif
