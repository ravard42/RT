/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:14:57 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/22 12:14:59 by owinckle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	real_init_cube(t_obj *o, int i, t_vect axe)
{
	float size;

	size = o->rad / 2.0;
	if (i == 0)
		o->ori = translate(o->ori, axe, size);
	if (i == 1)
		o->ori = translate(o->ori, axe, -size);
	if (i == 2)
		o->ori = translate(o->ori, axe, size);
	if (i == 3)
		o->ori = translate(o->ori, axe, -size);
	if (i == 4)
		o->ori = translate(o->ori, axe, size);
	if (i == 5)
		o->ori = translate(o->ori, axe, -size);
	o->lim.x = (t_vect){1.5, size, size};
	o->lim.z = (t_vect){1.5, size, size};
}

void	cube_set(t_env *e, xmlNodePtr noeud)
{
	int		i;
	t_obj	*cube;
	t_vect	axe;

	i = -1;
	while (++i < 6)
	{
		cube = new_obj(e);
		init_plane(e->o);
		load_plan(e->o, noeud, e);
		fix_color(&(e->o->col));
		ft_norme(&(e->o->axe));
		e->o->col_inv = col_inv(e->o->col);
		if (i == 0 || i == 1)
			axe = (t_vect){0, 1, 0};
		if (i == 2 || i == 3)
			axe = (t_vect){1, 0, 0};
		if (i == 4 || i == 5)
			axe = (t_vect){0, 0, 1};
		real_init_cube(e->o, i, axe);
		e->o->axe = axe;
		e->o->rot = compute_rot_qt(axe);
		e->o = cube;
	}
	e->nb_cube++;
}
