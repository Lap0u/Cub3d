/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 13:03:58 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/23 15:22:11 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"

int	good_id(char *str)
{
	if (ft_strcmp(str, "NO") != 0 && ft_strcmp(str, "SO") != 0
		&& ft_strcmp(str, "ES") != 0 && ft_strcmp(str, "WE") != 0
		&& ft_strcmp(str, "F") != 0 && ft_strcmp(str, "C") != 0)
		return (0);
	return (1);
}

int	tab_len(char **tab)
{
	int	i;

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
	int	ret;

	ret = 1;
	if (ft_strlen(id) == 1)
		ret = check_colour(str);
	else
		ret = check_file(str);
	return (ret);
}

int	check_map(char *str, int fd)
{
	if (str[0] != '1')
		return (1);
	(void)fd;
	return (1);/////regarder si la map es bonne
	return (0);
}

int	parse_line(char *str, int fd)
{
	char	**args;

	if (str[0] == 0)
		return (1);
	if (str[0] == '1')
		return (check_map(str, fd));
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

int	ret_int_free(int ret, char *tofree)
{
	free(tofree);
	return (ret);
}

int	check_lines(int fd)
{
	char	*str;
	int		counter;
	int		ret;

	counter = 1;
	while (1)
	{
		ret = get_next_line(fd, &str);
		if (ret > 0)
		{		
			if (parse_line(str, fd) == 0)
				return (ret_int_free(counter, str));
			free(str);
		}
		else
			break ;
		counter++;
	}			
	if (parse_line(str, fd) == 0)
		return (ret_int_free(counter, str));
	free(str);
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
	close(fd);
	if (err != -1)
	{
		ft_putstr_fd("Error\nWrong map configuration at line ", 2);
		ft_putnbr_fd(err, 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	return (1);
}
