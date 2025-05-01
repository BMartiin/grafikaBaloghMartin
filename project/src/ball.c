#include <GL/gl.h>
#include <math.h>
#include "renderer.h"
#include "ball.h"


void drawSphere(float radius, int stacks, int slices, unsigned int texture, int forceColor) {
    int textured = (texture != 0);

    glPushMatrix();

    if (textured) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    }

    // 🔧 Csak akkor állítsunk be színt, ha kifejezetten kérjük
    if (forceColor) {
        if (textured)
            glColor3f(1.0f, 1.0f, 1.0f);
        else
            glColor3f(1.0f, 0.0f, 0.0f);  // ha nincs textúra, piros
    }

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

            if (textured) glTexCoord2f((float)j / slices, (float)i / stacks);
            glNormal3f(x1, y1, z1);
            glVertex3f(radius * x1, radius * y1, radius * z1);

            if (textured) glTexCoord2f((float)j / slices, (float)(i + 1) / stacks);
            glNormal3f(x2, y2, z2);
            glVertex3f(radius * x2, radius * y2, radius * z2);
        }
        glEnd();
    }

    if (textured) glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

