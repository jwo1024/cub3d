
#ifndef RAY_CAST_H
# define RAY_CAST_H

typedef struct s_ray_info
{
	int		ray_x;
	int		ray_y;
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	double	first_dist_x;
	double	first_dist_y;
	double	second_dist_x;
	double	second_dist_y;
}	t_ray_info;

#endif;


/*
typedef struct s_player{
	double	pos_x;
	double	pos_y;
	double	plane_x;
	double	plane_y;
	double	dir_x; //방향백터
	double	dir_y;
}	t_player;
이거 쓰면은 되는 것이.. 아닌가욥?

ray의 방향이나 플레이어의 방향이나 같지 않나요??
아하
알겟습니당


ray의 방향벡터랑 ray좌표도 저기다 넣을까요??
저건 플레이어의 방향벡터 아닌가욥
반복문으로 계속 돌려야해서 따로 쓰는게 좋을것같다고 생각했습니답
*/