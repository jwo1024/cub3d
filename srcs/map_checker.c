/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:44:21 by jaeyjeon          #+#    #+#             */
/*   Updated: 2023/01/11 17:36:10 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<stdlib.h>
#include	"libft.h"
#include	"cub3d.h"

// 맵이 유효한 파일인지 확인
// 맵 파일의 확장자가 .cub인지 확인
int	is_valid_mapfile_name(char *mapname)
{
	char	*addr;

	if (mapname)
	{
		addr = ft_strchr(mapname, '.');
		if (addr && ft_strncmp(addr, ".cub\0", 5) == 0)
			return (TRUE);
	}
	return (FALSE);
}

static int	is_type_identifier_no(char *strm)
{
	return 0;
}

int	check_line(char *line, t_cub3d_info *info)
{
	t_textures_file_name *textures_fname;

	textures_fname = &info->textures_file_name;
	if (textures_fname->wall_north == NULL && is_type_identifier(line, "NO"))
		init_type_info_no(textures_fname);
	else if (textures_fname->wall_east == NULL && is_type_identifier(line, "EA"))
		init_type_info_ea(textures_fname);
	else if (textures_fname->wall_west == NULL && is_type_identifier(line, "WE"))
		init_type_info_we(textures_fname);
	else if (textures_fname->wall_south == NULL && is_type_identifier(line, "SO"))
		init_type_info_so(textures_fname);
	else if (textures_fname->sky_color == NULL && is_type_identifier(line, "C"))
		init_type_info_c(textures_fname);
	else if (textures_fname->ground_color == NULL && is_type_identifier(line, "F"))
		init_type_info_f(textures_fname);
	else
		; // 잘못된 id가 들어왔을때, 중복이 들어왔을때 error exit
	return (1);
}

int	map_texture()
{
}



// NO, SO, WE, EA, F, C로 시작하는 type identifier가 다 들어있는지, 양식대로 들어와있는지 확인
// (Map을 제외하고 비어있는 줄이 들어있을 수 있음)

// Map은 파일의 마지막에 들어와있어야 함
// Map에 들어와 있는 문자중 공백, 0, 1, N, S, W, E 외에 다른 문자가 들어와있진 않은지 확인
// Map이 벽으로 잘 둘러 쌓여진 완성된 Map인지 확인

// 확인중 잘못된 부분을 찾았을 때 Error\n과 함께 적절한 에러메시지를 출력하고 Exit 해주어야 함
