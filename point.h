#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

typedef struct {
    float x;
    float y;
    float z;
    float w;
} point;


point* creer_point(float x, float y, float z);

float getX(point* p);
float getY(point* p);
float getZ(point* p);
float getW(point* p);


void setX(point* p, float x);
void setY(point* p, float y);
void setZ(point* p, float z);

float** polygone(point** poly, int nb_point);

point* detruire_point(point* p);

#endif
