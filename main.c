/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 13:03:59 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/29 15:51:41 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"

int main(int ac, char **av)
{
	t_data	*data;
	
	if (check_arg(av[1], ac) == 0)
		return (1);
	if (check_input(av[1]) == 0)
		return (1);
	data = get_data(av[1]);
	if (data == NULL)
		return (bad_malloc());
	free_data(data);
	return (0);
}
