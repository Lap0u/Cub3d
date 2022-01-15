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

void	add_empty_tile(t_app *app, int x, int y, int size)
{
	int i;
	int j;

	i = 0;
	while (i < 192 / size)
	{
		j = 0;
		while (j < 192 / size)
		{
			my_mlx_pixel_put(&(app->img), x * (192 / size) + i, y * (192 / size) + j, 0x444444);
			j++;
		}
		i++;
	}
}

void	draw_around_player(t_app *app, float p_x, float p_y, int size)
{
	int	true_x;
	int	true_y;
	int	s_x;
	int	s_y;
	int i;
	int	j;

	i = 0;
	true_x = p_x / 64;
	true_y = p_y / 64;
	s_x = true_x - size / 2;
	s_y = true_y - size / 2;
	while (i < size)
	{
		j = 0;
		s_x = true_x - size / 2;
		while (j < size)
		{
			if (s_x < 0 || s_y < 0 || s_x > map_x || s_y > map_y)
				add_empty_tile(app, j, i, size);
			// else
			// 	add_full_tile(app, s_x, s_y, size);
			j++;
			s_x++;
		}
		i++;
		s_y++;
	}
}

void draw_map(t_app *app)
{
	int x;
	int y;
	int xo;
	int yo;

	// printf("floa %f %f\n", app->sp.game_state.player_x, app->sp.game_state.player_y);
	y = 0;	
	if (app->bool_map == 1)
		return ;
	if (map_y < 8 && map_x < 8)
	{
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
	else
		draw_around_player(app, app->sp.game_state.player_x, app->sp.game_state.player_y, 8);
}
