#include "raycaster.h"
# include <math.h>


int	player_input(int key, void *data)
{
	t_app	*app;
	float		x;
	float		y;

	app = (t_app *)(data);
	x = app->sp.game_state.player_x;
	y =app->sp.game_state.player_y;
	app->sp.game_state.player_old_x = x;
	app->sp.game_state.player_old_y = y;
	return (player_input_body(key, app));
}

int	player_input_body(int key, t_app *app)
{
	printf("key: %d, pa = %f\n", key, app->sp.game_state.pa);
	if (key == FL_LEFT || key == FL_RIGHT
		||key == LEFT || key == RIGHT || key == DOWN || key == UP)
	{
		if (key == FL_LEFT)
		{
			app->sp.game_state.pa -= 0.1;
			app->ray.game_state.pa -= 0.1;
			if (app->sp.game_state.pa < 0)
			{
				app->sp.game_state.pa += 2.0 * PI;
				app->ray.game_state.pa += 2.0 * PI;
			}
			app->sp.game_state.delta_x = cosf(app->sp.game_state.pa) * 5;
			app->sp.game_state.delta_y = sinf(app->sp.game_state.pa) * 5;
		}
		else if (key == FL_RIGHT)
		{
			app->sp.game_state.pa += 0.1;
			app->ray.game_state.pa += 0.1;
			if (app->sp.game_state.pa > 2.0 * PI)
			{
				app->sp.game_state.pa -= 2.0 * PI;
				app->ray.game_state.pa -= 2.0 * PI;
			}
			app->sp.game_state.delta_x = cosf(app->sp.game_state.pa) * 5;
			app->sp.game_state.delta_y = sinf(app->sp.game_state.pa) * 5;
		}
		else if (key == LEFT)
			app->sp.game_state.player_x += -1;
		else if (key == RIGHT)
			app->sp.game_state.player_x += 1;
		else if (key == DOWN)
		{
			app->sp.game_state.player_x += (app->sp.game_state.delta_x) / 5;
			app->sp.game_state.player_y += (app->sp.game_state.delta_y) / 5;
		}
		else if (key == UP)
		{
			app->sp.game_state.player_x -= (app->sp.game_state.delta_x) / 5;
			app->sp.game_state.player_y -= (app->sp.game_state.delta_y) / 5;
		}
		// if (check_pos_player(app))
		// {
		// 	app->nb_mvmt++;
		// 	write(1, "current number of movements: ", 30);
		// 	ft_putnbr(app->nb_mvmt);
		// 	write(1, "\n: ", 1);
		// }
	}
	if (key == ESC)
		destroy_game_data(app);
	return (1);
}

int	routine(void *data)
{
	t_app		*app;
	int			x;
	int			y;
	int			discard;

	app = (t_app *)(data);
	app->img.img = mlx_new_image(app->mlx, app->x, app->y);
	app->img.addr = mlx_get_data_addr(app->img.img,
			&app->img.bpp, &app->img.size, &app->img.endian);
	app->image_is_destroyed = 0;
	drow_background(app);
	draw_map(app);
	draw_sprite(app);
	mlx_put_image_to_window(app->mlx, app->win, app->img.img, 0, 0);
	mlx_destroy_image(app->mlx, app->img.img);
	app->img.img = NULL;
	app->image_is_destroyed = 1;
	return (0);
}
