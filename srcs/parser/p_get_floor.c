/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_get_floor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 13:43:14 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/04/14 10:47:38 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int				color_no_valid(int color)
{
	if (color > 255 || color < 0)
		return (1);
	return (0);
}

static void		find_nb(t_conf *conf, char **str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[j])
	{
		i = 0;
		while (str[j][i])
		{
			if (!ft_isdigit(str[j][i]))
				ft_error(conf, "digit", str);
			i++;
		}
		j++;
	}
	conf->f_red = ft_atoi(str[0]);
	conf->f_green = ft_atoi(str[1]);
	conf->f_blue = ft_atoi(str[2]);
	if (color_no_valid(conf->f_blue) || color_no_valid(conf->f_red)
		|| color_no_valid(conf->f_green))
		ft_error(conf, "rgb", str);
}

static void		get_f_color(t_conf *conf)
{
	conf->f_color = ((conf->f_red & 0x0ff) << 16) |
		((conf->f_green & 0x0ff) << 8) | (conf->f_blue & 0x0ff);
}

void			get_floor(t_conf *conf, char *line)
{
	int		arg;
	char	**path;
	char	**nb;
	int		i;

	i = 0;
	arg = 0;
	path = ft_split(line, ' ');
	arg = args_nb(path);
	if (arg != 2)
		ft_error(conf, "nb arg", path);
	while (path[1][i])
	{
		if (path[1][i] == ',' && path[1][i + 1] == ',')
			ft_error(conf, "coma", path);
		i++;
	}
	nb = ft_split(path[1], ',');
	free_tab(path);
	arg = args_nb(nb);
	if (arg != 3)
		ft_error(conf, "nb arg", nb);
	find_nb(conf, nb);
	free_tab(nb);
	get_f_color(conf);
}
