/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_checkmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:20:46 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/04/16 15:28:43 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int				is_first_line(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '1')
			return (0);
		i++;
	}
	if (ft_strchr(str, '1'))
		return (1);
	return (0);
}

static void		check_all(t_conf *conf)
{
	if (conf->r1 == 0 || conf->r2 == 0 || conf->no == NULL ||
		conf->so == NULL || conf->we == NULL || conf->ea == NULL ||
			conf->s == NULL || conf->f_red == -1 || conf->f_green == -1 ||
				conf->f_blue == -1 || conf->c_red == -1 ||
					conf->c_green == -1 || conf->c_blue == -1)
		ft_error(conf, "missing", NULL);
}

static char		*get_line(t_conf *conf, int fd)
{
	int		ret;

	conf->line = NULL;
	while ((ret = get_next_line(fd, &conf->line) > 0)
		&& (is_first_line(conf->line) != 1))
	{
		get_config_path(conf, conf->line);
		get_config_rgb(conf, conf->line);
		free(conf->line);
	}
	check_all(conf);
	if (is_first_line(conf->line) != 1)
	{
		free(conf->line);
		ft_error(conf, "wall", NULL);
	}
	if (is_first_line(conf->line) == 1)
		return (conf->line);
	return (NULL);
}

static char		*ft_add_char(char *line)
{
	char *tmp;

	tmp = ft_strjoin(line, "-");
	free(line);
	return (tmp);
}

void			parse_map(t_conf *conf, int fd)
{
	char	*tmpline;
	char	*mapline;
	int		ret;

	conf->in_config = 1;
	conf->line = get_line(conf, fd);
	conf->line = reass_join(conf->line, "-", &ft_strjoin);
	mapline = ft_strdup(conf->line);
	free(conf->line);
	ret = 1;
	conf->in_config = 0;
	while (ret > 0)
	{
		ret = get_next_line(fd, &conf->line);
		tmpline = ft_add_char(conf->line);
		mapline = reass_join(mapline, tmpline, &ft_strjoin);
		free(tmpline);
	}
	ft_get_tab(conf, mapline);
}
