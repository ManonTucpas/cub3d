/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 12:43:31 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/04/20 18:58:04 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void		get_distance(t_conf *c)
{
	c->r.mapx = (int)c->p.x_pos;
	c->r.mapy = (int)c->p.y_pos;
	c->r.camerax = 2 * c->r.i / (double)c->r1 - 1;
	c->r.dirx = c->p.x_dir + c->p.plan_x * c->r.camerax;
	c->r.diry = c->p.y_dir + c->p.plan_y * c->r.camerax;
	if (c->r.diry == 0)
		c->r.deltadistx = 0;
	else if (c->r.dirx == 0)
		c->r.deltadistx = 1;
	else
		c->r.deltadistx = sqrt(1 + (c->r.diry * c->r.diry) /
			(c->r.dirx * c->r.dirx));
	if (c->r.dirx == 0)
		c->r.deltadisty = 0;
	else if (c->r.diry == 0)
		c->r.deltadisty = 1;
	else
		c->r.deltadisty = sqrt(1 + (c->r.dirx * c->r.dirx)
			/ (c->r.diry * c->r.diry));
	c->r.perpwalldist = 0;
	c->r.hit = 0;
}

static void		get_step(t_conf *c)
{
	if (c->r.dirx < 0)
	{
		c->r.stepx = -1;
		c->r.sidedistx = (c->p.x_pos - c->r.mapx) * c->r.deltadistx;
	}
	else
	{
		c->r.stepx = 1;
		c->r.sidedistx = (c->r.mapx + 1.0 - c->p.x_pos) * c->r.deltadistx;
	}
	if (c->r.diry < 0)
	{
		c->r.stepy = -1;
		c->r.sidedisty = (c->p.y_pos - c->r.mapy) * c->r.deltadisty;
	}
	else
	{
		c->r.stepy = 1;
		c->r.sidedisty = (c->r.mapy + 1.0 - c->p.y_pos) * c->r.deltadisty;
	}
}

static void		perf_dda_perp(t_conf *conf)
{
	while (conf->r.hit == 0)
	{
		if (conf->r.sidedistx < conf->r.sidedisty)
		{
			conf->r.sidedistx += conf->r.deltadistx;
			conf->r.mapx += conf->r.stepx;
			conf->r.side = 0;
		}
		else
		{
			conf->r.sidedisty += conf->r.deltadisty;
			conf->r.mapy += conf->r.stepy;
			conf->r.side = 1;
		}
		if (conf->map[conf->r.mapy][conf->r.mapx] == '1')
			conf->r.hit = 1;
	}
	if (conf->r.side == 0)
		conf->r.perpwalldist = ((double)(conf->r.mapx) - conf->p.x_pos
			+ (1 - (double)conf->r.stepx) / 2) / conf->r.dirx;
	else
		conf->r.perpwalldist = ((double)(conf->r.mapy)
			- conf->p.y_pos + (1 - (double)conf->r.stepy) / 2) / conf->r.diry;
}

int				raycast(t_conf *conf)
{
	conf->r.i = 0;
	create_image(conf);
	movement(conf);
	draw_background(conf);
	while (conf->r.i < conf->r1)
	{
		get_distance(conf);
		get_step(conf);
		perf_dda_perp(conf);
		wall_height(conf);
		get_text_id(conf);
		draw_texture(conf);
		draw_column(conf);
		conf->buff[conf->r.i] = conf->r.perpwalldist;
		conf->r.i++;
	}
	draw_sprites(conf);
	print_map(conf);
	if (conf->save_image == 1)
		save_bmp(conf);
	mlx_put_image_to_window(conf->mlx.ptr,
		conf->img.mlx_win, conf->img.img, 0, 0);
	clean_image(conf);
	return (0);
}
