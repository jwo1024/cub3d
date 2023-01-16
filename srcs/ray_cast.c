
#include	"cub3d.h"
#include	"ray_cast.h"
#include	"math.h"

static void	init_ray_info(t_cub3d_info *info, t_ray_info *ray_info, int x);

void ray_cast(t_cub3d_info *info)
{
	int			x;
	t_ray_info	ray_info;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		init_ray_info(info, &ray_info, x);
		if (ray_info.raydir_x < 0) // 왼쪽으로 가다가 만나는 x
			ray_info.first_dist_x = (info->player.pos_x - ray_info.ray_x) * ray_info.second_dist_x;
		else // 오른쪽으로 가다가 만나는 x
			ray_info.first_dist_x = (ray_info.ray_x + 1.0 - info->player.pos_x) * ray_info.second_dist_x;
		if (ray_info.raydir_y < 0) // 아래로 가다가 만나는 y
			ray_info.first_dist_y = (info->player.pos_y - ray_info.ray_y) * ray_info.second_dist_y;
		else // 위로 가다가 만나는 y
			ray_info.first_dist_y = (ray_info.ray_y + 1.0 - info->player.pos_y) * ray_info.second_dist_y;
		whlie (info->map.data[ray_info.ray_y][ray_info.ray_x] != '1')
		{
			//ray를 한칸씩 움직여줌
		}
	}
}

static void	init_ray_info(t_cub3d_info *info, t_ray_info *ray_info, int x)
{
	ray_info->camera_x = 2 * x / SCREEN_WIDTH - 1;
	ray_info->raydir_x = info->player.dir_x + info->player.plane_x * ray_info->camera_x;
	ray_info->raydir_y = info->player.dir_y + info->player.plane_y * ray_info->camera_x;
	//반복할 때 마다 x가 1씩 증가하며 스크린의 모든x값을 확인
	//DDA
	ray_info->ray_x = (int)info->player.pos_x;
	ray_info->ray_y = (int)info->player.pos_y;
	ray_info->second_dist_x = fabs(1 / ray_info->raydir_x);
	ray_info->second_dist_y = fabs(1 / ray_info->raydir_y);
	// x,y 선분은 1단위로 딱 떨어지니 절대값으로 계산
}