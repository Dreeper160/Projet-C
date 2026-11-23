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
    int direction;        /* 0 = Haut, 1 = Bas, 2 = Gauche, 3 = Droite */ 
    int en_mouvement;     /* 0 = arrêt, 1 = marche */
    int frame_actuelle;   /* quelle image de l'animation jouer */
    int vitesse_anim;
}entite;
#endif