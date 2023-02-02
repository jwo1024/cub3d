/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_fov.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 20:16:57 by jiwolee           #+#    #+#             */
/*   Updated: 2023/02/02 21:59:44 by jiwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"
#include	"ray_cast.h"

typedef	struct s_bresenham_info
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
	int	dx;
	int	dy;
	int	fraction;
}	t_bresenham_info;


void	draw_minimap_fov(t_cub3d_info *info, t_ray_info *ray_info, int block)
{
	int	fullmini_x;
	int	fullmini_y;

	fullmini_x = (info->player.pos.x * 10 - (info->textures.minimap.width / 2));
	fullmini_y = (info->player.pos.y * 10 - (info->textures.minimap.height / 2));

	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;

	start_x = (int)(info->player.pos.x * 10.0) - fullmini_x;
	start_y = (int)(info->player.pos.y * 10.0) - fullmini_y;
	end_x = (int)(ray_info->ray.x * 10.0) + block - fullmini_x;
	end_y = (int)(ray_info->ray.y * 10.0) + block - fullmini_y;

	// (int start_x, int start_y int end_x, int end_y)

	int	dx = end_x - start_x;
	int	dy = end_y - start_y;
	int	stepx;
	int	stepy;

	char	*addr;

	stepx = 1;
	stepy = 1;
	if (dy < 0)
	{
		dy = -dy;
		stepy = -1;
	}
	if (dx < 0)
	{
		dx = -dx;
		stepx = -1;
	}
	dy <<= 1; /// 2배
	dx <<= 1;

//	int	fraction;
	if (dx > dy)
	{
		int fraction = dy - (dx >> 1);
		while (start_x != end_x)
		{
			if (fraction >= 0)
			{
				start_y += stepy;
				fraction -= dx;
			}
			start_x += stepx;
			fraction += dy;

			addr = get_pixel_addr_img(&info->textures.minimap, start_x, start_y);
			if (addr && (*(unsigned int *)addr == info->minimap_info.wall_color \
					|| *(unsigned int *)addr == info->minimap_info.door_color))
				break ;
			if (addr)
				*(unsigned *)addr =  0X00FFFFFF;
		}
	}
	else
	{
		int fraction = dx - (dy >> 1);

		while (start_y != end_y)
		{
			if (fraction >= 0)
			{
				start_x += stepx;
				fraction -= dy;
			}
			start_y += stepy;
			fraction += dx;

			addr = get_pixel_addr_img(&info->textures.minimap, start_x, start_y);
			if (addr && (*(unsigned int *)addr == info->minimap_info.wall_color \
					|| *(unsigned int *)addr == info->minimap_info.door_color))
				break ;
			if (addr)
				*(unsigned *)addr =  0XFFFFFF;
		}
	}
}

/*
int	draw_line_2(int start_x, int start_y, int end_x, int end_y)
{
	int	dx = end_x - start_x;
	int	dy = end_y - start_y;
	int	stepx;
	int	stepy;

	char	*addr;

	stepx = 1;
	stepy = 1;
	if (dy < 0)
	{
		dy = -dy;
		stepy = -1;
	}
	if (dx < 0)
	{
		dx = -dx;
		stepx = -1;
	}
	dy <<= 1;
	dx <<= 1;
	
	int fraction = dx - (dy >> 1);

	while (start_y != end_y)
	{
		if (fraction >= 0)
		{
			start_x += stepx;
			fraction -= dy;
		}
		start_y += stepy;
		fraction += dx;

		addr = get_pixel_addr_img(&info->textures.minimap, start_x, start_y);
		if (addr && (*(unsigned int *)addr == info->minimap_info.wall_color \
				|| *(unsigned int *)addr == info->minimap_info.door_color))
			break ;
		if (addr)
			*(unsigned *)addr =  0XFFFFFF;
	}
}
*/
