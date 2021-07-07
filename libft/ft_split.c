/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 08:20:52 by mlecuyer          #+#    #+#             */
/*   Updated: 2020/11/24 18:15:11 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**ft_malloc_error(char **tab)
{
	unsigned int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static int		ft_wordcount(char const *s, char c)
{
	int	i;
	int	wordcount;

	wordcount = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			wordcount++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (wordcount);
}

static int		ft_wordlen(char const *s, char c)
{
	int i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

char			**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	size_t	len_s;
	int		nb_word;

	if (!s)
		return (NULL);
	nb_word = ft_wordcount(s, c);
	i = 0;
	if (!(tab = (char **)malloc(sizeof(char *) * (nb_word + 1))))
		return (NULL);
	while (nb_word--)
	{
		while (*s == c && *s)
			s++;
		len_s = ft_wordlen(s, c);
		if (!(tab[i] = (char*)malloc(sizeof(char) * len_s + 1)))
			return (ft_malloc_error(tab));
		ft_strlcpy(tab[i], s, len_s + 1);
		i++;
		s += len_s;
	}
	tab[i] = NULL;
	return (tab);
}
