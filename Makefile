# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiwolee <jiwolee@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/22 15:27:03 by jiwolee           #+#    #+#              #
#    Updated: 2023/01/10 18:18:46 by jiwolee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Werror -Wextra

MLX_FLAGS	= -lmlx -framework OpenGL -framework AppKit
MLX_DIR		= ./mlx

HEADER		= ./includes
INCLUDES	= -I$(HEADER) -I$(MLX_DIR)

SRCS_1		= ./srcs/cub3d.c \
			  ./srcs/util_img.c

SRCS_2		= ./gnl_for_cub3d/get_next_line.c\
			  ./gnl_for_cub3d/get_next_line_utils.c

SRCS		= $(SRCS_1) $(SRCS_2)

OBJS		= $(SRCS:.c=.o)

%.o : %.c
		${CC} ${CFLAGS} $(INCLUDES) -c -o $@ $^

$(NAME) : $(OBJS)
		make -C $(MLX_DIR)
		$(CC) $(CFLAG) $(INCLUDES) -o $@ $^ -L $(MLX_DIR) $(MLX_FLAGS)

all : $(NAME)

clean :
		rm -f $(OBJS)
		make $@ -C $(MLX_DIR)

fclean : clean
		rm -f $(NAME)

re : clean all

PHONY : all clean fclean re