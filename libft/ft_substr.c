/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 23:22:11 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/09/22 11:57:47 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_setup_news(void)
{
	char	*str;

	str = malloc(sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*news;

	if (!s)
		return (NULL);
	i = 0;
	if (start >= (unsigned int)ft_strlen(s))
	{
		news = ft_setup_news();
		return (news);
	}
	while (s[i] && i < len + start)
		i++;
	if (i - start < len)
		len = i - start;
	news = malloc(sizeof(char) * len + 1);
	if (news == NULL)
		return (NULL);
	i = -1;
	while (++i < len && s[i + start])
		news[i] = s[i + start];
	news[i] = '\0';
	return (news);
}
