#include "../cub3d.h"
#include "../libft/libft.h"

void	init_check_map(t_check_map *my_check)
{
	my_check->trash = 0;
	my_check->empty_space = 0;
	my_check->collectible = 0;
	my_check->exit_map = 0;
	my_check->start_position = 0;
}

int	check_map_another(t_map *my_map)
{
	t_check_map	my_check;
	int			ret;

	ret = check_wall(my_map);
	if (ret == 1)
	{
		init_check_map(&my_check);
		ret = check_attributs(my_map, &my_check);
	}
	return (ret);
}
