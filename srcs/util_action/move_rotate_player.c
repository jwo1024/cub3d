/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_rotate_player.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:12:59 by jiwolee           #+#    #+#             */
/*   Updated: 2023/01/28 18:39:01 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"
#include	"util_action.h"
#include	<math.h>
#include	"stdio.h"

t_vector	rotate_vector(t_vector vector, double rot_speed) // vector
{
	double		new_x;
	double		new_y;

	new_x = vector.x * cos(rot_speed) - vector.y * sin(rot_speed);
	new_y = vector.x * sin(rot_speed) + vector.y * cos(rot_speed);
	vector.x = new_x;
	vector.y = new_y;
	return (vector);
}

void	move_player(t_cub3d_info *info, double speed) // speed * -1 or 1
{
	double	new_x;
	double	new_y;

	new_x = info->player.dir.x * speed * 2 + info->player.pos.x;
	new_y = info->player.dir.y * speed * 2 + info->player.pos.y;
	if (info->map.data[(int)new_y][(int)new_x] != '1')
	{
		info->player.pos.x = info->player.dir.x * speed + info->player.pos.x;
		info->player.pos.y = info->player.dir.y * speed + info->player.pos.y;
	}
}

void	move_player_side(t_cub3d_info *info, double speed) // speed * -1 or 1 // 왼오
{
	double		new_x;
	double		new_y;
	t_vector	side_dir;
	double		radian;

	radian = 3.141592f / 2.0f; // 각도를 radian으로 구하는 함수가 하나 있으면 좋겟다
	side_dir.x = info->player.dir.x;
	side_dir.y = info->player.dir.y;
	side_dir = rotate_vector(side_dir, radian);
	new_x = side_dir.x * speed * 2 + info->player.pos.x;
	new_y = side_dir.y * speed * 2 + info->player.pos.y;
	if (info->map.data[(int)new_y][(int)new_x] != '1')//is_not_wall(int x, int y);
	{
		info->player.pos.x = side_dir.x * speed + info->player.pos.x;
		info->player.pos.y = side_dir.y * speed + info->player.pos.y;
	}
	printf("pos x %f pos y %f\n", info->player.pos.x, info->player.pos.y);
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
		new_x = player->dir.x * cos(speed) - player->dir.y * sin(speed);
		new_y = player->dir.x * sin(speed) + player->dir.y * cos(speed);
		player->dir.x = new_x;
		player->dir.y = new_y;
	}
	{
		new_x = player->plane.x * cos(speed) - player->plane.y * sin(speed);
		new_y = player->plane.x * sin(speed) + player->plane.y * cos(speed);
		player->plane.x = new_x;
		player->plane.y = new_y;
	}
}
