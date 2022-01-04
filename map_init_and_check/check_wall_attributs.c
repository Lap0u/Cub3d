#include "../cub3d.h"
#include "../libft/libft.h"

int	check_first_last_wall(char *line)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(line);
	while (i < len)
	{
		if (line[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_medium_wall(char *line)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(line);
	while (i < len)
	{
		if (line[0] != '1' || line[len - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_wall(t_map *my_map)
{
	t_map	*current;
	int		len;
	int		len_current;
	int		i;

	i = 0;
	len = ft_strlen(my_map->line);
	current = my_map;
	while (i < ft_lstsize(my_map))
	{
		len_current = ft_strlen(current->line);
		if (len_current != len)
			return (-1);
		if (i == 0 || i == (ft_lstsize(my_map) - 1))
		{
			if (check_first_last_wall(current->line) != 1)
				return (0);
		}
		else
			if (check_medium_wall(current->line) != 1)
				return (0);
		i++;
		current = current->next;
	}
	return (1);
}

void	fill_up_attributs(t_map *my_map, t_check_map **my_check)
{
	int		i;
	t_map	*current;

	current = my_map;
	while (current)
	{
		i = 0;
		while (current->line[i])
		{
			if (current->line[i] == '0')
				(*my_check)->empty_space++;
			else if (current->line[i] == 'C')
				(*my_check)->collectible++;
			else if (current->line[i] == 'E')
				(*my_check)->exit_map++;
			else if (current->line[i] == 'P')
				(*my_check)->start_position++;
			else
				if (current->line[i] != '1')
					(*my_check)->trash++;
			i++;
		}
		current = current->next;
	}
}

int	check_attributs(t_map *my_map, t_check_map *my_check)
{
	fill_up_attributs(my_map, &my_check);
	if (my_check->exit_map < 1 || my_check->collectible < 1)
		return (2);
	else if (my_check->start_position != 1)
		return (3);
	else if (my_check->trash != 0)
		return (4);
	else if (my_check->empty_space < 1)
		return (5);
	return (1);
}
