/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 11:46:16 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/04/20 18:29:43 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int		keypress(int keysum, t_conf *conf)
{
	if (keysum == XK_Escape)
		ft_close(conf);
	else if (keysum == XK_Up || keysum == XK_w)
		conf->p.walk_dir = 1;
	else if (keysum == XK_Down || keysum == XK_s)
		conf->p.walk_dir = -1;
	else if (keysum == XK_Left)
		conf->p.turn_dir = -1;
	else if (keysum == XK_Right)
		conf->p.turn_dir = 1;
	else if (keysum == XK_a)
		conf->p.leftstep = 1;
	else if (keysum == XK_d)
		conf->p.rightstep = 1;
	else if (keysum == XK_Shift_L)
	{
		conf->p.speed *= 2;
		conf->p.r_speed *= 2;
		play_sound('s');
	}
	return (0);
}

static int		keyrelease(int keysum, t_conf *conf)
{
	if (keysum == XK_Escape)
		ft_close(conf);
	else if (keysum == XK_Up || keysum == XK_w)
		conf->p.walk_dir = 0;
	else if (keysum == XK_Down || keysum == XK_s)
		conf->p.walk_dir = 0;
	else if (keysum == XK_Left)
		conf->p.turn_dir = 0;
	else if (keysum == XK_Right)
		conf->p.turn_dir = 0;
	else if (keysum == XK_a)
		conf->p.leftstep = 0;
	else if (keysum == XK_d)
		conf->p.rightstep = 0;
	else if (keysum == XK_Shift_L)
	{
		conf->p.speed /= 2;
		conf->p.r_speed /= 2;
	}
	return (0);
}

void			key_actions(t_conf *conf)
{
	mlx_hook(conf->img.mlx_win, 2, 1L << 0, keypress, conf);
	mlx_hook(conf->img.mlx_win, 3, 1L << 1, keyrelease, conf);
	mlx_hook(conf->img.mlx_win, 33, 1L << 17, ft_close, conf);
	mlx_loop_hook(conf->mlx.ptr, raycast, conf);
	mlx_loop(conf->mlx.ptr);
}
