/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:52:17 by jaeyjeon          #+#    #+#             */
/*   Updated: 2023/01/26 18:09:06 by jiwolee          ###   ########.fr       */
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

#include	<stdio.h> // delete

void	ver_line(t_cub3d_info *info, t_ray_info *ray_info, t_vector *screen, t_img *texture) // t_img *texture  
{
	char	*dest_addr;
	char	*src_addr;
	t_vector img;

	double	ratio;
	// if (ray_info->is_y_side == TRUE)
	/* 왜 이런 식이 유도 되었는지 모르겠다 */
	/* player pos 을 기준으로 계산되기 때문에 앞뒤로 움직일 때 벽이 흐르는 것 같다 왜? */
	if (ray_info->is_y_side == TRUE)
		ratio = ray_info->ray_x + ray_info->wall_dist * ray_info->raydir_x;
	else
		ratio = ray_info->ray_y + ray_info->wall_dist * ray_info->raydir_y;

	ratio -= floor(ratio);
	printf("ratio %f\n", ratio);
	img.x = (int)(ratio * (double)texture->width);
	printf("img.x %f text->width %d\n", img.x, texture->width);


	screen->y = ray_info->draw_start;
	while (screen->y <= ray_info->draw_end)
	{
		img.y = (double)(screen->y - ray_info->draw_start) / (double)(ray_info->wall_height/*여기가문제*/) * (double)texture->height;
		dest_addr = get_pixel_addr_img(&info->textures.background, screen->x, screen->y);
		src_addr = get_pixel_addr_img(texture, img.x, img.y);
		*(unsigned int *)dest_addr = *(unsigned int *)src_addr;
		screen->y++;
	}
}

void	ray_cast(t_cub3d_info *info)
{
	t_vector	screen; //screen.x
	int			color;
	t_ray_info	ray_info;

	screen.x = 0;
	init_background_img(&info->textures.background,
		info->textures_info.ceiling_color, info->textures_info.floor_color);
	while (screen.x < SCREEN_WIDTH)
	{
		init_ray_info(info, &ray_info, screen.x);
		calc_first_ray_dist(info, &ray_info);
		check_ray_hit(info, &ray_info);
		calc_wall_height(info, &ray_info);
		if (info->map.data[ray_info.ray_y][ray_info.ray_x] == '1')
			color = 0xFF0000;
		else
			color = 0xFFFF00; //?
		if (ray_info.is_y_side == TRUE)
			color = color / 2;
		ver_line(info, &ray_info, &screen, &info->textures.wall_ea); // t_img texture...
		screen.x++;
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
