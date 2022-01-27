/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroying.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 22:41:17 by okushnir          #+#    #+#             */
/*   Updated: 2022/01/27 11:44:12 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"

int	destroy_game_data(void *data)
{
	t_app		*app;
	int			i;
	t_data	*spt;

	app = (t_app *)data;
	i = 0;
	spt = app->txr;
	while (i < 4)
	{
		mlx_destroy_image(app->mlx, spt[i].img);
		i++;
	}
	if (app->image_is_destroyed == 0)
		mlx_destroy_image(app->mlx, app->image);
	mlx_clear_window(app->mlx, app->win);
	mlx_destroy_window(app->mlx, app->win);
	mlx_destroy_display(app->mlx);
	free(app->mlx);
	// ft_lstclear(&(app->carte));
	// free(app->vars);
	exit (0);
}
