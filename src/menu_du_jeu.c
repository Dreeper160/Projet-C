#include <MLV/MLV_all.h>
#include <stdio.h>

#define NB_MAX 4
#define INTERLIGNE 30

typedef enum {
    quitter = 0,
    jouer = 1,
    charger = 2,
    options = 3,
    menu_pause = 4
} Etat;

/* Positions et textes des boutons (communs à l'affichage et au clic) */
static const int pos_x[NB_MAX] = {280, 220, 269, 0};
static const int pos_y[NB_MAX] = {160, 280, 400, 600};
static const char *textes[NB_MAX] = {"Jouer", "Charger une partie", "Options", "Quitter"};

void afficher_menu(MLV_Font *font_titre, MLV_Font *font_boutons) {
    int i;

    MLV_draw_text_with_font(217, 40, "BomberMan", font_titre, MLV_COLOR_WHITE);

    for (i = 0; i < NB_MAX; i++) {
        MLV_draw_adapted_text_box_with_font(
            pos_x[i], pos_y[i],
            textes[i],
            font_boutons,
            INTERLIGNE,
            MLV_COLOR_WHITE, MLV_COLOR_WHITE, MLV_COLOR_BLACK,
            MLV_TEXT_CENTER
        );
    }
}

/* Attend un clic et renvoie l'état correspondant au bouton cliqué.
   Renvoie -1 si le clic est en dehors de tous les boutons. */
int interagir_menu(MLV_Font *font_boutons) {
    int largeur[NB_MAX], hauteur[NB_MAX];
    int mx, my, i;
    int e;
    Etat etats[NB_MAX] = {jouer, charger, options, quitter};

    for (i = 0; i < NB_MAX; i++) {
        MLV_get_size_of_adapted_text_box_with_font(
            textes[i], font_boutons, INTERLIGNE, &largeur[i], &hauteur[i]
        );
    }

    MLV_wait_mouse(&mx, &my);
    e=-1;
    for (i = 0; i < NB_MAX; i++) {
        if (mx >= pos_x[i] && mx <= pos_x[i] + largeur[i]
            && my >= pos_y[i] && my <= pos_y[i] + hauteur[i]) {
            e = etats[i];
        }
    }
    return e;
}
