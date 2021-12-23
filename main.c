#include "cub3d.h"
#include "libft/libft.h"

int	check_extension(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len < 4)
	{
		ft_putstr_fd("Error\nWrong map file, .cub required\n", 2);
		return (0);
	}
	if (ft_strcmp(&str[len - 4], ".cub") != 0)
	{
		ft_putstr_fd("Error\nWrong map file, .cub required\n", 2);
		return (0);
	}
	return (1);
}

int	try_open(char *str)
{
	int ret;

	ret = ft_open_file_read(str);
	if (ret < 0)
	{
		ft_putstr_fd("Error\nCan't open this file\n", 2);
		return (0);
	}
	else
		close(ret);
	return (1);
}

int	check_arg(char *av, int ac)
{
	if (ac != 2)
	{
		ft_putstr_fd("Error\ncub3D only takes one file as arugment\n", 2);
		return (0);
	}
	if (check_extension(av) == 0 || try_open(av) == 0)
		return (0);
	return (1);
}

int main(int ac, char **av)
{
	if (check_arg(av[1], ac) == 0)
		return (1);
	// if (check_input(av[1]) == 0)
	// 	return (1);
	// t_datas = get_datas(av[1]);
	return (0);
}