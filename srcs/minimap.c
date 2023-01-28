/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:07:43 by jaeyjeon          #+#    #+#             */
/*   Updated: 2023/01/28 19:42:08 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"
#include	"util_img.h"
#include	"minimap.h"
#include	"mlx.h"
#include	"stdio.h" //NULL

static void			make_minimap_img(t_img *minimap_img, t_map *map, int block_size);
static unsigned int	get_wall_color(char wall_type);

void	draw_minimap(t_cub3d_info *info)
{
	int	mini_width;
	int	mini_height;
	int	background_x;
	int	background_y;


	char	*background_addr;
	char	*mini_addr;

	int		mini_x;
	int		mini_y;

	unsigned int	color;

	mini_width = SCREEN_WIDTH / 10;
	mini_height = SCREEN_HEIGHT / 10;
	background_y = 5;

	int	block_size = 10;

	mini_x = info->player.pos.x * block_size;
	mini_y = info->player.pos.y * block_size;
	mini_x = mini_x - mini_width / 2;
	mini_y = mini_y - mini_height / 2; // 범위가 아닐 경우에

	while (background_y < mini_height)
	{
		background_x = SCREEN_WIDTH - mini_width;
		mini_x = info->player.pos.x * block_size;
		mini_x = mini_x - mini_width / 2;

		while (background_x < info->textures.background.width - 5)
		{
			mini_addr = get_pixel_addr_img(&info->textures.minimap, mini_x, mini_y); // 이게 문제
			if (mini_addr == NULL)
				color = 0X00222222; // 수정
			else
				color = *(unsigned int *)mini_addr;
			background_addr = get_pixel_addr_img(&info->textures.background, background_x, background_y);
			*(unsigned int *)background_addr = color;
			background_x++;
			mini_x++;
		}
		background_y++;
		mini_y++;
	}

	// info->textures.background 에 그리기

	int	x;
	int	y;

	background_x = SCREEN_WIDTH - mini_width / 2;// + SCREEN_WIDTH - mini_width;
	background_y = mini_height / 2;

	color = 0x00CC0000;
	x = 0;
	y = 0;
	while (y < 3)
	{
		x = 0;
		while (x < 3)
		{
			background_addr = get_pixel_addr_img(&info->textures.background, background_x + x, background_y + y);
			*(unsigned int *)background_addr = color;
			x++;
		}
		y++;
	}

}


/*
	minimap->width = SCREEN_WIDTH / 10;
	minimap->hieght = SCREEN_HEIGHT / 10;
*/


int	init_minimap_img(t_cub3d_info *info, t_map *map)
{
	t_img	*minimap_img;
	int		block_size;

	block_size = 10;
	minimap_img = &info->textures.minimap;
// 여기부터 void *make_new_img(t_cub3d_info *info, t_img *img, int width, int heights);
	// minimap_img = calloc(); 혹은 cub3d_info->minimap_img;
	// 미니맵 이미지 만들기
	minimap_img->width = map->width * block_size; // 5px? if int범위 벗어났을때 예외
	minimap_img->height = map->height * block_size;
	minimap_img->img_ptr = mlx_new_image(info->mlx, minimap_img->width, minimap_img->height);

	minimap_img->addr = mlx_get_data_addr \
						(minimap_img->img_ptr, &minimap_img->bits_per_pixel, \
						&minimap_img->line_length, &minimap_img->endian);
// 여기까지는 new_background_img 랑 겹치기 때문에 새 함수 파서 사용하는 것이 좋을듯
	make_minimap_img(minimap_img, map, block_size);
	return (0);
}

static void	make_minimap_img(t_img *minimap_img, t_map *map, int block_size)
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
			color = get_wall_color(map->data[img_y / block_size][img_x / block_size]);
			addr = get_pixel_addr_img(minimap_img, img_x, img_y);
			*(unsigned int *)addr = color;
		//	draw_color(minimap_img, color);
			img_x++;
		}
		img_y++;
	}
}

static unsigned int	get_wall_color(char wall_type)
{
	unsigned int	color;

	if (wall_type == '1')
		color = 0X00003333;
	else if (wall_type == ' ')
		color = 0X00CCFFFF;
	else
		color = 0X00669999;
	return (color);
}


// int	draw_minimap_player(t_img minimap_img)
// {
// 	// pov 그리기
// }




/*
	map_y = 0;
	map_x = 0;
	while (map_y < map->height)
	{
		while (map_x < map->width)
		{
			draw_block();
			map_x++;
		}
		map_y++;
	}
	*/

/*
int	draw_block(t_img minimap_img, int map_x, int map_y, int block_size, unsigned int color)
{
	unsigned int	img_x;
	unsigned int	img_y;

	while (img_y < map_y + block_size)
	{
		while (img_x < map_y + block_size);
		{
			;
			img_x++;
		}
		img_y++;
	}

	get_pixel_addr_img();



}*/


/*
	minimap->width = SCREEN_WIDTH / 10;
	minimap->hieght = SCREEN_HEIGHT / 10;
*/
