/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_check_param.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 09:16:51 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/04/14 15:48:30 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	ft_check_get_path(t_conf *conf, char *str, char *arg)
{
	if (arg == NULL)
		get_path(conf, str);
	else
		ft_error(conf, "twice", NULL);
}

void		get_config_rgb(t_conf *conf, char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		str++;
	if (!ft_strchr("RNSWEFC", str[i]))
		ft_error(conf, "invalid parameter letter", NULL);
	if (str[i] == 'C' && str[i + 1] == ' ')
	{
		if (conf->c_red == -1 && conf->c_green == -1 && conf->c_blue == -1)
			get_ceiling(conf, str);
		else
			ft_error(conf, "twice", NULL);
	}
	if (str[i] == 'F' && str[i + 1] == ' ')
	{
		if (conf->f_red == -1 && conf->f_green == -1 && conf->f_blue == -1)
			get_floor(conf, str);
		else
			ft_error(conf, "twice", NULL);
	}
}

static void	get_bonus_path(char *str, int i, t_conf *conf)
{
	if (str[i] == 'S' && str[i + 1] == '1')
		ft_check_get_path(conf, str, conf->ss);
	if (str[i] == 'S' && str[i + 1] == '2')
		ft_check_get_path(conf, str, conf->sss);
}

void		get_config_path(t_conf *conf, char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		str++;
	if (!ft_strchr("RNSWEFC1", str[i]))
		ft_error(conf, "invalid parameter letter", NULL);
	if (str[i] == 'R' && str[i + 1] == ' ')
	{
		if (conf->r1 == 0 && conf->r2 == 0)
			get_resolution(conf, str);
		else
			ft_error(conf, "twice", NULL);
	}
	if (str[i] == 'N' && str[i + 1] == 'O')
		ft_check_get_path(conf, str, conf->no);
	if (str[i] == 'S' && str[i + 1] == 'O')
		ft_check_get_path(conf, str, conf->so);
	if (str[i] == 'W' && str[i + 1] == 'E')
		ft_check_get_path(conf, str, conf->we);
	if (str[i] == 'E' && str[i + 1] == 'A')
		ft_check_get_path(conf, str, conf->ea);
	if (str[i] == 'S' && str[i + 1] == ' ')
		ft_check_get_path(conf, str, conf->s);
	get_bonus_path(str, i, conf);
}
