/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 10:34:41 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/04/20 18:19:57 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_putstr(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

int		ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int		args_nb(char **str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str && str[i])
	{
		j = 0;
		while (str[i][j])
			j++;
		i++;
	}
	return (i);
}

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab[i]);
	free(tab);
}

char	*reass_join(char *s1, char *s2, char *(*f)(const char *, const char *))
{
	char *tmp;

	tmp = s1;
	s1 = (*f)(s1, s2);
	free(tmp);
	return (s1);
}
