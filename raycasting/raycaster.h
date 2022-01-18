/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 11:20:27 by cbeaurai          #+#    #+#             */
/*   Updated: 2022/01/07 15:14:15 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include "mlx_linux/mlx.h"
# include <stdlib.h>
# include <math.h>

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
#  define DR 0.0174533 // one degree in radians

# define RES_X 2048
# define RES_Y 1024

# define PATH_TO_NORTH "../textures/north.xpm"
# define PATH_TO_SOUTH "../textures/south.xpm"
# define PATH_TO_WEST "../textures/west.xpm"
# define PATH_TO_EAST "../textures/east.xpm"


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
} t_data;

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
	void		*image;
	void		*image_addr;
	int			x;
	int			y;
	int			image_is_destroyed;
	int			nb_mvmt;
	int			total_col;
	int			taken_col;
	int			flag;
}				t_app;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	my_mlx_pixel_put_line(t_app *app, int x, int y, int color);
void	init_app(t_app *app, char *title, int w, int h);
int		destroy_game_data(void *data);
void	draw_sprite(t_app *app);
void	init_sprite(t_app *app);
void	drow_background(t_app *app);


/*actions.c*/
int	player_input(int key, void *data);
int	player_input_body(int key, t_app *app);
int	routine(void *data);

/* draw_image.c*/
void	draw_img_at_pos(t_app *app, t_data *txr, int x, int y);
void	draw_img_at_pos_body(t_app *app, t_data *txr, int st, int bpp);
int		check_pixel(t_data *txr, int line, int col);
void	*bit_copy(void *dst, const void *src, int j);

/*map.c*/
void	drow_element(t_app *app, int x, int y, int color);
void	draw_map(t_app *app);

/*draw_3dray.c*/
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

/*init_1.c*/
void	init_path(t_app *app);
void	init_texture(t_app *app);

/*get_color.c*/

int		get_color(t_app *app, int x, int y, int scale, int rx, int i, int r, int mod);

#endif