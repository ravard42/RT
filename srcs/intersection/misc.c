/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:00:39 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/23 00:24:39 by dbirtel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		good_axis(t_vect n)
{
	if (n.y < 0)
		return (0);
	if (n.x > 0.001 || n.x < -0.001)
		return (0);
	if (n.z > 0.001 || n.z < -0.001)
		return (0);
	return (1);
}

void	load_ray(t_ray *r, float dist, t_vect hit, t_obj *o)
{
	if (o->trans != -1 && r->c_l == 42 && dist < r->inter)
	{
		r->c_trans = add_coord(r->c_trans, o->col);
		r->bool = 42;
	}
	r->inter = dist - FLT_EPSILON;
	r->p[1] = hit;
	r->o_inter = o;
	r->norm_mult = -1;
	if (r->c_l == 42 && r->o_inter->trans == -1 && r->bool != 42)
		r->o_inter->col = add_coord(r->o_inter->col,
			mult_coord(r->c_trans, o->trans));
}

void	load_ray_plus(t_ray *r, float dist, t_vect hit, t_obj *o)
{
	if (o->trans != -1 && r->c_l == 42 && dist < r->inter)
	{
		r->c_trans = add_coord(r->c_trans, o->col);
		r->bool = 42;
	}
	r->inter = dist - FLT_EPSILON;
	r->p[1] = hit;
	r->o_inter = o;
	r->norm_mult = 1;
	if (r->c_l == 42 && r->o_inter->trans == -1 && r->bool != 42)
		r->o_inter->col = add_coord(r->o_inter->col,
			mult_coord(r->c_trans, 0.5));
}
