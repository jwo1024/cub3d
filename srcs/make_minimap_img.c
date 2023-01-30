/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_full_minimap_img.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:07:43 by jaeyjeon          #+#    #+#             */
/*   Updated: 2023/01/30 19:28:01 by jiwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"
#include	"util_img.h"
#include	"minimap.h"
#include	"mlx.h"
#include	"stdio.h" //NULL

static void			init_minimap_info(t_minimap_info *mini_info);
static unsigned int	get_wall_color(t_minimap_info *mini_info, char wall_type);
static void			draw_full_minimap_img(t_minimap_info *mini_info, \
								t_img *minimap_img, t_map *map, int block_size);

t_img	*make_new_img(t_cub3d_info *info, t_img *img, int width, int height)
{
	img->width = width; // 5px? if int범위 벗어났을때 예외
	img->height = height;
	img->img_ptr = mlx_new_image(info->mlx, img->width, img->height);

	img->addr = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel, \
										&img->line_length, &img->endian);
	return (img);
}

int	init_minimap_img(t_cub3d_info *info, t_map *map) // void
{
	t_img	*full_minimap_img;
	int		block_size;

	init_minimap_info(&info->minimap_info);

	block_size = info->minimap_info.block_size;
	make_new_img(info, &info->textures.minimap, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10);
	full_minimap_img = make_new_img(info, &info->textures.full_minimap, map->width * block_size, map->height *block_size);
// 여기까지는 new_background_img 랑 겹치기 때문에 새 함수 파서 사용하는 것이 좋을듯
	draw_full_minimap_img(&info->minimap_info, full_minimap_img, map, block_size);
	return (0);
}

static void	init_minimap_info(t_minimap_info *mini_info)
{
	if (mini_info)
	{
		mini_info->block_size = 10;
		mini_info->floor_color = 0X00669999;
		mini_info->wall_color = 0X00003333;
		mini_info->door_color = 0X00FFFF00;
		mini_info->empty_color = 0X00CCFFFF;
		mini_info->player_color = 0x00CC0000;
	}
}

static void	draw_full_minimap_img(t_minimap_info *mini_info, \
								t_img *minimap_img, t_map *map, int block_size)
{
	int				img_x;
	int				img_y;
	unsigned int	color;
	char			*addr;

	img_y = 0;
	while (img_y < minimap_img->height)
	{
		img_x = 0;
		while (img_x < minimap_img->width)
		{
			// 복도 비어있는 공간 벽
			color = get_wall_color(mini_info, \
							map->data[img_y / block_size][img_x / block_size]);
			addr = get_pixel_addr_img(minimap_img, img_x, img_y);
			*(unsigned int *)addr = color;
		//	draw_color(minimap_img, color);
			img_x++;
		}
		img_y++;
	}
}

static unsigned int	get_wall_color(t_minimap_info *mini_info, char wall_type)
{
	unsigned int	color;

	if (wall_type == '1')
		color = mini_info->wall_color;
	else if (wall_type == ' ')
		color = mini_info->empty_color;
	else if (wall_type == '2')
		color = mini_info->door_color;
	else
		color = mini_info->floor_color;
	return (color);
}
