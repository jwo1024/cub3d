/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_rotate_player.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:12:59 by jiwolee           #+#    #+#             */
/*   Updated: 2023/01/27 22:00:00 by jiwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"
#include	"util_action.h"
#include	<math.h>


#include	"stdio.h"
t_vector	rotate_vector(t_vector vector, double rot_speed)
{
	double		new_x;
	double		new_y;

	new_x = vector.x * cos(rot_speed) - vector.y * sin(rot_speed);
	new_y = vector.x * sin(rot_speed) + vector.y * cos(rot_speed);
	vector.x = new_x;
	vector.y = new_y;
//	printf("new_x %f new_y %f x %f y %f\n", new_x, new_y, vector.x, vector.y);
	return (vector);
}

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

void	move_player_side(t_cub3d_info *info, double speed) // speed * -1 or 1 // 왼오
{
	double	new_x;
	double	new_y;
	t_vector	side_dir;
	double radian = 3.141592f / 2.0f; // 각도를 radian으로 구하는 함수가 하나 있으면 좋겟다

	printf("pos x %f pos y %f\n", info->player.pos_x, info->player.pos_y);

	side_dir.x = info->player.dir_x;
	side_dir.y = info->player.dir_y;
	side_dir = rotate_vector(side_dir, radian);

	new_x = side_dir.x * speed + info->player.pos_x;
	new_y = side_dir.y * speed + info->player.pos_y;
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
