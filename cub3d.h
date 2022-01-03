/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 11:20:27 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/29 16:00:54 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdio.h>
#  include "mlx_linux/mlx.h"

#  define UP 119
#  define DOWN 115
#  define LEFT 97
#  define RIGHT 100
#  define ESC 65307


typedef struct s_data
{
	char	*no_path;
	char	*so_path;
	char	*ea_path;
	char	*we_path;
	int		floor_col[3];
	int		ceiling_col[3];
	char	**map;//format a voir
}			t_data;

typedef struct s_state
{
	int	player_x;
	int	player_y;
	int	player_old_x;
	int	player_old_y;
}				t_state;

typedef struct s_map
{
	char			*line;
	struct s_map	*next;
}				t_map;

typedef struct s_check_map
{
	int	trash;
	int	empty_space;
	int	collectible;
	int	exit_map;
	int	start_position;
}				t_check_map;

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

typedef struct s_app
{
	void		*mlx;
	void		*win;
	void		*image;
	void		*image_addr;
	int			x;
	int			y;
	t_texture	sp[4];
	char		*path[4];
	t_data		data;
	t_map		*carte;
	int			image_is_destroyed;
	int			nb_mvmt;
	int			total_col;
	int			taken_col;
	int			flag;
}				t_app;

/*main.c*/

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
t_data	*get_data(char *str);
void	init_data(t_data **data);

/*parsing/exit_utils.c*/
int		bad_malloc();
int		bad_fd();
void	free_data(t_data *data);


/*parsing/parse_value.c*/
void	get_values(t_data *data, int fd);
void	add_line(t_data *data, char *str);
char	*skip_id(char *str);
void	add_col(t_data *data, char *val, char c);

/*parsing/parse_map.c*/
void	get_map(t_data *data, int fd);
void	add_map(char *first_line, int fd, t_data *data);
void	add_map_line(char ***map, char *new);

/*parsing/check_data.c*/
void	check_data(t_data *data);
/*parsing/print_data.c*/
void	print_data(t_data *data);


/*app_draw_and_action/init.c*/
int		is_texture_exist(const char *filename);
void	init_path(t_app *app);
void	init_sprite(t_app *app);
void	init_app(t_app *app, char *title, int w, int h);
void	player_position_init(t_app *app, int x, int y);

/*app_draw_and_action/destoying.c*/
int		destroy_game_data(void *data);

/*app_draw_and_action/action.c*/
int		check_pos_player(t_app *app);
int		change_map(t_app *app, char *pos);
int		player_input(int key, void *data);
int		player_input_body(int key, t_app *app);
int		routine(void *data);

/*app_draw_and_action/drawing.c*/
void	*bit_copy(void *dst, const void *src, int j);
void	drow_map_body(t_app *app, char c, int j, int i);
void	drow_map(t_app *app);
int		check_pixel(t_texture *txr, int line, int col);
void	draw_img_at_pos_body(t_app *app, t_texture *txr, int st, int bpp);
void	draw_img_at_pos(t_app *app, t_texture *txr, int x, int y);

/*map_init_and_check/check_map*/
void	init_check_map(t_check_map *my_check);
int		check_map_another(t_map *my_map);

/*map_init_and_check/check_wall_attributs.c*/
/*map_init_and_check/clear_map_list.c*/
/*map_init_and_check/fonctions_list.c*/
/*map_init_and_check/read_map.c*/


#endif