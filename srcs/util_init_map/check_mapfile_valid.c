/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mapfile_valid.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:39:55 by jiwolee           #+#    #+#             */
/*   Updated: 2023/01/24 18:53:22 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"
#include	"util_error.h"
#include	"util_init_map.h"

static int	classify_moveable_space(char map_data);
static void	check_position_moveable_space(t_map *map, unsigned int x, unsigned int y);
static void check_position(t_map *map, unsigned int x, unsigned int y);
static void	init_player(t_cub3d_info *info, unsigned int x, unsigned int y);

int	check_valid_map(t_cub3d_info *info)
{
	unsigned int		x;
	unsigned int		y;
	int		start_point;

	x = 0;
	y = 0;
	start_point = 0;
	while (y < info->map.height)
	{
		while (x < info->map.width)
		{
			check_position(&info->map, x, y);
			if (classify_moveable_space(info->map.data[y][x]) == 2)
			{
				start_point++;
				if (start_point == 2)
					exit_with_error("start_points are 2 or more");
				init_player(info, x, y);
			}
			x++;
		}
		y++;
		x = 0;
	}
	return (TRUE);
}

static void check_position(t_map *map, unsigned int x, unsigned int y)
{
	if (is_valid_char(map->data[y][x]) == FALSE)
		exit_with_error("invalid char in map");
	if (classify_moveable_space(map->data[y][x]))
		check_position_moveable_space(map, x, y);
}

static void	check_position_moveable_space(t_map *map, unsigned int x, unsigned int y)
{
	if (y == 0 || y == map->height - 1 || x == 0 || x == map->width - 1)
		exit_with_error("moveable space at edge");
	else if (map->data[y - 1][x - 1] == ' ' || map->data[y - 1][x] == ' ' ||\
		 map->data[y - 1][x + 1] == ' ' || map->data[y][x - 1] == ' ' ||\
		 map->data[y][x + 1] == ' ' || map->data[y + 1][x - 1] == ' ' ||\
		 map->data[y + 1][x] == ' ' || map->data[y + 1][x + 1] == ' ')
		exit_with_error("map isn't closed");
}

static int	classify_moveable_space(char map_data)
{
	if (map_data == 'N' || map_data == 'S' || map_data == 'E' || map_data == 'W')
		return (2);
	else if (map_data == '0')
		return (1);
	return (0);
}

static void	init_player(t_cub3d_info *info, unsigned int x, unsigned int y)
{
	double	plane_size;

	plane_size = 0.66; //width / height
	info->player.pos_x = (double)x;
	info->player.pos_y = (double)y;
	if (info->map.data[y][x] == 'N')
	{
		info->player.dir_x = (double)0;
		info->player.dir_y = (double)-1;
		info->player.plane_x = (double)-plane_size;
		info->player.plane_y = (double)0;
	}
	else if (info->map.data[y][x] == 'S')
	{
		info->player.dir_x = (double)0;
		info->player.dir_y = (double)1;
		info->player.plane_x = (double)plane_size;
		info->player.plane_y = (double)0;
	}
	else if (info->map.data[y][x] == 'W')
	{
		info->player.dir_x = (double)-1;
		info->player.dir_y = (double)0;
		info->player.plane_x = (double)0.0;
		info->player.plane_y = (double)plane_size;
	}
	else if (info->map.data[y][x] == 'E')
	{
		info->player.dir_x = (double)1;
		info->player.dir_y = (double)0;
		info->player.plane_x = (double)0.0;
		info->player.plane_y = (double)-plane_size;
	}
}
