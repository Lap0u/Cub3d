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

void	draw_grid(t_app *app, int size)
{
	int x;
	int y;

	x = 1;
	while (x < 192)
	{
		y = 1;
		while (y < 192)
		{
			if (y % (192 / size) == 0 || x % (192 / size) == 0)
				my_mlx_pixel_put(&(app->img), x, y, 0x0000FF);
			y++;
		}
		x++;
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
			my_mlx_pixel_put(&(app->img), x * (192 / size) + i, y * (192 / size) + j, 0x333333);
			j++;
		}
		i++;
	}
}

void	add_wall_tile(t_app *app, int x, int y, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < 192 / size)
	{
		j = 0;
		while (j < 192 / size)
		{
			my_mlx_pixel_put(&(app->img), x * (192 / size) + i, y * (192 / size) + j, 0x999999);
			j++;
		}
		i++;
	}
}

void	add_full_tile(t_app *app, int x, int y, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < 192 / size)
	{
		j = 0;
		while (j < 192 / size)
		{
			my_mlx_pixel_put(&(app->img), x * (192 / size) + i, y * (192 / size) + j, 0xEEEEEE);
			j++;
		}
		i++;
	}
}

void	draw_mini_player(t_app *app)//a deplacer un peu en fonction du decalage avec le mur
{
	int	x;
	int	y;
	int	i;

	x = 0;
	i = 0;
	while (x < 4)
	{
		y = 0;
		while (y < 4)
		{
			my_mlx_pixel_put(&(app->img), 192 / 2  - 2 + x, 192 / 2 - 2 + y, 0xFF0000);
			y++;
		}
		x++;
	}
	while (i < 15)
	{
		my_mlx_pixel_put(&(app->img), (192 / 2 + (i * cos(app->ray.game_state.pa)/2)),
		(192 / 2 + (i * sin(app->ray.game_state.pa)/2)), 0xFF0000);
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
				add_empty_tile(app, j, i, size); //check si la map est un espace
			else//check si la map est un mur
				add_wall_tile(app, j, i, size);
			// else//si la map est un sol (0)
			// 	add_full_tile(app, j, i, size);
			j++;
			s_x++;
		}
		i++;
		s_y++;
	}
	draw_mini_player(app);
	draw_grid(app, size);
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
