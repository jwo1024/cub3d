/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_init_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:14:17 by jaeyjeon          #+#    #+#             */
/*   Updated: 2023/01/11 17:30:53 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"util_init_map.h"
#include	"map_checker.h"
#include	"cub3d.h"
#include	"get_next_line.h"
#include	<fcntl.h>

t_cub3d_info	*init_map(t_cub3d_info *info, char *map_file_name)
{
	int	fd;

	if (info)
	{
		is_valid_mapfile_name(map_file_name);
		fd = safe_open(map_file_name);
		// check_map // info->map, info->te

		//  // info->map
		// is_valid_map;
	}
	return (info);
}

int	safe_open(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		; //error
	return (fd);
}

int	read_mapfile_info(int fd, t_cub3d_info *info)
{
	char	*line;
	int		save_info_cnt;

	save_info_cnt = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line && *line == '\n') // 함수화하기
			;
		else if (line)
		{
			if (check_line(line, info))
				save_info_cnt++;
		}
		else
			; // fail get file data
	}
	if (is_not_all_info(save_info_cnt))
		; // error..
	// 한줄씩 읽으면서
	// 내부함수에서 한줄 타입 검사 및 info 저장
}

int	read_mapfile_map(int fd)
{
	char	**map_addr;

	// 아 포인터 크기만 변경해주면 되어요 char **

	// gnl 에서 알아서 char *을 뱉으니까
	// 다 읽어와서 char **에 저장

}
