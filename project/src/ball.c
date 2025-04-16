#include <GL/gl.h>
#include <math.h>
#include "renderer.h"
#include "ball.h"

void drawSphere(float radius, int stacks, int slices) {
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < stacks; i++) {
        float phi1 = (i * PI) / stacks;
        float phi2 = ((i + 1) * PI) / stacks;

        int colorIndex = i % 3;
        if (colorIndex == 0) glColor3f(1.0f, 1.0f, 0.0f);
        else if (colorIndex == 1) glColor3f(1.0f, 1.0f, 1.0f);
        else glColor3f(1.0f, 0.5f, 0.0f);

        for (int j = 0; j < slices; j++) {
            float theta1 = (j * 2.0f * PI) / slices;
            float theta2 = ((j + 1) * 2.0f * PI) / slices;

            float x1 = radius * sinf(phi1) * cosf(theta1);
            float y1 = radius * cosf(phi1);
            float z1 = radius * sinf(phi1) * sinf(theta1);

            float x2 = radius * sinf(phi1) * cosf(theta2);
            float y2 = radius * cosf(phi1);
            float z2 = radius * sinf(phi1) * sinf(theta2);

            float x3 = radius * sinf(phi2) * cosf(theta1);
            float y3 = radius * cosf(phi2);
            float z3 = radius * sinf(phi2) * sinf(theta1);

            float x4 = radius * sinf(phi2) * cosf(theta2);
            float y4 = radius * cosf(phi2);
            float z4 = radius * sinf(phi2) * sinf(theta2);

            glVertex3f(x1, y1, z1); glVertex3f(x2, y2, z2); glVertex3f(x3, y3, z3);
            glVertex3f(x2, y2, z2); glVertex3f(x3, y3, z3); glVertex3f(x4, y4, z4);
        }
    }
    glEnd();
}
