/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key_action.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:11:11 by jiwolee           #+#    #+#             */
/*   Updated: 2023/01/26 20:41:00 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"
#include	"mlx.h"
#include	"util_action.h"
#include	<stdlib.h>

static void	get_key_w(t_cub3d_info *info);
static void	get_key_s(t_cub3d_info *info);
static void	get_key_a(t_cub3d_info *info);
static void	get_key_d(t_cub3d_info *info);

int	key_pressed(int key, t_cub3d_info *info)
{
	if (key == KEY_W)
		get_key_w(info);
	else if (key == KEY_A || key == KEY_LEFT)
		get_key_a(info);
	else if (key == KEY_S)
		get_key_s(info);
	else if (key == KEY_D || key == KEY_RIGHT)
		get_key_d(info);
	else if (key == MOUSE_ON_OFF)
		mouse_cursor_on_off(info);
	else if (key == KEY_ESC)
		exit(0);
	return (0);
}

static void	get_key_w(t_cub3d_info *info)
{
	move_player(info, MOVE_SPEED);
}

static void	get_key_s(t_cub3d_info *info)
{
	move_player(info, -MOVE_SPEED);
}

static void	get_key_a(t_cub3d_info *info)
{
	rotate_player(info, ROTATE_SPEED);
}

static void	get_key_d(t_cub3d_info *info)
{
	rotate_player(info, -ROTATE_SPEED);
}
