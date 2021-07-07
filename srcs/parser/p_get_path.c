/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_get_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 10:46:34 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/04/20 18:17:18 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void		check_xpm(t_conf *conf, char **tab_path)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_substr(tab_path[1], ft_strlen(tab_path[1]) - 4, 4);
	if (ft_strcmp(tmp, ".xpm") != 0)
	{
		free(tmp);
		ft_error(conf, "invalid xpm", tab_path);
	}
	free(tmp);
}

void			get_path(t_conf *conf, char *line)
{
	char	**path;
	int		arg;

	path = ft_split(line, ' ');
	arg = args_nb(path);
	if (arg != 2)
		ft_error(conf, "invalid parameter", path);
	check_xpm(conf, path);
	if (ft_strcmp(path[0], "NO") == 0)
		conf->no = ft_strdup(path[1]);
	else if (ft_strcmp(path[0], "SO") == 0)
		conf->so = ft_strdup(path[1]);
	else if (ft_strcmp(path[0], "EA") == 0)
		conf->ea = ft_strdup(path[1]);
	else if (ft_strcmp(path[0], "WE") == 0)
		conf->we = ft_strdup(path[1]);
	else if (ft_strcmp(path[0], "S") == 0)
		conf->s = ft_strdup(path[1]);
	else if (ft_strcmp(path[0], "S1") == 0)
		conf->ss = ft_strdup(path[1]);
	else if (ft_strcmp(path[0], "S2") == 0)
		conf->sss = ft_strdup(path[1]);
	free_tab(path);
}
