#include <GL/gl.h>
#include "ground.h"

void drawGroundPlane(float radius, GLuint groundTexture, GLuint wallTexture) {
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

    // Világítás beállításai
    GLfloat lightPos[] = { 0.0f, 5.0f, 5.0f, 1.0f };  // Itt próbálj finomítani a fény pozícióján
    GLfloat lightAmbient[] = { 0.3f, 0.3f, 0.3f, 1.0f }; // Szürkébb ambient fény
    GLfloat lightDiffuse[] = { 0.9f, 0.9f, 0.8f, 1.0f }; // Erősebb difúz fény
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Magas specular fény

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    // Anyagjellemzők – egy fokkal világosabb
    GLfloat matAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat matDiffuse[] = { 0.45f, 0.45f, 0.45f, 1.0f };  // Sötétebb szürke, hogy a fények jobban kiemeljék az árnyékot
    GLfloat matSpecular[] = { 0.6f, 0.6f, 0.6f, 1.0f };
    GLfloat matShininess[] = { 45.0f };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShininess);

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, groundTexture);
    glColor3f(0.9f, 0.9f, 0.9f);  // Majdnem fehér, hogy a fény erősebben érvényesüljön

    float backWallZ = -8.0f;
    float tileRepeat = 8.0f;

    // Padló
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-3.0f, -radius - 0.01f, backWallZ);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(3.0f, -radius - 0.01f, backWallZ);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(3.0f, -radius - 0.01f, 50.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-3.0f, -radius - 0.01f, 50.0f);
    glEnd();

    // Falak
    glBindTexture(GL_TEXTURE_2D, wallTexture);
    float wallRepeat = 8.0f;

    // Bal fal
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-3.0f, -radius - 0.01f, backWallZ);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-3.0f, 3.5f, backWallZ);
    glTexCoord2f(wallRepeat, 1.0f); glVertex3f(-3.0f, 3.5f, 50.0f);
    glTexCoord2f(wallRepeat, 0.0f); glVertex3f(-3.0f, -radius - 0.01f, 50.0f);
    glEnd();

    // Jobb fal
    glBegin(GL_QUADS);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(3.0f, -radius - 0.01f, backWallZ);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(3.0f, 3.5f, backWallZ);
    glTexCoord2f(wallRepeat, 1.0f); glVertex3f(3.0f, 3.5f, 50.0f);
    glTexCoord2f(wallRepeat, 0.0f); glVertex3f(3.0f, -radius - 0.01f, 50.0f);
    glEnd();

    // Tető
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-3.0f, 3.5f, backWallZ);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(3.0f, 3.5f, backWallZ);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(3.0f, 3.5f, 50.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-3.0f, 3.5f, 50.0f);
    glEnd();

    // Hátsó fal
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-3.0f, -radius - 0.01f, backWallZ);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(3.0f, -radius - 0.01f, backWallZ);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(3.0f, 3.5f, backWallZ);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-3.0f, 3.5f, backWallZ);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);
}
