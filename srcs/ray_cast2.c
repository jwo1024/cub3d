/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:00:35 by jaeyjeon          #+#    #+#             */
/*   Updated: 2023/01/26 21:04:55 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"ray_cast.h"
#include	"mlx.h"
#include	"util_action.h"
#include	"cub3d.h"

int	ray_loop(t_cub3d_info *info)
{
	mlx_clear_window(info->mlx, info->window);
	if (info->mouse == FALSE)
		get_mouse_action(info);
	ray_cast(info);
	return (0);
}

void	calc_wall_height(t_cub3d_info *info, t_ray_info *ray_info)
{
	if (ray_info->is_y_side == FALSE)
		ray_info->wall_dist = (ray_info->ray_x - info->player.pos_x + \
					(1 - ray_info->ray_move_dir_x) / 2) / ray_info->raydir_x;
	else
		ray_info->wall_dist = (ray_info->ray_y - info->player.pos_y + \
					(1 - ray_info->ray_move_dir_y) / 2) / ray_info->raydir_y;
	ray_info->wall_height = (int)(SCREEN_HEIGHT / ray_info->wall_dist);
	ray_info->draw_start = -ray_info->wall_height / 2 + SCREEN_HEIGHT / 2;
	if (ray_info->draw_start < 0)
		ray_info->draw_start = 0;
	ray_info->draw_end = ray_info->wall_height / 2 + SCREEN_HEIGHT / 2;
	if (SCREEN_HEIGHT <= ray_info->draw_end)
		ray_info->draw_end = SCREEN_HEIGHT - 1;
}
