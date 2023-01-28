/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:00:35 by jaeyjeon          #+#    #+#             */
/*   Updated: 2023/01/28 15:51:24 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"ray_cast.h"
#include	"mlx.h"
#include	"util_action.h"
#include	<stdio.h>
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
	if (ray_info->is_side == FALSE)
		ray_info->wall_dist = (ray_info->ray.x - info->player.pos.x + \
					(1 - ray_info->ray_move_dir.x) / 2) / ray_info->raydir.x;
	else
		ray_info->wall_dist = (ray_info->ray.y - info->player.pos.y + \
					(1 - ray_info->ray_move_dir.y) / 2) / ray_info->raydir.y;
	ray_info->wall_height = (int)(SCREEN_HEIGHT / ray_info->wall_dist);
	ray_info->draw_start = -ray_info->wall_height / 2 + SCREEN_HEIGHT / 2;
	if (ray_info->draw_start < 0)
		ray_info->draw_start = 0;
	ray_info->draw_end = ray_info->wall_height / 2 + SCREEN_HEIGHT / 2;
	if (SCREEN_HEIGHT <= ray_info->draw_end)
		ray_info->draw_end = SCREEN_HEIGHT - 1;
}

void	ver_line_each_side(t_cub3d_info *info, t_ray_info *ray_info, \
												t_vector *screen)
{
	if (ray_info->is_side == TRUE)
	{
		if (ray_info->ray_move_dir.y > 0)
			ver_line(info, ray_info, screen, &info->textures.wall_so);
		else if (ray_info->ray_move_dir.y < 0)
			ver_line(info, ray_info, screen, &info->textures.wall_no);
	}
	else
	{
		if (ray_info->ray_move_dir.x < 0)
			ver_line(info, ray_info, screen, &info->textures.wall_ea);
		if (ray_info->ray_move_dir.x > 0)
			ver_line(info, ray_info, screen, &info->textures.wall_we);
	}
}
