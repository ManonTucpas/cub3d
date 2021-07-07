/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 12:06:58 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/04/21 09:36:46 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void		fill_header(int fd, t_conf *conf)
{
	int tmp;
	int i;

	i = -1;
	write(fd, "BM", 2);
	tmp = 14 + 40 + 4 * conf->r1 * conf->r2;
	write(fd, &tmp, 4);
	tmp = 0;
	write(fd, &tmp, 2);
	write(fd, &tmp, 2);
	tmp = 54;
	write(fd, &tmp, 4);
	tmp = 40;
	write(fd, &tmp, 4);
	write(fd, &conf->r1, 4);
	write(fd, &conf->r2, 4);
	tmp = 1;
	write(fd, &tmp, 2);
	write(fd, &conf->img.bpp, 2);
	tmp = 0;
	while (++i < 6)
		write(fd, &tmp, 4);
}

static void		fill_pixel(int fd, t_conf *c)
{
	int x;
	int y;
	int r;
	int g;
	int b;

	y = c->r2;
	while (--y >= 0)
	{
		x = 0;
		while (x < c->r1)
		{
			r = c->img.addr[y * c->img.line_lenght + x *
			c->img.bpp / 8];
			g = c->img.addr[y * c->img.line_lenght + x *
			c->img.bpp / 8 + 1];
			b = c->img.addr[y * c->img.line_lenght + x *
			c->img.bpp / 8 + 2];
			write(fd, &r, 1);
			write(fd, &g, 1);
			write(fd, &b, 1);
			write(fd, "\0", 1);
			x++;
		}
	}
}

void			save_bmp(t_conf *conf)
{
	int	fd;

	fd = open("image_saved.bmp", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR
		| S_IWUSR);
	if (fd > 0)
	{
		fill_header(fd, conf);
		fill_pixel(fd, conf);
	}
	else
		ft_error(conf, "bmp", NULL);
	printf("Image saved\n");
	ft_close(conf);
}
