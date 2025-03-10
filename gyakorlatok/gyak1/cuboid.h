#ifndef CUBOID_H
#define CUBOID_H

/**
 * Data of a circle object in Descartes coordinate system
 */
typedef struct Cube
{
	double x;
	double y;
	double z;
} Cube;

/**
 * Set the data of the circle
 */
void set_cube_size(Cube* cube, double x, double y, double z);

double calc_cube_volume(Cube* cube, double x, double y, double z);

double calc_cube_surface(Cube* cube, double x, double y, double z);

int cube_has_square_side(Cube* cube, double x, double y, double z);

/**
 * Calculate the area of the circle.
 */

#endif // CIRCLE_H