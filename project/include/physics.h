#ifndef PHYSICS_H
#define PHYSICS_H

typedef struct {
    float x, y, z;
    float vx, vy, vz;
    float radius;
} Ball;

typedef struct {
    float x, y, z;
    int fallen;
} Pin;

void updateBallPosition(Ball *ball, float dt);
int checkCollision(Ball *ball, Pin *pin);
void applyCollision(Pin *pin);

#endif
