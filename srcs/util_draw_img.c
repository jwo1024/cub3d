/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_draw_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 20:30:12 by jaeyjeon          #+#    #+#             */
/*   Updated: 2023/01/25 14:36:44 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"util_draw_img.h"
#include	"cub3d.h"
#include	"util_img.h"
#include	"stdio.h"

void	init_background_img(t_img *background, \
						unsigned int ceiling_color, unsigned int floor_color)
{
	int				x;
	int				y;
	char			*pixcel_addr;
	unsigned int	color;

	y = 0;
	color = ceiling_color;
	while (y < background->height)
	{
		x = 0;
		if (y >= background->height / 2)
			color = floor_color;
		while (x < background->width)
		{
			pixcel_addr = get_pixel_addr_img(background, x, y);
			*(unsigned int *)pixcel_addr = color;
			++x;
		}
		++y;
	}
}
