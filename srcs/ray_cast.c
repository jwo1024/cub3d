/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:52:17 by jaeyjeon          #+#    #+#             */
/*   Updated: 2023/01/25 22:46:15 by jiwolee          ###   ########.fr       */
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


// obj_x를 구하려면 
// obj_x = 광선이 벽에 부딪친 x위치
// floor() ~ floor() + 1 한칸안에서의 비율을 구해보자
// ray_x - floor(ray_x) = 소수점값이 나올꺼고 그것이 바로 비율인데 ! 
// 그렇다면 . 
// ray_x - floor(ray_x)  = img_x / img.width;
// img_x =  ray_x - floor(ray_x)  * img.width;
// (y_size == TRUE) 일때 y 값으로 x를 구해야 한다. 
#include	<stdio.h> // delete

void	ver_line(t_cub3d_info *info, t_ray_info *ray_info, int screen_x, t_img *texture) // t_img *texture  
{
	int		screen_y;
	char	*dest_addr;
	char	*src_addr;
	int		img_y;
	int		img_x;
	double	ratio;
	double triangle;

/*
	triangle = pow(ray_info->wall_dist, 2) - pow(fabs(ray_info->ray_x - info->player.pos_x), 2);
	triangle = sqrt(fabs(triangle)); // 나머지 한변의 넓이 가 있을꺼고

	// ratio 예상한 범위 값이 안나옴 . 0.몇 ~ 나와야함.
	ratio = fabs(fabs(info->player.pos_y - (double)ray_info->ray_y) - triangle); 
	img_x = ratio * (double)texture->width;
	printf("ratio %f img_x %d img_width %d\n", ratio, img_x, texture->width);
*/


	if (ray_info->is_y_side == TRUE && 0)
	{
		triangle = pow(ray_info->wall_dist, 2) - pow(fabs(ray_info->ray_y - info->player.pos_y), 2);
		triangle = sqrt(fabs(triangle)); // 나머지 한변의 넓이 가 있을꺼고
		ratio = fabs(fabs(info->player.pos_x - (double)ray_info->ray_x) - triangle); 
		img_x = ratio * (double)texture->width;
		printf("1ratio %f img_x %d img_width %d\n", ratio, img_x, texture->width);
	}
	else
	{
		// wall dist 의 기준은 plane이기 때문에 오차가 나는 것 같다. 
		// 그렇다면 player의 pos가 아닌 plane상의 pos의 값을 가져와서 계산을 한다면 오차가 사라지지 않을까?!
		// 아닌 것 같.. 다. 
		triangle = pow(ray_info->wall_dist, 2) - pow(fabs(ray_info->ray_x - info->player.pos_x), 2);
		triangle = sqrt(fabs(triangle)); // 나머지 한변의 넓이 가 있을꺼고
		double first = info->player.dir_y + info->player.plane_y * ray_info->camera_x;
		ratio = fabs(fabs(first - (double)ray_info->ray_y) - triangle); 
		img_x = ratio * (double)texture->width;
		printf("2ratio %f img_x %d img_width %d\n", ratio, img_x, texture->width);
	}



//	img_x = 2;

	screen_y = ray_info->draw_start;
	while (screen_y <= ray_info->draw_end)
	{
	//	screen_y / screen_height = img.y / img.height;
	//	img_y = height안의 시작점 / 길이 * 
		img_y = (double)(screen_y - ray_info->draw_start) / (double)(ray_info->wall_height/*여기가문제*/) * (double)texture->height;
		dest_addr = get_pixel_addr_img(&info->textures.background, screen_x, screen_y);
		src_addr = get_pixel_addr_img(texture, img_x, img_y);
		*(unsigned int *)dest_addr = *(unsigned int *)src_addr;
		screen_y++;
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
		// x = 스크린의 x위치
		// ray_info.ray_x ? player position.. .

		// obj_x = 광선이 벽에 부딪친 x위치 
		// y_size == TRUE 일때 y 값으로 x를 구해야 한다. 
		// 
		ver_line(info, &ray_info, x, &info->textures.wall_ea); // t_img texture...
		x++;
	}
	{ // test
		t_img *texture = &info->textures.wall_ea;
		char *dest_addr;
		char *src_addr;
		
		for (int i = 0; i < texture->width; i++)
		{
			for (int j = 0; j< texture->height; j++)
			{
				dest_addr = get_pixel_addr_img(&info->textures.background, i, j);
				src_addr = get_pixel_addr_img(texture, i, j);
				*(unsigned int *)dest_addr = *(unsigned int *)src_addr;
			}
		}
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
