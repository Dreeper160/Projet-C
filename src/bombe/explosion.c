#include "explosion.h"
#define HAUT 0
#define BAS 1
#define GAUCHE 2
#define DROITE 3
void executer_explosion(explosion *exp, const bombe *b, int map[LIGNES][COLONNES])
{
    int rayon;
    int i, j;
    int bloque;
    rayon = b->rayon;
    int centre_ligne = (int)(b->b.pos.y / TAILLE_CASE);
    int centre_colonne = (int)(b->b.pos.x / TAILLE_CASE);
    /**
     * chaque direction est representé par un nombre si possible un jour je ferai mieux
     * haut : 0
     * bas : 1
     * gauche : 2
     * droite: 3
     */
    exp->nb_cases = 0;

    /* Ajoute le centre une seule fois */
    exp->cases[exp->nb_cases].ligne = centre_ligne;
    exp->cases[exp->nb_cases].colonne = centre_colonne;
    exp->nb_cases++;

    for (j = 0; j < 4; j++)
    {
        bloque = 0;
        for (i = 1; i <= rayon && bloque == 0; i++)
        {
            int ligne = centre_ligne;
            int colonne = centre_colonne;

            if (j == HAUT)
                ligne -= i;

            else if (j == BAS)
                ligne += i;
            else if (j == GAUCHE)
                colonne -= i;
            else if (j == DROITE)
                colonne += i;

            if (ligne < 0 || ligne >= LIGNES || colonne < 0 || colonne >= COLONNES)
            {
                bloque = 1;
            }
            else if (map[ligne][colonne] == 2)
            {
                bloque = 1;
            }
            else
            {
                /* Cette case est touchée */
                exp->cases[exp->nb_cases].ligne = ligne;
                exp->cases[exp->nb_cases].colonne = colonne;
                exp->nb_cases++;

                if (map[ligne][colonne] == 1)
                {
                    map[ligne][colonne] = 0;
                }
            }
        }
    }
    exp->active = 1;
    clock_gettime(CLOCK_MONOTONIC, &exp->temps_apparition);
}

void afficher_explosion(const explosion *exp)
{
    int i;
    int x;
    int y;

    if (exp->active == 0)
        return;

    for (i = 0; i < exp->nb_cases; i++)
    {
        x = exp->cases[i].colonne * TAILLE_CASE;
        y = exp->cases[i].ligne * TAILLE_CASE;
        MLV_draw_filled_rectangle(x, y, TAILLE_CASE, TAILLE_CASE,
                                  MLV_COLOR_ORANGE);
    }
}
int joueur_touche_explosion(const explosion *exp, const entite *joueur)
{
    int ligne_joueur;
    int colonne_joueur;
    int i;
    int touche;

    touche = 0;

    if (exp->active == 0 || joueur->est_en_vie == 0)
        return 0;

    ligne_joueur = (int)(joueur->pos.y / TAILLE_CASE);
    colonne_joueur = (int)(joueur->pos.x / TAILLE_CASE);

    for (i = 0; i < exp->nb_cases; i++)
    {
        if (exp->cases[i].ligne == ligne_joueur &&
            exp->cases[i].colonne == colonne_joueur)
        {
            touche = 1;
        }
    }

    return touche;
}

void actualiser_explosion(explosion *exp)
{
    struct timespec maintenant;
    double duree_ecoulee;

    if (exp->active == 1)
    {
        clock_gettime(CLOCK_MONOTONIC, &maintenant);
        duree_ecoulee =
            (maintenant.tv_sec - exp->temps_apparition.tv_sec) +
            (maintenant.tv_nsec - exp->temps_apparition.tv_nsec) / 1e9;

        if (duree_ecoulee >= DUREE_EXPLOSION)
        {
            exp->active = 0;
            exp->nb_cases = 0;
        }
    }
}