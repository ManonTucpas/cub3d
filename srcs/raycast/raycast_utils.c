/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 10:51:44 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/04/20 18:47:20 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void		my_pixel_put(t_conf *conf, int x, int y, int color)
{
	char *dst;

	dst = conf->img.addr + (y * conf->img.line_lenght + x *
		(conf->img.bpp / 8));
	*(unsigned int*)dst = color;
}

int			ft_close(t_conf *conf)
{
	ft_free_all(conf);
	exit(0);
	return (1);
}

void		clean_image(t_conf *conf)
{
	mlx_destroy_image(conf->mlx.ptr, conf->img.img);
}

void		get_text_id(t_conf *conf)
{
	if (conf->r.side == 1 && conf->r.diry < 0)
		conf->r.texdir = 0;
	if (conf->r.side == 1 && conf->r.diry >= 0)
		conf->r.texdir = 1;
	if (conf->r.side == 0 && conf->r.dirx < 0)
		conf->r.texdir = 2;
	if (conf->r.side == 0 && conf->r.dirx >= 0)
		conf->r.texdir = 3;
}
