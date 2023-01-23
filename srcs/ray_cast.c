/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:52:17 by jaeyjeon          #+#    #+#             */
/*   Updated: 2023/01/23 21:47:40 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"
#include	"ray_cast.h"
#include	"math.h"
#include	"mlx.h"
#include	<stdlib.h>

static void	init_ray_info(t_cub3d_info *info, t_ray_info *ray_info, int x);
static void	calc_first_ray_dist(t_cub3d_info *info, t_ray_info *ray_info);
static void	check_ray_hit(t_cub3d_info *info, t_ray_info *ray_info);

void	ver_line(t_cub3d_info *info, t_ray_info *ray_info, int x)
{
	int y;
	int color;

	color = 0xff0000;
	y = ray_info->draw_start;
	while (y <= ray_info->draw_end)
	{
		mlx_pixel_put(info->mlx, info->window, x, y, color);
		color++;
		y++;
	}
}

int	ray_cast(t_cub3d_info *info)
{
	int			x;
	t_ray_info	*ray_info;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		ray_info = malloc(sizeof(t_ray_info));
		init_ray_info(info, ray_info, x);
		calc_first_ray_dist(info, ray_info);
		check_ray_hit(info, ray_info);
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
		ver_line(info, ray_info, x);
		free(ray_info);
		x++;
	}
	return (0);
}

static void	init_ray_info(t_cub3d_info *info, t_ray_info *ray_info, int x)
{
	ray_info->camera_x = 2 * x / SCREEN_WIDTH - 1;
	ray_info->raydir_x = info->player.dir_x + \
						info->player.plane_x * ray_info->camera_x;
	ray_info->raydir_y = info->player.dir_y + \
						info->player.plane_y * ray_info->camera_x;
	ray_info->ray_x = (int)info->player.pos_x;
	ray_info->ray_y = (int)info->player.pos_y;
	ray_info->second_dist_x = fabs(1 / ray_info->raydir_x);
	ray_info->second_dist_y = fabs(1 / ray_info->raydir_y);
}

static void	calc_first_ray_dist(t_cub3d_info *info, t_ray_info *ray_info)
{
	if (ray_info->raydir_x < 0) // 오른쪽으로 가다가 만나는 x
	{
		ray_info->ray_move_dir_x = -1;
		ray_info->first_dist_x = (info->player.pos_x - ray_info->ray_x) * ray_info->second_dist_x;
	}
	else // 왼으로 가다가 만나는 x
	{
		ray_info->ray_move_dir_x = 1;
		ray_info->first_dist_x = (ray_info->ray_x + 1.0 - info->player.pos_x) * ray_info->second_dist_x;
	}
	if (ray_info->raydir_y < 0) // 위로 가다가 만나는 y
	{
		ray_info->ray_move_dir_y = -1;
		ray_info->first_dist_y = (info->player.pos_y - ray_info->ray_y) * ray_info->second_dist_y;
	}
	else // 아래로 가다가 만나는 y
	{
		ray_info->ray_move_dir_y = 1;
		ray_info->first_dist_y = (ray_info->ray_y + 1.0 - info->player.pos_y) * ray_info->second_dist_y;
	}
}

static void	check_ray_hit(t_cub3d_info *info, t_ray_info *ray_info) // DDA
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray_info->first_dist_x < ray_info->first_dist_y)
		{
			ray_info->first_dist_x += ray_info->second_dist_x;
			ray_info->ray_x += ray_info->ray_move_dir_x;
			ray_info->is_y_side = FALSE;
		}
		else
		{
			ray_info->first_dist_y += ray_info->second_dist_y;
			ray_info->ray_y += ray_info->ray_move_dir_y;
			ray_info->is_y_side = TRUE;
		}
		if (info->map.data[ray_info->ray_y][ray_info->ray_x] == '1')
			hit = 1;
	}
}
