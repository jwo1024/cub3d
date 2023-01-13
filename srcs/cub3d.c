/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:58:05 by jiwolee           #+#    #+#             */
/*   Updated: 2023/01/13 18:34:22 by jiwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"
#include	"util_img.h"
#include	<../mlx/mlx.h>
#include	"libft.h"
#include	"util_init_map.h"
#include	"cub3d.h"
#include	"util_init.h"
#include	<stdio.h>
#include	<stdlib.h>

void	func(void)
{
	system("leaks cub3D");
}

void	memset_info(t_cub3d_info *info);

int	main(int argc, char *argv[])
{
	t_cub3d_info	info;

	memset_info(&info);
	if (argc == 2)
	{
		init_map(&info, argv[1]); // molugetta
		check_valid_map(&info); //
		init_mlx_win(&info);
		init_imgs(&info);

		mlx_put_image_to_window(info.mlx, info.window, info.textures.wall_ea.img_ptr, 0, 0);
		mlx_put_image_to_window(info.mlx, info.window, info.textures.wall_we.img_ptr, 100, 0);
		mlx_put_image_to_window(info.mlx, info.window, info.textures.wall_so.img_ptr, 0, 100);
		mlx_put_image_to_window(info.mlx, info.window, info.textures.wall_no.img_ptr, 100, 100);

	}
	printf("1> %d  %d  %X  %X\n", info.map.height, info.map.width, info.textures_info.floor_color, info.textures_info.ceiling_color);
	printf("2> %s \n %s \n %s \n %s\n", info.textures_info.wall_ea_file_name, info.textures_info.wall_no_file_name, info.textures_info.wall_so_file_name, info.textures_info.wall_we_file_name);
	printf("3> map\n");
	for (unsigned int i = 0; i < info.map.height ; i++)
		printf("%s@\n", info.map.data[i]);

	printf("4> %f %f \n%f %f \n%f %f\n", info.player.dir_x, info.player.dir_y, \
		info.player.plane_x, info.player.plane_y, info.player.pos_x, info.player.pos_y);
//	system("leaks cub3D");
	mlx_loop(info.mlx);
	return (0);
}


void	memset_info(t_cub3d_info *info)
{
	ft_bzero(info, sizeof(t_cub3d_info));
}
