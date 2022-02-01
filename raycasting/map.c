/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:38:36 by cbeaurai          #+#    #+#             */
/*   Updated: 2022/02/01 09:55:25 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	drow_element(t_app *app, int x, int y, int color)
{
	int			i;
	int			j;
	float		xo;
	float		yo;

	xo = (float)app->map_x;
	yo = (float)app->map_y;
	xo = 192 / xo;
	yo = 192 / yo;
	i = -1;
	while (++i < yo)
	{
		j = -1;
		while (++j < xo)
			my_mlx_pixel_put(&(app->img), j + (x * xo), i + (y * yo), color);
	}
}

void	add_grid(t_app *app)
{
	int i;
	int j;
	int	xo;
	int	yo;

	xo = 192 / app->map_x;
	yo = 192 / app->map_x;
	i = xo;
	while (i < 192)
	{
		j = -1;
		while (++j < 192)
			my_mlx_pixel_put(&(app->img), i, j, 0x000000);
		i += xo;
	}
	i = yo;
	while (i < 192)
	{
		j = -1;
		while (++j < 192)
			my_mlx_pixel_put(&(app->img), j, i, 0x000000);
		i += yo;
	}
			
}

void	draw_map(t_app *app)
{
	int	x;
	int	y;

	y = 0;
	while (y < app->map_y)
	{
		x = 0;
		while (x < app->map_x)
		{
			if (app->map[y * app->map_x + x] == 1)
				drow_element(app, x, y, 0x00AAAAAA);
			else
				drow_element(app, x, y, 0x00A1A101);
			x++;
		}
		y++;
	}
	add_grid(app);
}
