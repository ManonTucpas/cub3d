/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 08:39:15 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/04/16 14:41:42 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void		free_path(t_conf *conf)
{
	if (conf->no)
		free(conf->no);
	if (conf->so)
		free(conf->so);
	if (conf->we)
		free(conf->we);
	if (conf->ea)
		free(conf->ea);
	if (conf->s)
		free(conf->s);
	if (conf->ss)
		free(conf->ss);
	if (conf->sss)
		free(conf->sss);
	if (conf->map)
		free_tab(conf->map);
	if (conf->buff)
		free(conf->buff);
	if (conf->spr)
		free(conf->spr);
}

void			ft_free_all(t_conf *conf)
{
	int i;

	i = 0;
	if (conf->in_config && conf->line)
	{
		free(conf->line);
		conf->line = NULL;
	}
	free_path(conf);
	while (i < MAXTEXTURES)
	{
		if (conf->t[i].img)
			mlx_destroy_image(conf->mlx.ptr, conf->t[i].img);
		i++;
	}
	if (conf->img.mlx_win)
		mlx_destroy_window(conf->mlx.ptr, conf->img.mlx_win);
	if (conf->mlx.ptr)
	{
		mlx_destroy_display(conf->mlx.ptr);
		free(conf->mlx.ptr);
	}
}

static void		ft_error_mlx(char *str)
{
	if (ft_strcmp(str, "bad text") == 0)
		printf("Error\nNot a valid xpm file\n");
	if (ft_strcmp(str, "image failed") == 0)
		printf("Error\nFailed to create an image\n");
	if (ft_strcmp(str, "img.add failed") == 0)
		printf("Error\nFailed to create an image's address\n");
	if (ft_strcmp(str, "new window") == 0)
		printf("Error\nFailed to create a new window\n");
	if (ft_strcmp(str, "failed mlx_init") == 0)
		printf("Error\nFailed to initiliaze mlx_ptr\n");
	if (ft_strcmp(str, "malloc error") == 0)
		printf("Error\nMalloc error\n");
	if (ft_strcmp(str, "sprite error") == 0)
		printf("Error\nSprite error\n");
	if (ft_strcmp(str, "bmp") == 0)
		printf("Error\nCan't open BMP file\n");
}

static void		ft_error_bis(char *str)
{
	if (ft_strcmp(str, "resolution max") == 0)
		printf("Error\nInvalid resolution parameter\n");
	if (ft_strcmp(str, "twice") == 0)
		printf("Error\nTwo times the same path, remove one to continue\n");
	if (ft_strcmp(str, "rgb") == 0)
		printf("Error\nRGB must be between 0 and 255\n");
	if (ft_strcmp(str, "missing") == 0)
		printf("Error\nParameter is missing in the .cub\n");
	if (ft_strcmp(str, "coma") == 0)
		printf("Error\nToo many comas fot the floor/ceilling color\n");
	if (ft_strcmp(str, "wall") == 0)
		printf("Error\nBad configuration for one of the wall edge\n");
	if (ft_strcmp(str, "nb arg") == 0)
		printf("Error\nWrong number of arguments for RGB\n");
	if (ft_strcmp(str, "digit") == 0)
		printf("Error\nRGB's arguments must be digits between 0 & 255\n");
	if (ft_strcmp(str, "zero error") == 0)
		printf("Error\nCheck your map: 0, 2 not protected\n");
	if (ft_strcmp(str, "direction") == 0)
		printf("Error\nThe direction must be only once in the map\n");
	if (ft_strcmp(str, "no zero") == 0)
		printf("Error\nNo zero in the map\n");
}

void			ft_error(t_conf *conf, char *str, char **tab)
{
	if (tab)
		free_tab(tab);
	if (ft_strcmp(str, "Open failed") == 0)
		printf("Error\nOpen failed, the file doesn't exist\n");
	if (ft_strcmp(str, "valid file") == 0)
		printf("Error\nNot a valid file, the file must be a '.cub'\n");
	if (ft_strcmp(str, "third arg invalid") == 0)
		printf("Error\nThird argument is invalid, try '--save\n");
	if (ft_strcmp(str, "error") == 0)
		printf("Error\nPlease enter two or three arguments\n");
	if (ft_strcmp(str, "invalid parameter") == 0)
		printf("Error\nInvalid parameter(s), check the .cub\n");
	if (ft_strcmp(str, "invalid parameter letter") == 0)
		printf("Error\nInvalid letter's parameter(s), check the .cub\n");
	if (ft_strcmp(str, "no line") == 0)
		printf("Error\nNo line in the .cub\n");
	if (ft_strcmp(str, "invalid xpm") == 0)
		printf("Error\nInvalid file .xpm\n");
	if (ft_strcmp(str, "can't open xpm") == 0)
		printf("Error\nCan't read the .xpm file\n");
	ft_error_bis(str);
	ft_error_mlx(str);
	ft_free_all(conf);
	exit(1);
}
