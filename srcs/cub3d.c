/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 10:33:38 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/04/21 09:44:13 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int		check_dotcub(t_conf *conf, char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	i--;
	if (str[i] == 'b' && str[i - 1] == 'u' &&
		str[i - 2] == 'c' && str[i - 3] == '.')
		return (0);
	else
		ft_error(conf, "valid file", NULL);
	return (0);
}

static void		check_save(t_conf *conf, char *str)
{
	if (ft_strcmp(str, "--save") == 0)
	{
		printf("Saving image...\n");
		conf->save_image = 1;
	}
	else
		ft_error(conf, "third arg invalid", NULL);
}

int				main(int argc, char **argv)
{
	int		fd;
	t_conf	conf;

	ft_memset(&conf, 0, sizeof(t_conf));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error(&conf, "Open failed", NULL);
	if (argc == 2 || argc == 3)
	{
		check_dotcub(&conf, argv[1]);
		ini_conf(&conf);
		if (argc == 3)
			check_save(&conf, argv[2]);
		parse_map(&conf, fd);
	}
	else
		ft_error(&conf, "error", NULL);
	if (close(fd) == -1)
		return (-1);
	launch_game(&conf);
	return (0);
}
