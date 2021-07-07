/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 12:29:51 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/04/20 18:25:46 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	wall_height(t_conf *conf)
{
	conf->r.line_height = (int)(conf->r2 / conf->r.perpwalldist);
	conf->r.drawstart = -conf->r.line_height / 2 + conf->r2 / 2;
	if (conf->r.drawstart < 0)
		conf->r.drawstart = 0;
	conf->r.drawend = conf->r.line_height / 2 + conf->r2 / 2;
	if (conf->r.drawend > (int)conf->r2 || conf->r.drawend < 0)
		conf->r.drawend = conf->r2;
}

void	draw_texture(t_conf *conf)
{
	conf->r.tex_nb = conf->map[conf->r.mapy][conf->r.mapx] - 1;
	if (conf->r.side == 0)
		conf->r.wallx = conf->p.y_pos + conf->r.perpwalldist * conf->r.diry;
	else
		conf->r.wallx = conf->p.x_pos + conf->r.perpwalldist * conf->r.dirx;
	conf->r.wallx -= floor((conf->r.wallx));
	conf->r.texx = (int)(conf->r.wallx * conf->t[conf->r.texdir].w)
		% conf->t[conf->r.texdir].w;
	if ((conf->r.side == 0 && conf->r.dirx > 0)
		|| (conf->r.side == 1 && conf->r.diry < 0))
		conf->r.texx = conf->t[conf->r.texdir].w - conf->r.texx - 1;
	conf->r.step = 1.0 * conf->t[conf->r.texdir].h / conf->r.line_height;
	conf->r.texpos = (conf->r.drawstart - conf->r2 /
		2 + conf->r.line_height / 2) * conf->r.step;
	draw_column(conf);
}

void	draw_background(t_conf *conf)
{
	int x;
	int y;

	y = 0;
	while (y < (int)conf->r2)
	{
		x = 0;
		while (x < (int)conf->r1)
		{
			if (y < (int)conf->r2 / 2)
				my_pixel_put(conf, x, y, conf->c_color);
			else
				my_pixel_put(conf, x, y, conf->f_color);
			x++;
		}
		y++;
	}
}

void	draw_column(t_conf *conf)
{
	int y;
	int c;

	y = conf->r.drawstart;
	while (y < conf->r.drawend)
	{
		conf->r.texy = y + (conf->r.line_height / 2) - (conf->r2 / 2);
		conf->r.texy = conf->r.texy *
			((double)conf->t[conf->r.texdir].h / conf->r.line_height);
		c = conf->t[conf->r.texdir].addr[(conf->r.texy
			* conf->t[conf->r.texdir].w * 4) + conf->r.texx * 4];
		conf->img.addr[(y * conf->r1 * 4) + conf->r.i * 4] = c;
		c = conf->t[conf->r.texdir].addr[(conf->r.texy
			* conf->t[conf->r.texdir].w * 4) + conf->r.texx * 4 + 1];
		conf->img.addr[(y * conf->r1 * 4) + conf->r.i * 4 + 1] = c;
		c = conf->t[conf->r.texdir].addr[(conf->r.texy
			* conf->t[conf->r.texdir].w * 4) + conf->r.texx * 4 + 2];
		conf->img.addr[(y * conf->r1 * 4) + conf->r.i * 4 + 2] = c;
		c = conf->t[conf->r.texdir].addr[(conf->r.texy
			* conf->t[conf->r.texdir].w * 4) + conf->r.texx * 4 + 3];
		conf->img.addr[(y * conf->r1 * 4) + conf->r.i * 4 + 3] = c;
		y++;
	}
}
