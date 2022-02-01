/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:08:54 by cbeaurai          #+#    #+#             */
/*   Updated: 2022/02/01 11:17:19 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>

int	player_input(int key, void *data)
{
	t_app		*app;
	float		x;
	float		y;

	app = (t_app *)(data);
	x = app->sp.game_state.player_x;
	y = app->sp.game_state.player_y;
	app->sp.game_state.player_old_x = x;
	app->sp.game_state.player_old_y = y;
	return (player_input_body(key, app));
}

int	player_input_body(int key, t_app *app)
{
	float xo, yo, posx, posx_add_xo, posx_sub_xo, posy, posy_add_yo, posy_sub_yo;
	float posx_add_yo, posx_sub_yo, posy_add_xo, posy_sub_xo;

	if (app->sp.game_state.delta_x < 0)
		xo = -RES_X / app->map_x / 3;
	else
		xo = RES_X / app->map_x / 3;
	if (app->sp.game_state.delta_y < 0)
		yo = -RES_Y / app->map_y / 3;
	else
		yo = RES_Y / app->map_y / 3;
	posx = app->sp.game_state.player_x * app->map_x / RES_X;
	posx_add_xo = posx + xo * app->map_x / RES_X;
	posx_sub_xo = posx - xo * app->map_x / RES_X;
	posy = app->sp.game_state.player_y * app->map_y / RES_Y;
	posy_add_yo = posy + yo * app->map_x / RES_Y;
	posy_sub_yo = posy - yo * app->map_x / RES_Y;
	posx_add_yo = posx + yo * app->map_x / RES_Y;
	posx_sub_yo = posx - yo * app->map_x / RES_Y;
	posy_add_xo = posy + xo * app->map_x / RES_X;
	posy_sub_xo = posy - xo * app->map_x / RES_X;
	if (key == MAP)
	{
		app->bool_map++;
		app->bool_map %= 2;
		return (1);
	}
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
			if (app->map[(int)posy * app->map_x + (int)posx_add_yo] != 1)
				app->sp.game_state.player_x += (app->sp.game_state.delta_y) / 1;
			if (app->map[(int)posy_sub_xo * app->map_x + (int)posx] != 1)
				app->sp.game_state.player_y -= (app->sp.game_state.delta_x) / 1;
		}
		else if (key == RIGHT)
		{
			if (app->map[(int)posy * app->map_x + (int)posx_sub_yo] != 1)
				app->sp.game_state.player_x -= (app->sp.game_state.delta_y) / 1;
			if (app->map[(int)posy_add_xo * app->map_x + (int)posx] != 1)
				app->sp.game_state.player_y += (app->sp.game_state.delta_x) / 1;
		}
		else if (key == DOWN)
		{
			if (app->map[(int)posy * app->map_x + (int)posx_sub_xo] != 1)
				app->sp.game_state.player_x -= (app->sp.game_state.delta_x) / 1;
			if (app->map[(int)posy_sub_yo * app->map_x + (int)posx] != 1)
				app->sp.game_state.player_y -= (app->sp.game_state.delta_y) / 1;
		}
		else if (key == UP)
		{
			if (app->map[(int)posy * app->map_x + (int)posx_add_xo] != 1)
				app->sp.game_state.player_x += (app->sp.game_state.delta_x) / 1;
			if (app->map[(int)posy_add_yo * app->map_x + (int)posx] != 1)
				app->sp.game_state.player_y += (app->sp.game_state.delta_y) / 1;
		}
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
	app->north.img = mlx_xpm_file_to_image(app->mlx, "../textures/north.xpm",
			&app->north.w, &app->north.h);
	app->north.addr = mlx_get_data_addr(app->north.img, &app->north.bpp,
			&app->north.size, &app->north.endian);
	app->south.img = mlx_xpm_file_to_image(app->mlx, "../textures/south.xpm",
			&app->south.w, &app->south.h);
	app->south.addr = mlx_get_data_addr(app->south.img, &app->south.bpp,
			&app->south.size, &app->south.endian);
	app->east.img = mlx_xpm_file_to_image(app->mlx, "../textures/east.xpm",
			&app->east.w, &app->east.h);
	app->east.addr = mlx_get_data_addr(app->east.img, &app->east.bpp,
			&app->east.size, &app->east.endian);
	app->west.img = mlx_xpm_file_to_image(app->mlx, "../textures/west.xpm",
			&app->west.w, &app->west.h);
	app->west.addr = mlx_get_data_addr(app->west.img, &app->west.bpp,
			&app->west.size, &app->west.endian);
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
	t_app	*app;

	app = (t_app *)(data);
	app->img.img = mlx_new_image(app->mlx, app->x, app->y);
	app->img.addr = mlx_get_data_addr(app->img.img,
			&app->img.bpp, &app->img.size, &app->img.endian);
	app->image_is_destroyed = 0;
	drow_background(app);
	// draw_rays_3d(app);
	draw_map(app);
	draw_sprite(app);
	mlx_put_image_to_window(app->mlx, app->win, app->img.img, 0, 0);
	mlx_destroy_image(app->mlx, app->img.img);
	app->img.img = NULL;
	app->image_is_destroyed = 1;
	return (0);
}
