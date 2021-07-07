/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 19:15:21 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/04/21 10:30:32 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void		get_spr_collision(t_conf *conf, int mapx, int mapy)
{
	if (mapx < conf->width - 1 && mapy < conf->height - 1
		&& mapx > 0 && mapy > 0)
	{
		if (conf->map[mapy][mapx] == '2')
		{
			conf->map[mapy][mapx] = '0';
			play_sound('b');
			conf->nb_spr--;
		}
		if (conf->map[mapy][mapx] == '3')
		{
			conf->map[mapy][mapx] = '0';
			play_sound('w');
			conf->nb_spr--;
		}
		if (conf->map[mapy][mapx] == '4')
		{
			conf->map[mapy][mapx] = '0';
			play_sound('e');
			conf->nb_spr--;
			ft_close(conf);
		}
	}
}

static void		rt_p_next(t_conf *conf, double old_dirx, double old_planex)
{
	old_dirx = conf->p.x_dir;
	old_planex = conf->p.plan_x;
	conf->p.x_dir = conf->p.x_dir * cos(conf->p.r_speed)
		- conf->p.y_dir * sin(conf->p.r_speed);
	conf->p.y_dir = old_dirx * sin(conf->p.r_speed)
		+ conf->p.y_dir * cos(conf->p.r_speed);
	conf->p.plan_x = conf->p.plan_x * cos(conf->p.r_speed)
		- conf->p.plan_y * sin(conf->p.r_speed);
	conf->p.plan_y = old_planex * sin(conf->p.r_speed)
		+ conf->p.plan_y * cos(conf->p.r_speed);
}

static void		rotate_player(t_conf *conf)
{
	double old_dirx;
	double old_planex;

	if (conf->p.turn_dir == -1)
	{
		old_dirx = conf->p.x_dir;
		old_planex = conf->p.plan_x;
		conf->p.x_dir = conf->p.x_dir * cos(-conf->p.r_speed)
			- conf->p.y_dir * sin(-conf->p.r_speed);
		conf->p.y_dir = old_dirx * sin(-conf->p.r_speed)
			+ conf->p.y_dir * cos(-conf->p.r_speed);
		conf->p.plan_x = conf->p.plan_x * cos(-conf->p.r_speed)
			- conf->p.plan_y * sin(-conf->p.r_speed);
		conf->p.plan_y = old_planex * sin(-conf->p.r_speed)
			+ conf->p.plan_y * cos(-conf->p.r_speed);
	}
	if (conf->p.turn_dir == 1)
		rt_p_next(conf, old_dirx, old_planex);
}

static void		update_player(t_conf *conf, float step, char c)
{
	int tx;
	int ty;

	tx = (int)conf->p.x_pos;
	ty = (int)conf->p.y_pos;
	if (tx > conf->width - 1 || ty > conf->height - 1 || conf->map[ty][tx]
		== '2' || conf->map[ty][tx] == '3' || conf->map[ty][tx] == '4'
			|| conf->map[ty][tx] == '1' || tx < 0 || ty < 0)
	{
		if (c == 'x')
			conf->p.x_pos = conf->p.x_pos - cos(conf->p.r_angle) * step;
		else if (c == 'y')
			conf->p.y_pos = conf->p.y_pos - sin(conf->p.r_angle) * step;
		else if (c == 'r')
		{
			conf->p.x_pos = conf->p.x_pos + conf->p.y_dir * conf->p.speed;
			conf->p.y_pos = conf->p.y_pos - conf->p.x_dir * conf->p.speed;
		}
		else if (c == 'l')
		{
			conf->p.x_pos = conf->p.x_pos - conf->p.y_dir * conf->p.speed;
			conf->p.y_pos = conf->p.y_pos + conf->p.x_dir * conf->p.speed;
		}
		get_spr_collision(conf, tx, ty);
	}
}

void			movement(t_conf *conf)
{
	float step;

	step = conf->p.walk_dir * conf->p.speed;
	conf->p.r_angle += conf->p.turn_dir * conf->p.r_speed;
	conf->p.x_pos = conf->p.x_pos + cos(conf->p.r_angle) * step;
	update_player(conf, step, 'x');
	conf->p.y_pos = conf->p.y_pos + sin(conf->p.r_angle) * step;
	update_player(conf, step, 'y');
	if (conf->p.leftstep == 0 && conf->p.rightstep == 1)
	{
		conf->p.x_pos = conf->p.x_pos - conf->p.y_dir * conf->p.speed;
		conf->p.y_pos = conf->p.y_pos + conf->p.x_dir * conf->p.speed;
		update_player(conf, step, 'r');
	}
	else if (conf->p.leftstep == 1 && conf->p.rightstep == 0)
	{
		conf->p.x_pos = conf->p.x_pos + conf->p.y_dir * conf->p.speed;
		conf->p.y_pos = conf->p.y_pos - conf->p.x_dir * conf->p.speed;
		update_player(conf, step, 'l');
	}
	rotate_player(conf);
}
