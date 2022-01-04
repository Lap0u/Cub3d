#include "raycaster.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	int		i;
	int		j;

	i = 0;
	while (i < data->h)
	{
		j = 0;
		while (j < data->w)
		{
			dst = data->addr + ((y + i) * data->line_length + (x + j) * (data->bits_per_pixel / 8));
			*(unsigned int*)dst = color;
			j++;
		}
		i++;
	}
}

void	my_mlx_pixel_put_sp(t_data *data, int x, int y, int color)
{
	char	*dst;
	int		i;
	int		j;

	i = 0;
	while (i < (data->h / 2))
	{
		j = 0;
		while (j < (data->w / 2))
		{
			dst = data->addr + ((y + i) * data->line_length + (x + j) * (data->bits_per_pixel / 8));
			*(unsigned int*)dst = color;
			j++;
		}
		i++;
	}
	while (i < (data->h))
	{
		dst = data->addr + ((y + i) * data->line_length + (x + j) * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
		j++;
		i++;
	}
}

void	init_sprite(t_app *app)
{
	app->sp.game_state.player_x = 10;
	app->sp.game_state.player_y = 10;
	app->sp.game_state.player_old_x = 0;
	app->sp.game_state.player_old_y = 0;
	app->sp.game_state.delta_x = 0;
	app->sp.game_state.delta_y = 0;
	app->sp.game_state.pa = 0;
	app->image_is_destroyed = 0;
}

void	draw_sprite(t_app *app)
{
	float x;
	float y;
	app->sp.w = 20;
	app->sp.h = 20;	
	x = app->sp.game_state.player_x;
	y = app->sp.game_state.player_y;
	// printf("app->sp.w = %d, app->sp.h = %d",  app->sp.w, app->sp.h);
	app->sp.img  = mlx_new_image(app->mlx, app->sp.w, app->sp.h);
	app->sp.addr = mlx_get_data_addr(app->sp.img, &(app->sp.bits_per_pixel),
			&(app->sp.line_length), &(app->sp.endian));
	my_mlx_pixel_put_sp(&(app->sp), 0, 0, 0x00FF0101);
	draw_img_at_pos(app, &(app->sp), x * 10, y * 10);
}


void	drow_background(t_app *app)
{
	app->brouillon.img = mlx_new_image(app->mlx, app->x, app->y);
	app->brouillon.w = app->x;
	app->brouillon.h = app->y;
	// printf("app->brouillon.w = %d, app->brouillon.h = %d\n", app->brouillon.w, app->brouillon.h);
	app->brouillon.addr = mlx_get_data_addr(app->brouillon.img, &(app->brouillon.bits_per_pixel), 
			&(app->brouillon.line_length), &(app->brouillon.endian));
	my_mlx_pixel_put(&(app->brouillon), 0, 0, 0x00876962);
	draw_img_at_pos(app, &(app->brouillon), 0, 0);
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
	if (app->brouillon.image_is_destroyed == 0)
		mlx_destroy_image(app->mlx, app->brouillon.img);
	if (app->wall.image_is_destroyed == 0)
		mlx_destroy_image(app->mlx, app->wall.img);
	if (app->space.image_is_destroyed == 0)
		mlx_destroy_image(app->mlx, app->space.img);
	if (app->sp.image_is_destroyed == 0)
		mlx_destroy_image(app->mlx, app->sp.img);
	if (app->image_is_destroyed == 0)
		mlx_destroy_image(app->mlx, app->image);
	mlx_clear_window(app->mlx, app->win);
	mlx_destroy_window(app->mlx, app->win);
	mlx_destroy_display(app->mlx);
	free(app->mlx);
	exit (0);
}