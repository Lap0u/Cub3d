/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 14:27:51 by cbeaurai          #+#    #+#             */
/*   Updated: 2020/12/01 14:27:53 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

int		get_next_line(int fd, char **line);

int		ft_count_endl(const char *str);

char	*ft_strcpy(const char *src);

char	*ft_realoc_cat(char *dst, const char *src);

int		ft_return(int read_bytes, char *str, char **line);

char	*ft_save_next(char *str, int return_value);

int		ft_solve(char *str, char **line);

char	*ft_return_free(char *str);

#endif
