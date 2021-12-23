/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 23:20:24 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/09/22 11:30:37 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_prim;
	unsigned char	*s2_prim;

	s1_prim = (unsigned char *)s1;
	s2_prim = (unsigned char *)s2;
	i = 0;
	while (i < n && (s1_prim[i] || s2_prim[i]))
	{
		if (s1_prim[i] != s2_prim[i])
			return (s1_prim[i] - s2_prim[i]);
		i++;
	}
	return (0);
}
