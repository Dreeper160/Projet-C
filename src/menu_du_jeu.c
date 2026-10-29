#include <MLV/MLV_all.h>
/*typedef enum etat{
    jouer = 1;
    charger = 2;
    options = 3;
    quitter = 0; 
}*/

void afficher_menu(){
    MLV_Font* font_titre = MLV_load_font( "Ressources/ARCADECLASSIC.TTF" , 50 ); /*Chargement de la police du texte du titre*/
    MLV_Font* font_boutons = MLV_load_font( "Ressources/ARCADECLASSIC.TTF" , 20 ); /*Chargement de la police du texte des boutons avec une taille plus petite*/
    MLV_draw_text_with_font(
        217,40,
        "BomberMan",
        font_titre, MLV_COLOR_WHITE
    ); /*Affichage du titre */

    MLV_draw_adapted_text_box_with_font(
                280,160,
                "Jouer",
                font_boutons,
                30,
                MLV_COLOR_WHITE, MLV_COLOR_WHITE, MLV_COLOR_BLACK,
                MLV_TEXT_CENTER
        ); /*Affichage du premier bouton*/

    MLV_draw_adapted_text_box_with_font(
                220,280,
                "Charger une partie",
                font_boutons,
                30,
                MLV_COLOR_WHITE, MLV_COLOR_WHITE, MLV_COLOR_BLACK,
                MLV_TEXT_CENTER
        ); /*Affichage du deuxieme bouton*/
    
    MLV_draw_adapted_text_box_with_font(
                269,400,
                "Options",
                font_boutons,
                30,
                MLV_COLOR_WHITE, MLV_COLOR_WHITE, MLV_COLOR_BLACK,
                MLV_TEXT_CENTER
        );
    
    MLV_draw_adapted_text_box_with_font(
                0,600,
                "Quitter",
                font_boutons,
                30,
                MLV_COLOR_WHITE, MLV_COLOR_WHITE, MLV_COLOR_BLACK,
                MLV_TEXT_CENTER
        );

}

void interagir_menu(){
    int x,y;
    MLV_wait_mouse(&x,&y);
    MLV_get_mouse_position(&x,&y);
    MLV_draw_text(
                        0, 40,
                        "Position de la souris : (%d, %d)",
                        MLV_COLOR_GREEN,
                        x, y 
                );
}

 

int main(void){ /*pour test les fonctions*/
    MLV_Keyboard_button touche;

    MLV_create_window("menu - test", "test",675,675);

    afficher_menu();
    MLV_actualise_window();
    interagir_menu();
    MLV_actualise_window();
    MLV_wait_keyboard( &touche, NULL, NULL );
    if(touche == MLV_KEYBOARD_q){
    MLV_free_window();}
    return 0;

}