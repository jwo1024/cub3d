# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/22 15:27:03 by jiwolee           #+#    #+#              #
#    Updated: 2023/01/12 21:58:18 by jaeyjeon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g

MLX_FLAGS	= -lmlx -framework OpenGL -framework AppKit
MLX_DIR		= ./mlx

LIBFT_DIR	= ./libft_for_cub3d

HEADER		= ./includes
INCLUDES	= -I$(HEADER) -I$(MLX_DIR) -I$(LIBFT_DIR)

SRCS_1		= ./srcs/cub3d.c \
			  ./srcs/util_img.c \
			  ./srcs/util_error.c \
			  ./srcs/util_init_map/util_init_map.c\
			  ./srcs/util_init_map/check_mapfile_info.c \
			  ./srcs/util_init_map/check_mapfile_map.c \
			  ./srcs/util_init_map/init_type_info1.c \
			  ./srcs/util_init_map/init_type_info2.c \
			  ./srcs/util_color.c \
			  ./srcs/util_safe_libft.c

SRCS_2		= ./gnl_for_cub3d/get_next_line.c\
			  ./gnl_for_cub3d/get_next_line_utils.c

SRCS		= $(SRCS_1) $(SRCS_2)

OBJS		= $(SRCS:.c=.o)

%.o : %.c
		${CC} ${CFLAGS} $(INCLUDES) -c -o $@ $^

$(NAME) : $(OBJS)
		make -C $(MLX_DIR)
		make -C $(LIBFT_DIR)
		$(CC) $(CFLAG) $(INCLUDES) -o $@ $^ -L $(MLX_DIR) $(MLX_FLAGS) -L $(LIBFT_DIR) -lft

all : $(NAME)

clean :
		rm -f $(OBJS)
		make $@ -C $(MLX_DIR)
		make $@ -C $(LIBFT_DIR)

fclean : clean
		make $@ -C $(LIBFT_DIR)
		rm -f $(NAME)

re : clean all

PHONY : all clean fclean re
