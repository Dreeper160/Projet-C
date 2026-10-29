#ifndef _ENTITE_H_
#define _ENTITE_H_

typedef struct{
    float x;
    float y;
}position;

typedef struct{
    int est_en_vie;
    position pos;
}entite;
#endif