#ifndef _ENTITE_H
#define _JOUEUR_H_

typedef struct
{
    float x;
    float y;
} position;

typedef struct
{
    int sante;
    position postion;
} entite;

#endif