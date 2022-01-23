OS		= ${shell uname}																	\


SRCS	=		1.c std_fonctions.c actions.c draw_image.c map.c \
				draw_3dray.c init_1.c get_color.c drow_tile.c\

OBJS	= ${SRCS:.c=.o}

OBJS_BONUS	= ${SRCS_BONUS:.c=.o}

NAME			= raycasting

CC			= gcc -g

CFLAGS		= 
# -fsanitize=address

RM	= rm -f

# mlx library

	MINILIBX = -Lmlx_linux -lmlx_Linux -lXext -lX11
	MLX = @make -C mlx_linux
	INCLUDE_ADD = -D LINUX



all: 		mlx ${NAME}

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} ${INCLUDE_ADD}

mlx :		
			${MLX}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${MINILIBX} -lm

bonus : 	mlx ${NAME_BONUS}

${NAME_BONUS}:	${OBJS_BONUS}
				${CC} ${CFLAGS} -o ${NAME}_bonus ${OBJS_BONUS} ${MINILIBX}

clean:		
			${MLX} clean
			${RM} ${OBJS} ${OBJS_BONUS}

fclean:		clean
			${RM} ${NAME} ${NAME}_bonus

re:			fclean all

.PHONY:		all mlx clean fclean re
