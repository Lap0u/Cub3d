// #include "raycaster.h"
#include "../cub3d.h"
#include "../libft/libft.h"

int	isinset(char c, char *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y *data->size + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

float modul(float n)
{
	if (n < 0)
	{
		n = n * -1;
	}
	return (n);
}


void	init_sprite(t_app *app)
{
	app->sp.game_state.player_x = app->starting_x * RES_X / app->map_x + RES_X / app->map_x / 2;
	app->sp.game_state.player_y = app->starting_y * RES_Y / app->map_y + RES_Y / app->map_y / 2;
	app->sp.game_state.player_old_x = 0;
	app->sp.game_state.player_old_y = 0;
	app->sp.game_state.pa = app->starting_angle;
	app->sp.game_state.delta_x = cosf(app->sp.game_state.pa) * 6;
	app->sp.game_state.delta_y = sinf(app->sp.game_state.pa) * 6;
	app->ray.game_state.pa = app->starting_angle;
}

void	draw_line(t_app *app)
{
	float	x;
	float	y;
	int		i;

	x = app->sp.game_state.player_x;
	y = app->sp.game_state.player_y;
	i = 0;
	while (i < 30)
	{
		my_mlx_pixel_put(&(app->img), ((x) + (i * cos(app->ray.game_state.pa)/2)) / 2, 
		((y) + (i * sin(app->ray.game_state.pa)/2)) / 2, 0x003A51B0);
		i++;
	}
}

void    draw_sprite(t_app *app)
{
    float        i;
    float        j;
    float    x;
    float    y;

    i = -1;
    x = app->sp.game_state.player_x * 192.f / RES_X;
    y = app->sp.game_state.player_y * 192.f / RES_Y;
    // printf("aft x = %f et y = %f\n", xo, yo);

    // draw_line(app);
    draw_mini_rays(app);
    while (++i < 5) //changer le size en fonction de la taille de la map 
    {
        j = -1;
        while (++j < 5)
            my_mlx_pixel_put(&(app->img), (j + (x - 2.5)), (i + (y - 2.5)), 0x00FFFFFF);
    }
	//affiche un contour de map
	i = 0;
	while (i < 192)
	{
            my_mlx_pixel_put(&(app->img), i, 192, 0x00FFFFFF);
            my_mlx_pixel_put(&(app->img), 192, i, 0x00FFFFFF);
			i++;
	}
}





void	drow_background(t_app *app)
{
	int i;
	int	y;
	int color;

	i = 0;
	while (i < RES_X)
	{
		y = 0;
		while (y < RES_Y)
		{
			if (y < RES_Y / 2)
				color = color_ceil(app, i, y);
			else
				color = color_floor(app, i, y);
			if (i >= 64 * SCALING || y >= 64 * SCALING || app->bool_map == 1)//laisse la place pour la map en haut a gauche, change valeur pour agrandir / retraicir / faire un scaling
				my_mlx_pixel_put(&(app->img), i, y, color);
			y++;
		}
		i++;
	}
}

void	add_starting_angle(t_app *app, char c)
{
	if (c == 'N')
		app->starting_angle = PI / -2;
	else if (c == 'S')
		app->starting_angle = PI / 2;
	else if (c == 'W')
		app->starting_angle = 0;
	else if (c == 'E')
		app->starting_angle = PI;
}

void	init_colors(t_app *app)
{
	app->ceil_col.red = app->vars->ceiling_col[0];
	app->ceil_col.green = app->vars->ceiling_col[1];
	app->ceil_col.blue = app->vars->ceiling_col[2];
	app->flo_col.red = app->vars->floor_col[0];
	app->flo_col.green = app->vars->floor_col[1];
	app->flo_col.blue = app->vars->floor_col[2];
}

int	*fill_map(int size, int longest, char **map, t_app *app)
{
	int	*tab;
	int	i;
	int	j;

	tab = malloc(sizeof(int) * size);
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (map[i])
	{
		j = 0;
		while(j < longest)
		{
			if (j < ft_strlen(map[i]) && map[i][j] != ' ')
				tab[i * longest + j] = map[i][j] -48;
			else
				tab[i * longest + j] = -1; //pour les espaces et les vides
			if (j < ft_strlen(map[i]) && isinset(map[i][j], "NSWE"))
			{
				app->starting_x = j;
				app->starting_y = i;
				add_starting_angle(app, map[i][j]);
				tab[i * longest + j] = 0;
			}
			j++;
		}
		free(map[i]);
		i++;
	}
	free(map);
	return (tab);
}

void	init_map(t_app *app, char **map)
{
	int	i;
	int	longest;

	i = 1;
	longest = ft_strlen(map[0]);
	while (map[i])
	{
		if (ft_strlen(map[i]) > longest)
			longest = ft_strlen(map[i]);
		i++;
	}
	app->map = fill_map(longest * i, longest, map, app);
	if (app->map == NULL)
		printf("faut gerer l'erreur lol\n");
	app->map_x = longest;
	app->map_y = i - 1;
	printf("map: x %d y %d\n", app->starting_x, app->starting_y);
}

void	disp_map(t_app *app)
{
	int i;
	int j;

	i = 0;
	printf("display as int map\n");
	while(i < app->map_y)
	{
		j = 0;
		while (j < app->map_x)
		{
			printf("%d", app->map[i * app->map_x + j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\nend\n");
}

void	init_app(t_app *app, char *title, int w, int h)
{	
	app->mlx = mlx_init();
	if (app->mlx == NULL)
		exit (1);
	init_path(app);
	init_texture(app);
	init_map(app, app->vars->map);
	disp_map(app);
	app->x = w;
	app->y = h;
	app->bool_map = 1;
	if (app->mlx == NULL)
		exit (1);
	app->win = mlx_new_window(app->mlx, w, h, title);
	if (app->win == NULL)
	{
		free(app->mlx);
		exit (1);
	}
	init_sprite(app);
	init_colors(app);
	free(app->vars);
	printf("boucle\n");
}

int	destroy_game_data(void *data)
{
	t_app		*app;

	app = (t_app *)data;
	if (app->image_is_destroyed == 0)
		mlx_destroy_image(app->mlx, app->img.img);
	mlx_clear_window(app->mlx, app->win);
	mlx_destroy_window(app->mlx, app->win);
	mlx_destroy_display(app->mlx);
	free(app->mlx);
	exit (0);
}