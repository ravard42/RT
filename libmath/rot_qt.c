/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_qt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbirtel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 17:18:59 by dbirtel           #+#    #+#             */
/*   Updated: 2017/04/07 01:25:37 by dbirtel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

t_qt	rot_qt(t_qt v, t_qt r)
{
	t_qt	i;
	float	theta;

	theta = r.a;
	r.a = cos(theta) / 2.0f;
	r.v = vec_norm(r.v);
	r.v.x *= -sin(theta) / 2.0f;
	r.v.y *= -sin(theta) / 2.0f;
	r.v.z *= -sin(theta) / 2.0f;
	r = norm_qt(r);
	i = inv_qt(r);
	return (mult_qt(mult_qt(r, v), i));
}
