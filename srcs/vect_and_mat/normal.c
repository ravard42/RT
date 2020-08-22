/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 13:00:35 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/22 13:00:36 by owinckle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_vect	cylinder_normal(t_ray *r)
{
	t_qt	n;
	t_qt	rot;

	n.a = 0.0;
	n.v = r->p[1];
	n.v.y = 0.0;
	n.v = vec_norm(n.v);
	if (good_axis(r->o_inter->axe))
		return (n.v);
	rot = inv_qt(r->o_inter->rot);
	n = rot_qt(n, rot);
	return (n.v);
}

static t_vect	cone_normal(t_ray *r)
{
	t_qt	rot;
	t_qt	n;

	n.a = 0.0;
	n.v = r->p[1];
	rot = inv_qt(r->o_inter->rot);
	if (n.v.y < 0)
		n.v.y += (vec_len(r->p[1]) / cos(r->o_inter->rad));
	else
		n.v.y -= (vec_len(r->p[1]) / cos(r->o_inter->rad));
	n.v = vec_norm(n.v);
	if (good_axis(r->o_inter->axe))
		return (n.v);
	n = rot_qt(n, rot);
	return (n.v);
}

t_vect			get_normal(t_ray *r)
{
	t_vect	normal;

	if (r->o_inter->type == SPHERE)
		normal = (vec_norm(r->p[1]));
	else if (r->o_inter->type == CYLINDER)
		normal = (cylinder_normal(r));
	else if (r->o_inter->type == CONE)
		normal = (cone_normal(r));
	else if (r->o_inter->type == PLANE)
	{
		if (r->o_inter->sinus == 1)
			normal = sinus_plane(r);
		else
			normal = (r->o_inter->axe);
	}
	if (r->norm_mult == -1)
		normal = mult_coord(normal, -1.0f);
	return (normal);
}
