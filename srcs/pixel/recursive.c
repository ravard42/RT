/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:35:56 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/22 12:35:58 by owinckle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vect	refl_dir(t_vect v, t_vect n)
{
	t_vect		ref;
	float		doot;

	doot = dot(v, n);
	if (doot < 0)
	{
		ref = mult_coord(n, -2.0 * dot(v, n));
		ref = add_coord(ref, v);
		return (ref);
	}
	return (n);
}

t_vect	reflection(t_data_th *th)
{
	t_vect		color;
	t_vect		normal;
	float		val;

	val = th->r.o_inter->refl;
	color = (t_vect){0, 0, 0};
	if (th->r.refl < 2 && val > 0 && val < 1)
	{
		th->r.refl++;
		normal = get_normal(&th->r);
		th->r.ori = th->r.p[0];
		th->r.dir = refl_dir(th->r.dir, normal);
		color = add_coord(color, select_inter_func(th));
		color = mult_coord(color, val);
	}
	return (color);
}

t_vect	transparent(t_data_th *th)
{
	t_vect		color;
	float		val;

	val = th->r.o_inter->trans;
	color = (t_vect){0, 0, 0};
	if (th->r.refl < 3)
	{
		th->r.refl++;
		th->r.ori = th->r.p[0];
		color = add_coord(color, select_inter_func(th));
		color = mult_coord(color, val);
	}
	return (color);
}

t_vect	refl_trans(t_data_th *th)
{
	t_vect		color;

	color = (t_vect){0, 0, 0};
	if (th->r.o_inter->refl > 0 && th->r.o_inter->refl < 1)
	{
		th->r.p[0] = translate(th->r.ori, th->r.dir, th->r.inter - 0.1);
		color = reflection(th);
	}
	else if (th->r.o_inter->trans > 0 && th->r.o_inter->trans < 1)
	{
		th->r.p[0] = translate(th->r.ori, th->r.dir, th->r.inter + 0.1);
		color = transparent(th);
	}
	return (color);
}
