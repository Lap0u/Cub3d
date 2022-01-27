// #include "raycaster.h"
#include "../cub3d.h"

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
	app->sp.game_state.player_x = 200;
	app->sp.game_state.player_y = 200;
	app->sp.game_state.player_old_x = 0;
	app->sp.game_state.player_old_y = 0;
	app->sp.game_state.pa = PI / -2;
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
	while (i < 30)
	{
		my_mlx_pixel_put(&(app->img), ((x) + (i * cos(app->ray.game_state.pa)/2)) / 2, 
		((y) + (i * sin(app->ray.game_state.pa)/2)) / 2, 0x003A51B0);
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
	draw_line(app);
	draw_mini_rays(app);
	while (++i < 10)
	{
		j = -1;
		while (++j < 10)
			my_mlx_pixel_put(&(app->img), (j + (x - 5))/2, (i + (y - 5))/2, 0x00FF0000);

	}
}


void	drow_background(t_app *app)
{
	int i;
	int	y;
	int color;

	i = 0;
	while (i < RES_X)
	{
		y = 0;
		while (y < RES_Y)
		{
			if (y < RES_Y / 2)
				color = color_ceil(app, i, y);
			else
				color = color_floor(app, i, y);
			if (i >= 64 * SCALING || y >= 64 * SCALING || app->bool_map == 1)//laisse la place pour la map en haut a gauche, change valeur pour agrandir / retraicir / faire un scaling
				my_mlx_pixel_put(&(app->img), i, y, color);
			y++;
		}
		i++;
	}
}

void	init_colors(t_app *app)
{
	app->ceil_col.red = 0;
	app->ceil_col.green = 0;
	app->ceil_col.blue = 255;
	app->flo_col.red = 255;
	app->flo_col.green = 0;
	app->flo_col.blue = 0;
}
void	init_app(t_app *app, char *title, int w, int h)
{	
	app->mlx = mlx_init();
	if (app->mlx == NULL)
		exit (1);
	init_path(app);
	init_texture(app);
	app->x = w;
	app->y = h;
	app->bool_map = 1;
	if (app->mlx == NULL)
		exit (1);
	app->win = mlx_new_window(app->mlx, w, h, title);
	if (app->win == NULL)
	{
		free(app->mlx);
		exit (1);
	}
	init_sprite(app);
	init_colors(app);
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