#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 160
#define WIDTH 40
#define RADIAN 3.142/180

float X, Y, Z;
float scale_const = 40;
float focal = 100;
float cube_size = 20;

int buffer_2d[LENGTH * WIDTH];

float x_pos(float x, float y, float z) {
    return x * (cos(X) * cos(Y)) +
           y * (cos(X) * sin(Y) * sin(Z) - sin(X) * cos(Z)) +
           z * (cos(X) * sin(Y) * cos(Z) + sin(X) * sin(Z));
}

float y_pos(float x, float y, float z) {
    return x * (sin(X) * cos(Y)) +
           y * (sin(X) * sin(Y) * sin(Z) + cos(X) * cos(Z)) +
           z * (sin(X) * sin(Y) * cos(Z) - cos(X) * sin(Z));
}

float z_pos(float x, float y, float z) {
    return x * (-sin(Y)) +
           y * (cos(Y) * sin(Z)) +
           z * (cos(Y) * cos(Z));
}

void translate_point(float cube_x, float cube_y, float cube_z) {
    float x = x_pos(cube_x, cube_y, cube_z);
    float y = y_pos(cube_x, cube_y, cube_z);
    float z = z_pos(cube_x, cube_y, cube_z) + focal;

    float ooz = 1.0f/z;

    int xp = (int)(LENGTH/2 + scale_const * x * ooz * 2);
    int yp = (int)(WIDTH/2 + scale_const * y * ooz);

    buffer_2d[xp + LENGTH * yp] = 1;
}

int main(int argc, char* argv[]) {
    X = atoi(argv[1]) * RADIAN;
    Y = atoi(argv[2]) * RADIAN;
    Z = atoi(argv[3]) * RADIAN;

    for (float cube_x = -cube_size; cube_x < cube_size; cube_x++) {
        for (float cube_y = -cube_size; cube_y < cube_size; cube_y++) {
            for (float cube_z = -cube_size; cube_z < cube_size; cube_z++) {
                translate_point(cube_x, cube_y, cube_z);
            }
        }
    }

    for (int j = 0; j < WIDTH; j++) {
        for (int i = 0; i < LENGTH; i++) {
            if (buffer_2d[i + LENGTH * j]) {
                printf("#");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }

    return 0;
}
