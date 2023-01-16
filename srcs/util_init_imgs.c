/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_init_imgs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:32:32 by jiwolee           #+#    #+#             */
/*   Updated: 2023/01/16 15:09:41 by jiwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"
#include	"util_init.h"
#include	"mlx.h"
#include	<stdio.h>

static void	init_textures_imgs(t_cub3d_info *info);
static void	get_xpm_data_from_file(void *mlx, t_img *img, char *file_name);
static void	new_background_img(void *mlx, t_img *img);

void	init_imgs(t_cub3d_info *info)
{
	init_textures_imgs(info);
	new_background_img(info->mlx, &info->textures.background);
}

static void	init_textures_imgs(t_cub3d_info *info)
{
	t_textures_img	*textures_img;
	t_textures_info	*textures_info;

	textures_img = &info->textures;
	textures_info = &info->textures_info;
	get_xpm_data_from_file(info->mlx, &info->textures.wall_ea, \
							info->textures_info.wall_ea_file_name);
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
		; // 잘못된 file name 혹은 불러오기 실패
	img->addr = mlx_get_data_addr \
		(img->img_ptr, &img->bits_per_pixel, &img->line_length, &img->endian);
}

static void	new_background_img(void *mlx, t_img *img)
{
	if (!img || !mlx || img->img_ptr)
		;
	img->img_ptr = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT); // 64?
	if (img->img_ptr == NULL)
		; // img 만들기 실패
	img->addr = mlx_get_data_addr \
		(img->img_ptr, &img->bits_per_pixel, &img->line_length, &img->endian);
}
