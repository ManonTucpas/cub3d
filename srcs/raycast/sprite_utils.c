/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 11:22:21 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/04/20 19:03:58 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void		new_sprite(t_conf *conf, int i, int x, int y)
{
	conf->spr[i].startx = 0;
	conf->spr[i].starty = 0;
	conf->spr[i].endx = 0;
	conf->spr[i].endy = 0;
	conf->spr[i].screenx = 0;
	conf->spr[i].newy = 0;
	conf->spr[i].type = conf->map[y][x] - '0';
	conf->spr[i].x = x + 0.5;
	conf->spr[i].y = y + 0.5;
	conf->spr[i].dist = hypot(conf->spr[i].x - conf->p.x_pos,
		conf->spr[i].y - conf->p.y_pos);
	conf->spr[i].h = conf->t[conf->spr[i].type + 2].h;
	conf->spr[i].w = conf->t[conf->spr[i].type + 2].w;
	if (conf->t[conf->spr[i].type + 2].img == NULL)
		ft_error(conf, "sprite error", NULL);
}

void			malloc_t_sprite(t_conf *conf)
{
	if (conf->spr != NULL)
		free(conf->spr);
	conf->spr = malloc(sizeof(t_sprite) * conf->nb_spr);
	if (!conf->spr)
		ft_error(conf, "malloc error", NULL);
}

static void		update_dist(t_conf *conf)
{
	int i;

	i = 0;
	while (i < conf->nb_spr)
	{
		conf->spr[i].dist = hypot(conf->spr[i].x - conf->p.x_pos,
		conf->spr[i].y - conf->p.y_pos);
		i++;
	}
}

void			sort_sprites(t_conf *conf)
{
	int			i;
	int			nb;
	t_sprite	tmp;
	int			done;

	nb = conf->nb_spr;
	done = 0;
	update_dist(conf);
	while (done == 0)
	{
		done = 1;
		i = 0;
		while (i < nb - 1)
		{
			if (conf->spr[i].dist < conf->spr[i + 1].dist)
			{
				tmp = conf->spr[i];
				conf->spr[i] = conf->spr[i + 1];
				conf->spr[i + 1] = tmp;
				done = 0;
			}
			i++;
		}
		nb--;
	}
}

void			get_sprites(t_conf *conf)
{
	int x;
	int y;
	int i;

	y = 0;
	i = 0;
	malloc_t_sprite(conf);
	while (y < conf->height)
	{
		x = 0;
		while (x < conf->width)
		{
			if (strchr(SPRITE, conf->map[y][x]))
			{
				new_sprite(conf, i, x, y);
				i++;
			}
			x++;
		}
		y++;
	}
}
