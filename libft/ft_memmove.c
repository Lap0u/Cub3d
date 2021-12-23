/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 23:17:19 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/09/22 11:41:39 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int		i;
	char	*dst_prim;
	char	*src_prim;

	src_prim = (char *)src;
	dst_prim = (char *)dst;
	i = 0;
	if (&dst_prim[i] > &src_prim[i])
	{
		i = len - 1;
		while (i >= 0)
		{
			dst_prim[i] = src_prim[i];
			i--;
		}
	}
	else if (&dst_prim[i] < &src_prim[i])
	{
		while (i < (int)len)
		{
			dst_prim[i] = src_prim[i];
			i++;
		}
	}
	return (dst);
}
