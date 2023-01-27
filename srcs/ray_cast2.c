/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:00:35 by jaeyjeon          #+#    #+#             */
/*   Updated: 2023/01/27 18:27:48 by jiwolee          ###   ########.fr       */
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

void	ver_line_each_side(t_cub3d_info *info, t_ray_info *ray_info, t_vector *screen)
{
	if (ray_info->is_side == TRUE)
	{
		if (ray_info->ray_move_dir_y > 0)
			ver_line(info, ray_info, screen, &info->textures.wall_so);
		else if (ray_info->ray_move_dir_y < 0)
			ver_line(info, ray_info, screen, &info->textures.wall_no);
	}
	else
	{
		if (ray_info->ray_move_dir_x < 0)
			ver_line(info, ray_info, screen, &info->textures.wall_ea);
		if (ray_info->ray_move_dir_x > 0)
			ver_line(info, ray_info, screen, &info->textures.wall_we);
	}
}