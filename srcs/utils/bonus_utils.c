/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 11:03:29 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/04/21 09:34:57 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	play_sound(char c)
{
	if (c == 's')
		system("mpg123 ./sound/racestart.mp3 &");
	else if (c == 'b')
		system("mpg123 ./sound/peach.mp3 &");
	else if (c == 'e')
		system("mpg123 ./sound/congrats.mp3 &");
	else if (c == 'w')
		system("mpg123 ./sound/woo.mp3 &");
}

void	get_text_bonus(t_conf *c)
{
	if (c->ss)
	{
		c->t[5].img = mlx_xpm_file_to_image(c->mlx.ptr, c->ss,
			&(c->t[5].w), &(c->t[5].h));
		if (c->t[5].img == NULL)
			ft_error(c, "bad text", NULL);
	}
	if (c->sss)
	{
		c->t[6].img = mlx_xpm_file_to_image(c->mlx.ptr, c->sss,
			&(c->t[6].w), &(c->t[6].h));
		if (c->t[6].img == NULL)
			ft_error(c, "bad text", NULL);
	}
}
