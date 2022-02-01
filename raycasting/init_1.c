/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:36:37 by cbeaurai          #+#    #+#             */
/*   Updated: 2022/01/31 16:38:21 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_texture_exist(const char *filename)
{
	int	fd;

	fd = 0;
	fd = open(filename, O_RDONLY);
	if (fd > 0)
		close(fd);
	else
		write(2, "Error\nThe texture doesn't exist\n", 32);
	return (1);
}

void	init_path(t_app *app)
{
	if (is_texture_exist(app->vars->no_path))
		app->path[0] = app->vars->no_path;
	if (is_texture_exist(app->vars->so_path))
		app->path[1] = app->vars->so_path;
	if (is_texture_exist(app->vars->we_path))
		app->path[2] = app->vars->we_path;
	if (is_texture_exist(app->vars->ea_path))
		app->path[3] = app->vars->ea_path;
}

void	init_texture(t_app *app)
{
	int			i;
	t_data		*txr;
	char		**m_path;

	i = 0;
	txr = app->txr;
	m_path = app->path;
	while (i < 4)
	{
		txr[i].img = mlx_xpm_file_to_image(app->mlx, m_path[i],
				&txr[i].w, &txr[i].h);
		free(m_path[i]);
		if (txr[i].img == NULL)
		{
			printf("this is not a good image(free a gerer)\n");
			exit(1);
		} // il faut free et exit ici
		//gerer l'erreur si mauvaise images
		txr[i].addr = mlx_get_data_addr(txr[i].img, &(txr[i].bpp),
				&(txr[i].size), &(txr[i].endian));
		i++;
	}
}
