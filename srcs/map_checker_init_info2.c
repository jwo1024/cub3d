/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_init_info2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:15:15 by jaeyjeon          #+#    #+#             */
/*   Updated: 2023/01/11 18:29:56 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "util_safe_libft.h"
#include <stdlib.h>

void is_valid_type_color(info_line)
{
	// 띄워쓰기 없어야함
	// , 2개
	// 숫자 랑 ,만 들어옴
	// 숫자인지는 그냥 is_digit(); == TRUE 일때만
	// 각 숫자가 255를 넘으면 안됨
}

void	init_type_info_f(t_textures_file_name *textures_fname, char *line)
{
	char	*info_line;

	// 중복검사
	if (textures_fname->ground_color != NULL)
	{
		info_line = safe_ft_substr(line, 2, ft_strlen(line) - 3);
		// 유효성검사
		is_valid_type_color(info_line);
		// 저장
		textures_fname->ground_color = info_line;
	}
	else
		; // error
}

void	init_type_info_c(t_textures_file_name *textures_fname, char *line)
{
	char	*info_line;

	// 중복검사
	if (textures_fname->sky_color != NULL)
	{
		info_line = safe_ft_substr(line, 2, ft_strlen(line) - 3);
		// 유효성검사
		is_valid_type_color(info_line);
		// 저장
		textures_fname->sky_color = info_line;
	}
	else
		; // error
}
