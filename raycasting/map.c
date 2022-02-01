/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:38:36 by cbeaurai          #+#    #+#             */
/*   Updated: 2022/02/01 09:43:50 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	drow_element(t_app *app, int x, int y, int color)
{
	int			i;
	int			j;
	float		xo;
	float		yo;

	if (app->map_x > 15 || app->map_y > 15)
		mod = 0;
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
}
