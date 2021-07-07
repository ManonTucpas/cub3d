/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 10:33:52 by mlecuyer          #+#    #+#             */
/*   Updated: 2020/11/21 09:48:26 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	i;
	char	*tmp_s;

	i = 0;
	if (!s)
		return (NULL);
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (new_str == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (new_str);
	tmp_s = (char *)s;
	while (tmp_s[start] && i < len)
	{
		new_str[i] = tmp_s[start];
		i++;
		start++;
	}
	new_str[i] = '\0';
	return (new_str);
}
