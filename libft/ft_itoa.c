/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 23:16:06 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/09/22 11:50:49 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_pow(int nb, int power)
{
	int	res;

	res = 1;
	while (power > 1)
	{
		res *= nb;
		power--;
	}
	return (res);
}

static int	ft_nbr_len(int n)
{
	long long int	nbr;
	int				cmpt;

	if (n == 0)
		return (1);
	cmpt = 0;
	nbr = n;
	if (nbr < 0)
	{
		nbr = -nbr;
		cmpt++;
	}
	while (nbr > 0)
	{
		nbr /= 10;
		cmpt++;
	}
	return (cmpt);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		div;
	int		len;

	len = ft_nbr_len(n);
	str = malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	if (n < 0)
	{
		div = -ft_pow(10, len - 1);
		str[i++] = '-';
	}
	else
		div = ft_pow(10, len);
	while (i < len)
	{
		str[i++] = n / div + '0';
		n %= div;
		div /= 10;
	}
	str[i] = '\0';
	return (str);
}
