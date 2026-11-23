#include "constante.h"
#include "level.h"

void rempl_lvl_1(int map[LIGNES][COLONNES]){
    int i, j;
    int nv[LIGNES][COLONNES] = {
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
    for (i = 0; i < LIGNES; i++){
        for (j = 0; j < COLONNES; j++) map[i][j] = nv[i][j];
    }
};
                             /*matrice du plateau. Bloc représenté par des chiffres. 
                             0 : bloc vert
                             1 : bloc destructible
                             2 : bloc indestructible*/
void charger_images_niveau(Images_niveau *imgs) {
    imgs->sol            = MLV_load_image("Ressources/undertale_soil.png");
    imgs->mur_cassable   = MLV_load_image("Ressources/undertale_leaf.png");
    imgs->mur_incassable = MLV_load_image("Ressources/undertale_wall.png");

    if (imgs->sol != NULL) MLV_resize_image(imgs->sol, TAILLE_CASE, TAILLE_CASE);
    if (imgs->mur_cassable != NULL) MLV_resize_image(imgs->mur_cassable, TAILLE_CASE, TAILLE_CASE);
    if (imgs->mur_incassable != NULL) MLV_resize_image(imgs->mur_incassable, TAILLE_CASE, TAILLE_CASE);
};                  

void afficher_niveau(int map[LIGNES][COLONNES], Images_niveau imgs){
    int i, j, x, y;
    for (i = 0; i < LIGNES; i++){
        for (j = 0; j < COLONNES; j++){
            x = j * TAILLE_CASE;
            y = i * TAILLE_CASE;

            if (map[i][j] == 0){
                /* Bloc de sol */
                if (imgs.sol != NULL) MLV_draw_image(imgs.sol, x, y);
                else MLV_draw_filled_rectangle(x, y, TAILLE_CASE, TAILLE_CASE, MLV_COLOR_PURPLE);
            }
            if (map[i][j] == 1){
                /* Bloc cassable */
                if (imgs.mur_cassable != NULL) MLV_draw_image(imgs.mur_cassable, x, y);
                else MLV_draw_filled_rectangle(x, y, TAILLE_CASE, TAILLE_CASE, MLV_COLOR_RED);
            }
            if (map[i][j] == 2){
                /* Bloc incassable */
                if (imgs.mur_incassable != NULL) MLV_draw_image(imgs.mur_incassable, x, y);
                else MLV_draw_filled_rectangle(x, y, TAILLE_CASE, TAILLE_CASE, MLV_COLOR_GREY);
            }
        }
    }
}

void liberer_images_niveau(Images_niveau *imgs){
    if (imgs->sol != NULL)  MLV_free_image(imgs->sol);
    if (imgs->mur_cassable != NULL) MLV_free_image(imgs->mur_cassable);
    if (imgs->mur_incassable != NULL)    MLV_free_image(imgs->mur_incassable);
};

void rempl_lvl_rand(int map[LIGNES][COLONNES]){
    int i, j;
     for (i = 0; i < LIGNES; i++){
        for (j = 0; j < COLONNES; j++){
            if (!((i == 1 && j == 1) || (i == 1 && j == 2) 
                || (i == 2 && j == 1)) && map[i][j] != 2){
                map[i][j] = rand() % 2;
                }
            }
        }
};