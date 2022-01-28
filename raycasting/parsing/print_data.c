/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 13:17:40 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/29 15:54:21 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"

void	print_map(char **map)
{
	int i;

	i = 0;
	printf("AFFICHAGE DE LA MAP :\n\n");
	while (map[i])
		printf("%s\n", map[i++]);
	printf("\n");
}

void	print_data(t_data *data)
{
	printf("AFFICHAGE DES DONNEES :\n\n");
	if (data->no_path)
		printf("NO : %s\n", data->no_path);
	if (data->so_path)
		printf("SO : %s\n", data->so_path);
	if (data->ea_path)
		printf("EA : %s\n", data->ea_path);
	if (data->we_path)
		printf("WE : %s\n", data->we_path);
	printf("floor : %d %d %d\n", data->floor_col[0],
	data->floor_col[1], data->floor_col[2]);
	printf("ceiling : %d %d %d\n\n", data->ceiling_col[0], 
	data->ceiling_col[1], data->ceiling_col[2]);
	print_map(data->map);
	printf("FIN\n\n");
}