/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 22:41:01 by okushnir          #+#    #+#             */
/*   Updated: 2022/01/27 10:43:42 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"


int	check_pos_player(t_app *app)
{
	t_map	*p;
	int		len;
	int		str_len;
	int		i;

	i = 0;
	p = app->carte;
	len = app->sp[3].game_state.player_y;
	str_len = app->sp[3].game_state.player_x;
	while (i < len)
	{
		p = p->next;
		i++;
	}
	if (p->line[str_len] == '1')
	{
		app->sp[3].game_state.player_x = app->sp[3].game_state.player_old_x;
		app->sp[3].game_state.player_y = app->sp[3].game_state.player_old_y;
		return (0);
	}
	else if (p->line[str_len] == 'C' || p->line[str_len] == 'E')
		return (change_map(app, &(p->line[str_len])));
	return (1);
}

int	change_map(t_app *app, char *pos)
{
	if (*pos == 'C')
	{
		*pos = '0';
		app->taken_col++;
	}
	else if (*pos == 'E')
	{
		if (app->taken_col != app->total_col)
		{
			app->sp[3].game_state.player_x = app->sp[3].game_state.player_old_x;
			app->sp[3].game_state.player_y = app->sp[3].game_state.player_old_y;
			return (0);
		}
		else
			destroy_game_data(app);
	}
	return (1);
}

int	player_input(int key, void *data)
{
	t_app	*app;
	int		x;
	int		y;

	app = (t_app *)(data);
	x = app->sp[3].game_state.player_x;
	y = app->sp[3].game_state.player_y;
	app->sp[3].game_state.player_old_x = x;
	app->sp[3].game_state.player_old_y = y;
	return (player_input_body(key, app));
}

int	player_input_body(int key, t_app *app)
{
	if (key == LEFT || key == RIGHT || key == DOWN || key == UP)
	{
		if (key == LEFT)
			app->sp[3].game_state.player_x += -1;
		else if (key == RIGHT)
			app->sp[3].game_state.player_x += 1;
		else if (key == DOWN)
			app->sp[3].game_state.player_y += 1;
		else if (key == UP)
			app->sp[3].game_state.player_y += -1;
		if (check_pos_player(app))
		{
			app->nb_mvmt++;
			write(1, "current number of movements: ", 30);
			ft_putnbr_fd(app->nb_mvmt, 1);
			write(1, "\n: ", 1);
		}
	}
	if (key == ESC)
		destroy_game_data(app);
	return (1);
}

int	routine(void *data)
{
	t_app		*app;
	int			x;
	int			y;
	int			discard;

	app = (t_app *)(data);
	app->image = mlx_new_image(app->mlx, app->x, app->y);
	app->image_addr = mlx_get_data_addr(app->image,
			&discard, &discard, &discard);
	app->image_is_destroyed = 0;
	drow_map(app);
	x = app->sp[3].game_state.player_x;
	y = app->sp[3].game_state.player_y;
	draw_img_at_pos(app, &(app->sp[3]), 48 * x, 48 * y);
	mlx_put_image_to_window(app->mlx, app->win, app->image, 0, 0);
	mlx_destroy_image(app->mlx, app->image);
	app->image = NULL;
	app->image_is_destroyed = 1;
	return (0);
}