/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 11:20:27 by cbeaurai          #+#    #+#             */
/*   Updated: 2022/01/27 12:45:38 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include "mlx_linux/mlx.h"
# include <stdlib.h>
# include <math.h>

# define RES_X 2048
# define RES_Y 1024
# define SCALING 3
#  define UP 119
#  define DOWN 115
#  define LEFT 97
#  define RIGHT 100
#  define FL_RIGHT 65363
#  define FL_LEFT 65361

#  define ESC 65307
#  define PI 3.14159265359
#  define PI2 PI/2
#  define PI3 3*PI/2
#  define DR (0.0174533 / 32)// one degree in radians

# define PATH_TO_NORTH "../textures/north.xpm"
# define PATH_TO_SOUTH "../textures/south.xpm"
# define PATH_TO_WEST "../textures/west.xpm"
# define PATH_TO_EAST "../textures/east.xpm"

#  define RES_X	2048
#  define RES_Y 1024

#  define MAP 109
#  define BLUR +0x888888
#  define MARGIN 100
#  define OPACITY 0.5

# define SCALING 3

typedef struct s_rgb
{	
	unsigned char red;
	unsigned char green;/* data */
	unsigned char blue;
	unsigned char op;
}				t_rgb;

typedef struct s_state
{
	float	player_x;
	float	player_y;
	float	player_old_x;
	float	player_old_y;
	float	delta_x;
	float	delta_y;
	float	pa;
}				t_state;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		bpp;
	int		size;
	int		endian;
	int		sp_x;
	int		sp_y;
	t_state	game_state;
}				t_texture;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		size;
	int		endian;
	int		w;
	int		h;
	t_state	game_state;
	int		image_is_destroyed;
} 			t_data;

typedef struct s_vars
{
	char	*no_path;
	char	*so_path;
	char	*ea_path;
	char	*we_path;
	unsigned char floor_col[3];
	unsigned char ceiling_col[3];
	char	**map;//format a voir
}			t_vars;

typedef struct s_draw
{
	int		i;
	int		j;
	int		k;
	int		r;
	int		mx; // coordinate x de case du tableau dont de notre ray touche
	int		my; // coordinate y de case du tableau dont de notre ray touche
	int		mp; // taille de tab
	int		dof;
	int		mod; // type de texture

	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	hx;
	float	hy;
	float	vx;
	float	vy;
	float	yo;
	float	a_tan;
	float	n_tan;
	float	x;
	float	y;
	float	hdist;
	float	vdist;
	float	tdist;
	float	dis_ta;
	float	lineH;
	float	lineO;
	float	ca;
	float	saveH;
}				t_draw;

typedef struct s_app
{
	void		*mlx;
	void		*win;
	t_draw		dr; //draw struct de drawing 3d
	t_data		img; // main img dans laquelle on ecrit
	t_data		txr[4];
	char		*path[4];
	t_data		sp;
	t_data		wall;
	t_data		space;
	t_data		ray;
	t_data		north;
	t_data		south;
	t_data		east;
	t_data		west;
	t_vars		vars;
	void		*image;
	void		*image_addr;
	int			x;
	int			y;
	int			image_is_destroyed;
	int			nb_mvmt;
	int			total_col;
	int			taken_col;
	int			flag;
	int			bool_map;
	t_rgb		ceil_col;
	t_rgb		flo_col;
}				t_app;

/*parsing/check_arg.c*/

int		check_extension(char *str);
int		try_open(char *str);
int		check_arg(char *av, int ac);

/*parsing/check_input.c*/
int		check_input(char *file);
int		check_lines(int fd);
int		ret_int_free(int ret, char *tofree);
int		good_id(char *str);
int		tab_len(char **tab);
int		check_file(char *str);
int		check_colour(char *str);
int		second_args(char *str, char *id);
int		isonlyset(char *str, char *set);
int		check_map(char *str, int fd);
int		parse_line(char *str, int fd);


/*parsing/store_data.c*/
t_vars	*get_data(char *str);
void	init_data(t_vars **data);

/*parsing/exit_utils.c*/
int		bad_malloc();
int		bad_fd();
void	free_data(t_vars *data);


/*parsing/parse_value.c*/
void	get_values(t_vars *data, int fd);
void	add_line(t_vars *data, char *str);
char	*skip_id(char *str);
void	add_col(t_vars *data, char *val, char c);

/*parsing/parse_map.c*/
void	get_map(t_vars *data, int fd);
void	add_map(char *first_line, int fd, t_vars *data);
void	add_map_line(char ***map, char *new);

