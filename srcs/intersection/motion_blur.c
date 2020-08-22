/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_blur.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:04:17 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/22 12:04:18 by owinckle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static void		apply_motion(t_obj *o, float t)
{
	o->ori.x = o->m_b.a.x * pow(t, 2) + o->m_b.b.x * t + o->m_b.saved.x;
	o->ori.y = o->m_b.a.y * pow(t, 2) + o->m_b.b.y * t + o->m_b.saved.y;
	o->ori.z = o->m_b.a.z * pow(t, 2) + o->m_b.b.z * t + o->m_b.saved.z;
}

static void		apply_all_motion(t_data_th *th, int t)
{
	t_obj	*o;

	o = th->e->o;
	while (o != NULL)
	{
		if (o->m_b.is_m_b_obj)
			apply_motion(o, (float)t * MB_TIME);
		o = o->next;
	}
}

static void		reset_m_b_obj(t_obj *o)
{
	while (o != NULL)
	{
		if (o->m_b.is_m_b_obj)
			o->ori = o->m_b.saved;
		o = o->next;
	}
}

t_vect			motion_b_inter(t_data_th *th)
{
	t_vect	color[MB_RAY];
	int		t;
	t_ray	save;

	save = th->r;
	t = -1;
	while (++t < MB_RAY)
	{
		apply_all_motion(th, t);
		th->r = save;
		find_inter(&th->r, th->o);
		if (!th->r.o_inter)
			color[t] = (t_vect){0, 0, 0};
		else
		{
			th->r.p[0] = translate(th->r.ori, th->r.dir, th->r.inter - 0.001f);
			th->r.col = (th->r.o_inter->tex.is_tex_obj) ?
				hexa_to_rgb(tex(th->r)) : th->r.o_inter->col;
			color[t] = find_color(&(th->r), th->o, th->l, th->e->amb);
			color[t] = add_coord(color[t], refl_trans(th));
			color[t] = add_coord(color[t], filter(th->e->filter_id, th));
		}
	}
	reset_m_b_obj(th->o);
	return (rfix_color(mix_color(color, 5)));
}
