/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 13:03:59 by cbeaurai          #+#    #+#             */
/*   Updated: 2022/01/27 14:21:28 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"

int main(int ac, char **av)
{
	t_vars	*data;
	t_app	my_app;
	
	if (check_arg(av[1], ac) == 0)
		return (1);
	if (check_input(av[1]) == 0)
		return (1);
	data = get_data(av[1]);
	if (data == NULL)
		return (bad_malloc());
	my_app.vars = data;
	init_app(&my_app, "Cub3D", RES_X, RES_Y);
	mlx_hook(my_app.win, 2, 1L << 0, &player_input, &my_app);
	mlx_hook(my_app.win, 17, 0, destroy_game_data, &my_app);
	mlx_loop_hook(my_app.mlx, &routine, &my_app);
	mlx_loop(my_app.mlx);
	return (0);
}
