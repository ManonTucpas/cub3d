/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_get_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 15:02:53 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/04/20 18:18:52 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void			get_res_max(t_conf *conf)
{
	int maxx;
	int maxy;

	mlx_get_screen_size(conf->mlx.ptr, &maxx, &maxy);
	if ((int)conf->r1 >= maxx)
		conf->r1 = maxx;
	if ((int)conf->r2 >= maxy)
		conf->r2 = maxy;
}

static void		find_resolution_nb(t_conf *conf, char **str)
{
	int i;

	i = 0;
	while (str[1][i])
	{
		if (!ft_isdigit(str[1][i]))
			ft_error(conf, "invalid parameter", str);
		i++;
	}
	conf->r1 = ft_atoi(str[1]);
	i = 0;
	while (str[2][i])
	{
		if (!ft_isdigit(str[2][i]))
			ft_error(conf, "invalid parameter", str);
		i++;
	}
	conf->r2 = ft_atoi(str[2]);
	if (conf->r2 <= 0 || conf->r1 <= 0)
		ft_error(conf, "resolution max", NULL);
}

void			get_resolution(t_conf *conf, char *line)
{
	char	**res;
	int		i;
	int		j;

	j = 0;
	i = 0;
	res = ft_split(line, ' ');
	while (res[i])
	{
		j = 0;
		while (res[i][j])
			j++;
		i++;
	}
	if ((i != 3) || (ft_strcmp(res[0], "R") != 0))
		ft_error(conf, "invalid parameter", res);
	find_resolution_nb(conf, res);
	free_tab(res);
}
