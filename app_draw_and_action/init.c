/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okushnir <okushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 22:41:34 by okushnir          #+#    #+#             */
/*   Updated: 2022/01/02 22:41:41 by okushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../cub3d.h"
#include "../libft/libft.h"


int	is_texture_exist(const char *filename)
{
	int	fd;

	fd = 0;
	write(1, filename, ft_strlen(filename));
	write(1, "\n", 1);
	fd = open(filename, O_RDONLY);
	if (fd > 0)
		close(fd);
	else
		write(2, "Error\nThe texture doesn't exist\n", 32);
	return (1);
}

void	init_path(t_app *app)
{
	if (is_texture_exist(app->data.no_path))
		app->path[0] = app->data.no_path;
	if (is_texture_exist(app->data.so_path))
		app->path[1] = app->data.so_path;
	if (is_texture_exist(app->data.we_path))
		app->path[2] = app->data.we_path;
	if (is_texture_exist(app->data.ea_path))
		app->path[3] = app->data.ea_path;
}

void	init_sprite(t_app *app)
{
	int			i;
	t_texture	*spt;
	char		**m_path;

	i = 0;
	spt = app->sp;
	m_path = app->path;
	while (i < 4)
	{
		spt[i].img = mlx_xpm_file_to_image(app->mlx, m_path[i],
				&spt[i].sp_x, &spt[i].sp_y);
		spt[i].addr = mlx_get_data_addr(spt[i].img, &(spt[i].bpp),
				&(spt[i].size), &(spt[i].endian));
		i++;
	}
}

void	init_app(t_app *app, char *title, int w, int h)
{
	app->mlx = mlx_init();
	if (app->mlx == NULL)
		exit (1);
	init_path(app);
	init_sprite(app);
	app->x = w * app->sp[0].sp_x;
	app->y = h * app->sp[0].sp_y;
	app->win = mlx_new_window(app->mlx, app->x, app->y, title);
	if (app->win == NULL)
	{
		free(app->mlx);
		exit (1);
	}
	app->sp[3].game_state.player_x = 0;
	app->sp[3].game_state.player_y = 0;
	app->sp[3].game_state.player_old_x = 0;
	app->sp[3].game_state.player_old_y = 0;
	app->image_is_destroyed = 0;
	app->total_col = 0;
	app->taken_col = 0;
	app->flag = 0;
	app->nb_mvmt = 0;
}

void	player_position_init(t_app *app, int x, int y)
{
	if (app->sp[3].game_state.player_x == 0
		&& app->sp[3].game_state.player_y == 0)
	{
		app->sp[3].game_state.player_x = x;
		app->sp[3].game_state.player_y = y;
		app->sp[3].game_state.player_old_x = x;
		app->sp[3].game_state.player_old_y = y;
	}	
}
