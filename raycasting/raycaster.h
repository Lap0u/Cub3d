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
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		w;
	int		h;
	t_state	game_state;
	int		image_is_destroyed;
} t_data;

// typedef struct s_texture
// {
// 	void	*img;
// 	char	*addr;
// 	int		bpp;
// 	int		size;
// 	int		endian;
// 	int		sp_x;
// 	int		sp_y;
// 	t_state	game_state;
// }				t_texture;

typedef struct s_app
{
	void		*mlx;
	void		*win;
	t_data		brouillon;
	t_data		sp;
	t_data		wall;
	t_data		space;
	t_data		ray;
	void		*image;
	void		*image_addr;
	int			x;
	int			y;
	char		*path[5];
	int			image_is_destroyed;
	int			nb_mvmt;
	int			total_col;
	int			taken_col;
	int			flag;
}				t_app;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	my_mlx_pixel_put_sp(t_data *data, int x, int y, int color);
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
void init_wall(t_app *app);
void init_space(t_app *app);
void draw_map(t_app *app);

#endif