// 헤더 넣어주세욥

#include	"cub3d.h"
#include	"mlx.h"
#include	"util_error.h"
#include	"stdlib.h"

void	init_mlx_win(t_cub3d_info *info)
{
	info->mlx = mlx_init();
	if (info->mlx == NULL)
		exit_with_error("mlx init fail");
	info->window = mlx_new_window(info->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	if (info->window == NULL)
		exit_with_error("window init fail");
}

void	destroy_window(t_cub3d_info *info)
{
	if (info->window)
		mlx_destroy_window(info->mlx, info->window);
}