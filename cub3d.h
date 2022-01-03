/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 11:20:27 by cbeaurai          #+#    #+#             */
/*   Updated: 2022/01/03 14:33:12 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdio.h>

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
int		check_player(t_data *data);
int		check_walls(t_data *data);
int		check_inside(t_data *data);


/*parsing/check_data_utils.c*/
int		char_inset(char c, char *set);
int		full_line(char *str);
int		check_surround(char *check, char *prev, char *next);

/*parsing/print_data.c*/
void	print_data(t_data *data);


#endif