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
	app->sp.game_state.player_x = 200;
	app->sp.game_state.player_y = 200;
	app->sp.game_state.player_old_x = 0;
	app->sp.game_state.player_old_y = 0;
	app->sp.game_state.pa = PI / 2 - 1;
	app->sp.game_state.delta_x = cosf(app->sp.game_state.pa) * 5;
	app->sp.game_state.delta_y = sinf(app->sp.game_state.pa) * 5;
	app->ray.game_state.pa = PI / 2 - 1;
}

void	draw_line(t_app *app)
{
	float	x;
	float	y;
	int		i;

	x = app->sp.game_state.player_x;
	y = app->sp.game_state.player_y;
	i = 0;
	if (app->bool_map == 1)
		return ;
	while (i < 30)
	{
		my_mlx_pixel_put(&(app->img), ((x) + (i * cos(app->ray.game_state.pa)/2)) / SCALING, 
		((y) + (i * sin(app->ray.game_state.pa)/2)) / SCALING, 0x003A51B0);
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
	draw_rays_3d(app);
	draw_line(app);
	if (app->bool_map == 1)
		return ;
	while (++i < 10)
	{
		j = -1;
		while (++j < 10)
			my_mlx_pixel_put(&(app->img), (j + (x - 5)) / SCALING, (i + (y - 5)) / SCALING, 0x00FF0000);
	}
}


void	drow_background(t_app *app)
{
	int	i;
	int	j;

	i = -1;
	if (app->bool_map == 1)
		return ;
	while (++i < app->y)
	{
		j = -1;
		while (++j < app->x)
		if (j <= 64 * SCALING && i <= 64 * SCALING)
			my_mlx_pixel_put(&(app->img), j, i, 0x00876962);
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