/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 13:04:06 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/23 15:21:21 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"

int	check_extension(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len < 4)
	{
		ft_putstr_fd("Error\nWrong map file, .cub required\n", 2);
		return (0);
	}
	if (ft_strcmp(&str[len - 4], ".cub") != 0)
	{
		ft_putstr_fd("Error\nWrong map file, .cub required\n", 2);
		return (0);
	}
	return (1);
}

int	try_open(char *str)
{
	int	ret;

	ret = ft_open_file_read(str);
	if (ret < 0)
	{
		ft_putstr_fd("Error\nCan't open this file\n", 2);
		return (0);
	}
	else
		close(ret);
	return (1);
}

int	check_arg(char *av, int ac)
{
	if (ac != 2)
	{
		ft_putstr_fd("Error\ncub3D only takes one file as arugment\n", 2);
		return (0);
	}
	if (check_extension(av) == 0 || try_open(av) == 0)
		return (0);
	return (1);
}
