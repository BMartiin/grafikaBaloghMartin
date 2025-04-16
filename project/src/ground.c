#include <GL/gl.h>
#include "ground.h"

void drawGroundPlane(float radius) {
    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex3f(-3.0f, -radius - 0.01f, -100.0f);
    glVertex3f(3.0f, -radius - 0.01f, -100.0f);
    glVertex3f(3.0f, -radius - 0.01f, 50.0f);
    glVertex3f(-3.0f, -radius - 0.01f, 50.0f);
    glEnd();
}
