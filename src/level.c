#include "constante.h"
#include "level.h"

int map[LIGNES][COLONNES] = {
                            {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                            {2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 2},
                            {2, 0, 2, 1, 2, 1, 2, 0, 2, 1, 2, 1, 2, 0, 2},
                            {2, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 2},
                            {2, 1, 2, 0, 2, 0, 2, 1, 2, 0, 2, 0, 2, 1, 2},
                            {2, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 2},
                            {2, 0, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 0, 2},
                            {2, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 2},
                            {2, 0, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 0, 2},
                            {2, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 2},
                            {2, 1, 2, 0, 2, 0, 2, 1, 2, 0, 2, 0, 2, 1, 2},
                            {2, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 2},
                            {2, 0, 2, 1, 2, 1, 2, 0, 2, 1, 2, 1, 2, 0, 2},
                            {2, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 2},
                            {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}
                        };
                             /*matrice du plateau. Bloc représenté par des chiffres. 
                             0 : bloc vert
                             1 : bloc destructible
                             2 : bloc indestructible*/

void afficher_niveau()
{
    int i, j, x, y;
    MLV_draw_filled_rectangle(0, 0, COLONNES * TAILLE_CASE, LIGNES * TAILLE_CASE, MLV_COLOR_GREEN);
    for (i = 0; i < LIGNES; i++)
    {
        for (j = 0; j < COLONNES; j++)
        {
            x = j * TAILLE_CASE;
            y = i * TAILLE_CASE;

            if (map[i][j] == 2)
            {
                /* Bloc incassable en  gris */
                MLV_draw_filled_rectangle(x, y, TAILLE_CASE, TAILLE_CASE, MLV_COLOR_GREY);
            }
            else if (map[i][j] == 1)
            {
                /* Bloc cassable en marron */
                MLV_draw_filled_rectangle(x, y, TAILLE_CASE, TAILLE_CASE, MLV_COLOR_BROWN);
            }
        }
    }
}