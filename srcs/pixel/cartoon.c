/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartoon.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:29:59 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/22 12:30:00 by owinckle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vect		cartoon(t_vect *col, t_ray *r, int *bord)
{
	t_obj	*ref;
	int		i;

	ref = r[0].o_inter;
	i = 0;
	while (++i < 5)
	{
		if (r[i].o_inter != ref)
		{
			*bord = 1;
			return (t_vect){0, 0, 0};
		}
	}
	return (mix_color(col, 5));
}
