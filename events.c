#include "wolf.h"
#include "minilibx/mlx.h"

int             ft_close(int keycode, t_mlx_ptr *s)
{
	if (keycode == 65307)
    	mlx_destroy_window(s->mlx, s->win);
	return(0);
}

int	ft_key_hit(int keycode, t_info *info)
{
	if (keycode == KEY_UP)
		info->move.up = 1;
	if (keycode == KEY_DOWN)
		info->move.down = 1;
	if (keycode == KEY_LEFT)
		info->move.left = 1;
	if (keycode == KEY_RIGHT)
		info->move.right = 1;
	if (keycode == ROTATE_RIGHT)
		info->move.camr = 1;
	if (keycode == ROTATE_LEFT)
		info->move.caml = 1;
	return (1);
}

int	ft_key_release(int keycode, t_info *info)
{
	if (keycode == KEY_UP)
		info->move.up = 0;
	if (keycode == KEY_DOWN)
		info->move.down = 0;
	if (keycode == KEY_LEFT)
		info->move.left = 0;
	if (keycode == KEY_RIGHT)
		info->move.right = 0;
	if (keycode == ROTATE_RIGHT)
		info->move.camr = 0;
	if (keycode == ROTATE_LEFT)
		info->move.caml = 0;
	return (1);
}

// void	ft_move(t_info *info)
// {
// 	int pos;

// 	if (env->move.up == 1 || env->move.down == 1)
// 		up_down(env);
// 	if (env->move.strafr == 1 || env->move.strafl == 1)
// 		straf(env);
// 	if (env->move.left == 1)
// 		ft_rotate(env, -1);
// 	if (env->move.right == 1)
// 		ft_rotate(env, 1);
// 	pos = env->map[(int)(env->player_y)][(int)(env->player_x)];
// 	if (pos == 'B')
// 		ft_bonus(env);
// 	if (pos == 'A')
// 		ft_reload_ammo(env);
// 	if (pos == 'O')
// 		ft_ennemy(env);
// 	if (pos == 'T')
// 		env->treasure_caught = 1;
// 	if (pos == 'T')
// 		env->sprite_count--;
// 	if (ft_strchr("BAT", pos))
// 		env->map[(int)(env->player_y)][(int)(env->player_x)] = '0';
// 	if (pos == 'T')
// 		ft_next_level(env);
// }

int	ft_key_press(int keycode, t_info *info, t_sprites *barrel)
{
	printf("keycode = %d\n", keycode);
	// if (info->move.up == 1 || info->move.down == 1)
	// {
	// 	if (keycode == KEY_UP || keycode == KEY_DOWN)
	// 		ft_moove(keycode, info);
	// }
	// if (info->move.left == 1 || info->move.right == 1)
	// {
	// 	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
	// 		ft_angle(keycode, info);
	// }
	if (keycode == 65307)
		exit(0);
    	// mlx_destroy_window(s->mlx, s->win);
	// rendering(info);
	// // // printf("a.x = %f\n", info->a.x);
	// // // printf("a.y = %f\n", info->a.y);
	// // // printf("angle = %f\n", info->angle);
	return 1;
}

int             ft_moove(int keycode, t_info *info)
{
	if (info->move.up == 1)
	{
		if (keycode == KEY_UP) //fleche avant
    	{
    		motion(info, FORWARD);
		}
	}
	if (info->move.down == 1)
	{
		if (keycode == KEY_DOWN) //fleche arriere
		{
			motion(info, BACKWARD);
		}
	}
	return(0);
}

int             ft_angle(int keycode, t_info *info)
{
    int i;
    // 360 deg done in 2 seconds while button is pressed = 0,0055555555 sec per deg
	if (info->move.right == 1)
	{
		if (keycode == KEY_RIGHT)
		{
			(info->angle) += 4; // motion(info, RIGHT); doit encore etre implémenté si nécessaire
		}
	}
	if (info->move.left == 1)
	{
		if (keycode == KEY_LEFT)
		{
			(info->angle) -= 4; // motion(info, LEFT);
			if (info->angle < 0)
				info->angle = 360 + info->angle;
		}
	}
	if (info->angle >= 360)
		info->angle -= 360;
	// // // printf("keycode2 = %d\n", keycode);
	// // // printf("info.angle = %f\n", info->angle);
	return(0);
}
