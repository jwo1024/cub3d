/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:52:17 by jaeyjeon          #+#    #+#             */
/*   Updated: 2023/01/24 21:37:16 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"
#include	"ray_cast.h"
#include	"math.h"
#include	"mlx.h"
#include	"util_draw_img.h"
#include	<stdlib.h>

static void	init_ray_info(t_cub3d_info *info, t_ray_info *ray_info, int x);
static void	calc_first_ray_dist(t_cub3d_info *info, t_ray_info *ray_info);
static void	check_ray_hit(t_cub3d_info *info, t_ray_info *ray_info);

void	ver_line(t_cub3d_info *info, t_ray_info *ray_info, int x, int color)
{
	int		y;
	char	*pixel_addr;

	y = ray_info->draw_start;
	while (y <= ray_info->draw_end)
	{
		pixel_addr = get_pixel_addr_img(&info->textures.background, x, y);
		*(unsigned int *)pixel_addr = (unsigned int)color;
		y++;
	}
}

void	ray_cast(t_cub3d_info *info)
{
	int			x;
	int			color;
	t_ray_info	ray_info;

	x = 0;
	init_background_img(&info->textures.background,
		info->textures_info.ceiling_color, info->textures_info.floor_color);
	while (x < SCREEN_WIDTH)
	{
		init_ray_info(info, &ray_info, x);
		calc_first_ray_dist(info, &ray_info);
		check_ray_hit(info, &ray_info);
		calc_wall_height(info, &ray_info);
		if (info->map.data[ray_info.ray_y][ray_info.ray_x] == '1')
			color = 0xFF0000;
		else
			color = 0xFFFF00;
		if (ray_info.is_y_side == TRUE)
			color = color / 2;
		ver_line(info, &ray_info, x, color);
		x++;
	}
	mlx_put_image_to_window(info->mlx, info->window, \
							info->textures.background.img_ptr, 0, 0);
}

static void	init_ray_info(t_cub3d_info *info, t_ray_info *ray_info, int x)
{
	ray_info->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
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
	if (ray_info->raydir_x < 0)
	{
		ray_info->ray_move_dir_x = -1;
		ray_info->first_dist_x = (info->player.pos_x - ray_info->ray_x) \
									* ray_info->second_dist_x;
	}
	else
	{
		ray_info->ray_move_dir_x = 1;
		ray_info->first_dist_x = (ray_info->ray_x + 1.0 - info->player.pos_x) \
									* ray_info->second_dist_x;
	}
	if (ray_info->raydir_y < 0)
	{
		ray_info->ray_move_dir_y = -1;
		ray_info->first_dist_y = (info->player.pos_y - ray_info->ray_y) \
									* ray_info->second_dist_y;
	}
	else
	{
		ray_info->ray_move_dir_y = 1;
		ray_info->first_dist_y = (ray_info->ray_y + 1.0 - info->player.pos_y) \
									* ray_info->second_dist_y;
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
