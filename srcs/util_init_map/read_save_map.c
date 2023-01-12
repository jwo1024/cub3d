/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_save_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:00:21 by jaeyjeon          #+#    #+#             */
/*   Updated: 2023/01/12 22:07:17 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"util_init_map.h"
#include	"cub3d.h"
#include	"util_safe_libft.h"
#include	"get_next_line.h"
#include	"libft.h"

void	read_save_map(int fd, t_map *map)
{
	char			*line;
	unsigned int	x;
	unsigned int	y;

	malloc_t_map(map);
	line = skip_empty_line(fd);
	y = 0;
	while (line && y < map->height)
	{
		free(line);
		line = get_next_line(fd);
	//	y = ;
		map->data[y] = ft_memcpy();
		y++;
	}
	(void);
	// info 넘어가고
	// 읽고
	// 저장하고


}

static t_map	*malloc_t_map(t_map *map)
{
	int	idx;

	if (map && map->data == NULL)
	{
		map->data = (char *)malloc(sizeof(char) * map->height);
		if (map->data == NULL)
			; // fata error
		idx = 0;
		while (idx < map->height)
		{
			map->data[idx] = (char)malloc(sizeof(char) * map->width + 1);
			if (map->data[idx] == NULL)
				; // fatal error
			idx++;
		}
	}
	return (map);
}

static char	*skip_mapfile_info_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && is_info_line(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

static int	is_info_line(char *line)
{
	if (is_type_identifier(line, "NO") || is_type_identifier(line, "EA") \
		|| is_type_identifier(line, "WE") || is_type_identifier(line, "SO") \
		|| is_type_identifier(line, "C") || is_type_identifier(line, "F") \
		|| is_empty_line(line))
		return (TRUE);
	return (FALSE);
}
