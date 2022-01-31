/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 14:31:56 by cbeaurai          #+#    #+#             */
/*   Updated: 2022/01/31 15:55:56 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"

int	char_inset(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	full_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	check_surround(char *check, char *prev, char *next)
{
	int	i;

	i = 1;
	while (check[i])
	{
		if (char_inset(check[i], "NSWE0"))
		{
			if (i >= ft_strlen(prev) || i >= ft_strlen(next))
				return (0);
			else if (check[i - 1] == ' ' || check[i + 1] == ' '
				|| prev[i] == ' ' || next[i] == ' ')
				return (0);
		}
		i++;
	}
	return (1);
}
