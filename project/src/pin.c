#include <GL/gl.h>
#include "pin.h"

void drawPin(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(0.2f, 0.6f, 0.2f);
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);

    // Előlap
    glVertex3f(-0.5f, -0.5f, 0.5f); glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f,  0.5f, 0.5f); glVertex3f(-0.5f, 0.5f, 0.5f);
    // Hátlap
    glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f,  0.5f, -0.5f); glVertex3f(-0.5f, 0.5f, -0.5f);
    // Oldalak
    glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f,  0.5f, 0.5f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f); glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f,  0.5f, 0.5f); glVertex3f(0.5f, 0.5f, -0.5f);
    // Tető és alj
    glVertex3f(-0.5f, 0.5f, -0.5f); glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f,  0.5f, 0.5f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f,  -0.5f, 0.5f); glVertex3f(-0.5f, -0.5f, 0.5f);

    

    glEnd();
    glPopMatrix();
}
