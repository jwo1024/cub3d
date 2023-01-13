
#include	"cub3d.h"
#include	"mlx.h"
#include	"util_action.h"

void	key_pressed(int key, t_cub3d_info *info)
{
	if (key == KEY_W)
		get_key_w(info);
	else if (key == KEY_A)
		get_key_a(info);
	else if (key == KEY_S)
		get_key_s(info);
	else if (key == KEY_D)
		get_key_d(info);
	else if (key == KEY_ESC)
		exit(0);
	else
		return ;
	// ray_casting(); 버퍼에 그리고
		// 벽검사 dda
		// 충돌검사
		// 버퍼에 그리기
			// image texture 비율계산
	// draw_new_window();
//	mlx_clear_window(info->mlx, info->window);
//	mlx_put_image_to_window(info->mlx, info->window, info->textures.background, 0, 0); //window 출력

	//다시 그리기 추가
}

static void	get_key_w(t_cub3d_info *info)
{
	// position = 가는 정도 * 방향;
	// modify_player_position(double position);
		// rotation
}

static void	get_key_a(t_cub3d_info *info)
{
	mlx_clear_window(info->mlx, info->window);
}

static void	get_key_s(t_cub3d_info *info)
{
	mlx_clear_window(info->mlx, info->window);
}

static void	get_key_d(t_cub3d_info *info)
{
	mlx_clear_window(info->mlx, info->window);
}

