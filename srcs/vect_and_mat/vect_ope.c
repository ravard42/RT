/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_ope.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 13:02:57 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/22 13:02:57 by owinckle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vect	*vect_sum(t_vect *dst, t_vect u, t_vect v)
{
	dst->x = u.x + v.x;
	dst->y = u.y + v.y;
	dst->z = u.z + v.z;
	return (dst);
}

t_vect	*vect_sub(t_vect *dst, t_vect u, t_vect v)
{
	dst->x = u.x - v.x;
	dst->y = u.y - v.y;
	dst->z = u.z - v.z;
	return (dst);
}

t_vect	*vect_multi(t_vect *dst, float k, t_vect u)
{
	dst->x = k * u.x;
	dst->y = k * u.y;
	dst->z = k * u.z;
	return (dst);
}

t_vect	*vect_prod(t_vect *dst, t_vect u, t_vect v)
{
	dst->x = u.y * v.z - u.z * v.y;
	dst->y = u.z * v.x - u.x * v.z;
	dst->z = u.x * v.y - u.y * v.x;
	return (dst);
}

float	dot_prod(t_vect u, t_vect v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}
