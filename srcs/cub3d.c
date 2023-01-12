/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:58:05 by jiwolee           #+#    #+#             */
/*   Updated: 2023/01/12 22:26:00 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"
#include	"util_img.h"
#include	<../mlx/mlx.h>
#include	"libft.h"
#include	"util_init_map.h"
#include	"cub3d.h"
#include	<stdio.h>
#include	<stdlib.h>

void	func(void)
{
	system("leaks cub3D");
}

int	main(int argc, char *argv[])
{
	t_cub3d_info	info;

	if (argc == 2)
		init_map(&info, argv[1]);
	printf("%d  %d  %X  %X\n", info.map.height, info.map.width, info.textures_info.ground_color, info.textures_info.sky_color);
	printf("%s \n %s \n %s \n %s\n", info.textures_info.wall_ea_file_name, info.textures_info.wall_no_file_name, info.textures_info.wall_so_file_name, info.textures_info.wall_we_file_name);
	system("leaks cub3D");
	return (0);
}
