/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 18:34:13 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/02/25 09:15:04 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	int			result;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\v' ||
				str[i] == '\n' || str[i] == '\r' || str[i] == '\f'))
		i++;
	if (str[i] == '-' && (str[i + 1] >= 48 && str[i + 1] <= 57))
	{
		sign = sign * -1;
		i++;
	}
	else if (str[i] == '+' && (str[i + 1] >= 48 && str[i + 1] <= 57))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	return (result * sign);
}
