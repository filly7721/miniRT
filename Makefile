NAME		=	miniRT

SRCS		=	main.c init.c hook.c \
				parsing.c parse_lights.c split_by_char.c  \
				parse_camera.c parse_plane.c parse_sphere.c parse_cylinder.c \
				print_env.c utils.c tuple.c tuple_oper.c matrix_oper.c determinant_mat.c \
				inverting_mat.c rotation_mat.c scaling_mat.c translation_mat.c \
				ray.c intersections.c intersect_sphere.c \
				color.c generate_ray.c free_minirt.c free_shapes.c free_lights.c

OBJS		=	${SRCS:.c=.o}

LIBFTDIR	=	./libft
LIBFT		=	${LIBFTDIR}/libft.a
LIBFTFLAGS	=	 -L ${LIBFTDIR} -lft

OS := $(shell uname)

ifeq (${OS}, Darwin)
	MLXDIR := mlx
	MLX := ${MLXDIR}/libmlx.a
	MLXFLAGS = -L$(MLXDIR) -lmlx -framework OpenGL -framework Appkit -L/usr/lib -lm
else ifeq (${OS}, Linux)
    MLXDIR := mlx_linux
	MLX 	= ${MLXDIR}/libmlx_Linux.a
	MLXFLAGS = -L$(MLXDIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
endif

CFLAGS		=	-Werror -Wextra -Werror
CFLAGS		+=	-I ${LIBFTDIR}
CFLAGS		+=	-I ${MLXDIR}
CFLAGS		+=	-g3

all					: ${NAME}

%.o					:	%.c
			cc ${CFLAGS} $< -c -o $@

${NAME}				:	${MLX} ${LIBFT} ${OBJS} 
			cc ${CFLAGS} ${OBJS} ${MLXFLAGS} ${LIBFTFLAGS} -o ${NAME}

${MLX}	:
			make -C ${MLXDIR}

${LIBFT}:
			make -C ${LIBFTDIR}

clean				:
			rm -f ${OBJS}
			make -C ${LIBFTDIR} clean

fclean				:	clean
			rm -f ${NAME}
			rm -f ${LIBFT}
			make -C ${MLXDIR} clean

re					: fclean all

.PHONY				:	all clean fclean
