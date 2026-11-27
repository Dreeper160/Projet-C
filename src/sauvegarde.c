#include "sauvegarde.h"
#include "constante.h"
#include "entite.h"
#include <stdio.h>

int sauvegarder_partie(int map[LIGNES][COLONNES], entite j, int nb) {
    int i, l;
    FILE *f;
    char *fichiers[4] = {
        "saves/sauvegarde1.txt",
        "saves/sauvegarde2.txt",
        "saves/sauvegarde3.txt",
        "saves/sauvegarde4.txt"
    };

    if (nb < 1 || nb > 4) {
        fprintf(stderr, "Erreur numéro de sauvegarde impossible\n");
        return -1;
    }

    if ((f = fopen(fichiers[nb - 1], "w")) == NULL) {
        fprintf(stderr, "Erreur ouverture sauvegarde\n");
        return -1;
    }
    fprintf(f,"%d %f %f %d %d %d\n", j.est_en_vie, j.pos.x, j.pos.y, j.direction, j.en_mouvement, j.frame_actuelle);
    for(i = 0; i < LIGNES; i++){
        for(l = 0; l < COLONNES; l++) fprintf(f,"%d ",map[i][l]);
        fprintf(f,"\n");
    }
    fclose(f);
    return 0;
}

int charger_partie(int map[LIGNES][COLONNES], entite *j, int nb){
     int i, l;
    FILE *f;
    char *fichiers[4] = {
        "saves/sauvegarde1.txt",
        "saves/sauvegarde2.txt",
        "saves/sauvegarde3.txt",
        "saves/sauvegarde4.txt"
    };

    if (nb < 1 || nb > 4) {
        fprintf(stderr, "Erreur numéro de sauvegarde impossible\n");
        return -1;
    }

    if ((f = fopen(fichiers[nb - 1], "r")) == NULL) {
        fprintf(stderr, "Erreur ouverture sauvegarde\n");
        return -1;
    }
    fscanf(f,"%d %f %f %d %d %d\n", &j->est_en_vie, &j->pos.x, &j->pos.y, &j->direction, &j->en_mouvement, &j->frame_actuelle);
    j->vitesse_anim = MLV_get_time();
    for(i = 0; i < LIGNES; i++){
        for(l = 0; l < COLONNES; l++) fscanf(f,"%d ",&map[i][l]);
    }
    fclose(f);
    return 0;
}