/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 13:17:40 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/29 13:27:42 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"

void	print_data(t_data *data)
{
	printf("AFFICHAGE DES DONNEES\n\n");
	if (data->no_path)
		printf("NO : %s\n", data->no_path);
	if (data->so_path)
		printf("SO : %s\n", data->so_path);
	if (data->ea_path)
		printf("EA : %s\n", data->ea_path);
	if (data->we_path)
		printf("WE : %s\n", data->we_path);
	printf("%d\n", data->floor_col[0]);
	printf("%d\n", data->floor_col[1]);
	printf("%d\n", data->floor_col[2]);
	printf("%d\n", data->ceiling_col[0]);
	printf("%d\n", data->ceiling_col[1]);
	printf("%d\n", data->ceiling_col[2]);
	printf("FIN\n\n");
}