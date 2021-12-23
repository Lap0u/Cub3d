/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:44:33 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/09/22 11:34:54 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (dst[i] && i < dstsize)
		i++;
	j = 0;
	while (i + j + 1 < dstsize && src[j])
	{
		dst[j + i] = src[j];
		j++;
	}
	if (i < dstsize)
		dst[j + i] = '\0';
	return (i + ft_strlen(src));
}
