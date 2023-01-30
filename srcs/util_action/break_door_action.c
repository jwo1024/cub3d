/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_door_action.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:08:56 by jaeyjeon          #+#    #+#             */
/*   Updated: 2023/01/30 17:33:11 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"util_action.h"
#include	"cub3d.h"
#include	"ray_cast.h"

static void	break_door(t_cub3d_info *info);
static void	upadate_minimap(t_cub3d_info *info, t_vector ray);

int	key_pressed_space(int key, t_cub3d_info *info)
{
	if (key == KEY_SPACE)
		break_door(info);
	return (0);
}

static void	break_door(t_cub3d_info *info)
{
	t_ray_info	ray_info;

	init_ray_info(info, &ray_info, SCREEN_WIDTH / 2);
	calc_first_ray_dist(info, &ray_info);
	check_ray_hit(info, &ray_info);
	calc_wall_height(info, &ray_info);
	if (ray_info.wall_dist <= 3.0f)
	{
		if (info->map.data[(int)ray_info.ray.y][(int)ray_info.ray.x] == '2')
		{
			info->map.data[(int)ray_info.ray.y][(int)ray_info.ray.x] = '0';
			upadate_minimap(info, ray_info.ray);
		}
	}
}

static void	upadate_minimap(t_cub3d_info *info, t_vector ray)
{
	int			block_size; // 통일된 데이터 저장장소가 있으면 좋겠다. minimap 색깔 등..
	t_vector	pos;
	t_vector	end;
	char		*addr;

	block_size = 10;
	pos.x = (int)ray.x * block_size;
	pos.y = (int)ray.y * block_size;
	end.x = pos.x + block_size;
	end.y = pos.y + block_size;
	while (pos.y < end.y)
	{
		pos.x = (int)ray.x * block_size;
		while (pos.x < end.x)
		{
			addr = get_pixel_addr_img(&info->textures.minimap, pos.x, pos.y);
			*(unsigned int *)addr = 0X00669999;
			++pos.x;
		}
		++pos.y;
	}
}
