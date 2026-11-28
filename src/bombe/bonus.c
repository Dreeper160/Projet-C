#include "bonus.h"
static MLV_Image *sprite_trifolium = NULL;
void initialiser_bonus(bonus *b)
{
    b->trefle.visible = 0;
    b->effet.actif = 0;
}
int spawn_trifolium(bonus *b, int ligne, int colonne)
{
    int drop;
    if (b->effet.actif == 0 && b->trefle.visible == 0)
    {
        drop = rand() % 100;
        if (drop < TAUX_DE_DROP)
        {
            b->trefle.visible = 1;
            b->trefle.ligne = ligne;
            b->trefle.colonne = colonne;
            clock_gettime(CLOCK_MONOTONIC, &b->trefle.apparition);
            return 1; /* le trefle a spawn */
        }
    }
    return 0; /*le trèdfle n'a pas réussit à spawn */
}
int ramasser_trifolium(bonus *b, const entite *joueur)
{
    int ligne_joueur;
    int colonne_joueur;

    int touche;

    touche = 0;

    ligne_joueur = (int)(joueur->pos.y / TAILLE_CASE);
    colonne_joueur = (int)(joueur->pos.x / TAILLE_CASE);

    if (b->trefle.visible == 1 && b->effet.actif == 0 && joueur->est_en_vie == 1 && b->trefle.ligne == ligne_joueur && b->trefle.colonne == colonne_joueur)
    {
        touche = 1;
        b->trefle.visible = 0;
        b->effet.actif = 1;

        clock_gettime(CLOCK_MONOTONIC, &b->effet.debut);
    }

    return touche;
}
void actualiser_bonus(bonus *b)
{
    struct timespec maintenant;
    struct timespec maintenant_disparition;
    double duree_ecoulee;
    double duree_ecoulee_disparition;
    if (b->effet.actif == 1)
    {
        clock_gettime(CLOCK_MONOTONIC, &maintenant);
        duree_ecoulee = ((maintenant.tv_sec - b->effet.debut.tv_sec) +
                         (maintenant.tv_nsec - b->effet.debut.tv_nsec) / 1e9);
        if (duree_ecoulee >= DUREE_EFFET_TRIFOLIUM)
        {
            b->effet.actif = 0;
        }
    }
    if (b->trefle.visible == 1)
    {
        clock_gettime(CLOCK_MONOTONIC, &maintenant_disparition);
        duree_ecoulee_disparition = ((maintenant_disparition.tv_sec - b->trefle.apparition.tv_sec) +
                                     (maintenant_disparition.tv_nsec - b->trefle.apparition.tv_nsec) / 1e9);
        if (duree_ecoulee_disparition >= TEMPS_APPARITION)
        {
            b->trefle.visible = 0;
        }
    }
}

void charger_images_trifolium(void)
{

    sprite_trifolium = MLV_load_image("Ressources/bomb/Trifolium-Sheet.png");
    if (sprite_trifolium != NULL)
        MLV_resize_image(sprite_trifolium, 180, 45);
}
void liberer_images_trifolium(void)
{
    if (sprite_trifolium != NULL)
    {
        MLV_free_image(sprite_trifolium);
        sprite_trifolium = NULL;
    }
}
void afficher_trifolium(const bonus *b)
{
    int centre_x = b->trefle.colonne * TAILLE_CASE + TAILLE_CASE / 2;
    int centre_y = b->trefle.ligne * TAILLE_CASE + TAILLE_CASE / 2;
    int frame;
    double secondes;
    struct timespec maintenant;

    if (b->trefle.visible == 1)
    {
        clock_gettime(CLOCK_MONOTONIC, &maintenant);
        secondes =
            (maintenant.tv_sec - b->trefle.apparition.tv_sec) + (maintenant.tv_nsec - b->trefle.apparition.tv_nsec) / 1e9;
        if (secondes < 0.0)
            secondes = 0.0;
        if (sprite_trifolium != NULL)
        {
            frame = (int)(secondes / TEMPS_APPARITION * FRAME_TRIFOLIUM);
            if (frame >= FRAME_TRIFOLIUM)
                frame = FRAME_TRIFOLIUM - 1;

            MLV_draw_partial_image(
                sprite_trifolium,
                frame * 45,
                0,
                45,
                45,
                centre_x - 45 / 2,
                centre_y - 45 / 2);
            return;
        }
        else
        {
            MLV_draw_filled_circle(centre_x, centre_y, TAILLE_CASE / 4, MLV_COLOR_GREEN);
        }
    }
}