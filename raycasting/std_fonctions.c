#include "raycaster.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y *data->size + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

float modul(float n)
{
	if (n < 0)
	{
		n = n * -1;
	}
	return (n);
}


void	init_sprite(t_app *app)
{
	app->sp.game_state.player_x = 10;
	app->sp.game_state.player_y = 10;
	app->sp.game_state.player_old_x = 0;
	app->sp.game_state.player_old_y = 0;
	app->sp.game_state.pa = PI / 2;
	app->sp.game_state.delta_x = cosf(app->sp.game_state.pa) * 5;
	app->sp.game_state.delta_y = sinf(app->sp.game_state.pa) * 5;
	app->ray.game_state.pa = PI / -2;
}

void	draw_line(t_app *app)
{
	float	x;
	float	y;
	int		i;

	x = app->sp.game_state.player_x;
	y = app->sp.game_state.player_y;
	i = 0;
	while (i < 100)
	{
		my_mlx_pixel_put(&(app->img), (x * 10 + 5) + (i * cos(app->ray.game_state.pa)/2), (y * 10 + 5) + (i * sin(app->ray.game_state.pa)/2), 0x00FF0101);
		i++;
	}
}

void	draw_sprite(t_app *app)
{
	int		i;
	int		j;
	float	x;
	float	y;

	i = -1;
	x = app->sp.game_state.player_x;
	y = app->sp.game_state.player_y;
	while (++i < 10)
	{
		j = -1;
		while (++j < 10)
			my_mlx_pixel_put(&(app->img), j + (x * 10), i + (y * 10), 0x00FF0000);
	}
	draw_line(app);
	// draw_rays_3d(app);
}


void	drow_background(t_app *app)
{
	int	i;
	int	j;

	i = -1;
	while (++i < app->y)
	{
		j = -1;
		while (++j < app->x)
			my_mlx_pixel_put(&(app->img), j, i, 0x00876962);
	}
}

void	init_app(t_app *app, char *title, int w, int h)
{	
	app->mlx = mlx_init();
	app->x = w;
	app->y = h;
	if (app->mlx == NULL)
		exit (1);
	app->win = mlx_new_window(app->mlx, w, h, title);
	if (app->win == NULL)
	{
		free(app->mlx);
		exit (1);
	}
	init_sprite(app);	
}

int	destroy_game_data(void *data)
{
	t_app		*app;

	app = (t_app *)data;
	if (app->image_is_destroyed == 0)
		mlx_destroy_image(app->mlx, app->img.img);
	mlx_clear_window(app->mlx, app->win);
	mlx_destroy_window(app->mlx, app->win);
	mlx_destroy_display(app->mlx);
	free(app->mlx);
	exit (0);
}