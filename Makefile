# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/22 15:27:03 by jiwolee           #+#    #+#              #
#    Updated: 2023/02/05 22:12:14 by jiwolee          ###   ########seoul.kr   #
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
			  ./srcs/utils/util_img.c \
			  ./srcs/utils/util_error.c \
			  ./srcs/init_map/util_init_map.c\
			  ./srcs/init_map/check_mapfile_info.c \
			  ./srcs/init_map/check_mapfile_map.c \
			  ./srcs/init_map/init_type_info1.c \
			  ./srcs/init_map/init_type_info2.c \
			  ./srcs/init_map/read_save_map.c \
			  ./srcs/init_map/check_mapfile_valid.c \
			  ./srcs/init/init_mlx.c \
			  ./srcs/init/init_imgs.c \
			  ./srcs/ray_cast/ray_cast.c \
			  ./srcs/ray_cast/ray_cast2.c \
			  ./srcs/ray_cast/check_wall.c\
			  ./srcs/utils/util_color.c \
			  ./srcs/utils/util_safe_libft.c \
			  ./srcs/util_action/get_key_action.c \
			  ./srcs/util_action/move_rotate_player.c \
			  ./srcs/util_action/get_mouse_action.c \
			  ./srcs/util_action/break_door_action.c \
			  ./srcs/minimap/init_minimap_img.c \
			  ./srcs/minimap/draw_minimap.c \
			  ./srcs/minimap/draw_fov_on_minimap.c

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
