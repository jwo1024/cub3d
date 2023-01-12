/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_img.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:04:01 by jiwolee           #+#    #+#             */
/*   Updated: 2023/01/12 21:32:03 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_IMG_H
# define UTIL_IMG_H

typedef struct s_img{
	void	*img_ptr;
	int		width;
	int		height;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

t_img	*load_img(char *file_name, void *mlx_ptr);
t_img	*delete_img(t_img *img, void *mlx_ptr);
char	*get_pixel_addr_img(t_img *img, int x, int y);

#endif
