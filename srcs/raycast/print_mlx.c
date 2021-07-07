/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:59:23 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/04/20 18:45:06 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void			print_player(t_conf *c)
{
	int		radius;
	float	x;
	float	y;
	float	angle;
	int		i;

	x = c->p.x_pos * (TILE / SCALE);
	y = c->p.y_pos * (TILE / SCALE);
	radius = 4;
	angle = 0;
	i = 0;
	while (i <= radius)
	{
		my_pixel_put(c, x, y, 0x00000000);
		angle = 0;
		while (angle <= 6.28)
		{
			x = (c->p.x_pos * (TILE / SCALE)) + cos(angle) * i;
			y = (c->p.y_pos * (TILE / SCALE)) + sin(angle) * i;
			my_pixel_put(c, x, y, 0x00000000);
			angle += 0.1;
		}
		i++;
	}
}

static void		pr_squ(t_conf *conf, int x, int y, unsigned int color)
{
	float	x_init;
	float	ord;
	float	abs;
	float	x_pos;
	float	y_pos;

	x_pos = (float)x * (TILE / SCALE);
	y_pos = (float)y * (TILE / SCALE);
	ord = y_pos + (TILE / SCALE);
	abs = x_pos + (TILE / SCALE);
	while (y_pos < ord && y_pos < conf->r2)
	{
		x_init = x_pos;
		while (x_init < abs && x_init < conf->r1)
		{
			my_pixel_put(conf, x_init, y_pos, color);
			x_init++;
		}
		y_pos++;
	}
}

void			print_map(t_conf *conf)
{
	int x;
	int y;

	y = 0;
	while ((y < (int)conf->height) && y < (int)conf->r2)
	{
		x = 0;
		while (x < (int)conf->r1 && x < (int)conf->width)
		{
			if (conf->map[y][x] == '1')
				pr_squ(conf, x, y, 0x00FF8000);
			if (conf->map[y][x] == '0')
				pr_squ(conf, x, y, 0x00FF00FF);
			if (conf->map[y][x] == '2' || conf->map[y][x] == '3'
				|| conf->map[y][x] == '4')
				pr_squ(conf, x, y, 0x00867979);
			x++;
		}
		y++;
	}
	print_player(conf);
}
