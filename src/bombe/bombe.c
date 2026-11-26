#include "constante.h"
#include "bombe.h"

static MLV_Image *sprite_bombe = NULL;
static MLV_Image *sprite_bombe_ignite = NULL;

void charger_images_bombe(void)
{
    sprite_bombe = MLV_load_image("Ressources/bomb/bombe_normal-Sheet.png");
    if (sprite_bombe != NULL)
        MLV_resize_image(sprite_bombe, 270, 45);

    sprite_bombe_ignite = MLV_load_image("Ressources/bomb/bombe_normal_ignite-Sheet.png");
}

void liberer_images_bombe(void)
{
    if (sprite_bombe != NULL)
    {
        MLV_free_image(sprite_bombe);
        sprite_bombe = NULL;
    }
    if (sprite_bombe_ignite != NULL)
    {
        MLV_free_image(sprite_bombe_ignite);
        sprite_bombe_ignite = NULL;
    }
}

void afficher_bombe(bombe bombe)
{
    int centre_x = bombe.b.pos.x;
    int centre_y = bombe.b.pos.y;
    struct timespec maintenant;
    double secondes;
    int frame;

    if (bombe.state == BOMBE_IGNITE)
    {
        double secondes_ignite;
        int rayon;

        clock_gettime(CLOCK_MONOTONIC, &maintenant);
        secondes_ignite =
            (maintenant.tv_sec - bombe.temps_explosion.tv_sec) + (maintenant.tv_nsec - bombe.temps_explosion.tv_nsec) / 1e9;
        if (secondes_ignite < 0.0)
            secondes_ignite = 0.0;

        if (sprite_bombe_ignite != NULL)
        {
            frame = (int)(secondes_ignite / T_IGNITE * FRAMES_IGNITE);
            if (frame >= FRAMES_IGNITE)
                frame = FRAMES_IGNITE - 1;

            MLV_draw_partial_image(
                sprite_bombe_ignite,
                frame * 45,
                0,
                45,
                45,
                centre_x - 45 / 2,
                centre_y - 45 / 2);
            return;
        }

        rayon = (int)(10.0 + (secondes_ignite / T_IGNITE) * (TAILLE_CASE / 2));
        if (rayon > TAILLE_CASE)
            rayon = TAILLE_CASE;

        MLV_draw_filled_circle(centre_x, centre_y, rayon, MLV_COLOR_ORANGE);
        MLV_draw_filled_circle(
            centre_x,
            centre_y,
            rayon * 2 / 3,
            MLV_COLOR_YELLOW);
        MLV_draw_filled_circle(
            centre_x,
            centre_y,
            rayon / 3,
            MLV_COLOR_RED);
        return;
    }

    if (sprite_bombe == NULL)
    {
        MLV_draw_filled_circle(
            centre_x,
            centre_y,
            (TAILLE_CASE / 2) - 4,
            MLV_COLOR_BLACK);
        return;
    }

    clock_gettime(CLOCK_MONOTONIC, &maintenant);
    secondes = (maintenant.tv_sec - bombe.temps_pose.tv_sec) + (maintenant.tv_nsec - bombe.temps_pose.tv_nsec) / 1e9;

    /*
     * Répartit toutes les frames sur la durée totale de la bombe.
     * Avec 6 frames et T_MAX = 1 secondes, chaque frame dure environ 166 ms.
     */
    frame = (int)(secondes / T_MAX * FRAMES_MECHE);
    if (frame >= FRAMES_MECHE)
        frame = FRAMES_MECHE - 1;
    if (frame < 0)
        frame = 0;

    MLV_draw_partial_image(
        sprite_bombe,
        frame * 45,
        0,
        45,
        45,
        centre_x - 45 / 2,
        centre_y - 45 / 2);
}

/*timespec contient
    *tv_sec :secondes
    tv_nsec: Nano secondes */
int bombe_expiree(bombe *b)
{ /*Recuperation du temps actuel */
    struct timespec now;
    double secondes;
    double secondes_ignite;

    clock_gettime(CLOCK_MONOTONIC, &now);
    /*Les nano secondes passé sont utilisé pour L'EXACTITUDE de du calcul de secondes passé pour eviter les bypass*/
    secondes = (now.tv_sec - b->temps_pose.tv_sec) + (now.tv_nsec - b->temps_pose.tv_nsec) / 1e9;

    if (b->state == BOMBE_MECHE && secondes >= T_MAX)
    {
        b->state = BOMBE_IGNITE; /*ignite signifie allumage */
        b->temps_explosion = now;
    }

    if (b->state == BOMBE_IGNITE)
    {
        secondes_ignite =
            (now.tv_sec - b->temps_explosion.tv_sec) + (now.tv_nsec - b->temps_explosion.tv_nsec) / 1e9;

        if (secondes_ignite >= T_IGNITE)
        {
            b->b.est_en_vie = 0;
            b->state = BOMBE_MECHE;
            return 1;
        }
    }

    return 0;
}

void placer_bombe(bombe *bom, entite j)
{
    int colonne;
    int ligne;

    /*
     * Le joueur se déplace en pixels, mais la carte fonctionne
     * avec des cases. On convertit donc sa position en coordonnées
     * de case pour savoir où placer la bombe.
     */
    colonne = (int)(j.pos.x / TAILLE_CASE);
    ligne = (int)(j.pos.y / TAILLE_CASE);

    /*
     * On récupère l'état du joueur, puis on replace la bombe
     * au centre exact de la case dans laquelle se trouve le joueur.
     * Cela évite de placer la bombe entre deux cases.
     */
    bom->b = j;
    bom->b.pos.x = colonne * TAILLE_CASE + TAILLE_CASE / 2.0;
    bom->b.pos.y = ligne * TAILLE_CASE + TAILLE_CASE / 2.0;

    /* La bombe devient active et on note le moment exact ou la bombe a été placé (utile pour faire despawn la bombe ) */
    bom->b.est_en_vie = 1;
    bom->state = BOMBE_MECHE;
    clock_gettime(CLOCK_MONOTONIC, &bom->temps_pose);
}
