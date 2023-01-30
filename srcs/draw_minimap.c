/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:00:16 by jaeyjeon          #+#    #+#             */
/*   Updated: 2023/01/30 19:35:09 by jiwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"
#include	"util_img.h"
#include	"minimap.h"
#include	"mlx.h"
#include	"stdio.h" //NULL

static void	init_minimap_data(t_cub3d_info *info, t_vector *background, \
									t_vector *mini_pos, t_vector *mini_size);
static void	draw_minimap_map(t_cub3d_info *info, t_vector *background, \
									t_vector *mini_pos, t_vector *mini_size);
static void	draw_minimap_player(t_cub3d_info *info, t_vector *background, \
													t_vector *mini_player_pos);

void	draw_minimap(t_cub3d_info *info)
{
	t_vector	background;
	t_vector	mini_pos;
	t_vector	mini_size;

	init_minimap_data(info, &background, &mini_pos, &mini_size);
	draw_minimap_map(info, &background, &mini_pos, &mini_size);
	draw_minimap_player(info, &background, &mini_size);
}

static void	init_minimap_data(t_cub3d_info *info, t_vector *background, \
									t_vector *mini_pos, t_vector *mini_size)
{
	int			border;
	int			block_size;

	block_size = info->minimap_info.block_size;
	border = 25;
	background->x = SCREEN_WIDTH - SCREEN_WIDTH / 10 - border;
	background->y = border;
	mini_size->x = SCREEN_WIDTH / 10;
	mini_size->y = SCREEN_HEIGHT / 10;
	mini_pos->x = (info->player.pos.x * block_size) - mini_size->x / 2;
	mini_pos->y = (info->player.pos.y * block_size) - mini_size->y / 2;
}

static void	draw_minimap_map(t_cub3d_info *info, t_vector *background, \
									t_vector *mini_pos, t_vector *mini_size)
{
	char	*bg_addr;
	char	*mini_addr;
	char	*minimap_addr;
	int		x;
	int		y;

	y = 0;
	while (y < mini_size->y)
	{
		x = 0;
		while (x < mini_size->x)
		{
			bg_addr = get_pixel_addr_img(&info->textures.background, \
										background->x + x, background->y + y);
			minimap_addr = get_pixel_addr_img(&info->textures.minimap, x, y); //
			mini_addr = get_pixel_addr_img(&info->textures.full_minimap, \
									mini_pos->x + x, mini_pos->y + y);
			if (bg_addr && mini_addr == NULL)
			{
				*(unsigned int *)minimap_addr = info->minimap_info.empty_color;
				*(unsigned int *)bg_addr = info->minimap_info.empty_color;
			}
			else if (bg_addr)
			{
				*(unsigned int *)minimap_addr = *(unsigned int *)mini_addr;
				*(unsigned int *)bg_addr = *(unsigned int *)mini_addr;
			}
			++x;
		}
		++y;
	}
}

static void	draw_minimap_player(t_cub3d_info *info, t_vector *background, \
														t_vector *mini_size)
{
	int				x;
	int				y;
	unsigned int	color;
	char			*background_addr;
	char			*minimap_addr;

	color = info->minimap_info.player_color;
	y = 0;
	while (y < 3)
	{
		x = 0;
		while (x < 3)
		{
			minimap_addr = get_pixel_addr_img(&info->textures.minimap, mini_size->x / 2 + x, mini_size->y / 2 + y);
			background_addr = get_pixel_addr_img(&info->textures.background, \
										background->x + mini_size->x / 2 + x, \
										background->y + mini_size->y / 2 + y);
			*(unsigned int *)background_addr = color;
			*(unsigned int *)minimap_addr = color;
			x++;
		}
		y++;
	}
}
