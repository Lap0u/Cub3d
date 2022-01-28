/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 12:49:46 by cbeaurai          #+#    #+#             */
/*   Updated: 2022/01/28 15:05:59 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"


void	add_col(t_vars *data, char *val, char c)
{
	char **tab;

	printf("val = %s\n", val);
	tab = ft_split(val, ',');
	if (tab == NULL)
		return ;
	if (c == 'C')
	{
		data->ceiling_col[0] = ft_atoi(tab[0]);
		data->ceiling_col[1] = ft_atoi(tab[1]);
		data->ceiling_col[2] = ft_atoi(tab[2]);
	}
	else if (c == 'F')
	{	
		data->floor_col[0] = ft_atoi(tab[0]);
		data->floor_col[1] = ft_atoi(tab[1]);
		data->floor_col[2] = ft_atoi(tab[2]);
	}
	ft_free_3dtab(tab);
	free(val);
}

char	*skip_id(char *str)
{
	char	**tab;
	char	*res;
	int		i;

	i = 1;
	res = ft_strdup("");
	if (res == NULL)
		return (NULL);
	tab = ft_split(str, ' ');
	if (tab == NULL)
		return (free(res), NULL);
	while (tab[i])
	{
		res = ft_strjoin(res, tab[i]);
		free(tab[i]);
		if (res == NULL)
			return (NULL);
		i++;
	}
	free(tab[0]);
	free(tab);
	return (res);
}

void	add_line(t_vars *data, char *str)
{
	char	*path;

	path = skip_id(str);
	if (ft_strncmp(str, "NO ", 3) == 0 && data->no_path == NULL)
		data->no_path = path;
	else if (ft_strncmp(str, "SO ", 3) == 0 && data->so_path == NULL)
		data->so_path = path;
	else if (ft_strncmp(str, "EA ", 3) == 0 && data->ea_path == NULL)
		data->ea_path = path;
	else if (ft_strncmp(str, "WE ", 3) == 0 && data->we_path == NULL)
		data->we_path = path;
	else if (ft_strncmp(str, "F ", 2) == 0)
		add_col(data, path, 'F');
	else if (ft_strncmp(str, "C ", 2) == 0)
		add_col(data, path, 'C');
	else
		free(path);
}

void	get_values(t_vars *data, int fd)
{
	char	*line;
	int		count;
	int		ret;

	count = 0;
	line = NULL;
	ret = -1;
	while (count < 6 && ret != -1)
	{
		ret = get_next_line(fd, &line);
		if (line[0] != 0)
		{
			add_line(data, line);
			count++;
		}
		free(line);
	}
}
