/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 18:36:14 by mlecuyer          #+#    #+#             */
/*   Updated: 2020/11/24 10:30:51 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void *str;

	str = malloc(count * size);
	if (str == NULL)
		return (NULL);
	if (str)
		ft_memset(str, 0, count * size);
	return (str);
}
