/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 10:14:07 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/04/21 09:42:53 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void			create_window(t_conf *conf)
{
	conf->img.mlx_win = mlx_new_window(
		conf->mlx.ptr, conf->r1, conf->r2, "KIOUBETRIDI");
	if (!conf->img.mlx_win)
		ft_error(conf, "new window", NULL);
}

void				create_image(t_conf *conf)
{
	conf->img.img = mlx_new_image(conf->mlx.ptr, conf->r1, conf->r2);
	if (!conf->img.img)
		ft_error(conf, "image failed", NULL);
	conf->img.addr = mlx_get_data_addr(conf->img.img, &conf->img.bpp,
		&conf->img.line_lenght, &conf->img.endian);
	if (!conf->img.addr)
		ft_error(conf, "img.add failed", NULL);
}

static void			get_texture_address(t_conf *conf)
{
	conf->t[0].addr = mlx_get_data_addr(conf->t[0].img,
		&conf->img.bpp, &conf->img.line_lenght, &conf->img.endian);
	conf->t[1].addr = mlx_get_data_addr(conf->t[1].img,
		&conf->img.bpp, &conf->img.line_lenght, &conf->img.endian);
	conf->t[2].addr = mlx_get_data_addr(conf->t[2].img,
		&conf->img.bpp, &conf->img.line_lenght, &conf->img.endian);
	conf->t[3].addr = mlx_get_data_addr(conf->t[3].img,
		&conf->img.bpp, &conf->img.line_lenght, &conf->img.endian);
	conf->t[4].addr = mlx_get_data_addr(conf->t[4].img,
		&conf->img.bpp, &conf->img.line_lenght, &conf->img.endian);
	if (conf->ss)
		conf->t[5].addr = mlx_get_data_addr(conf->t[5].img,
			&conf->img.bpp, &conf->img.line_lenght, &conf->img.endian);
	if (conf->sss)
		conf->t[6].addr = mlx_get_data_addr(conf->t[6].img,
			&conf->img.bpp, &conf->img.line_lenght, &conf->img.endian);
}

static void			get_texture(t_conf *conf)
{
	conf->t[0].img = mlx_xpm_file_to_image(conf->mlx.ptr,
		conf->no, &(conf->t[0].w), &(conf->t[0].h));
	if (conf->t[0].img == NULL)
		ft_error(conf, "bad text", NULL);
	conf->t[1].img = mlx_xpm_file_to_image(conf->mlx.ptr,
		conf->so, &(conf->t[1].w), &(conf->t[1].h));
	if (conf->t[1].img == NULL)
		ft_error(conf, "bad text", NULL);
	conf->t[2].img = mlx_xpm_file_to_image(conf->mlx.ptr,
		conf->we, &(conf->t[2].w), &(conf->t[2].h));
	if (conf->t[2].img == NULL)
		ft_error(conf, "bad text", NULL);
	conf->t[3].img = mlx_xpm_file_to_image(conf->mlx.ptr,
		conf->ea, &(conf->t[3].w), &(conf->t[3].h));
	if (conf->t[3].img == NULL)
		ft_error(conf, "bad text", NULL);
	conf->t[4].img = mlx_xpm_file_to_image(conf->mlx.ptr,
		conf->s, &(conf->t[4].w), &(conf->t[4].h));
	if (conf->t[4].img == NULL)
		ft_error(conf, "bad text", NULL);
	get_text_bonus(conf);
	get_texture_address(conf);
}

void				launch_game(t_conf *conf)
{
	conf->mlx.ptr = mlx_init();
	if (conf->mlx.ptr == 0)
		ft_error(conf, "failed mlx_init", NULL);
	get_res_max(conf);
	if (conf->save_image == 0)
		create_window(conf);
	get_texture(conf);
	ini_buff(conf);
	raycast(conf);
	key_actions(conf);
}
