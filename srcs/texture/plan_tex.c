/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:43:39 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/23 19:52:25 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		plan_tex_set(t_env *e, xmlNodePtr noeud)
{
	xmlChar	*attr;

	if ((attr = xmlGetProp(noeud, (xmlChar *)"path")))
		e->o->tex = load_png((char *)attr, e, -1);
	if ((attr = xmlGetProp(noeud, (xmlChar *)"ori")))
		load_vect(&(e->o->tex.ori), (char *)attr);
	if ((attr = xmlGetProp(noeud, (xmlChar *)"Vx")))
	{
		load_vect(&(e->o->tr_mat.vx), (char *)attr);
		ft_norme(&(e->o->tr_mat.vx));
		vect_prod(&(e->o->tr_mat.vz), e->o->tr_mat.vx, e->o->tr_mat.vy);
	}
	inverse(&(e->o->tr_mat));
	if ((attr = xmlGetProp(noeud, (xmlChar *)"texel_dim")))
		e->o->tex.dim = ft_atof((char *)attr, 1);
	if ((attr = xmlGetProp(noeud, (xmlChar *)"rep_x")))
		e->o->tex.rep_x = ft_atof((char *)attr, 1);
	if ((attr = xmlGetProp(noeud, (xmlChar *)"rep_y")))
		e->o->tex.rep_y = ft_atof((char *)attr, 1);
}

static int	select_pix(t_vect tmp, t_tex t)
{
	int	x;
	int	y;

	x = (int)(tmp.x / t.dim);
	if (t.rep_x > 0 && (x < 0 || x / t.width >= t.rep_x))
		return (-42);
	x %= t.width;
	x = (x < 0) ? x + t.width : x;
	y = (int)(tmp.z / t.dim);
	if (t.rep_y > 0 && (y < 0 || y / t.height >= t.rep_y))
		return (-42);
	y %= t.height;
	y = (y < 0) ? y + t.height : y;
	return (y * t.width + x);
}

int			plan_tex(t_ray r)
{
	t_obj	*o;
	t_vect	tmp;
	int		pix;
	int		sup;

	o = r.o_inter;
	vect_sub(&tmp, r.p[0], o->tex.ori);
	mat_prod(&tmp, o->tr_mat, tmp);
	pix = select_pix(r.p[1], o->tex);
	if (pix == -42)
		return (rgb_to_hexa(r.o_inter->col));
	sup = o->tex.width * o->tex.height;
	pix = (pix >= sup) ? sup - 1 : pix;
	return (*(o->tex.addr + pix));
}
