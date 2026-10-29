#include "constante.h"
#include "bombe.h"

void afficher_bombe(bombe bombe)
{

    int centre_x = bombe.b.pos.x;
    int centre_y = bombe.b.pos.y;

    MLV_draw_filled_circle(centre_x, centre_y, (TAILLE_CASE / 2) - 4, MLV_COLOR_BLACK);
}

void placer_bombe(bombe *bom, entite j)
{
    bom->b = j;
    bom->b.pos.x = ((int)(j.pos.x / TAILLE_CASE) * TAILLE_CASE) + (TAILLE_CASE / 2.0);
    bom->b.pos.y = ((int)(j.pos.y / TAILLE_CASE) * TAILLE_CASE) + (TAILLE_CASE / 2.0);
    bom->b.est_en_vie = 1;

    clock_gettime(CLOCK_MONOTONIC, &bom->temps_pose); /* mémorise l’heure de pose */
}
/*timespec contient
    *tv_sec :secondes
    tv_nsec: Nano secondes */
int bombe_expiree(bombe *b)
{ /*Recuperation du temps actuel */
    struct timespec now;

    clock_gettime(CLOCK_MONOTONIC, &now);
    /*Les nano secondes passé sont utilisé pour L'EXACTITUDE de du calcul de secondes passé pour eviter les bypass*/
    double secondes = (now.tv_sec - b->temps_pose.tv_sec) + (now.tv_nsec - b->temps_pose.tv_nsec) / 1e9;
    if (secondes >= T_MAX)
    {
        b->b.est_en_vie = 0; /*"tue" la bombe */
        return 1;
    }
    return 0;
}