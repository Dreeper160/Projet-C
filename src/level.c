#include "constante.h"
#include "level.h"

static MLV_Image *img_sol = NULL;
static MLV_Image *img_mur_cassable = NULL;
static MLV_Image *img_mur_incassable = NULL;

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

void charger_images_niveau(){
    /* 1. Chargement des fichiers */
    img_sol            = MLV_load_image("Ressources/undertale_soil.png");
    img_mur_cassable   = MLV_load_image("Ressources/undertale_leaf.png");
    img_mur_incassable = MLV_load_image("Ressources/undertale_wall.png");

    /* 2. Redimensionnement en 45x45 pixels */
    if (img_sol != NULL) {
        MLV_resize_image(img_sol, TAILLE_CASE, TAILLE_CASE);
    }
    if (img_mur_cassable != NULL) {
        MLV_resize_image(img_mur_cassable, TAILLE_CASE, TAILLE_CASE);
    }
    if (img_mur_incassable != NULL) {
        MLV_resize_image(img_mur_incassable, TAILLE_CASE, TAILLE_CASE);
    }
}                             

void afficher_niveau(){
    int i, j, x, y;
    for (i = 0; i < LIGNES; i++)
    {
        for (j = 0; j < COLONNES; j++)
        {
            x = j * TAILLE_CASE;
            y = i * TAILLE_CASE;

            if (map[i][j] == 0){
                /* Bloc de sol */
                MLV_draw_image(img_sol, x, y);
            }
            if (map[i][j] == 1){
                /* Bloc cassable */
                MLV_draw_image(img_mur_cassable, x, y);
            }
            if (map[i][j] == 2){
                /* Bloc incassable */
                MLV_draw_image(img_mur_incassable, x, y);
            }
        }
    }
}

void liberer_images_niveau(){
    if (img_sol != NULL)  MLV_free_image(img_sol);
    if (img_mur_cassable != NULL) MLV_free_image(img_mur_cassable);
    if (img_mur_incassable != NULL)    MLV_free_image(img_mur_incassable);
}