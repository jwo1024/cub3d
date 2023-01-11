/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_init_info1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:57:44 by jaeyjeon          #+#    #+#             */
/*   Updated: 2023/01/11 18:22:02 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "util_safe_libft.h"
#include <stdlib.h>

void	init_type_info_no(t_textures_file_name *textures_fname, char *line)
{
	char	*info_line;

	// 중복검사
	if (textures_fname->wall_north != NULL)
	{
		info_line = safe_ft_substr(line, 3, ft_strlen(line) - 3);
		// 유효성검사
		// is_valid_type_file_name(info_line);
		// 저장
		textures_fname->wall_north = info_line;
	}
	else
		;// error
}

void	init_type_info_so(t_textures_file_name *textures_fname, char *line)
{
	char	*info_line;

	// 중복검사
	if (textures_fname->wall_south != NULL)
	{
		info_line = safe_ft_substr(line, 3, ft_strlen(line) - 3);
		// 유효성검사
		// is_valid_type_file_name(info_line);
		// 저장
		textures_fname->wall_south = info_line;
	}
	else
		; // error
}

void	init_type_info_ea(t_textures_file_name *textures_fname, char *line)
{
	char	*info_line;

	// 중복검사
	if (textures_fname->wall_east != NULL)
	{
		info_line = safe_ft_substr(line, 3, ft_strlen(line) - 3);
		// 유효성검사
		// is_valid_type_file_name(info_line);
		// 저장
		textures_fname->wall_east = info_line;
	}
	else
		; // error
}

void	init_type_info_we(t_textures_file_name *textures_fname, char *line)
{
	char	*info_line;

	// 중복검사
	if (textures_fname->wall_west != NULL)
	{
		info_line = safe_ft_substr(line, 3, ft_strlen(line) - 3);
		// 유효성검사
		// is_valid_type_file_name(info_line);
		// 저장
		textures_fname->wall_west = info_line;
	}
	else
		; // error
}
