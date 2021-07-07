/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_get_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 12:32:50 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/04/20 18:16:42 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void		ft_check_border_right(t_conf *conf)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	while (conf->map[i])
	{
		j = 0;
		while (conf->map[i][j])
			j++;
		j--;
		while (conf->map[i][j] && conf->map[i][j] == '*')
			j--;
		if (conf->map[i][j] != '1')
			ft_error(conf, "wall", conf->map);
		i++;
	}
}

static void		ft_check_border_left(t_conf *conf)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	while (conf->map[i])
	{
		j = 0;
		while (conf->map[i][j] && conf->map[i][j] == '*')
			j++;
		if (conf->map[i][j] != '1')
			ft_error(conf, "wall", conf->map);
		i++;
	}
}

static char		*ft_complete_line(t_conf *conf, unsigned int i)
{
	unsigned int	k;
	unsigned int	len_tmp;
	char			*tmp;
	char			*new;

	tmp = NULL;
	new = NULL;
	len_tmp = 0;
	k = 0;
	len_tmp = conf->width - ft_strlen(conf->map[i]);
	tmp = (char *)malloc(sizeof(char) * len_tmp + 1);
	while (k < len_tmp)
	{
		tmp[k] = '*';
		k++;
	}
	tmp[k] = '\0';
	new = ft_strjoin(conf->map[i], tmp);
	free(tmp);
	free(conf->map[i]);
	return (new);
}

static void		ft_fill_spaces(t_conf *conf)
{
	int i;
	int j;

	i = 0;
	while (conf->map[i] && i < conf->height)
	{
		j = 0;
		while (conf->map[i][j] && j < conf->width)
		{
			if (conf->map[i][j] == ' ')
				conf->map[i][j] = '*';
			j++;
		}
		if ((int)ft_strlen(conf->map[i]) < conf->width)
			conf->map[i] = ft_complete_line(conf, i);
		i++;
	}
}

void			ft_get_tab(t_conf *conf, char *mapline)
{
	int i;
	int j;

	i = 0;
	conf->map = ft_split(mapline, '-');
	free(mapline);
	while (conf->map[i])
	{
		j = 0;
		while (conf->map[i][j])
			j++;
		if (j > conf->width)
			conf->width = j;
		i++;
	}
	conf->height = i;
	if (is_first_line(conf->map[conf->height - 1]) != 1)
		ft_error(conf, "wall", NULL);
	ft_fill_spaces(conf);
	ft_check_border_right(conf);
	ft_check_border_left(conf);
	ft_check_inside(conf);
}
