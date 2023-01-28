/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:52:17 by jaeyjeon          #+#    #+#             */
/*   Updated: 2023/01/28 19:12:00 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"
#include	"ray_cast.h"
#include	"math.h"
#include	"mlx.h"
#include	"util_init.h"
#include	<stdlib.h>
#include	"minimap.h"

static void	init_ray_info(t_cub3d_info *info, t_ray_info *ray_info, int x);
static void	calc_first_ray_dist(t_cub3d_info *info, t_ray_info *ray_info);
static void	check_ray_hit(t_cub3d_info *info, t_ray_info *ray_info);

#include	<stdio.h> // delete

void	ver_line(t_cub3d_info *info, t_ray_info *ray_info, t_vector *screen, t_img *texture) // t_img *texture
{
	char		*dest_addr;
	char		*src_addr;
	t_vector	img;
	double		ratio;
// get_ratio ()
	if (ray_info->is_side == TRUE)
		ratio = info->player.pos.x + ray_info->wall_dist * ray_info->raydir.x;
	else
		ratio = info->player.pos.y + ray_info->wall_dist * ray_info->raydir.y;
	ratio -= floor(ratio);

	if ((ray_info->is_side == TRUE && ray_info->ray_move_dir.y < 0) \
		|| (ray_info->is_side == FALSE && ray_info->ray_move_dir.x > 0))
		ratio = 1 - ratio;
	// 이미지 좌우 반전 되는것

	img.x = (int)(ratio * (double)texture->width);
	screen->y = ray_info->draw_start;
	while (screen->y <= ray_info->draw_end)
	{
		// -1.2370370370370369 = 334 / 135 * ((135 - SCREEN_HEIGHT ) / 2 + 472)

		if (ray_info->wall_height > SCREEN_HEIGHT)
			img.y = ((double)texture->height) / ray_info->wall_height * ((ray_info->wall_height - SCREEN_HEIGHT/*여기*/) / 2 + screen->y);
		else
			img.y = (screen->y - (double)ray_info->draw_start) / ray_info->wall_height * texture->height;

		//img.y : texture->height = screen->y - ray_info->draw_start : wall_height


		dest_addr = get_pixel_addr_img(&info->textures.background, screen->x, screen->y);
		src_addr = get_pixel_addr_img(texture, img.x, img.y);
		*(unsigned int *)dest_addr = *(unsigned int *)src_addr;
		screen->y++;
	}
}

void	ray_cast(t_cub3d_info *info)
{
	t_vector	screen;
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
		screen.x++;
	}
	draw_minimap(info);
	printf("draw_minimap\n");
	mlx_put_image_to_window(info->mlx, info->window, \
							info->textures.background.img_ptr, 0, 0);
	// mlx_put_image_to_window(info->mlx, info->window, \
	//  						info->textures.minimap.img_ptr, 0, 0);
	// 미니맵 그려주기
}

static void	init_ray_info(t_cub3d_info *info, t_ray_info *ray_info, int x)
{
	ray_info->camera_x = 2 * x / (double)SCREEN_WIDTH - 1; //x 값이 카메라 평면상에서 차지하는 x좌표
	ray_info->raydir.x = info->player.dir.x + \
						info->player.plane.x * ray_info->camera_x; // ray의 방향벡터
	ray_info->raydir.y = info->player.dir.y + \
						info->player.plane.y * ray_info->camera_x;
	ray_info->ray.x = (int)info->player.pos.x; // 현재 ray가 존재하는 칸의 x,y 좌표
	ray_info->ray.y = (int)info->player.pos.y;
	ray_info->second_dist.x = fabs(1 / ray_info->raydir.x);
	ray_info->second_dist.y = fabs(1 / ray_info->raydir.y);
	 // 1은 x와 y의 비율로 계산하기때문에 같은값으로 나눠 비율을 같게해주는것, 100이든 1000이든 결과는 같음
}

static void	calc_first_ray_dist(t_cub3d_info *info, t_ray_info *ray_info)
{
	if (ray_info->raydir.x < 0)
	{
		ray_info->ray_move_dir.x = -1;
		ray_info->first_dist.x = (info->player.pos.x - ray_info->ray.x) \
									* ray_info->second_dist.x;
	}
	else
	{
		ray_info->ray_move_dir.x = 1;
		ray_info->first_dist.x = (ray_info->ray.x + 1.0 - info->player.pos.x) \
									* ray_info->second_dist.x;
	}
	if (ray_info->raydir.y < 0)
	{
		ray_info->ray_move_dir.y = -1;
		ray_info->first_dist.y = (info->player.pos.y - ray_info->ray.y) \
									* ray_info->second_dist.y;
	}
	else
	{
		ray_info->ray_move_dir.y = 1;
		ray_info->first_dist.y = (ray_info->ray.y + 1.0 - info->player.pos.y) \
									* ray_info->second_dist.y;
	}
}

static void	check_ray_hit(t_cub3d_info *info, t_ray_info *ray_info)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray_info->first_dist.x < ray_info->first_dist.y)
		{
			ray_info->first_dist.x += ray_info->second_dist.x;
			ray_info->ray.x += ray_info->ray_move_dir.x;
			ray_info->is_side = FALSE;
		}
		else
		{
			ray_info->first_dist.y += ray_info->second_dist.y;
			ray_info->ray.y += ray_info->ray_move_dir.y;
			ray_info->is_side = TRUE;
		}
		if (info->map.data[(int)ray_info->ray.y][(int)ray_info->ray.x] == '1')
			hit = 1;
	}
}
