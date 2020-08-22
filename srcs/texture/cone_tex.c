/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:39:41 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/22 12:39:42 by owinckle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		cone_tex_set(t_env *e, xmlNodePtr noeud)
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
	if ((attr = xmlGetProp(noeud, (xmlChar *)"rep_x")))
		e->o->tex.rep_x = ft_atof((char *)attr, 1);
}

static int	select_pix(t_vect tmp, t_obj *o)
{
	int		x;
	int		y;
	t_vect	v;
	float	var;

	var = sqrt(pow(tmp.x, 2) + pow(tmp.z, 2));
	y = (int)sqrt(pow(var, 2) + pow(tmp.y, 2));
	y %= o->tex.height;
	y = (y < 0) ? y + o->tex.height : y;
	v = (t_vect){1, 0, 0};
	tmp.y = 0;
	var = acos(dot_prod(v, vec_norm(tmp)));
	var = (tmp.z > 0) ? var : 2 * M_PI - var;
	var /= 2 * M_PI / o->tex.rep_x;
	x = (int)(o->tex.width * var);
	x %= o->tex.width;
	return (y * o->tex.width + x);
}

int			cone_tex(t_ray r)
{
	t_obj	*o;
	t_vect	tmp;
	int		pix;
	int		sup;

	o = r.o_inter;
	vect_sub(&tmp, r.p[0], o->tex.ori);
	mat_prod(&tmp, o->tr_mat, tmp);
	pix = select_pix(tmp, o);
	sup = o->tex.width * o->tex.height;
	pix = (pix >= sup) ? sup - 1 : pix;
	return (*(o->tex.addr + pix));
}
