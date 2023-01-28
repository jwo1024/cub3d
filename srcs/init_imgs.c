/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_imgs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:32:32 by jiwolee           #+#    #+#             */
/*   Updated: 2023/01/28 16:04:38 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"
#include	"util_init.h"
#include	"mlx.h"
#include	"util_error.h"
#include	<stdio.h>

static void	init_textures_imgs(t_cub3d_info *info);
static void	get_xpm_data_from_file(void *mlx, t_img *img, char *file_name);
static void	new_background_img(void *mlx, t_img *img);

void	init_imgs(t_cub3d_info *info)
{
	init_textures_imgs(info);
	new_background_img(info->mlx, &info->textures.background);
}

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

static void	init_textures_imgs(t_cub3d_info *info)
{
	t_textures_img	*textures_img;
	t_textures_info	*textures_info;

	textures_img = &info->textures;
	textures_info = &info->textures_info;
	get_xpm_data_from_file(info->mlx, &info->textures.wall_ea, \
							info->textures_info.wall_ea_file_name); // width ? height ? init?
	get_xpm_data_from_file(info->mlx, &info->textures.wall_no, \
							info->textures_info.wall_no_file_name);
	get_xpm_data_from_file(info->mlx, &info->textures.wall_so, \
							info->textures_info.wall_so_file_name);
	get_xpm_data_from_file(info->mlx, &info->textures.wall_we, \
							info->textures_info.wall_we_file_name);
}

static void	get_xpm_data_from_file(void *mlx, t_img *img, char *file_name)
{
	if (!img || !mlx || img->img_ptr)
		;
	img->img_ptr = \
		mlx_xpm_file_to_image(mlx, file_name, &img->width, &img->height);
	if (img->img_ptr == NULL)
		exit_with_error("invalid file error"); // 잘못된 file name 혹은 불러오기 실패
	img->addr = mlx_get_data_addr \
		(img->img_ptr, &img->bits_per_pixel, &img->line_length, &img->endian);
}

static void	new_background_img(void *mlx, t_img *img)
{
	if (!img || !mlx || img->img_ptr)
		;
	img->img_ptr = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT); // 64?
	img->width = SCREEN_WIDTH;
	img->height = SCREEN_HEIGHT;
	if (img->img_ptr == NULL)
		exit_with_error("background img error ");; // img 만들기 실패
	img->addr = mlx_get_data_addr \
		(img->img_ptr, &img->bits_per_pixel, &img->line_length, &img->endian);
}