/*parsing/check_data.c*/
void	check_data(t_vars *data);
int		check_player(t_vars *data);
int		check_walls(t_vars *data);
int		check_inside(t_vars *data);


/*parsing/check_data_utils.c*/
int		char_inset(char c, char *set);
int		full_line(char *str);
int		check_surround(char *check, char *prev, char *next);

/*parsing/print_data.c*/
void	print_data(t_vars *data);


// /*app_draw_and_action/init.c*/
// int		is_texture_exist(const char *filename);
// void	init_path(t_app *app);
// void	init_sprite(t_app *app);
// void	init_app(t_app *app, char *title, int w, int h);
// void	player_position_init(t_app *app, int x, int y);

// /*app_draw_and_action/destoying.c*/
// int		destroy_game_data(void *data);

// /*app_draw_and_action/action.c*/
// int		check_pos_player(t_app *app);
// int		change_map(t_app *app, char *pos);
// int		player_input(int key, void *data);
// int		player_input_body(int key, t_app *app);
// int		routine(void *data);

// /*app_draw_and_action/drawing.c*/
// void	*bit_copy(void *dst, const void *src, int j);
// void	drow_map_body(t_app *app, char c, int j, int i);
// void	drow_map(t_app *app);
// int		check_pixel(t_data *txr, int line, int col);
// void	draw_img_at_pos_body(t_app *app, t_data *txr, int st, int bpp);
// void	draw_img_at_pos(t_app *app, t_data *txr, int x, int y);

// /*map_init_and_check/check_map*/
// void	init_check_map(t_check_map *my_check);
// int		check_map_another(t_map *my_map);

// void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
// void	my_mlx_pixel_put_line(t_app *app, int x, int y, int color);
// void	init_colors(t_app *app);
// void	init_app(t_app *app, char *title, int w, int h);
// int		destroy_game_data(void *data);
// void	draw_sprite(t_app *app);
// void	init_sprite(t_app *app);
// void	drow_background(t_app *app);

/*map.c*/
void	drow_element(t_app *app, int x, int y, int color);
void	draw_map(t_app *app);

/*raycasting/draw_3dray.c*/
void	prepa_init_ray(t_app *app);
void	check_hor_down(t_app *app);
void	check_hor_up(t_app *app);
void	check_hor_left_right(t_app *app);
void	check_hor_action(t_app *app);
void	check_horizont_line(t_app *app);
void	check_vert_left(t_app *app);
void	check_vert_right(t_app *app);
void	check_vert_down_up(t_app *app);
void	check_vert_action(t_app *app);
void	check_vertical_line(t_app *app);
void	draw_mini_rays(t_app *app);
void	draw_rays_3d(t_app *app);

/*raycasting/init_1.c*/
void	init_path(t_app *app);
void	init_texture(t_app *app);

/*raycasting/get_color.c*/
void	opacity(t_app *app, int y, int x, t_rgb *color);
int		color_ceil(t_app *app, int x, int y);
int		color_floor(t_app *app, int x, int y);
int		get_color(t_app *app, int x, int y, int scale, int rx, int i, int r, int mod);

/*raycasting/drow_tile.c*/
void	drow_element(t_app *app, int x, int y, int color);
void	draw_grid(t_app *app, float offx, float offy, int size);
void	add_empty_tile(t_app *app, int x, int y, int size);
void	add_wall_tile(t_app *app, int x, int y, int size);
void	add_full_tile(t_app *app, int x, int y, int size);
void	draw_mini_player(t_app *app, float offx, float offy);//a deplacer un peu en fonction du decalage avec le mur
void	draw_around_player(t_app *app, float p_x, float p_y, int size);

/*raycasting/std_fonctions.c*/
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
float modul(float n);
void	init_sprite(t_app *app);
void	draw_line(t_app *app);
void	draw_sprite(t_app *app);
void	drow_background(t_app *app);
void	init_colors(t_app *app);
void	init_app(t_app *app, char *title, int w, int h);
int	destroy_game_data(void *data);

/*raycasting/draw_image.c*/
void	draw_img_at_pos(t_app *app, t_data *txr, int x, int y);
void	draw_img_at_pos_body(t_app *app, t_data *txr, int st, int bpp);
int	check_pixel(t_data *txr, int line, int col);
void	*bit_copy(void *dst, const void *src, int j);

/*raycasting/actions.c*/
int	player_input(int key, void *data);
int	player_input_body(int key, t_app *app);
char	*copy_size(char *str, int bpp, int size);
void	open_images(t_app *app); ///retour de fonctions a check ->img = NULL
void	close_images(t_app *app);
int	routine(void *data);

#endif