/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:52:17 by jaeyjeon          #+#    #+#             */
/*   Updated: 2023/01/27 18:29:13 by jiwolee          ###   ########.fr       */
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

// get_ratio ()
	if (ray_info->is_side == TRUE)
		ratio = info->player.pos_x + ray_info->wall_dist * ray_info->raydir_x;
	else
		ratio = info->player.pos_y + ray_info->wall_dist * ray_info->raydir_y;
	ratio -= floor(ratio);

	if ((ray_info->is_side == TRUE && ray_info->ray_move_dir_y < 0) \
		|| (ray_info->is_side == FALSE && ray_info->ray_move_dir_x > 0))
		ratio = 1 - ratio;
	// 이미지 좌우 반전 되는것
//

	img.x = (int)(ratio * (double)texture->width);
	screen->y = ray_info->draw_start;
	while (screen->y <= ray_info->draw_end)
	{
		img.y = ((double)texture->height) / ray_info->wall_height * ((ray_info->wall_height - SCREEN_HEIGHT) / 2 + screen->y);
		dest_addr = get_pixel_addr_img(&info->textures.background, screen->x, screen->y);
		src_addr = get_pixel_addr_img(texture, img.x, img.y);
		*(unsigned int *)dest_addr = *(unsigned int *)src_addr;
		screen->y++;
	}
}

void	ray_cast(t_cub3d_info *info)
{
	t_vector	screen; //screen.x
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
		ver_line_each_side(info, &ray_info, &screen);
		// ver_line(info, &ray_info, &screen, &info->textures.wall_ea); // t_img texture...
		screen.x++;
	}
	mlx_put_image_to_window(info->mlx, info->window, \
							info->textures.background.img_ptr, 0, 0);
}

static void	init_ray_info(t_cub3d_info *info, t_ray_info *ray_info, int x)
{
	ray_info->camera_x = 2 * x / (double)SCREEN_WIDTH - 1; //x 값이 카메라 평면상에서 차지하는 x좌표
	ray_info->raydir_x = info->player.dir_x + \
						info->player.plane_x * ray_info->camera_x; // ray의 방향벡터
	ray_info->raydir_y = info->player.dir_y + \
						info->player.plane_y * ray_info->camera_x;
	ray_info->ray_x = (int)info->player.pos_x; // 현재 ray가 존재하는 칸의 x,y 좌표
	ray_info->ray_y = (int)info->player.pos_y;
	ray_info->second_dist_x = fabs(1 / ray_info->raydir_x);
	ray_info->second_dist_y = fabs(1 / ray_info->raydir_y);
	 // 1은 x와 y의 비율로 계산하기때문에 같은값으로 나눠 비율을 같게해주는것, 100이든 1000이든 결과는 같음
}

static void	calc_first_ray_dist(t_cub3d_info *info, t_ray_info *ray_info)
{	// first_dist_x : delta_dist_x = (ray_x + 1) - pos_x : 1
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
			ray_info->is_side = FALSE;
		}
		else
		{
			ray_info->first_dist_y += ray_info->second_dist_y;
			ray_info->ray_y += ray_info->ray_move_dir_y;
			ray_info->is_side = TRUE;
		}
		if (info->map.data[ray_info->ray_y][ray_info->ray_x] == '1')
			hit = 1;
	}
}
