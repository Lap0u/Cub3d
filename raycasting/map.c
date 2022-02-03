#include "raycaster.h"

int map_x = 15;
int map_y = 8;
int map_s = 120;

// int map1[] =
// {
// 	1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 0, 1, 0, 0, 0, 0, 1,
// 	1, 0, 1, 0, 0, 0, 0, 1,
// 	1, 0, 1, 0, 0, 0, 0, 1,
// 	1, 0, 0, 0, 0, 0, 0, 1,
// 	1, 0, 0, 0, 0, 1, 0, 1,
// 	1, 0, 0, 0, 0, 0, 0, 1,
// 	1, 1, 1, 1, 1, 1, 1, 1,
// };

int map[] =
{
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

void	drow_element(t_app *app, int x, int y, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 63/2)
	{
		j = -1;
		while (++j < 63/2)
			my_mlx_pixel_put(&(app->img), j + (x * 64/2), i + (y *64/2), color);
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
