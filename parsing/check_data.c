/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 12:50:12 by cbeaurai          #+#    #+#             */
/*   Updated: 2022/01/31 15:41:04 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"

int	check_inside(t_vars *data)
{
	int	i;

	i = 1;
	while (data->map[i + 1])
	{
		if (check_surround(data->map[i], data->map[i -1],
				data->map[i + 1]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_walls(t_vars *data)
{
	int	i;

	if (tab_len(data->map) <= 2)
		return (0);
	i = 1;
	while (data->map[i + 1])
	{
		if (!char_inset(data->map[i][0], "1 ")
			|| !char_inset(data->map[i][ft_strlen(data->map[i]) - 1], "1 "))
			return (0);
		i++;
	}
	if (full_line(data->map[i]) == 0 || full_line(data->map[0]) == 0)
		return (0);
	return (1);
}

int	check_player(t_vars *data)
{
	int	i;
	int	j;
	int	b_player;

	i = 0;
	b_player = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (char_inset(data->map[i][j], "NSWE") && b_player == 0)
				b_player = 1;
			else if (char_inset(data->map[i][j], "NSWE") && b_player == 1)
				data->map[i][j] = '0';
			j++;
		}
		i++;
	}
	return (b_player);
}

void	check_data(t_vars *data)
{
	if (check_player(data) == 0)
	{
		ft_putstr_fd("Error\nNo starting position found in map\n", 2);
		free_data(data);
		exit(1);
	}
	if (check_walls(data) == 0 || check_inside(data) == 0)
	{
		ft_putstr_fd("Error\nMap not closed\n", 2);
		free_data(data);
		exit(1);
	}
}
