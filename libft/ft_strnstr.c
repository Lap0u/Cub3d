/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 23:21:00 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/09/22 11:28:31 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (i < len && big[i])
	{
		j = 0;
		while ((unsigned char)little[j] == (unsigned char)big[j + i]
			&& i + j < len && big[i + j])
		{
			j++;
			if ((unsigned char)little[j] == '\0')
				return ((char *)big + i);
		}
		i++;
	}
	return (NULL);
}
