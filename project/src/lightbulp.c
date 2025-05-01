#include <GL/gl.h>
#include <math.h>
#include "lightbulp.h"

#define PI 3.14159265358979323846

// Árnyékmátrix kiszámítása
static void computeShadowMatrix(GLfloat shadowMat[16], const GLfloat lightPos[4], const GLfloat groundPlane[4]) {
    GLfloat dot = groundPlane[0] * lightPos[0] +
                  groundPlane[1] * lightPos[1] +
                  groundPlane[2] * lightPos[2] +
                  groundPlane[3] * lightPos[3];

    shadowMat[0] = dot - lightPos[0] * groundPlane[0];
    shadowMat[1] = -lightPos[1] * groundPlane[0];
    shadowMat[2] = -lightPos[2] * groundPlane[0];
    shadowMat[3] = -lightPos[3] * groundPlane[0];
    shadowMat[4] = -lightPos[0] * groundPlane[1];
    shadowMat[5] = dot - lightPos[1] * groundPlane[1];
    shadowMat[6] = -lightPos[2] * groundPlane[1];
    shadowMat[7] = -lightPos[3] * groundPlane[1];
    shadowMat[8] = -lightPos[0] * groundPlane[2];
    shadowMat[9] = -lightPos[1] * groundPlane[2];
    shadowMat[10] = dot - lightPos[2] * groundPlane[2];
    shadowMat[11] = -lightPos[3] * groundPlane[2];
    shadowMat[12] = -lightPos[0] * groundPlane[3];
    shadowMat[13] = -lightPos[1] * groundPlane[3];
    shadowMat[14] = -lightPos[2] * groundPlane[3];
    shadowMat[15] = dot - lightPos[3] * groundPlane[3];
}

// Gömb kirajzolása
static void drawSphere(float radius, int stacks, int slices) {
    for (int i = 0; i < stacks; i++) {
        float phi1 = (i * PI) / stacks;
        float phi2 = ((i + 1) * PI) / stacks;

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= slices; j++) {
            float theta = (j * 2.0f * PI) / slices;

            float x1 = sinf(phi1) * cosf(theta);
            float y1 = cosf(phi1);
            float z1 = sinf(phi1) * sinf(theta);

            float x2 = sinf(phi2) * cosf(theta);
            float y2 = cosf(phi2);
            float z2 = sinf(phi2) * sinf(theta);

            glNormal3f(x1, y1, z1);
            glVertex3f(radius * x1, radius * y1, radius * z1);

            glNormal3f(x2, y2, z2);
            glVertex3f(radius * x2, radius * y2, radius * z2);
        }
        glEnd();
    }
}

// Fényforrás és árnyék kirajzolása
void drawLightbulbAndShadow(void (*drawObject)()) {
    GLfloat lightPos[] = { -2.0f, 3.5f, -2.0f, 1.0f };
    GLfloat spotDir[] = { 0.3f, -1.0f, -0.3f };

    GLfloat lightAmbient[]  = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat lightDiffuse[]  = { 0.85f, 0.85f, 0.5f, 1.0f };
    GLfloat lightSpecular[] = { 1.2f, 1.2f, 1.0f, 1.0f };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0f);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 5.0f);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Fényforrás gömb
    glPushMatrix();
    glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 0.6f);
    drawSphere(0.5f, 30, 30);
    glEnable(GL_LIGHTING);
    glPopMatrix();

    // Árnyék
    GLfloat groundPlane[4] = { 0.0f, 1.0f, 0.0f, 0.0f };
    GLfloat shadowMat[16];
    computeShadowMatrix(shadowMat, lightPos, groundPlane);

    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);
    glColor4f(0.0f, 0.0f, 0.0f, 0.9f); // Árnyék színe és átlátszóság

    glPushMatrix();
    glTranslatef(0.0f, -0.2f, 0.0f);
    glMultMatrixf(shadowMat);
    drawObject();
    glPopMatrix();

    glEnable(GL_LIGHTING);
}
