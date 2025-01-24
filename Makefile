NAME		=	miniRT

SRCS		=	main.c init.c hook.c \
				parsing.c parse_lights.c split_by_char.c free_split.c \
				parse_camera.c parse_plane.c parse_sphere.c parse_cylinder.c \
				print_env.c utils.c tuple.c tuple_oper.c matrix_oper.c determinant_mat.c \
				inverting_mat.c rotation_mat.c scaling_mat.c translation_mat.c \
				ray.c intersections.c intersect_sphere.c \
				color.c

OBJS		=	${SRCS:.c=.o}

CFLAGS		=	-Werror -Wextra -Werror -I ${MLXDIR} -I ${LIBFTDIR}
CFLAGS		+=	-g3

LIBFTDIR	=	./libft
LIBFT		=	${LIBFTDIR}/libft.a
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

re			: fclean all

.PHONY		:	all clean fclean
