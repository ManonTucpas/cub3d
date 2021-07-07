/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_get_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 14:39:33 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/04/14 10:47:33 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void		find_nb(t_conf *conf, char **str)
{
	int			i;
	int			j;

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
	conf->c_red = ft_atoi(str[0]);
	conf->c_green = ft_atoi(str[1]);
	conf->c_blue = ft_atoi(str[2]);
	if (color_no_valid(conf->c_blue) || color_no_valid(conf->c_red) ||
		color_no_valid(conf->c_green))
		ft_error(conf, "rgb", str);
}

static void		get_c_color(t_conf *conf)
{
	conf->c_color = ((conf->c_red & 0x0ff) << 16) |
		((conf->c_green & 0x0ff) << 8) | (conf->c_blue & 0x0ff);
}

void			get_ceiling(t_conf *conf, char *line)
{
	int			arg;
	char		**path;
	char		**nb;
	int			i;

	i = 0;
	arg = 0;
	path = ft_split(line, ' ');
	arg = args_nb(path);
	if (arg != 2)
		ft_error(conf, "nb arg", path);
	while (path && path[1] && path[1][i])
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
	get_c_color(conf);
}
