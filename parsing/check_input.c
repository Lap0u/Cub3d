/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 13:03:58 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/23 14:33:26 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"

int	good_id(char *str)
{
	if (ft_strcmp(str, "NO") != 0 && ft_strcmp(str, "SO") != 0 &&
		ft_strcmp(str, "ES") != 0 && ft_strcmp(str, "WE") != 0 &&
		ft_strcmp(str, "F") != 0 && ft_strcmp(str, "C") != 0)
		return (0);
	return (1);
}

int	tab_len(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	check_file(char *str)
{
	int	ret;

	ret = ft_open_file_read(str);
	if (ret < 0)
		return (0);
	else
		close(ret);
	return (1);
}

int	check_colour(char *str)
{
	char	**val;
	int		i;
	int		ret;

	i = 0;
	val = ft_split(str, ',');
	if (tab_len(val) != 3 || str[ft_strlen(str) -1] == ',')
	{
		ft_free_3dtab(val);
		return (0);
	}
	while (i < 3)
	{
		ret = ft_atoi(val[i]);
		if (ret < 0 || ret > 255)
		{
			ft_free_3dtab(val);
			return (0);
		}
		i++;
	}
	ft_free_3dtab(val);
	return (1);
}

int	second_args(char *str, char *id)
{
	int ret;

	ret = 1;
	if (ft_strlen(id) == 1)
		ret = check_colour(str);
	else
		ret = check_file(str);
	return (ret);
}

int	parse_line(char *str)
{
	char	**args;

	if (str[0] == 0)
		return (1);
	args = ft_split(str, ' ');
	if (!args)
		return (0);
	if (tab_len(args) != 2)
	{
		ft_free_3dtab(args);
		return (0);
	}
	if (good_id(args[0]) == 0 || second_args(args[1], args[0]) == 0)
	{
		ft_free_3dtab(args);
		return (0);
	}
	ft_free_3dtab(args);
	return (1);
}

int	check_lines(int fd)
{
	char	*str;
	int		ret;
	int		counter;

	counter = 1;
	while (1)
	{
		ret = get_next_line(fd, &str);
		if (ret > 0)
		{
			if (parse_line(str) == 0)
			{
				free(str);
				close(fd);
				return (counter);
			}
			free(str);
		}
		else
			break ;
		counter++;
	}
	close(fd);
	return (-1);
}

int	check_input(char *file)
{
	int	fd;
	int	err;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nCan't open this file\n", 2);
		return (0);
	}
	err = check_lines(fd);
	if (err != -1)
	{
		ft_putstr_fd("Error\nWrong map configuration at line ", 2);
		ft_putnbr_fd(err, 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	return (1);
}