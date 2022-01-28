#include "../cub3d.h"
// #include "raycaster.h"

void	draw_grid(t_app *app, float offx, float offy, int size)
{
	int x;
	int y;

	x = offx;
	while (x < 192)
	{
		y = offy;
		while (y < 192)
		{
			if ((y % (192 / size) == 0 || x % (192 / size) == 0) && x + offx >= 0 && y + offy >= 0)
				my_mlx_pixel_put(&(app->img), x + offx, y + offy, 0x0000FF);
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

void	draw_mini_player(t_app *app, float offx, float offy)//a deplacer un peu en fonction du decalage avec le mur
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
			my_mlx_pixel_put(&(app->img), 192 / 2  - 2 + x + offx, 192 / 2 - 2 + y + offy, 0xFF0000);
			y++;
		}
		x++;
	}
	while (i < 15)
	{
		my_mlx_pixel_put(&(app->img), (192 / 2 + (i * cos(app->ray.game_state.pa)/2) + offx),
		(192 / 2 + (i * sin(app->ray.game_state.pa)/2) + offy), 0xFF0000);
		i++;
	}
}

void	draw_around_player(t_app *app, float p_x, float p_y, int size)
{
	float	true_x;
	float	true_y;
	int	s_x;
	int	s_y;
	int i;
	int	j;
	float	off_x;
	float	off_y;

	i = 0;
	true_x = p_x / 64;
	true_y = p_y / 64;
	off_x = (int)p_x % 64 / size - size / 2;
	off_y = (int)p_y % 64 / size - size / 2;

	s_x = true_x - size / 2;
	s_y = true_y - size / 2;
	while (i < size)
	{
		j = 0;
		s_x = true_x - size / 2;
		while (j < size)
		{
			if (s_x < 0 || s_y < 0 || s_x > app->map_x || s_y > app->map_y)
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
	draw_grid(app, off_x, off_y, size);
	draw_mini_player(app, off_x, off_y);
}