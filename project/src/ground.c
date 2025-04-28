#include <GL/gl.h>
#include "ground.h"

void drawGroundPlane(float radius, GLuint groundTexture, GLuint wallTexture) {
    glEnable(GL_TEXTURE_2D);

    // Padló
    glBindTexture(GL_TEXTURE_2D, groundTexture);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-3.0f, -radius - 0.01f, -100.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(3.0f, -radius - 0.01f, -100.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(3.0f, -radius - 0.01f, 50.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-3.0f, -radius - 0.01f, 50.0f);
    glEnd();

    // Bal fal
    glBindTexture(GL_TEXTURE_2D, wallTexture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-3.0f, -radius - 0.01f, -100.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-3.0f, 3.5f, -100.0f);
    glTexCoord2f(1.0f, 15.0f); glVertex3f(-3.0f, 3.5f, 50.0f);
    glTexCoord2f(0.0f, 15.0f); glVertex3f(-3.0f, -radius - 0.01f, 50.0f);
    glEnd();

    // Jobb fal
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(3.0f, -radius - 0.01f, -100.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(3.0f, 3.5f, -100.0f);
    glTexCoord2f(1.0f, 15.0f); glVertex3f(3.0f, 3.5f, 50.0f);
    glTexCoord2f(0.0f, 15.0f); glVertex3f(3.0f, -radius - 0.01f, 50.0f);
    glEnd();

    // Tető 
    glBindTexture(GL_TEXTURE_2D, wallTexture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-3.0f, 3.5f, -100.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(3.0f, 3.5f, -100.0f);
    glTexCoord2f(1.0f, 15.0f); glVertex3f(3.0f, 3.5f, 50.0f);
    glTexCoord2f(0.0f, 15.0f); glVertex3f(-3.0f, 3.5f, 50.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}
