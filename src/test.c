#include <MLV/MLV_all.h>
int main(void)
{
    MLV_create_window("test", "test", 640, 480);
    MLV_draw_text(20, 20, "MLV OK", MLV_COLOR_WHITE);
    MLV_actualise_window();
    MLV_wait_seconds(3);
    MLV_free_window();
    return 0;
}
