/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:52:13 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/04/21 12:18:08 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void			draw_textures_sprite(t_sprite *spr, int x, int y, t_conf *conf)
{
	int	color;
	int	tx;
	int	ty;
	int	offsety;

	tx = (int)(256 * (x - (-spr->size / 2 + spr->screenx)) *
				(spr->w - 1) / spr->size) / 256;
	while (y < spr->endy)
	{
		offsety = y * 256 - conf->r2 * 128 + spr->size * 128;
		ty = ((offsety * spr->h) / spr->size) / 256;
		if ((ty * spr->w) + tx < (int)sizeof(conf->t[spr->type + 2].addr))
			return ;
		color = conf->t[spr->type + 2].addr[(ty * spr->w * 4) + tx * 4];
		if (color != -16777216 && color != 0x000000)
			conf->img.addr[(y * conf->r1 * 4) + x * 4] = color;
		color = conf->t[spr->type + 2].addr[(ty * spr->w * 4) + tx * 4 + 1];
		if (color != -16777216 && color != 0x000000)
			conf->img.addr[(y * conf->r1 * 4) + x * 4 + 1] = color;
		color = conf->t[spr->type + 2].addr[(ty * spr->w * 4) + tx * 4 + 2];
		if (color != -16777216 && color != 0x000000)
			conf->img.addr[(y * conf->r1 * 4) + x * 4 + 2] = color;
		y++;
	}
}

static void		draw_one_sprite(t_sprite *spr, float newy, t_conf *conf)
{
	int x;
	int y;

	x = spr->startx;
	while (x <= spr->endx)
	{
		if (newy > 0 && x > 0 && x < conf->r1 && newy < conf->buff[x])
		{
			y = spr->starty;
			draw_textures_sprite(spr, x, y, conf);
		}
		x++;
	}
}

void			get_coord_draw(t_sprite *spr, t_conf *conf)
{
	int		tmpw;
	int		tmph;

	tmpw = spr->size;
	spr->startx = -tmpw / 2 + spr->screenx;
	if (spr->startx < 0)
		spr->startx = 0;
	spr->endx = tmpw / 2 + spr->screenx;
	if (spr->endx >= (int)conf->r1)
		spr->endx = conf->r1;
	tmph = spr->size;
	spr->starty = -tmph / 2 + conf->r2 / 2;
	if (spr->starty < 0)
		spr->starty = 0;
	spr->endy = tmph / 2 + conf->r2 / 2;
	if (spr->endy >= (int)conf->r2)
		spr->endy = conf->r2;
}

static void		get_newy(t_conf *conf, int i)
{
	float	delt_x;
	float	delt_y;
	float	inv_det;
	float	newx;
	float	newy;

	delt_x = conf->spr[i].x - conf->p.x_pos;
	delt_y = conf->spr[i].y - conf->p.y_pos;
	inv_det = 1.0 / ((conf->p.plan_x * conf->p.y_dir) -
		(conf->p.x_dir * conf->p.plan_y));
	newx = inv_det * (conf->p.y_dir * delt_x - conf->p.x_dir * delt_y);
	newy = inv_det * (-conf->p.plan_y * delt_x + conf->p.plan_x * delt_y);
	conf->spr[i].screenx = (int)((conf->r1 / 2) * (1 + newx / newy));
	conf->spr[i].newy = newy;
}

void			draw_sprites(t_conf *conf)
{
	int		i;
	float	coef;

	coef = 0;
	i = 0;
	sort_sprites(conf);
	while (i < conf->nb_spr)
	{
		get_newy(conf, i);
		if (conf->spr[i].type == 3 || conf->spr[i].type == 4)
			coef = 0.2;
		else
			coef = 0.5;
		conf->spr[i].size = coef * abs((int)(conf->r2 / (conf->spr[i].newy)));
		get_coord_draw(&conf->spr[i], conf);
		draw_one_sprite(&conf->spr[i], conf->spr[i].newy, conf);
		i++;
	}
}
