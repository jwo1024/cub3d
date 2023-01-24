/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_action.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:36:51 by jaeyjeon          #+#    #+#             */
/*   Updated: 2023/01/24 17:41:16 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_ACTION_H
# define UTIL_ACTION_H

# include "cub3d.h"

# define KEY_W		13
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2
# define KEY_ESC	53

int		key_pressed(int key, t_cub3d_info *info);
void	move_player(t_cub3d_info *info, double speed);
void	rotate_player(t_cub3d_info *info, double speed);

#endif
