/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 14:27:27 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/09/29 10:44:47 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

int	ft_error_case(int read_bytes, char *str, char **line)
{
	if (read_bytes < 0)
		return (-1);
	else if (read_bytes == 0 && str == NULL)
	{
		*line = ft_strdup("");
		if (*line == NULL)
			return (-1);
		return (0);
	}
	return (ft_solve(str, line));
}

char	*ft_realoc_cat(char *dst, const char *src)
{
	char	*temp;
	int		i;
	int		j;

	i = -1;
	j = -1;
	temp = malloc(sizeof(char) * (ft_strlen(dst) + ft_strlen(src) + 1));
	if (temp == NULL)
	{
		free(dst);
		return (NULL);
	}
	while (dst[++i])
		temp[i] = dst[i];
	while (src[++j])
		temp[i + j] = src[j];
	temp[i + j] = '\0';
	free(dst);
	return (temp);
}

char	*ft_save_next(char *str, int return_value)
{
	int		index;
	char	*temp;
	int		j;

	if (return_value == 0)
		return (ft_return_free(str));
	j = 0;
	index = 0;
	while (str[index] && str[index] != '\n')
		index++;
	while (str[index + j + 1])
		j++;
	if (j == 0)
		return (ft_return_free(str));
	temp = malloc(sizeof(char) * j + 1);
	if (temp == NULL)
		return (ft_return_free(str));
	j = -1;
	while (str[++j + index + 1] != '\0')
		temp[j] = str[j + index + 1];
	temp[j] = '\0';
	free(str);
	return (temp);
}

int	ft_solve_gnl(char *str, char **line)
{
	int	temp;

	temp = ft_count_endl(str);
	if (temp)
	{
		*line = ft_strcpy(str);
		if (*line == NULL)
		{
			free(str);
			return (-1);
		}
	}
	else
	{
		*line = ft_strcpy(str);
		if (*line == NULL)
		{
			free(str);
			return (-1);
		}
		return (0);
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	t_gnl		gnl;
	static char	*str;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	gnl.read_bytes = 1;
	while (gnl.read_bytes > 0)
	{
		gnl.read_bytes = read(fd, gnl.buff, BUFFER_SIZE);
		gnl.buff[gnl.read_bytes] = '\0';
		if (str == NULL)
			str = ft_strdup(gnl.buff);
		else
		{
			str = ft_realoc_cat(str, gnl.buff);
			if (str == NULL)
				return (-1);
		}
		if (ft_count_endl(str))
			break ;
	}
	gnl.return_value = ft_error_case(gnl.read_bytes, str, line);
	if (gnl.return_value >= 0)
		str = ft_save_next(str, gnl.return_value);
	return (gnl.return_value);
}
