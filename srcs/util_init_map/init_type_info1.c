/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_type_info1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:15:15 by jaeyjeon          #+#    #+#             */
/*   Updated: 2023/01/13 16:39:49 by jiwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"
#include	"libft.h"
#include	"util_safe_libft.h"
#include	"util_init_map.h"
#include	"util_error.h"
#include	"util_color.h"
#include	<stdlib.h>

static int	is_str_digit(char *str);
static int	is_valid_type_color_info(char **nums);
static void if_valid_type_save_color(char *info_line, unsigned int *save_destination);

void	init_type_info_f(t_textures_info *textures_info, char *line)
{
	char	*info_line;

	if (textures_info->floor_color == 0)
	{
		info_line = get_info_line(line, 1);
		if_valid_type_save_color(info_line, &textures_info->floor_color);
		free(info_line);
	}
	else
		exit_with_error("identifier error");
}

void	init_type_info_c(t_textures_info *textures_info, char *line)
{
	char	*info_line;

	if (textures_info->ceiling_color == 0)
	{
		info_line = get_info_line(line, 1);
		if_valid_type_save_color(info_line, &textures_info->ceiling_color);
		free(info_line);
	}
	else
		exit_with_error("identifier error");
}

static int	is_str_digit(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (ft_isdigit(str[i]))
			i++;
		if (i == (int)ft_strlen(str))
			return (TRUE);
	}
	return (FALSE);
}

static int	is_valid_type_color_info(char **nums)
{
	if (nums && nums[0] && nums[1] && nums[2] && nums[3] == NULL \
		&& is_str_digit(nums[0]) && is_str_digit(nums[1]) && is_str_digit(nums[2]))
		return (TRUE);
	return (FALSE);
}

static void if_valid_type_save_color(char *info_line, unsigned int *save_destination)
{
	char **nums;
	int	r;
	int	g;
	int	b;

	nums = safe_ft_split(info_line, ',');
	if (is_valid_type_color_info(nums))
	{
		r = atoi(nums[0]);
		g = atoi(nums[1]);
		b = atoi(nums[2]);
		if (r <= 255 && g <= 255 && b <=255)
			*save_destination = make_color(0xFF, r, g, b);
		else
			; // error worng 범위
	}
	else
		; // error wrong clolor info
	free_ft_split(nums);
}
