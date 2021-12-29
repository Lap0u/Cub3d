/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 11:20:27 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/29 13:19:35 by cbeaurai         ###   ########.fr       */
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

/*parsing/exit_utils.c*/
int		bad_malloc();
int		bad_fd();

/*parsing/parse_value.c*/
void	get_values(t_data *data, int fd);
void	add_line(t_data *data, char *str);
char	*skip_id(char *str);
void	add_col(t_data *data, char *val, char c);

/*parsing/parse_map.c*/
void	get_map(t_data *data, int fd);

/*parsing/check_data.c*/
void	check_data(t_data *data);
/*parsing/print_data.c*/
void	print_data(t_data *data);


#endif