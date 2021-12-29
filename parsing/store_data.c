/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 12:38:47 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/29 13:32:43 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"

t_data	*get_data(char *str)
{
	t_data	*data;
	int		fd;
	
	data = NULL;
	fd = ft_open_file_read(str);
	if (fd < 0)
		exit (bad_fd());
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	ft_bzero(data, sizeof(t_data));
	get_values(data, fd);
	get_map(data, fd);
	close(fd);
	check_data(data); //exit si pb
	return (data);
}