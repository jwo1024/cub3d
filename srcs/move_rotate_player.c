/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_rotate_player.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:12:59 by jiwolee           #+#    #+#             */
/*   Updated: 2023/01/24 18:20:39 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"
#include	"util_action.h"
#include	<math.h>

void	move_player(t_cub3d_info *info, double speed) // speed * -1 or 1
{
	// 충돌검사
	// 0 = 0 ~ 1 까지 이니까.
	double	new_x;
	double	new_y;

	new_x = info->player.dir_x * speed + info->player.pos_x;
	new_y = info->player.dir_y * speed + info->player.pos_y;
	if (info->map.data[(int)new_y][(int)new_x] != '1')//is_not_wall(int x, int y);
	{
		info->player.pos_x = new_x;
		info->player.pos_y = new_y;
	}
}

void	rotate_player(t_cub3d_info *info, double speed) // speed * -1 or 1
{
	// x = dirx * cos(-speed) - diry * sin(-speed)
	// y = dirx * sin(-speed) + diry * cos(-speed)
	t_player	*player;
	double		new_x;
	double		new_y;

	player = &(info->player);
	{
		new_x = player->dir_x * cos(speed) - player->dir_y * sin(speed);
		new_y = player->dir_x * sin(speed) + player->dir_y * cos(speed);
		player->dir_x = new_x;
		player->dir_y = new_y;
	}
	{
		new_x = player->plane_x * cos(speed) - player->plane_y * sin(speed);
		new_y = player->plane_x * sin(speed) + player->plane_y * cos(speed);
		player->plane_x = new_x;
		player->plane_y = new_y;
	}
}
