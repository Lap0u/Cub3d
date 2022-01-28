/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 13:03:58 by cbeaurai          #+#    #+#             */
/*   Updated: 2022/01/28 16:31:58 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"

int	ret_int_free(int ret, char *tofree)
{
	free(tofree);
	return (ret);
}

int	good_id(char *str)
{
	if (ft_strcmp(str, "NO") != 0 && ft_strcmp(str, "SO") != 0
		&& ft_strcmp(str, "EA") != 0 && ft_strcmp(str, "WE") != 0
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
		if (ret < 0 || ret > 255 || isonlyset(val[i], "0123456789") == 0)
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

	// printf("id = %s\tval = %s\n", id, str);
	ret = 1;
	if (ft_strlen(id) == 1)
		ret = check_colour(str);
	else
		ret = check_file(str);
	return (ret);
}

int	isonlyset(char *str, char *set)
{
	int i;
	int j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (j < ft_strlen(set))
		{
			if (str[i] == set[j])
				break;
			j++;
		}
		if (j == ft_strlen(set))
			return (0);
		i++;
	}
	return (1);
}


int	check_map(char *str, int fd)
{
	int ret;

	if (str[0] != '1')
		return (1);
	if (isonlyset(str, " 10NSWE") == 0)
		return (0);
	while (1)
	{
		ret = get_next_line(fd, &str);
		if (ret > 0)
		{
			if (isonlyset(str, " 10NSWE") == 0)
				return (0);
			free(str);
		}
		else
			break;
	}
	if (isonlyset(str, " 10NSWE") == 0)
		return(ret_int_free(0, str));
	return (ret_int_free(1, str));
}

char	*get_colours(char **args)
{
	int		i;
	char	*temp;

	temp = ft_strdup("");
	if (temp == NULL)
		return (NULL);
	i = 1;
	while (args[i])
	{
		temp = ft_strjoin(temp, args[i]);
		free(args[i]);
		args[i] = NULL;
		if (temp == NULL)
			return (NULL);
		i++;
	}
	// printf("%s\n", temp);
	return (temp);

}



int	isonlyspace(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f' || str[i] == '\r'
		|| str[i] == ' ')
			i++;
		else
			return (0);
	}
	return (1);
}

int	parse_line(char *str, int fd)
{
	char		**args;
	static int	i = 0;
	
	if (str[0] == 0)
		return (1);
	if (isonlyspace(str) == 1)
		return (0);
	if (i == 6)
		return (check_map(str, fd));
	args = ft_split(str, ' ');
	if (!args)
		return (0);
	if (args[0][0] == 'C' || args[0][0] == 'F')
		args[1] = get_colours(args);
	if (tab_len(args) != 2 || !args[1])
	{
		// printf("noright\n");
		ft_free_3dtab(args);
		return (0);
	}
	if (good_id(args[0]) == 0 || second_args(args[1], args[0]) == 0)
	{
		ft_free_3dtab(args);
		return (0);
	}
	ft_free_3dtab(args);
	i++;
	return (1);
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
