/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 13:03:38 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/22 13:03:39 by owinckle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vect	*vect_set(t_vect *dst, float a, float b, float c)
{
	if (dst == NULL)
		dst = (t_vect *)malloc(sizeof(t_vect));
	dst->x = a;
	dst->y = b;
	dst->z = c;
	return (dst);
}

t_vect	*vect_copy(t_vect *dst, t_vect src)
{
	if (dst == NULL)
		dst = (t_vect *)malloc(sizeof(t_vect));
	dst->x = src.x;
	dst->y = src.y;
	dst->z = src.z;
	return (dst);
}

float	ft_dist(t_vect a, t_vect b)
{
	return (sqrt(pow(b.x - a.x, 2)
		+ pow(b.y - a.y, 2)
		+ pow(b.z - a.z, 2)));
}

t_vect	*ft_norme(t_vect *v)
{
	float	tmp;

	if (v->x == 0 && v->y == 0 && v->z == 0)
		ft_error("on ne peut pas normer le vecteur NULL!\n", NULL);
	tmp = sqrt(pow(v->x, 2) + pow(v->y, 2) + pow(v->z, 2));
	v->x /= tmp;
	v->y /= tmp;
	v->z /= tmp;
	return (v);
}
