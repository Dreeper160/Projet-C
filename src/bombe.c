#include "constante.h"
#include "bombe.h"

void afficher_bombe(bombe bombe)
{

    int centre_x = bombe.b.pos.x;
    int centre_y = bombe.b.pos.y;

    MLV_draw_filled_circle(centre_x, centre_y, (TAILLE_CASE / 2) - 4, MLV_COLOR_BLACK);
}

void placer_bombe(bombe *b, entite j)
{
    b->b = j;
    b->b.pos.x = ((int)(j.pos.x / TAILLE_CASE) * TAILLE_CASE) + (TAILLE_CASE / 2.0);
    b->b.pos.y = ((int)(j.pos.y / TAILLE_CASE) * TAILLE_CASE) + (TAILLE_CASE / 2.0);
    b->b.est_en_vie = 1;
}
