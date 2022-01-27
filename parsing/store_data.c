/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 12:38:47 by cbeaurai          #+#    #+#             */
/*   Updated: 2022/01/27 10:41:12 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"

void	init_data(t_vars **data)
{
	*data = malloc(sizeof(t_vars));
	if (*data == NULL)
		return ;
	ft_bzero(*data, sizeof(t_vars));
	(*data)->ceiling_col[0] = -1;
	(*data)->ceiling_col[1] = -1;
	(*data)->ceiling_col[2] = -1;
	(*data)->floor_col[0] = -1;
	(*data)->floor_col[1] = -1;
	(*data)->floor_col[2] = -1;
}

t_vars	*get_data(char *str)
{
	t_vars	*data;
	int		fd;
	
	data = NULL;
	fd = ft_open_file_read(str);
	if (fd < 0)
		exit (bad_fd());
	init_data(&data);
	if (data == NULL)
	{
		close(fd);
		return (NULL);
	}
	get_values(data, fd);
	get_map(data, fd);
	print_data(data);
	// printf("HAHAHAHAH NO : %s\n", data->no_path);
	close(fd);
	check_data(data); //exit si pb
	print_data(data);
	return (data);
}