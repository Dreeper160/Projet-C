#ifndef _ENTITE_H_
#define _ENTITE_H_
#include <MLV/MLV_all.h>

typedef struct{
    float x;
    float y;
}position;

typedef struct{
    int est_en_vie;
    position pos;
}entite;
#endif