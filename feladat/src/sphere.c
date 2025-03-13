#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <math.h>

#define WIDTH 900
#define HEIGHT 600
#define COLOR_WHITE 0xffffffff
#define PI 3.142857

int main(int argc, char *argv[]){

    //Ablak inicializálása + hibaüzi
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL hiba: %s\n", SDL_GetError());
        return -1;
    }

    //az ablak:
    SDL_Window* window = SDL_CreateWindow("feladatAlpha1_gomb", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    if (!window) {
        fprintf(stderr, "Ablak hiba: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    
    // Context:
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        fprintf(stderr, "OpenGL kontextusos hiba: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    int running = 1;
    SDL_Event event;
    float angle = 0.0f;

    //3D rendereléshez kell
    glEnable(GL_DEPTH_TEST);

    //glFrustum használatával perspektíva megadása
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -0.75, 0.75, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);

    while(running){
        //Ez azért kell, ha valaki útközbe bezárja vagy vmi
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        //háttér:
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //forgatás:
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -2.5f); //Hátra tolás
        glRotatef(angle, 0.0f, 1.0f, 2.0f); //függőleges forgatás

        //bele nézel a gömbbe?

        float radius = 0.7f;
        int stacks = 40;
        int slices = 80;
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
        angle += 0.05f;
        //kb 60fps
        SDL_Delay(16);
    }

    //5mp bezárás előtt
    //SDL_Delay(5000);

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}