/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:01:40 by jiwolee           #+#    #+#             */
/*   Updated: 2023/01/16 15:16:32 by jiwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include	"util_img.h"

# define TRUE	1
# define FALSE	0

# define SCREEN_WIDTH	1920
# define SCREEN_HEIGHT	1080

typedef struct s_textures_img{
	t_img	background; // window? 
	t_img	wall_ea;
	t_img	wall_we;
	t_img	wall_so;
	t_img	wall_no;
	t_img	ceiling;
	t_img	floor;
}	t_textures_img;

typedef struct s_textures_info{ // textures_init_infos
	char			*wall_ea_file_name;
	char			*wall_we_file_name;
	char			*wall_so_file_name;
	char			*wall_no_file_name;
	unsigned int	ceiling_color;
	unsigned int	floor_color;
}	t_textures_info;

typedef struct s_map{
	char			**data;
	unsigned int	width;
	unsigned int	height;
}	t_map;

typedef struct s_window{
	void	*win;
	int		width;
	int		height;
}	t_window;

typedef struct s_player{
	double	pos_x;
	double	pos_y;
	double	plane_x;
	double	plane_y;
	double	dir_x;
	double	dir_y;
}	t_player;

typedef struct s_cub3d_info{
	void					*mlx;
	void					*window;
	t_map					map;
	t_player				player;
	t_textures_img			textures;
	t_textures_info			textures_info;
}	t_cub3d_info;

#endif
