#include <MLV/MLV_all.h>

int main( int argc, char *argv[] ){

	MLV_create_window( "Nom_fenetre", "nom_icone", 640, 480 );

	MLV_draw_text(
		10, 120, 
		"Bonjour, vous utilisez la librairie mlv-2.0.2.",
		MLV_COLOR_MAGENTA
	);

	MLV_actualise_window();

	MLV_wait_seconds( 10 );

	MLV_free_window();

	return 0;
}
