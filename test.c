#include <MLV/MLV_all.h>
#include <stdlib.h>
#include <stdio.h>
int main(void) {
    int i, j;
    /* 1. Création d'une fenêtre de 640x480 pixels */
    MLV_create_window("Test MLV - UJM", "Test", 1920, 1080);

    /* 2. Dessin d'un fond gris foncé, d'un cercle et d'un texte */
    MLV_clear_window(MLV_rgba(30, 35, 45, 255));
    for (i = 50; i < 800; i += 50) {
    for (j = 50; j < 800; j += 50){ MLV_draw_filled_rectangle(i, j, 100, 100, MLV_COLOR_GREEN);
    if (i == 100 && j == 100){
       
        MLV_draw_filled_rectangle(100, 100, 100, 100, MLV_COLOR_GREY); 
        
    }

    }
}

    /* 3. Actualisation de l'affichage */
    MLV_actualise_window();

    /* 4. Attente d'un clic ou d'une touche (ou 5 secondes max) */
    MLV_wait_keyboard_or_mouse(NULL, NULL, NULL, NULL, NULL);

    /* 5. Fermeture propre et libération de la mémoire */
    MLV_free_window();
    exit(EXIT_SUCCESS);
}