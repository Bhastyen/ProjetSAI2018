#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

typedef struct {
    float x;
    float y;
    float z;
    float w;
} point;


point* creer_point(float x, float y, float z);

/*Fonction :point* creer_point_angle(float teta,float phy,float rayon);
Genere un point en fonction de deux angle

*/
point* creer_point_angle_pos(float teta,float phy,float rayon,point* position);

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
