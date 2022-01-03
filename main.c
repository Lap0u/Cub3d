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
	t_app	my_app;
	
	if (check_arg(av[1], ac) == 0)
		return (1);
	if (check_input(av[1]) == 0)
		return (1);
	data = get_data(av[1]);
	if (data == NULL)
		return (bad_malloc());
	my_app.data = *(data);
	init_app(&my_app, "Cub3D",
			34, 13);
	mlx_key_hook(my_app.win, &player_input, &my_app);
	mlx_hook(my_app.win, 17, 0, destroy_game_data, &my_app);
	mlx_loop_hook(my_app.mlx, &routine, &my_app);
	mlx_loop(my_app.mlx);
	free_data(data);
	return (0);
}
