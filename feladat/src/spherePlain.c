#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <math.h>

#define WIDTH 1200
#define HEIGHT 750
#define COLOR_WHITE 0xffffffff
#define PI 3.142857

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL hiba: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("feladatAlpha1_gomb", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    if (!window) {
        fprintf(stderr, "Ablak hiba: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        fprintf(stderr, "OpenGL kontextusos hiba: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    int running = 1;
    SDL_Event event;
    float angle1 = 0.0f;  // Angle for the first sphere
    float angle2 = 0.0f;  // Angle for the second sphere

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.5, 1.5, -1.0, 1.0, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glLoadIdentity();
        glTranslatef(0.0f, -1.0f, -3.0f); // Slightly higher camera angle, closer view

        // First sphere
        glPushMatrix();
        glTranslatef(-2.0f, 0.0f, 0.0f); // Bring the sphere closer
        glRotatef(angle1, 1.0f, 1.0f, 0.0f);  // Rotate the first sphere around the Y-axis
        float radius = 0.3f;
        int stacks = 40;
        int slices = 80;
        glBegin(GL_TRIANGLES);
        for (int i = 0; i < stacks; i++) {
            float phi1 = (i * PI) / stacks;
            float phi2 = ((i + 1) * PI) / stacks;
            int colorIndex = i % 3;
            if (colorIndex == 0)
                glColor3f(1.0f, 1.0f, 0.0f);
            else if (colorIndex == 1)
                glColor3f(1.0f, 1.0f, 1.0f);
            else
                glColor3f(1.0f, 0.5f, 0.0f);

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
                glVertex3f(x1, y1, z1);
                glVertex3f(x2, y2, z2);
                glVertex3f(x3, y3, z3);
                glVertex3f(x2, y2, z2);
                glVertex3f(x3, y3, z3);
                glVertex3f(x4, y4, z4);
            }
        }
        glEnd();
        glPopMatrix();
        
        // Second sphere (now moving independently)
        glPushMatrix();
        glTranslatef(2.0f, 0.0f, 0.0f); // Bring the second sphere closer
        glRotatef(angle2, 1.0f, 1.0f, 0.0f);  // Rotate the second sphere around the Y-axis
        glBegin(GL_TRIANGLES);
        for (int i = 0; i < stacks; i++) {
            float phi1 = (i * PI) / stacks;
            float phi2 = ((i + 1) * PI) / stacks;
            int colorIndex = i % 3;
            if (colorIndex == 0)
                glColor3f(1.0f, 1.0f, 0.0f);
            else if (colorIndex == 1)
                glColor3f(1.0f, 1.0f, 1.0f);
            else
                glColor3f(1.0f, 0.5f, 0.0f);

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
                glVertex3f(x1, y1, z1);
                glVertex3f(x2, y2, z2);
                glVertex3f(x3, y3, z3);
                glVertex3f(x2, y2, z2);
                glVertex3f(x3, y3, z3);
                glVertex3f(x4, y4, z4);
            }
        }
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.0f, 0.0f, -3.0f); // Bring the second sphere closer
        glRotatef(angle2, 1.0f, 1.0f, 0.0f);  // Rotate the second sphere around the Y-axis
        glBegin(GL_TRIANGLES);
        for (int i = 0; i < stacks; i++) {
            float phi1 = (i * PI) / stacks;
            float phi2 = ((i + 1) * PI) / stacks;
            int colorIndex = i % 3;
            if (colorIndex == 0)
                glColor3f(1.0f, 1.0f, 0.0f);
            else if (colorIndex == 1)
                glColor3f(1.0f, 1.0f, 1.0f);
            else
                glColor3f(1.0f, 0.5f, 0.0f);

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
                glVertex3f(x1, y1, z1);
                glVertex3f(x2, y2, z2);
                glVertex3f(x3, y3, z3);
                glVertex3f(x2, y2, z2);
                glVertex3f(x3, y3, z3);
                glVertex3f(x4, y4, z4);
            }
        }
        glEnd();
        glPopMatrix();

        // Plane under the spheres
        glBegin(GL_QUADS);
        glColor3f(0.3f, 0.3f, 0.3f);
        glVertex3f(-3.0f, -radius - 0.01f, -100.0f);
        glVertex3f(3.0f, -radius - 0.01f, -100.0f);
        glVertex3f(3.0f, -radius - 0.01f, 50.0f);
        glVertex3f(-3.0f, -radius - 0.01f, 50.0f);
        glEnd();

        SDL_GL_SwapWindow(window);

        angle1 += 1.0f;  // Increment the angle for the first sphere
        angle2 += 1.5f;  // Increment the angle for the second sphere (faster rotation)

        SDL_Delay(16);
    }

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
