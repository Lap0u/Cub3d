/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 12:36:12 by cbeaurai          #+#    #+#             */
/*   Updated: 2022/01/27 10:40:50 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"

int	bad_malloc()
{
	ft_putstr_fd("Error while allocating memory space, exiting...\n", 2);
	return (1);
}

int	bad_fd()
{
	ft_putstr_fd("Can't open the map, exiting...\n" , 2);
	return (1);
}

void	free_data(t_vars *data)
{
	int i;

	if (data->map)
	{
		while (data->map[i])
			free(data->map[i++]);
		free(data->map);
	}
	free(data->ea_path);
	free(data->so_path);
	free(data->no_path);
	free(data->we_path);
	free(data);
}