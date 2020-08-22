/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:48:24 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/22 12:48:25 by owinckle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_qt	compute_rot_qt(t_vect dir)
{
	t_qt	rot;
	t_vect	n;
	t_vect	axis;
	float	det;
	float	dotp;

	axis.x = FLT_EPSILON;
	axis.y = 1.0;
	axis.z = FLT_EPSILON;
	n = vec_norm(cross(dir, axis));
	dotp = dot(axis, dir);
	det = axis.x * dir.y * n.z + dir.x * n.y * axis.z + n.x * axis.y * dir.z \
		- axis.z * dir.y * n.x - dir.z * n.y * axis.x - n.z * axis.y * dir.x;
	rot.a = atan2(det, dotp) / 2.0;
	rot.v = n;
	return (rot);
}
