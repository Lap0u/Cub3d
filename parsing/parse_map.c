/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 12:49:58 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/29 15:52:42 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"

void	add_map_line(char ***map, char *new)
{
	int		i;
	char	**res;

	i = tab_len(*map);
	res = malloc(sizeof(char *) * (i + 2));
	if (res == NULL)
		return (ft_free_3dtab(*map));
	i = 0;
	while ((*map)[i] != NULL)
	{
		res[i] = (*map)[i];
		i++;
	}
	res[i] = new;
	res[i + 1] = NULL;
	free(*map);
	*map = res;
}

void	add_map(char *first_line, int fd, t_data *data)
{
	int		ret;
	char	*line;

	line = NULL;
	data->map = malloc(sizeof(char *) * 2);
	if (data->map == NULL)
		return(free(first_line));
	data->map[0] = first_line;
	data->map[1] = NULL;
	while (1)
	{
		ret = get_next_line(fd, &line);
		if (ret < 0)
			return ;
		add_map_line(&data->map, line);
		if (data->map == NULL || ret == 0)
			return ;
	}
}

void	get_map(t_data *data, int fd)
{
	char	*line;
	int		ret;
	line = NULL;
	while(1)
	{
		ret = get_next_line(fd, &line);
		if (ret < 0)
			return (free(line));
		if (line[0] != 0)
		{
			add_map(line, fd, data);
			return ;
		}
	}
}