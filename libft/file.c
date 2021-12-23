/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 00:15:26 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/09/27 14:26:28 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_open_file_read(char *str)
{
	char	buff[10];
	int		fd;
	int		bytes;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (fd);
	bytes = read(fd, buff, 1);
	close(fd);
	if (bytes < 0)
		return (bytes);
	fd = open(str, O_RDONLY);
	return (fd);
}

int	ft_open_file_write(char *str)
{
	int		fd;

	fd = open(str, O_WRONLY);
	return (fd);
}

int	ft_open_file_write_create(char *str)
{
	int		fd;

	fd = open(str, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	return (fd);
}

int	ft_open_file_read_write(char *str)
{
	char	buff[10];
	int		fd;
	int		bytes;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (fd);
	bytes = read(fd, buff, 1);
	close(fd);
	if (bytes < 0)
		return (bytes);
	fd = open(str, O_RDWR);
	return (fd);
}
