#include <MLV/MLV_all.h>

#define LIGNES 15
#define COLONNES 15
#define TAILLE_CASE 45

    int niv_1[LIGNES][COLONNES]={{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
                                 {2,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
                                 {2,0,1,0,0,0,0,2,0,0,0,0,0,0,2},
                                 {2,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
                                 {2,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
                                 {2,0,0,0,1,0,0,0,0,0,0,0,0,0,2},
                                 {2,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
                                 {2,0,0,0,0,1,0,0,0,0,0,0,0,0,2},
                                 {2,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
                                 {2,0,0,0,0,0,0,2,0,0,0,0,0,0,2},
                                 {2,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
                                 {2,0,0,0,1,0,0,0,0,0,0,0,0,0,2},
                                 {2,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
                                 {2,0,0,0,0,1,0,0,0,0,0,0,0,0,2},
                                 {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
};

void afficher_niveau() {
    int i, j, x, y;
    MLV_draw_filled_rectangle(0, 0, COLONNES * TAILLE_CASE, LIGNES * TAILLE_CASE, MLV_COLOR_GREEN);
    for (i = 0; i < LIGNES; i++) {
        for (j = 0; j < COLONNES; j++) {
            x = j * TAILLE_CASE;
            y = i * TAILLE_CASE;

            if (map[i][j] == 2) {
                /* Bloc incassable en  gris */
                MLV_draw_filled_rectangle(x, y, TAILLE_CASE, TAILLE_CASE, MLV_COLOR_GREY);
            }
            else if (map[i][j] == 1) {
                /* Bloc cassable en marron */
                MLV_draw_filled_rectangle(x, y, TAILLE_CASE, TAILLE_CASE, MLV_COLOR_BROWN);
            }
        }
    }
}

int main(void) {
    /* Largeur : 15 colonnes * 45px = 675. Hauteur : 13 lignes * 45px = 585 */
    MLV_create_window("Bomberman - Test Niveau", "Bomberman", 1080, 1920);

    /* Appel de ta fonction pour dessiner la grille */
    afficher_niveau();

    /* Actualisation obligatoire pour afficher les dessins à l'écran */
    MLV_actualise_window();

    /* Met le programme en pause jusqu'à ce qu'on appuie sur une touche */
    MLV_wait_keyboard_or_mouse(NULL, NULL, NULL, NULL, NULL);

    MLV_free_window();
    return 0;
}
/*test 1 2 1*/