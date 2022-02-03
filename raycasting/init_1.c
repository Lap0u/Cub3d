#include "raycaster.h"

int	is_texture_exist(const char *filename)
{
	int	fd;

	fd = 0;
	fd = open(filename, O_RDONLY);
	if (fd > 0)
		close(fd);
	else
		write(2, "Error\nThe texture doesn't exist\n", 32);
	return (1);
}


void	init_path(t_app *app)
{
	if (is_texture_exist(PATH_TO_NORTH))
		app->path[0] = PATH_TO_NORTH;
	if (is_texture_exist(PATH_TO_SOUTH))
		app->path[1] = PATH_TO_SOUTH;
	if (is_texture_exist(PATH_TO_WEST))
		app->path[2] = PATH_TO_WEST;
	if (is_texture_exist(PATH_TO_EAST))
		app->path[3] = PATH_TO_EAST;
}

void	init_texture(t_app *app)
{
	int			i;
	t_data		*txr;
	char		**m_path;

	i = 0;
	txr = app->txr;
	m_path = app->path;
	write(1, "_1\n", 3);
	while (i < 4)
	{
		txr[i].img = mlx_xpm_file_to_image(app->mlx, m_path[i],
				&txr[i].w, &txr[i].h);
		txr[i].addr = mlx_get_data_addr(txr[i].img, &(txr[i].bpp),
				&(txr[i].size), &(txr[i].endian));
		printf("&img = %p, addr = %p\n", txr[i].img, txr[i].addr);
		i++;
	}
}