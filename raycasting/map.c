#include "../cub3d.h"

void	drow_element(t_app *app, int x, int y, int color)
{
	int	i;
	int	j;
	int xo;
	int yo;

	xo = app->map_x;
	yo = app->map_y;

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

void draw_map(t_app *app)
{
	int x;
	int y;
	int xo;
	int yo;

	y = 0;
	// if (app->bool_map == 1)
	// 	return ;
	while (y < app->map_y)
	{
		x = 0;
		while (x < app->map_x)
		{
			if (app->map[y * app->map_x + x] == 1)
				drow_element(app, x, y, 0x00AAAAAA);

			else
				drow_element(app, x, y, 0x00010101);
			x++;
		}
		y++;
	}
}
