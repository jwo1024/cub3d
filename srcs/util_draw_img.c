/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_draw_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 20:30:12 by jaeyjeon          #+#    #+#             */
/*   Updated: 2023/01/26 16:20:20 by jiwolee          ###   ########.fr       */
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
	pixcel_addr = NULL;
	color = ceiling_color;
	while (y < background->height)
	{
		x = 0;
		if (y >= background->height / 2)
			color = floor_color;
		while (x < background->width)
		{
			pixcel_addr = get_pixel_addr_img(background, x, y);
			if (pixcel_addr)
				*(unsigned int *)pixcel_addr = color;
			++x;
		}
		++y;
	}
}
