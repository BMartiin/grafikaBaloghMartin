#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "renderer.h"
#include "pin.h"
#include "ball.h"
#include "ground.h"
#include "physics.h"

#define NUM_PINS 10

Ball ball = {
    .x = 0.0f, .y = 0.0f, .z = 3.0f,   // indulási pozíció
    .vx = 0.0f, .vy = 0.0f, .vz = -4.0f, // előrefelé gurul
    .radius = 0.2f
};

Pin pins[NUM_PINS];

void initPins() {
    // 1-2-3-4 elrendezés (háromszög)
    int layout[] = {4, 3, 2, 1};
    int index = 0;
    float startZ = -4.0f;
    for (int row = 0; row < 4; ++row) {
        int count = layout[row];
        float offset = -(count - 1) * 0.25f;
        for (int i = 0; i < count; ++i) {
            if (index >= NUM_PINS) break;
            pins[index].x = offset + i * 0.5f;
            pins[index].z = startZ + row * 0.5f;
            pins[index].y = 0.0f;
            pins[index].fallen = 0;
            index++;
        }
    }
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL hiba: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("bowling", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    if (!window) return -1;

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) return -1;

    initPins();
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.5, 1.5, -1.0, 1.0, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);

    float angle1 = 0.0f;
    const float radius = ball.radius;
    const int stacks = 40;
    const int slices = 80;
    float distanceTraveled = 0.0f;

    int running = 1;
    while (running) {
        float deltaTime = 0.016f; // kb. 60 FPS

        // Fizika frissítés
        updateBallPosition(&ball, deltaTime);
        for (int i = 0; i < NUM_PINS; ++i) {
            if (!pins[i].fallen && checkCollision(&ball, &pins[i])) {
                applyCollision(&pins[i]);
            }
        }

        // Eseménykezelés
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;
        }

        // Kirajzolás
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glTranslatef(0.0f, -1.0f, -3.0f);

        distanceTraveled += ball.vz * deltaTime;
        angle1 = distanceTraveled / radius * (180.0f / PI);

        // Golyó kirajzolása
        glPushMatrix();
        glTranslatef(ball.x, ball.y, ball.z);
        glRotatef(angle1, 1.0f, 0.0f, 0.0f);
        drawSphere(radius, stacks, slices);
        glPopMatrix();

        // Bábuk kirajzolása
        for (int i = 0; i < NUM_PINS; ++i) {
            if (!pins[i].fallen) {
                drawPin(pins[i].x, pins[i].y, pins[i].z);
            }
        }

        drawGroundPlane(radius);

        SDL_GL_SwapWindow(window);
        SDL_Delay(16);
    }

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
