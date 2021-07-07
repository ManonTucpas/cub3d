/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 18:03:14 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/04/20 18:19:31 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int			is_valid_char(char c)
{
	if (strchr(CHARVALID, c))
		return (1);
	return (0);
}

void		ft_check_ar(t_conf *conf, unsigned int i, unsigned int j)
{
	if (conf->map[i - 1][j] == '*')
		ft_error(conf, "zero error", conf->map);
	if (conf->map[i + 1][j] == '*')
		ft_error(conf, "zero error", conf->map);
	if (conf->map[i][j - 1] == '*')
		ft_error(conf, "zero error", conf->map);
	if (conf->map[i][j + 1] == '*')
		ft_error(conf, "zero error", conf->map);
}

void		check_p_dir(t_conf *conf, unsigned int i, unsigned int j)
{
	if (conf->p.dir != 'x')
		ft_error(conf, "direction", NULL);
	conf->p.dir = conf->map[i][j];
}
