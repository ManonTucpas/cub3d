/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_get_map_inside.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 10:31:54 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/04/20 18:13:20 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void		update_dir_bis(t_conf *conf, unsigned int i, unsigned int j)
{
	if (conf->map[i][j] == 'S')
	{
		conf->p.r_angle = 0.5 * PI;
		conf->p.y_dir = 1;
		conf->p.plan_x = -0.66;
	}
	if (conf->map[i][j] == 'W')
	{
		conf->p.r_angle = PI;
		conf->p.x_dir = -1;
		conf->p.plan_y = -0.66;
	}
}

static void		ft_check_dir(t_conf *conf, unsigned int i, unsigned int j)
{
	if (conf->p.dir != 'x')
		ft_error(conf, "direction", NULL);
	conf->p.dir = conf->map[i][j];
	if (conf->map[i][j] == 'N')
	{
		conf->p.r_angle = 1.5 * PI;
		conf->p.y_dir = -1;
		conf->p.plan_x = 0.66;
	}
	if (conf->map[i][j] == 'E')
	{
		conf->p.r_angle = 0;
		conf->p.x_dir = 1;
		conf->p.plan_y = 0.66;
	}
	update_dir_bis(conf, i, j);
	conf->p.x_pos = j + 0.5;
	conf->p.y_pos = i + 0.5;
	conf->map[i][j] = '0';
}

static void		ft_check_zero_inside(t_conf *conf)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 1;
	while (conf->map[i] && i < conf->height)
	{
		j = 1;
		while (conf->map[i][j] && j < conf->width)
		{
			if (conf->map[i][j] == '0')
				k++;
			j++;
		}
		i++;
	}
	if (k == 0)
		ft_error(conf, "no zero", conf->map);
}

void			count_sprites(t_conf *conf, int i, int j)
{
	if (conf->map[i][j] == '2' || conf->map[i][j] == '3' ||
		conf->map[i][j] == '4')
	{
		ft_check_ar(conf, i, j);
		conf->nb_spr++;
	}
}

void			ft_check_inside(t_conf *conf)
{
	int i;
	int j;

	i = 1;
	ft_check_zero_inside(conf);
	while (conf->map[i] && i < conf->height)
	{
		j = 1;
		while (conf->map[i][j] && j < conf->width)
		{
			if (!is_valid_char(conf->map[i][j]))
				ft_error(conf, "invalid parameter", NULL);
			if (conf->map[i][j] == '0')
				ft_check_ar(conf, i, j);
			count_sprites(conf, i, j);
			if ((conf->map[i][j] == 'N' || conf->map[i][j] == 'W' ||
				conf->map[i][j] == 'S' || conf->map[i][j] == 'E'))
				ft_check_dir(conf, i, j);
			j++;
		}
		i++;
	}
	if (conf->p.dir == 'x')
		ft_error(conf, "direction", NULL);
}
