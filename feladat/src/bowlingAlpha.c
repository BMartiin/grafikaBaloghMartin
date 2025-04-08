#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <math.h>

#define WIDTH 1200
#define HEIGHT 750
#define PI 3.142857

void drawBrick(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(0.2f, 0.6f, 0.2f);
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    
    // Front face
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    
    // Back face
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    
    // Left face
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    
    // Right face
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    
    // Top face
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    
    // Bottom face
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    
    glEnd();
    glPopMatrix();
}

void drawSphere(float x, float y, float z, float angle) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(angle, 1.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    float radius = 0.3f;
    int stacks = 20;
    int slices = 40;
    
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < stacks; i++) {
        float phi1 = (i * PI) / stacks;
        float phi2 = ((i + 1) * PI) / stacks;
        
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
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Bowling Scene", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    if (!window) {
        fprintf(stderr, "Window error: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        fprintf(stderr, "OpenGL context error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    int running = 1;
    SDL_Event event;
    float angle = 0.0f;

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

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glTranslatef(0.0f, -1.0f, -2.5f);

        drawSphere(0.0f, -0.2f, -0.5f, angle);
        for (int i = -2; i <= 2; i++) {
            drawBrick(i * 0.5f, 0.3f, -3.0f);
        }

        SDL_GL_SwapWindow(window);
        angle += 1.0f;
        SDL_Delay(16);
    }

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
