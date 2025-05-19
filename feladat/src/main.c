#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>

#include "renderer.h"
#include "pin.h"
#include "ball.h"
#include "ground.h"
#include "physics.h"
#include "texture.h"
#include "lightbulp.h"

#define NUM_PINS 10

// játék állapotok
typedef enum {
    STATE_AIMING,
    STATE_RUNNING
} GameState;

GLuint ballTexture;
GLuint groundTexture;
GLuint wallTexture;
GLuint pinTexture;
GLuint backWallTexture;
GLuint ceilingTexture;
GLuint lightbulpTexture;

Ball ball;
Pin pins[NUM_PINS];
GameState gameState = STATE_AIMING;

int followBall = 0;  // kamera mód: 0 = statikus, 1 = követi a golyót

// a játék elején a golyó helyzete és sebessége
void resetBallPosition(Ball* b) {
    b->x = 0.0f;
    b->y = 0.0f;
    b->z = 4.0f;
    b->vx = 0.0f;
    b->vy = 0.0f;
    b->vz = 0.0f;
}

//billentyűkezelés
void handleInput(SDL_Event event, Ball* b, GameState* state) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_a:
                if (*state == STATE_AIMING && b->x > -1.0f)
                    b->x -= 0.2f;
                break;
            case SDLK_d:
                if (*state == STATE_AIMING && b->x < 1.0f)
                    b->x += 0.2f;
                break;
            case SDLK_RETURN:
                if (*state == STATE_AIMING) {
                    b->vz = -2.0f;
                    *state = STATE_RUNNING;
                }
                break;
            case SDLK_SPACE:
                followBall = !followBall;
                break;
        }
    }
}

// bábúk helyének inicializálása
void initPins() {
    int layout[] = {4, 3, 2, 1};
    int index = 0;
    float startZ = -6.0f;
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

// gömb kirajzolása árnyékkal
void drawBallForShadow() {
    glPushMatrix();
    glTranslatef(ball.x, ball.y, ball.z);
    drawSphere(ball.radius, 20, 40, 0, 0);
    glPopMatrix();
}

// -------- Fővezér -----------
int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL hiba: %s\n", SDL_GetError());
        return -1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        fprintf(stderr, "SDL_image nem inicializálható: %s\n", IMG_GetError());
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Bowling", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    if (!window) return -1;

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) return -1;

    //textúrák betöltése
    ballTexture = loadTexture("assets/ball1.png");
    groundTexture = loadTexture("assets/padlo_textura.jpg");
    wallTexture = loadTexture("assets/fal_textura.jpg");
    pinTexture = loadTexture("assets/pin1.jpg");
    backWallTexture = loadTextureClamp("assets/fal_2_textura.jpg");
    ceilingTexture = loadTexture("assets/plafon_textura.jpg");
    lightbulpTexture = loadTexture("assets/lampa_textura.jpg");  
    setLightbulpTexture(lightbulpTexture);

    if (ballTexture == 0 || groundTexture == 0 || wallTexture == 0 || pinTexture == 0 || backWallTexture == 0 || ceilingTexture == 0) {
        fprintf(stderr, "Egy vagy tobb textura betoltese sikertelen.\n");
        return -1;
    }

    initPins();
    resetBallPosition(&ball);
    ball.radius = 0.2f;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)WIDTH / (double)HEIGHT, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);

    // világítás beállítása
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // világítás pozíciója és színe
    GLfloat lightPos[] = { 0.0f, 3.0f, 3.0f, 1.0f };
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat lightDiffuse[] = { 2.0f, 2.0f, 2.0f, 1.0f };
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    float angle1 = 0.0f;
    float distanceTraveled = 0.0f;
    const float radius = ball.radius;
    const int stacks = 40;
    const int slices = 80;

    float cameraZ = 6.2f;  // dinamikus kamera z-koordináta

    //futunk
    int running = 1;
    while (running) {
        float deltaTime = 0.016f; // 60 FPS

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;
            handleInput(event, &ball, &gameState);
        }

        if (gameState == STATE_RUNNING) {
            updateBallPosition(&ball, deltaTime);
            for (int i = 0; i < NUM_PINS; ++i) {
                if (!pins[i].fallen && checkCollision(&ball, &pins[i])) {
                    applyCollision(&pins[i]);
                }
            }

            for (int i = 0; i < NUM_PINS; ++i) {
                updatePinRotation(&pins[i], deltaTime);
            }

            distanceTraveled += ball.vz * deltaTime;
            angle1 = distanceTraveled / radius * (180.0f / PI);

            float targetZ = ball.z + 2.2f;
            if (followBall && targetZ < cameraZ && ball.z > -1.0f) {
                cameraZ = targetZ;
            }
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        gluLookAt(0.0f, 2.5f, cameraZ,
                  0.0f, 0.0f, cameraZ - 6.0f,
                  0.0f, 1.0f, 0.0f); // kamera pozíciója

        drawLightbulbAndShadow(drawBallForShadow);

        glPushMatrix();
        glTranslatef(ball.x, ball.y, ball.z);
        if (gameState == STATE_RUNNING) {
            glRotatef(angle1, 1.0f, 0.0f, 0.0f);
        }
        drawSphere(radius, stacks, slices, ballTexture, 1);
        glPopMatrix();

        for (int i = 0; i < NUM_PINS; ++i) {
            glPushMatrix();
            glTranslatef(pins[i].x, pins[i].y, pins[i].z);
            if (pins[i].fallen || pins[i].animating) {
                glRotatef(pins[i].rotation * (180.0f / PI), 1.0f, 0.0f, 0.0f);
            }
            drawPin(0.0f, 0.0f, 0.0f, pinTexture);
            glPopMatrix();
        }

        drawGroundPlane(radius, groundTexture, wallTexture, backWallTexture, ceilingTexture);

        SDL_GL_SwapWindow(window);
        SDL_Delay(16);
    }

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
