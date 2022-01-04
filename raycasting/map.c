#include "raycaster.h"

int map_x = 8;
int map_y = 8;
int map_s = 64;

int map[] =
{
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 0, 1, 1,
	1, 0, 0, 1, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
};

void init_wall(t_app *app)
{
	app->wall.img = mlx_new_image(app->mlx, 64, 64);
	app->wall.w = 64;
	app->wall.h = 64;
	app->wall.addr = mlx_get_data_addr(app->wall.img, &(app->wall.bits_per_pixel), 
			&(app->wall.line_length), &(app->wall.endian));
	my_mlx_pixel_put(&(app->wall), 0, 0, 0x00AAAAAA);
}

void init_space(t_app *app)
{
	app->space.img = mlx_new_image(app->mlx, 64, 64);
	app->space.w = 64;
	app->space.h = 64;
	app->space.addr = mlx_get_data_addr(app->space.img, &(app->space.bits_per_pixel), 
			&(app->space.line_length), &(app->space.endian));
	my_mlx_pixel_put(&(app->space), 0, 0, 0x00010101);
}

void draw_map(t_app *app)
{
	int x;
	int y;
	int xo;
	int yo;

	init_wall(app);
	init_space(app);
	y = 0;
	while (y < map_y)
	{
		x = 0;
		while (x < map_x)
		{
			if (map[y * map_x + x] == 1)
				draw_img_at_pos(app, &(app->wall), x * 66, y * 66);

			else
				draw_img_at_pos(app, &(app->space), x * 66, y * 66);
			x++;
		}
		y++;
	}
}