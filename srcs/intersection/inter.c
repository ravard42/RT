/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 11:59:17 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/23 00:21:45 by dbirtel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_ray	move_ray(t_ray ray, t_obj *obj)
{
	t_qt	pos;
	t_qt	vec;

	ray.ori = sub_coord(ray.ori, obj->ori);
	if (obj->axe.y > 0 && obj->axe.x < 0.01 && obj->axe.x > -0.01 &&
		obj->axe.z < 0.01 && obj->axe.z > -0.01)
		return (ray);
	pos.a = 0.0f;
	pos.v = ray.ori;
	pos = rot_qt(pos, obj->rot);
	ray.ori = pos.v;
	vec.a = 0.0f;
	vec.v = ray.dir;
	vec = rot_qt(vec, obj->rot);
	ray.dir = vec.v;
	return (ray);
}

void	find_inter(t_ray *r, t_obj *o)
{
	t_obj	*list;

	list = o;
	while (list)
	{
		if (list->type == PLANE)
			plan_inter(r, list);
		else if (list->type == SPHERE)
			sphere_inter(r, list);
		else if (list->type == CYLINDER)
			cyl_inter(r, list);
		else if (list->type == CONE)
			cone_inter(r, list);
		list = list->next;
	}
}

t_vect	find_color(t_ray *r, t_obj *o, t_light *light, float amb)
{
	t_ray	saved;
	t_light	*l;
	t_vect	color;

	l = light;
	saved = *r;
	r->ori = r->p[0];
	color = (t_vect){0, 0, 0};
	while (l && (r->c_l = 42))
	{
		r->o_inter = NULL;
		r->inter = l->t != 0 ? INTER_MAX : vec_len(sub_coord(r->p[0], l->ori));
		r->dir = vec_norm(l->t != 0 ? l->ori : sub_coord(l->ori, r->ori));
		find_inter(r, o);
		if (!r->o_inter)
			light_process(r, &saved, l, &color);
		l = l->next;
	}
	*r = saved;
	color = amb ? add_coord(color, mult_coord(r->col, amb)) : color;
	return (rfix_color(color));
}

t_vect	select_inter_func(t_data_th *th)
{
	th->r.inter = INTER_MAX;
	th->r.o_inter = NULL;
	if (th->e->effet == 0)
		return (inter(th));
	else if (th->e->effet == 1 || th->e->effet == 2)
		return (antia_inter(th, -1, 0));
	else if (th->e->effet == 3)
		return (motion_b_inter(th));
	return (t_vect){0, 0, 0};
}

t_vect	inter(t_data_th *th)
{
	t_vect color;

	find_inter(&(th->r), th->o);
	if (!th->r.o_inter)
		return (t_vect){0, 0, 0};
	th->r.p[0] = translate(th->r.ori, th->r.dir, th->r.inter - 0.1);
	th->r.col = (th->r.o_inter->tex.is_tex_obj) ?
		hexa_to_rgb(tex(th->r)) : th->r.o_inter->col;
	color = find_color(&(th->r), th->o, th->l, th->e->amb);
	color = add_coord(color, refl_trans(th));
	color = add_coord(color, filter(th->e->filter_id, th));
	fix_color(&color);
	return (color);
}
