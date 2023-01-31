/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:00:35 by jaeyjeon          #+#    #+#             */
/*   Updated: 2023/01/31 22:15:11 by jiwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"ray_cast.h"
#include	"mlx.h"
#include	"util_action.h"
#include	<math.h>
#include	<stdio.h>
#include	"cub3d.h"

static double	get_ratio(t_cub3d_info *info, t_ray_info *ray_info);


void	recursive_draw_line_1(int p, t_vector *start, t_vector *end, t_cub3d_info *info, t_vector *mini);
void	draw_line(t_cub3d_info *info, t_ray_info *ray_info);


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
	if (ray_info->is_door == TRUE)
		ver_line(info, ray_info, screen, &info->textures.wall_do);
	else if (ray_info->is_side == TRUE)
	{
		if (ray_info->ray_move_dir.y > 0)
			ver_line(info, ray_info, screen, &info->textures.wall_no);
		else if (ray_info->ray_move_dir.y < 0)
			ver_line(info, ray_info, screen, &info->textures.wall_so);
	}
	else
	{
		if (ray_info->ray_move_dir.x < 0)
			ver_line(info, ray_info, screen, &info->textures.wall_ea);
		else if (ray_info->ray_move_dir.x > 0)
			ver_line(info, ray_info, screen, &info->textures.wall_we);
	}
}

void	ver_line(t_cub3d_info *info, t_ray_info *ray_info, \
											t_vector *screen, t_img *texture)
{
	char		*dest_addr;
	char		*src_addr;
	t_vector	img;
	double		ratio;
	int			x;

	x = SCREEN_WIDTH - 1 - screen->x;

	
	ratio = get_ratio(info, ray_info);
	
	draw_line(info, ray_info); //

	img.x = (int)(ratio * texture->width);
	screen->y = ray_info->draw_start;
	while (screen->y < ray_info->draw_end)
	{
		// 이미지 울렁거림... ... ...
		if (ray_info->wall_height > SCREEN_HEIGHT)
			img.y = ((double)texture->height) / ray_info->wall_height \
					* ((ray_info->wall_height - SCREEN_HEIGHT) / 2 + screen->y);
		else
			img.y = (int)((screen->y - ray_info->draw_start) \
							/ ray_info->wall_height * texture->height);
		dest_addr = get_pixel_addr_img(&info->textures.background, x, \
															screen->y);
		src_addr = get_pixel_addr_img(texture, img.x, img.y);
		*(unsigned int *)dest_addr = *(unsigned int *)src_addr;
		screen->y++;
	}
}

static double	get_ratio(t_cub3d_info *info, t_ray_info *ray_info)
{
	double		ratio;

	if (ray_info->is_side == TRUE)
	{
		ratio = info->player.pos.x + ray_info->wall_dist * ray_info->raydir.x;
		ray_info->raydir.x += ratio;
	}
	else
	{
		ratio = info->player.pos.y + ray_info->wall_dist * ray_info->raydir.y;
		ray_info->raydir.y += ratio;
	}
	ratio -= floor(ratio);
	if ((ray_info->is_side == TRUE && ray_info->ray_move_dir.y < 0) \
		|| (ray_info->is_side == FALSE && ray_info->ray_move_dir.x > 0))
		ratio = 1 - ratio;
	return (ratio);
}


void	draw_line(t_cub3d_info *info, t_ray_info *ray_info)
{
	int	dx;
	int	dy;
	t_vector	start;
	t_vector	end;
	t_vector	mini;

	mini.x = (info->player.pos.x * 10 - (info->textures.minimap.width / 2));
	mini.y = (info->player.pos.y * 10 - (info->textures.minimap.height / 2));

	start.x = (int)(info->player.pos.x * 10.0);
	start.y = (int)(info->player.pos.y * 10.0);
	end.x = (int)(ray_info->ray.x * 10.0);
	end.y = (int)(ray_info->ray.y * 10.0);


	dx = fabs(start.x - end.x);
	dy = fabs(start.y - end.y);

	int	p;
	if (dx != 0 && dy / dx > 1)
	{
		p = 2 * dx - dy;
		recursive_draw_line_1(p, &start, &end, info, &mini);
	}
	else
	{
		p = 2 * dy - dx;
	//	recursive_draw_line_2(p, &start, &end);
	}

}

void	recursive_draw_line_1(int p, t_vector *start, t_vector *end, t_cub3d_info *info, t_vector *mini)
{
	int		dx;
	int		dy;
	char	*addr;
	int		x;
	int		y;
	int		x_move;
	int		y_move;

	x_move = 1;
	y_move = 1;
	if (start->x > end->x)
		x_move = x_move * -1;
	if (start->y > end->y)
		y_move = y_move * -1;
	dx = fabs(start->x - end->x);
	dy = fabs(start->y - end->y);

	while (!(start->x == end->x && start->y == end->y))
	{
		if (p < 0)
		{
			start->y += y_move;
			dx = fabs(start->x - end->x);
			dy = fabs(start->y - end->y);
			p = p + 2 * dx;
		}
		else
		{
			start->x += x_move;
			start->y += y_move;
			dx = fabs(start->x - end->x);
			dy = fabs(start->y - end->y);
			p = p + 2 * (dx - dy);
		}
		x = start->x - mini->x;
		y = start->y - mini->y;
		addr = get_pixel_addr_img(&info->textures.minimap, x, y);

		if (addr)
			*(unsigned int *)addr = 0X00FFFFFF;
	}
}
