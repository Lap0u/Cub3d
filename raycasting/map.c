#include "raycaster.h"

int map_x = 8;
int map_y = 8;
int map_s = 64;

int map[] =
{
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
};

void	drow_element(t_app *app, int x, int y, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 63)
	{
		j = -1;
		while (++j < 63)
			my_mlx_pixel_put(&(app->img), (j + (x * 64)) / SCALING, (i + (y *64)) / SCALING, color);
	}
}

void draw_map(t_app *app)
{
	int x;
	int y;
	int xo;
	int yo;

	y = 0;
	while (y < map_y)
	{
		x = 0;
		while (x < map_x)
		{
			if (map[y * map_x + x] == 1)
				drow_element(app, x, y, 0x00AAAAAA);

			else
				drow_element(app, x, y, 0x00010101);
			x++;
		}
		y++;
	}
}
