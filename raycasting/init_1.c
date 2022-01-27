#include "../cub3d.h"
// #include "raycaster.h"

int	is_texture_exist(const char *filename)//c'est pas comme ca qu'on verifie si une image est correcte
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
	if (is_texture_exist(app->vars.no_path))
		app->path[0] = app->vars.no_path;
	if (is_texture_exist(app->vars.so_path))
		app->path[1] = app->vars.so_path;
	if (is_texture_exist(app->vars.we_path))
		app->path[2] = app->vars.we_path;
	if (is_texture_exist(app->vars.ea_path))
		app->path[3] = app->vars.ea_path;
}

void	init_texture(t_app *app)
{
	int			i;
	t_data		*txr;
	char		**m_path;

	i = 0;
	txr = app->txr;
	m_path = app->path;
	printf("p1 : %s\n", m_path[0]);
	while (i < 4)
	{
		txr[i].img = mlx_xpm_file_to_image(app->mlx, m_path[i],
				&txr[i].w, &txr[i].h);
		//gerer l'erreur si mauvaise images
		txr[i].addr = mlx_get_data_addr(txr[i].img, &(txr[i].bpp),
				&(txr[i].size), &(txr[i].endian));
		i++;
	}
}