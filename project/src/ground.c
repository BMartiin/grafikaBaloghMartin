#include <GL/gl.h>
#include "ground.h"

void drawGroundPlane(float radius, GLuint groundTexture, GLuint wallTexture, GLuint backWallTexture, GLuint ceilingTexture) {
    //ez a rész a fényforrás meg árnyék meg ilyenek miatt kell
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

    // fényforrás beállítása
    GLfloat lightPos[] = { 0.0f, 5.0f, 5.0f, 1.0f };
    GLfloat lightAmbient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat lightDiffuse[] = { 0.9f, 0.9f, 0.8f, 1.0f };
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    GLfloat matAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat matDiffuse[] = { 0.45f, 0.45f, 0.45f, 1.0f };
    GLfloat matSpecular[] = { 0.6f, 0.6f, 0.6f, 1.0f };
    GLfloat matShininess[] = { 45.0f };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShininess);

    glEnable(GL_TEXTURE_2D);

    //hátsó fal helye, pálya vége
    float backWallZ = -8.0f;

    // padló
    glBindTexture(GL_TEXTURE_2D, groundTexture);
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-3.0f, -radius - 0.01f, backWallZ);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(3.0f, -radius - 0.01f, backWallZ);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(3.0f, -radius - 0.01f, 4.1f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-3.0f, -radius - 0.01f, 4.1f);
    glEnd();

    // oldalfalak
    glBindTexture(GL_TEXTURE_2D, wallTexture);
    float wallRepeat = 8.0f; // textúra ismétlődése

    // bal fal
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-3.0f, -radius - 0.01f, backWallZ);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-3.0f, 3.5f, backWallZ);
    glTexCoord2f(wallRepeat, 0.0f); glVertex3f(-3.0f, 3.5f, 50.0f);
    glTexCoord2f(wallRepeat, 1.0f); glVertex3f(-3.0f, -radius - 0.01f, 50.0f);
    glEnd();

    // jobb fal
    glBegin(GL_QUADS);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(3.0f, -radius - 0.01f, backWallZ);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(3.0f, 3.5f, backWallZ);
    glTexCoord2f(wallRepeat, 0.0f); glVertex3f(3.0f, 3.5f, 50.0f);
    glTexCoord2f(wallRepeat, 1.0f); glVertex3f(3.0f, -radius - 0.01f, 50.0f);
    glEnd();


    // plafon
    glBindTexture(GL_TEXTURE_2D, ceilingTexture);
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f);  // lefelé néz
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-3.0f, 3.5f, backWallZ);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(3.0f, 3.5f, backWallZ);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(3.0f, 3.5f, 4.1f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-3.0f, 3.5f, 4.1f);
    glEnd();


    // hátsó fal, nem ismétlődik a textúra
    
    glBindTexture(GL_TEXTURE_2D, backWallTexture);
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
