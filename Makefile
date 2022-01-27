# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/23 11:12:25 by cbeaurai          #+#    #+#              #
#    Updated: 2022/01/27 10:37:04 by cbeaurai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

SRCS		=	main.c parsing/check_arg.c parsing/check_input.c parsing/exit_utils.c \
				parsing/store_data.c parsing/parse_map.c parsing/parse_value.c \
				parsing/check_data.c parsing/print_data.c parsing/check_data_utils.c \
				app_draw_and_action/init.c app_draw_and_action/destroying.c \
				app_draw_and_action/action.c app_draw_and_action/drawing.c \
				std_fonctions.c actions.c draw_image.c map.c draw_3dray.c \
				init_1.c get_color.c drow_tile.c\
				#map_init_and_check/check_map map_init_and_check/check_wall_attributs.c \
				#map_init_and_check/clear_map_list.c map_init_and_check/fonctions_list.c \
				#smap_init_and_check/read_map.c \

OBJS		= $(SRCS:.c=.o)

CC			= gcc

RM			= rm -rf

LFT			= ./libft

CFLAGS		= -Wall -Werror -Wextra -no-pie -g -fsanitize=address -I.

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
