/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:02:23 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/23 02:04:43 by dbirtel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		plane_limit(t_vect p, t_obj *o)
{
	if (vec_len(p) > o->rad && o->rad > 0 && o->id == 0)
		return (0);
	if (o->lim.x.x > 1.0f)
		if ((o->lim.x.y > 0.0f && p.x > o->lim.x.y) ||
			(o->lim.x.z > 0.0f && -p.x > o->lim.x.z))
			return (0);
	if (o->lim.x.x > 0.0f && o->lim.x.x < 1.0f)
		if ((o->lim.x.y > 0.0f && p.x < o->lim.x.y) &&
			(o->lim.x.z > 0.0f && -p.x < o->lim.x.z))
			return (0);
	if (o->lim.z.x > 1.0f)
		if ((o->lim.z.y > 0.0f && p.z > o->lim.z.y) ||
			(o->lim.z.z > 0.0f && -p.z > o->lim.z.z))
			return (0);
	if (o->lim.z.x > 0.0f && o->lim.z.x < 1.0f)
		if ((o->lim.z.y > 0.0f && p.z < o->lim.z.y) &&
			(o->lim.z.z > 0.0f && -p.z < o->lim.z.z))
			return (0);
	return (1);
}

int		inside_specific_lim(t_vect p, t_obj *o)
{
	if (o->lim.z.x > 1.0f)
		if ((o->lim.z.y > 0.0f && p.z > o->lim.z.y) ||
			(o->lim.z.z > 0.0f && -p.z > o->lim.z.z))
			return (0);
	if (o->lim.z.x > 0.0f && o->lim.z.x < 1.0f)
		if ((o->lim.z.y > 0.0f && p.z < o->lim.z.y) &&
			(o->lim.z.z > 0.0f && -p.z < o->lim.z.z))
			return (0);
	return (1);
}

int		in_lim(t_vect p, t_obj *o)
{
	if (o->type == PLANE)
		return (plane_limit(p, o));
	if (o->lim.x.x > 1.0f)
		if ((o->lim.x.y > 0.0f && p.x > o->lim.x.y) ||
			(o->lim.x.z > 0.0f && -p.x > o->lim.x.z))
			return (0);
	if (o->lim.x.x > 0.0f && o->lim.x.x < 1.0f)
		if ((o->lim.x.y > 0.0f && p.x < o->lim.x.y) &&
			(o->lim.x.z > 0.0f && -p.x < o->lim.x.z))
			return (0);
	if (o->lim.y.x > 1.0f)
		if ((o->lim.y.y > 0.0f && p.y > o->lim.y.y) ||
			(o->lim.y.z > 0.0f && -p.y > o->lim.y.z))
			return (0);
	if (o->lim.y.x > 0.0f && o->lim.y.x < 1.0f)
		if ((o->lim.y.y > 0.0f && p.y < o->lim.y.y) &&
			(o->lim.y.z > 0.0f && -p.y < o->lim.y.z))
			return (0);
	return (inside_specific_lim(p, o));
}

int		realim_sweet(t_vect p, t_lim l)
{
	if (l.y.x > 1.0f)
		if ((l.y.y > 0.0f && p.y > l.y.y) ||
			(l.y.z > 0.0f && -p.y > l.y.z))
			return (0);
	if (l.y.x > 0.0f && l.y.x < 1.0f)
		if ((l.y.y > 0.0f && p.y < l.y.y) &&
			(l.y.z > 0.0f && -p.y < l.y.z))
			return (0);
	if (l.z.x > 1.0f)
		if ((l.z.y > 0.0f && p.z > l.z.y) ||
			(l.z.z > 0.0f && -p.z > l.z.z))
			return (0);
	if (l.z.x > 0.0f && l.z.x < 1.0f)
		if ((l.z.y > 0.0f && p.z < l.z.y) &&
			(l.z.z > 0.0f && -p.z < l.z.z))
			return (0);
	return (1);
}

int		rlim(t_vect ori, t_vect dir, float d, t_lim l)
{
	t_vect	p;

	if (l.x.x < 0 && l.y.x < 0 && l.z.x < 0)
		return (1);
	p = translate(ori, dir, d);
	if (l.x.x > 1.0f)
		if ((l.x.y > 0.0f && p.x > l.x.y) ||
			(l.x.z > 0.0f && -p.x > l.x.z))
			return (0);
	if (l.x.x > 0.0f && l.x.x < 1.0f)
		if ((l.x.y > 0.0f && p.x < l.x.y) &&
			(l.x.z > 0.0f && -p.x < l.x.z))
			return (0);
	return (realim_sweet(p, l));
}
