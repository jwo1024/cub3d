/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:01:40 by jiwolee           #+#    #+#             */
/*   Updated: 2023/01/11 17:09:36 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include	"util_img.h"

# define TRUE	1
# define FALSE	0

typedef struct s_textures_img{
	t_img	*canvas;
	t_img	*wall_east;
	t_img	*wall_west;
	t_img	*wall_south;
	t_img	*wall_north;
	t_img	*sky; // img -> color ?
	t_img	*ground;
}	t_textures_img;

typedef struct s_textures_file_name{
	char	*canvas;
	char	*wall_east;
	char	*wall_west;
	char	*wall_south;
	char	*wall_north;
	char	*sky_color;
	char	*ground_color;
}	t_textures_file_name;

typedef struct s_map{
	char	**data;
	int		width;
	int		height;
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
	t_map					map;
	t_player				player;
	t_window				window;
	t_img					window_buff;
	t_textures_img			textures;
	t_textures_file_name	textures_file_name;
}	t_cub3d_info;

#endif
