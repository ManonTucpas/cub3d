/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 17:07:54 by mlecuyer          #+#    #+#             */
/*   Updated: 2020/11/23 19:06:44 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*cursor;

	cursor = lst;
	if (!lst || !f)
		return ;
	while (cursor)
	{
		f(lst->content);
		lst = cursor->next;
		cursor = lst;
	}
}
