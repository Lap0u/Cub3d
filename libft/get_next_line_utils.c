/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 14:28:05 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/09/22 11:20:01 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strcpy(const char *src)
{
	int		i;
	char	*dst;

	i = 0;
	while (src[i] && src[i] != '\n')
		i++;
	dst = malloc(sizeof(char) * i + 1);
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (src[i] && src[i] != '\n')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	ft_count_endl(const char *str)
{
	int	i;
	int	cmpt;

	i = 0;
	cmpt = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			cmpt++;
		i++;
	}
	return (cmpt);
}

char	*ft_return_free(char *str)
{
	free(str);
	return (NULL);
}
