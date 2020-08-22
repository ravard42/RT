/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan_inter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:03:51 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/23 02:04:58 by dbirtel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		plan_inter(t_ray *r, t_obj *o)
{
	t_ray	ray;
	float	dist;
	t_vect	hit;

	ray = move_ray(*r, o);
	dist = -(ray.ori.y / ray.dir.y) - FLT_EPSILON;
	hit = translate(ray.ori, ray.dir, dist);
	if (dist < r->inter && dist > 0.0 && in_lim(hit, o))
	{
		if (rlim(r->ori, r->dir, dist, o->l) && !hit_void(hit, o))
		{
			if (ray.ori.y < hit.y)
				load_ray(r, dist, hit, o);
			else
				load_ray_plus(r, dist, hit, o);
		}
	}
}
