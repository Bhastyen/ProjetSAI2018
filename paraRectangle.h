#ifndef PARARECTANGLE_H_INCLUDED
#define PARARECTANGLE_H_INCLUDED

#include "point.h"

typedef struct para{
    point* pos;
    point* t_aretes;
} para;


para* creer_para(float x, float y, float z, float tx, float ty, float tz);
void draw_para(para* p);

#endif
