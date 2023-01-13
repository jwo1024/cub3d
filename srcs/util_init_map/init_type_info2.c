/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_type_info2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:57:44 by jaeyjeon          #+#    #+#             */
/*   Updated: 2023/01/13 14:27:55 by jiwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"
#include	"libft.h"
#include	"util_safe_libft.h"
#include	"util_init_map.h"
#include	"util_error.h"
#include	<stdlib.h>

char	*get_info_line(char *line, int start_num); // h 파일로 옮기기

void	init_type_info_no(t_textures_info *textures_info, char *line)
{
	char	*info_line;

	if (textures_info->wall_no_file_name == NULL)
	{
		info_line = get_info_line(line, 2);
		// 유효성검사
		// is_valid_type_file_name(info_line);
		textures_info->wall_no_file_name = info_line;
	}
	else
		exit_with_error("identifier error NO");
}

void	init_type_info_so(t_textures_info *textures_info, char *line)
{
	char	*info_line;

	if (textures_info->wall_so_file_name == NULL)
	{
		info_line = get_info_line(line, 2);
		// 유효성검사
		// is_valid_type_file_name(info_line);
		textures_info->wall_so_file_name = info_line;
	}
	else
		exit_with_error("identifier error SO");
}

void	init_type_info_ea(t_textures_info *textures_info, char *line)
{
	char	*info_line;

	if (textures_info->wall_ea_file_name == NULL)
	{
		info_line = get_info_line(line, 2);
		// 유효성검사
		// is_valid_type_file_name(info_line);
		textures_info->wall_ea_file_name = info_line;
	}
	else
		exit_with_error("identifier error EA");
}

void	init_type_info_we(t_textures_info *textures_info, char *line)
{
	char	*info_line;

	if (textures_info->wall_we_file_name == NULL)
	{
		info_line = get_info_line(line, 2);
		// 유효성검사
		// is_valid_type_file_name(info_line);
		textures_info->wall_we_file_name = info_line;
	}
	else
		exit_with_error("identifier error WE");
}

char	*get_info_line(char *line, int start_num)
{
 	int		start;
	char	*info_line;

	start = start_num;
	if (line[start] && line[start] != ' ')
		exit_with_error("space not found at identifier");;//error
	while(line[start] && line[start] == ' ')
	{
		start++;
	}
	info_line = safe_ft_substr(line, start, ft_strlen(line) - start);
	return (info_line);
}
