#include "physics.h"
#include <math.h>

void updateBallPosition(Ball *ball, float dt) {
    ball->x += ball->vx * dt;
    ball->y += ball->vy * dt;
    ball->z += ball->vz * dt;
}

int checkCollision(Ball *ball, Pin *pin) {
    if (pin->fallen) return 0;

    float dx = ball->x - pin->x;
    float dz = ball->z - pin->z;
    float distance = sqrtf(dx * dx + dz * dz);

    return distance < ball->radius + 0.1f; // egyszerű ütközési távolság
}

void applyCollision(Pin *pin) {
    pin->fallen = 1;
}
