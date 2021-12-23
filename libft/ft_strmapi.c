/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:12:46 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/09/22 11:32:28 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*news;
	int		i;

	if (!s || !f)
		return (NULL);
	i = 0;
	news = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (news == NULL)
		return (NULL);
	while (i < ft_strlen(s))
	{
		news[i] = f(i, s[i]);
		i++;
	}
	news[i] = '\0';
	return (news);
}
