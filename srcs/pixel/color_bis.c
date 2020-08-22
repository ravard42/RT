/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:33:06 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/22 12:33:07 by owinckle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		rgb_to_hexa(t_vect col)
{
	return (((int)col.x << 16) + ((int)col.y << 8) + ((int)col.z));
}

t_vect	hexa_to_rgb(int col)
{
	return (t_vect){(unsigned char)(col >> 16),
		(unsigned char)(col >> 8),
			(unsigned char)col};
}

void	light_process(t_ray *r, t_ray *saved, t_light *l, t_vect *color)
{
	saved->normal_hit = get_normal(saved);
	*color = add_coord(*color, diffuse(saved, r->dir, r->inter, l->t));
	if (saved->o_inter->spec > 0)
		*color = add_coord(*color, specular(saved, r->dir, r->inter));
}

t_vect	mix_color(t_vect *col, int n)
{
	int		i;
	t_vect	dst;

	dst = (t_vect){0.01, 0.01, 0.01};
	i = -1;
	while (++i < n)
	{
		dst.x += col[i].x;
		dst.y += col[i].y;
		dst.z += col[i].z;
	}
	dst.x /= n;
	dst.y /= n;
	dst.z /= n;
	return (dst);
}
