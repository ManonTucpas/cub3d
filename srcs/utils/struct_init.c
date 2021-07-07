/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:20:53 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/04/21 10:05:04 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void			ini_buff(t_conf *conf)
{
	if (conf->buff)
		free(conf->buff);
	conf->buff = malloc(sizeof(double) * conf->r1);
	if (conf->buff == NULL)
		ft_error(conf, "malloc error", NULL);
	ft_bzero(conf->buff, sizeof(double) * conf->r1);
	get_sprites(conf);
}

static void		ini_texture(t_conf *conf)
{
	int i;

	i = 0;
	while (i < MAXTEXTURES)
	{
		conf->t[i].addr = NULL;
		conf->t[i].img = NULL;
		conf->t[i].h = 0;
		conf->t[i].w = 0;
		i++;
	}
	conf->img.mlx_win = NULL;
}

void			ini_player(t_player *p)
{
	p->dir = 'x';
	p->turn_dir = 0;
	p->walk_dir = 0;
	p->leftstep = 0;
	p->rightstep = 0;
	p->speed = 0.1;
	p->plan_x = 0;
	p->plan_y = 0;
	p->x_dir = 0;
	p->y_dir = 0;
	p->r_speed = 0.05;
}

static void		ini_next(t_conf *conf)
{
	conf->no = NULL;
	conf->so = NULL;
	conf->we = NULL;
	conf->ea = NULL;
	conf->s = NULL;
	conf->ss = NULL;
	conf->sss = NULL;
	conf->map = NULL;
	conf->spr = NULL;
	conf->buff = NULL;
	conf->mlx.ptr = NULL;
	conf->img.img = NULL;
}

void			ini_conf(t_conf *conf)
{
	conf->error = 0;
	conf->save_image = 0;
	conf->r1 = 0;
	conf->r2 = 0;
	conf->f_red = -1;
	conf->f_green = -1;
	conf->f_blue = -1;
	conf->c_red = -1;
	conf->c_green = -1;
	conf->c_blue = -1;
	conf->f_color = 0;
	conf->c_color = 0;
	conf->param_ok = 0;
	conf->height = 0;
	conf->width = 0;
	ini_next(conf);
	ini_texture(conf);
	ini_player(&conf->p);
}
