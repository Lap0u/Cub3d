#include "raycaster.h"
#include "../cub3d.h"

int	main(void)
{
	t_app	my_app;
	t_data	img;

	init_app(&my_app, "raycasting", RES_X, RES_Y);
	mlx_hook(my_app.win, 2, 1L << 0, &player_input, &my_app);
	mlx_hook(my_app.win, 17, 0, destroy_game_data, &my_app);
	mlx_loop_hook(my_app.mlx, &routine, &my_app);
	mlx_loop(my_app.mlx);
	return (0);
}