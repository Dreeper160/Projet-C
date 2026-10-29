#ifndef BOMBE_H
#define BOMBE_H
#define T_MAX 20
#include <time.h>
#include "constante.h"
#include "entite.h"

typedef struct
{
    entite b;
    int rayon;
    struct timespec temps_pose;
} bombe;

typedef struct
{
    entite explo;
    struct timespec temps_apparition;
} explosion;
void afficher_bombe(bombe bombe);
void placer_bombe(bombe *b, entite j);

#endif