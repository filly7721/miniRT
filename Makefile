NAME		=	miniRT

SRCS		=	main.c

OBJS		=	${SRCS:.c=.o}

CFLAGS		=	-Werror -Wextra -Werror -I ${MLXDIR} -I/usr/include
CFLAGS		+=	-g3

MLXDIR		=	mlx
MLXFLAGS	=	-L ${MLXDIR} -lmlx -framework OpenGL -framework AppKit
MLX			=	${MLXDIR}/libmlx.a

all			: ${NAME}

%.o			:	%.c
			cc ${CFLAGS} $< -c -o $@

${NAME}		:	${OBJS} ${MLX}
			cc ${CFLAGS} ${OBJS} ${MLXFLAGS} -o ${NAME}

${MLX}		:
			make -C mlx

clean		:
			rm -f ${OBJS}

fclean		:	clean
			rm -f ${NAME}
			make -C mlx clean

.PHONY		:	all clean fclean
