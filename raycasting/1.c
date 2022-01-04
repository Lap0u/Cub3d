#include "raycaster.h"


float px, py; // player position

void draw_player()
{

}

int	main(void)
{
	t_app	my_app;
	t_data	img;

	init_app(&my_app, "raycasting", 1024, 512);
	mlx_key_hook(my_app.win, &player_input, &my_app);
	// mlx_put_image_to_window(my_app.mlx, my_app.win, my_app.brouillon.img, 0, 0);
	// mlx_put_image_to_window(my_app.mlx, my_app.win, my_app.sp.img, 300, 300);
	mlx_hook(my_app.win, 17, 0, destroy_game_data, &my_app);
	mlx_loop_hook(my_app.mlx, &routine, &my_app);
	mlx_loop(my_app.mlx);
}