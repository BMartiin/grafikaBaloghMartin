#include <GL/gl.h>
#include "pin.h"

void drawPin(float x, float y, float z, GLuint pinTexture) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(0.2f, 0.6f, 0.2f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, pinTexture);
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);

    // Előlap
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f,  0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, -0.5f,  0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f,  0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f,  0.5f);

    // Hátlap
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f, -0.5f);

    // Bal oldal
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f,  0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f,  0.5f,  0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f, -0.5f);

    // Jobb oldal
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f,  0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f,  0.5f,  0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f,  0.5f, -0.5f);

    // Tető
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, 0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f, 0.5f,  0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f,  0.5f);

    // Alap
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f, -0.5f,  0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f,  0.5f);

    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
