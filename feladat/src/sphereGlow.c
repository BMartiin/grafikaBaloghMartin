#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <math.h>

#define WIDTH 1000
#define HEIGHT 700
#define PI 3.142857

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Sphere with Glow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
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
    float radius = 0.8f;
    int stacks = 40, slices = 80;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -0.75, 0.75, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;
        }

        glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -2.5f);
        glRotatef(angle, 0.0f, 1.0f, 0.0f);
        
        // Glow effect
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
        glDepthMask(GL_FALSE);
        glColor4f(1.0f, 1.0f, 0.0f, 0.3f);
        float glowRadius = radius * 1.4f;
        
        glBegin(GL_TRIANGLES);
        for (int i = 0; i < stacks; i++) {
            float phi1 = (i * PI) / stacks;
            float phi2 = ((i + 1) * PI) / stacks;
            for (int j = 0; j < slices; j++) {
                float theta1 = (j * 2.0f * PI) / slices;
                float theta2 = ((j + 1) * 2.0f * PI) / slices;

                float x1 = glowRadius * sinf(phi1) * cosf(theta1);
                float y1 = glowRadius * cosf(phi1);
                float z1 = glowRadius * sinf(phi1) * sinf(theta1);

                float x2 = glowRadius * sinf(phi1) * cosf(theta2);
                float y2 = glowRadius * cosf(phi1);
                float z2 = glowRadius * sinf(phi1) * sinf(theta2);

                float x3 = glowRadius * sinf(phi2) * cosf(theta1);
                float y3 = glowRadius * cosf(phi2);
                float z3 = glowRadius * sinf(phi2) * sinf(theta1);

                float x4 = glowRadius * sinf(phi2) * cosf(theta2);
                float y4 = glowRadius * cosf(phi2);
                float z4 = glowRadius * sinf(phi2) * sinf(theta2);

                glVertex3f(x1, y1, z1);
                glVertex3f(x2, y2, z2);
                glVertex3f(x3, y3, z3);
                glVertex3f(x2, y2, z2);
                glVertex3f(x3, y3, z3);
                glVertex3f(x4, y4, z4);
            }
        }
        glEnd();
        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);

        //forgi
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -2.5f); //Hátra tolás
        glRotatef(angle, 0.0f, 1.0f, 2.0f);
        
        // Wireframe Sphere
        float phi, theta;
        float theta_step = (2.0f + PI) / slices;

        glBegin(GL_TRIANGLES);
        for (int i = 0; i < stacks; i++) {
            float phi1 = (i * PI) / stacks;
            float phi2 = ((i + 1) * PI) / stacks;

            // Color cycling: 0 = yellow, 1 = white, 2 = orange
            int colorIndex = i % 3;
            if (colorIndex == 0)
                glColor3f(1.0f, 1.0f, 0.0f); // Yellow
            else if (colorIndex == 1)
                glColor3f(1.0f, 1.0f, 1.0f); // White
            else
                glColor3f(1.0f, 0.5f, 0.0f); // Orange

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

                // Draw the two triangles that make up each quad
                glVertex3f(x1, y1, z1);
                glVertex3f(x2, y2, z2);
                glVertex3f(x3, y3, z3);

                glVertex3f(x2, y2, z2);
                glVertex3f(x3, y3, z3);
                glVertex3f(x4, y4, z4);
            }
        }
        glEnd();
        
        SDL_GL_SwapWindow(window);
        angle += 2.0f;
        SDL_Delay(16);
    }

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
