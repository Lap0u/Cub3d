# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/23 11:12:25 by cbeaurai          #+#    #+#              #
#    Updated: 2022/01/27 13:28:35 by cbeaurai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

SRCS		=	main.c parsing/check_arg.c parsing/check_input.c parsing/exit_utils.c \
				parsing/store_data.c parsing/parse_map.c parsing/parse_value.c \
				parsing/check_data.c parsing/print_data.c parsing/check_data_utils.c \
				raycasting/std_fonctions.c raycasting/actions.c raycasting/draw_image.c \
				raycasting/map.c raycasting/draw_3dray.c raycasting/init_1.c \
				raycasting/get_color.c raycasting/drow_tile.c\
				#map_init_and_check/check_map map_init_and_check/check_wall_attributs.c \
				#map_init_and_check/clear_map_list.c map_init_and_check/fonctions_list.c \
				#smap_init_and_check/read_map.c \

OBJS		= $(SRCS:.c=.o)

CC			= gcc

RM			= rm -rf

LFT			= ./libft

CFLAGS		= -no-pie  #-g -fsanitize=address#-Wall -Werror -Wextra -I.

LIBS		= -L ./libft -lft -L ./mlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lbsd

MAKE_LIB	= ${MAKE} -C ${LFT}

all:		$(NAME)

.c .o	:
			${CC} ${CFLAGS} -I ./inc -I ./mlx_linux -c $< -o $(<:.c=.o)
			
$(NAME):	$(OBJS)
			$(MAKE_LIB) && make -C ./mlx_linux
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

clean:		
			$(RM) $(OBJS)
			$(MAKE_LIB) clean

fclean:		clean
			$(RM) $(NAME)
			$(MAKE_LIB) fclean

re:			fclean $(NAME)

.PHONY:		all clean fclean re
