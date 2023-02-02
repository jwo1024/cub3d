/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:00:42 by jaeyjeon          #+#    #+#             */
/*   Updated: 2023/02/02 20:31:06 by jiwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "cub3d.h"
# include "ray_cast.h"

int		init_minimap_img(t_cub3d_info *info, t_map *map);
void	draw_minimap(t_cub3d_info *info);
void	draw_minimap_fov(t_cub3d_info *info, t_ray_info *ray_info, int block);

#endif
