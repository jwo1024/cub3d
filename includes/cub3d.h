/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:01:40 by jiwolee           #+#    #+#             */
/*   Updated: 2023/01/10 21:33:31 by jiwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include   "util_img.h"

typedef struct s_textures{
	t_img	*canvas;
	t_img	*wall_east;
	t_img	*wall_west;
	t_img	*wall_south;
	t_img	*wall_north;
// t_img *sky;
// t_img *ground;
}	t_textures;

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
	t_map		map;
	t_player	player;
	t_window	window;
	t_img		window_buff;
	t_textures	textures;
}	t_cub3d_info;

#endif
