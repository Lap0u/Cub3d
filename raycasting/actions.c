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
	extern int map[];
	extern int map_x;
	extern int map_y;
	int xo, yo, posx, posx_add_xo, posx_sub_xo, posy, posy_add_yo, posy_sub_yo;
	int posx_add_yo, posx_sub_yo, posy_add_xo, posy_sub_xo;

	if (app->sp.game_state.delta_x < 0)
		xo = -10; //modifier ces valeurs pour choisir l'ecart min avec le mur 
	else
		xo = 10;
	if (app->sp.game_state.delta_y < 0)
		yo = -10;
	else
		yo = 10;
	//
	posx = app->sp.game_state.player_x / 64.0;
	posx_add_xo = (app->sp.game_state.player_x + xo) / 64.0;
	posx_sub_xo = (app->sp.game_state.player_x - xo) / 64.0;
	//
	posy = app->sp.game_state.player_y / 64.0;
	posy_add_yo = (app->sp.game_state.player_y + yo) / 64.0;
	posy_sub_yo = (app->sp.game_state.player_y - yo) / 64.0;
	//
	posx_add_yo = (app->sp.game_state.player_x + yo) / 64.0;
	posx_sub_yo = (app->sp.game_state.player_x - yo) / 64.0;
	//
	posy_add_xo = (app->sp.game_state.player_y + xo) / 64.0;
	posy_sub_xo = (app->sp.game_state.player_y - xo) / 64.0;
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
		{
			if (map[posy * map_x + posx_add_yo] != 1)
				app->sp.game_state.player_x += (app->sp.game_state.delta_y) / 1;
			if (map[posy_sub_xo * map_x + posx] != 1)
				app->sp.game_state.player_y -= (app->sp.game_state.delta_x) / 1;
		}
		else if (key == RIGHT)
		{
			if (map[posy * map_x + posx_sub_yo] != 1)
				app->sp.game_state.player_x -= (app->sp.game_state.delta_y) / 1;
			if (map[posy_add_xo * map_x + posx] != 1)
				app->sp.game_state.player_y += (app->sp.game_state.delta_x) / 1;
		}
		else if (key == DOWN)
		{
			if (map[posy * map_x + posx_sub_xo] != 1)
				app->sp.game_state.player_x -= (app->sp.game_state.delta_x) / 1;
			if (map[posy_sub_yo * map_x + posx] != 1)	
				app->sp.game_state.player_y -= (app->sp.game_state.delta_y) / 1;
		}
		else if (key == UP)
		{
			if (map[posy * map_x + posx_add_xo] != 1)
				app->sp.game_state.player_x += (app->sp.game_state.delta_x) / 1;
			if (map[posy_add_yo * map_x + posx] != 1)
				app->sp.game_state.player_y += (app->sp.game_state.delta_y) / 1;
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

char	*copy_size(char *str, int bpp, int size)
{
	int		i;
	char	*temp;

	i = 0;
	temp = malloc(sizeof(char) * ((size + 1) * bpp));
	if (temp == NULL)
		return (NULL);
	while ((i * bpp) < (size * bpp) && str[i * bpp])
	{
		temp[i] = str[i * bpp];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

void	open_images(t_app *app) ///retour de fonctions a check ->img = NULL
{
	app->north.img = mlx_xpm_file_to_image(app->mlx, "../textures/north.xpm", &app->north.w, &app->north.h);
	app->north.addr = mlx_get_data_addr(app->north.img, &app->north.bpp, &app->north.size, &app->north.endian);
	
	
	// int		bpp;
	// char	*str;

	// bpp = app->north.bpp / 8;
	// str = copy_size(&app->north.addr[3 * app->north.size + 3 * bpp + 0], bpp, 5);
	// printf("code = [%s]\n", str);
	// free(str);
	
	
	app->south.img = mlx_xpm_file_to_image(app->mlx, "../textures/south.xpm", &app->south.w, &app->south.h);
	app->south.addr = mlx_get_data_addr(app->south.img, &app->south.bpp, &app->south.size, &app->south.endian);
	app->east.img = mlx_xpm_file_to_image(app->mlx, "../textures/east.xpm", &app->east.w, &app->east.h);
	app->east.addr = mlx_get_data_addr(app->east.img, &app->east.bpp, &app->east.size, &app->east.endian);
	app->west.img = mlx_xpm_file_to_image(app->mlx, "../textures/west.xpm", &app->west.w, &app->west.h);
	app->west.addr = mlx_get_data_addr(app->west.img, &app->west.bpp, &app->west.size, &app->west.endian);
}

void	close_images(t_app *app)
{
	mlx_destroy_image(app->mlx, app->north.img);
	mlx_destroy_image(app->mlx, app->south.img);
	mlx_destroy_image(app->mlx, app->east.img);
	mlx_destroy_image(app->mlx, app->west.img);
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
	open_images(app);
	app->image_is_destroyed = 0;
	drow_background(app);
	draw_map(app);
	draw_sprite(app);
	mlx_put_image_to_window(app->mlx, app->win, app->img.img, 0, 0);
	mlx_destroy_image(app->mlx, app->img.img);
	close_images(app);
	app->img.img = NULL;
	app->image_is_destroyed = 1;
	return (0);
}
