#include "physics.h"
#include <math.h>

#define PI 3.14159265358979323846

// goló mozgásának frissítése
void updateBallPosition(Ball *ball, float dt) {
    ball->x += ball->vx * dt;
    ball->y += ball->vy * dt;
    ball->z += ball->vz * dt;
}

// ütközés ellenőrzése
int checkCollision(Ball *ball, Pin *pin) {
    if (pin->fallen) return 0;

    float dx = ball->x - pin->x;
    float dz = ball->z - pin->z;
    float distance = sqrtf(dx * dx + dz * dz);

    return distance < ball->radius + 0.1f; // ütközési távolság (mintha hitbox méret lenne)
}

// ütközés
void applyCollision(Pin *pin) {
    pin->fallen = 1;
    pin->animating = 1;
    pin->rotationSpeed = (PI / 2.0f)*4.0f;  // gyorsítottam, mert vicces volt
}

// bábú megborulása
void updatePinRotation(Pin *pin, float dt) {
    if (pin->animating) {
        pin->rotation += pin->rotationSpeed * dt;
        if (pin->rotation > PI / 2.0f) { // 90 fok = pi/2 radián
            pin->rotation = PI / 2.0f;
            pin->animating = 0;
        }
    }
}
