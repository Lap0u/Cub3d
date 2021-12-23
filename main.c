/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 13:03:59 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/23 13:04:00 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"

int main(int ac, char **av)
{
	if (check_arg(av[1], ac) == 0)
		return (1);
	if (check_input(av[1]) == 0)
		return (1);
	// t_datas = get_datas(av[1]);
	return (0);
}