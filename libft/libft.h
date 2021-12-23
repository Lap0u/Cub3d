/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 11:58:29 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/09 17:07:28 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFFER_SIZE 4096

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_gnl
{
	int		read_bytes;
	char	buff[BUFFER_SIZE + 1];
	int		return_value;
}				t_gnl;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

int				ft_isalnum(int c);

int				ft_isalpha(int c);

int				ft_isdigit(int c);

int				ft_isprint(int c);

int				ft_isascii(int c);

char			*ft_itoa(int n);

void			*ft_memccpy(void *dst, const void *src, int c, size_t n);

void			*ft_memchr(const void *s, int c, size_t n);

int				ft_memcmp(const void *s1, const void *s2, size_t n);

void			*ft_memcpy(void *dst, const void *src, size_t n);

void			*ft_memmove(void *dst, const void *src, size_t len);

void			*ft_memset(void *b, int c, size_t len);

void			*ft_calloc(size_t count, size_t size);

void			ft_bzero(void *s, size_t n);

int				ft_atoi(const char *str);

int				ft_strlen(const char *str);

void			ft_putchar_fd(char c, int fd);

void			ft_putendl_fd(char *s, int fd);

void			ft_putnbr_fd(int n, int fd);

void			ft_putstr_fd(char *s, int fd);

char			**ft_split(char const *s, char c);

char			*ft_strchr(const char *s, int c);

char			*ft_strdup(const char *s1);

char			*ft_strjoin(char const *s1, char const *s2);

size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);

size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);

char			*ft_strtrim(char const *s1, char const *set);

char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));

int				ft_strncmp(const char *s1, const char *s2, size_t n);

int				ft_strcmp(char *s1, char *s2);

char			*ft_strnstr(const char *haystack, const char *needle,
					size_t len);

char			*ft_strrchr(const char *s, int c);

char			*ft_substr(char const *s, unsigned int start, size_t len);

int				ft_toupper(int c);

int				ft_tolower(int c);

t_list			*ft_lstnew(void *content);

void			ft_lstadd_front(t_list **alst, t_list *new);

int				ft_lstsize(t_list *lst);

t_list			*ft_lstlast(t_list *lst);

void			ft_lstadd_back(t_list **alst, t_list *new);

void			ft_lstdelone(t_list *lst, void (*del)(void *));

void			ft_lstclear(t_list **lst, void (*del)(void *));

void			ft_lstiter(t_list *lst, void (*f)(void *));

t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));

int				get_next_line(int fd, char **line);

int				ft_count_endl(const char *str);

char			*ft_strcpy(const char *src);

char			*ft_realoc_cat(char *dst, const char *src);

int				ft_return(int read_bytes, char *str, char **line);

char			*ft_save_next(char *str, int return_value);

int				ft_solve_gnl(char *str, char **line);

char			*ft_return_free(char *str);

int				ft_open_file_read(char *str);

int				ft_open_file_write(char *str);

int				ft_open_file_read_write(char *str);

int				ft_open_file_write_create(char *str);

void			ft_wrong_arg(void);

void			ft_wrong_file(void);

void			ft_wrong_env(void);

void			ft_wrong_malloc(void);

void			ft_free_3dtab(char **tab);

#endif
