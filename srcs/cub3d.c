/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:58:05 by jiwolee           #+#    #+#             */
/*   Updated: 2023/01/11 15:48:19 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"
#include	"util_img.h"
#include	<../mlx/mlx.h>
#include	"libft.h"
#include	"map_checker.h"
#include	<stdio.h>
#include	<stdlib.h>

void	func(void)
{
	system("leaks cub3D");
}

int	main(int argc, char *argv[])
{
	void	*mlx_ptr;
	void	*window;
	t_img	*img;

	if (argc && argv)
	{
		mlx_ptr = mlx_init();
		window = mlx_new_window(mlx_ptr, 640, 480, "hello");
		img = load_img("./asset/sword_ground.xpm", mlx_ptr);
		mlx_put_image_to_window(mlx_ptr, window, img->img_ptr, 100, 100);

		char *color_addr;

		for (int i = 0; i < img->height; i++)
		{
			for (int j = 0; j < img->width; j++)
			{
				color_addr = get_pixel_addr_img(img, j, i);
				mlx_pixel_put(mlx_ptr, window, j, i, *(unsigned int *)(color_addr));
			}
		}

		mlx_loop(mlx_ptr);
	}

	return (0);
}
