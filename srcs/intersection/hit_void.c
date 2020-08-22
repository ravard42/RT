/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_void.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 11:58:57 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/22 11:58:58 by owinckle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		void_sphere(t_vect hit, t_obj *o)
{
	if (o->lim.x.x < 0 && o->lim.y.x < 0 && o->lim.z.x < 0)
	{
		if (vec_len(sub_coord(hit, o->ori)) < o->rad)
			return (1);
		else
			return (0);
	}
	if (void_sphere_inter(hit, o))
		return (1);
	return (0);
}

int		void_plane(t_vect hit, t_obj *o)
{
	if (dot(sub_coord(hit, o->ori), o->axe) > 0)
		return (1);
	return (0);
}

int		void_cyl(t_vect hit, t_obj *o)
{
	t_vect	bam;

	if (good_axis(o->axe))
	{
		bam = o->ori;
		bam.y = hit.y;
		if (vec_len(sub_coord(hit, bam)) < o->rad)
		{
			if (o->lim.x.x < 0 && o->lim.y.x < 0 && o->lim.z.x < 0)
				return (1);
			if (in_lim(sub_coord(hit, o->ori), o))
				return (1);
		}
		return (0);
	}
	if (void_cyl_inter(hit, o))
		return (1);
	return (0);
}

int		void_cone(t_vect hit, t_obj *o)
{
	if (void_cone_inter(hit, o))
		return (1);
	return (0);
}

int		hit_void(t_vect hit, t_obj *o)
{
	t_obj	*vide;
	int		ret;

	vide = o->vide;
	while (vide)
	{
		if (vide->type == SPHERE)
			ret = void_sphere(hit, vide);
		else if (vide->type == PLANE)
			ret = void_plane(hit, vide);
		else if (vide->type == CYLINDER)
			ret = void_cyl(hit, vide);
		else if (vide->type == CONE)
			ret = void_cone(hit, vide);
		if (ret == 1)
			return (1);
		vide = vide->next;
	}
	return (0);
}
