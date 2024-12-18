NAME		=	miniRT

SRCS		=	main.c init.c

OBJS		=	${SRCS:.c=.o}

CFLAGS		=	-Werror -Wextra -Werror -I ${MLXDIR} -I ${LIBFTDIR}
CFLAGS		+=	-g3

LIBFTDIR	=	./libft
LIBFT		=	${LIBFTDIR}/libft
LIBFTFLAGS	=	 -L ${LIBFTDIR} -lft

MLXDIR		=	./mlx
MLX			=	${MLXDIR}/libmlx.a
MLXFLAGS	=	-L ${MLXDIR} -lmlx -framework OpenGL -framework AppKit

all			: ${NAME}

%.o			:	%.c
			cc ${CFLAGS} $< -c -o $@

${NAME}		:	${OBJS} ${MLX} ${LIBFT}
			cc ${CFLAGS} ${OBJS} ${MLXFLAGS} ${LIBFTFLAGS} -o ${NAME}

${MLX}		:
			make -C ${MLXDIR}

${LIBFT}	:
			make -C ${LIBFTDIR}

clean		:
			rm -f ${OBJS}
			make -C ${LIBFTDIR} clean

fclean		:	clean
			rm -f ${NAME}
			rm -f ${LIBFT}
			make -C ${MLXDIR} clean

.PHONY		:	all clean fclean
