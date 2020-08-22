/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_qt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbirtel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 17:43:18 by dbirtel           #+#    #+#             */
/*   Updated: 2017/04/10 09:35:30 by dbirtel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

t_qt	mult_qt(t_qt a, t_qt b)
{
	t_qt	r;

	r.a = a.a * b.a - a.v.x * b.v.x - a.v.y * b.v.y - a.v.z * b.v.z;
	r.v.x = a.a * b.v.x + a.v.x * b.a + a.v.y * b.v.z - a.v.z * b.v.y;
	r.v.y = a.a * b.v.y - a.v.x * b.v.z + a.v.y * b.a + a.v.z * b.v.x;
	r.v.z = a.a * b.v.z + a.v.x * b.v.y - a.v.y * b.v.x + a.v.z * b.a;
	return (r);
}
