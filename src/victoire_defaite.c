#include "victoire_defaite.h"
#include "constante.h"

int verif_victoire(int map[LIGNES][COLONNES]){
    int i, j;
    int res = 0;
    for (i = 0; i < LIGNES; i++){
        for (j = 0; j < COLONNES; j++){
            if (map[i][j] == 1) res = 1;
        }
    }
    return res;
};