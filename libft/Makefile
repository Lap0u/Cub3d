# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/23 00:02:15 by cbeaurai          #+#    #+#              #
#    Updated: 2021/12/08 11:12:19 by cbeaurai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	  ft_isdigit.c ft_isprint.c ft_memccpy.c ft_memchr.c ft_memcmp.c \
	  ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strdup.c \
	  ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c \
	  ft_strrchr.c ft_tolower.c ft_toupper.c ft_itoa.c ft_putchar_fd.c \
	  ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strjoin.c \
	  ft_strmapi.c ft_strtrim.c ft_substr.c get_next_line.c \
	  get_next_line_utils.c file.c error.c free.c ft_strcmp.c

SRCBONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	   	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
		ft_lstmap.c

OBJS	= $(SRC:.c=.o)

OBJB	= $(SRCBONUS:.c=.o)

CC = clang

CFLAGS = -Wall -Werror -Wextra

ARRCS	= ar rcs

RM	= rm -f

all: ${NAME}

.c.o:
			${CC} ${CFLAGS} -c $< -o $(<:.c=.o)

$(NAME): ${OBJS}
			${ARRCS} ${NAME} ${OBJS} 

clean:
			${RM} ${OBJS} ${OBJB}

fclean: clean
			${RM} ${NAME}

re: fclean all

bonus :	${OBJS} ${OBJB}
			${ARRCS} ${NAME} ${OBJS} ${OBJB}

rebonus: fclean bonus

.PHONY: all re clean fclean lib rebonus
