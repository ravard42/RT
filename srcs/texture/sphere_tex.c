/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_tex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:44:39 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/23 06:53:55 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	handle_solar_sys(t_env *e, char *attr)
{
	if (!ft_strcmp((char *)attr, TERRE))
		e->astre[0] = e->o;
	else if (!ft_strcmp((char *)attr, LUNE))
		e->astre[1] = e->o;
	else if (!ft_strcmp((char *)attr, MERCURE))
		e->astre[2] = e->o;
	else if (!ft_strcmp((char *)attr, VENUS))
		e->astre[3] = e->o;
	else if (!ft_strcmp((char *)attr, MARS))
		e->astre[4] = e->o;
	else if (!ft_strcmp((char *)attr, JUPITER))
		e->astre[5] = e->o;
}

void		sphere_tex_set(t_env *e, xmlNodePtr noeud)
{
	xmlChar		*attr;
	float		tmp;

	if ((attr = xmlGetProp(noeud, (xmlChar *)"path")))
	{
		handle_solar_sys(e, (char *)attr);
		e->o->tex = load_png((char *)attr, e, -1);
	}
	if ((attr = xmlGetProp(noeud, (xmlChar *)"ori")))
		load_vect(&(e->o->tex.ori), (char *)attr);
	if ((attr = xmlGetProp(noeud, (const xmlChar *)"val_rot")))
		if ((tmp = ft_atof((char *)attr, 1)) > 0.005)
		{
			rot(&(e->o->tr_mat.vy), M_PI / tmp, e->o->tr_mat.vx);
			rot(&(e->o->tr_mat.vz), M_PI / tmp, e->o->tr_mat.vx);
			inverse(&(e->o->tr_mat));
		}
}

static int	select_pix(t_vect tmp, t_obj *o)
{
	float	lalo[2];
	t_vect	vect[2];
	int		x;
	int		y;

	vect[0] = (t_vect){0, 1, 0};
	lalo[0] = acos(dot_prod(vect[0], tmp));
	lalo[0] /= M_PI;
	y = (int)(o->tex.height * lalo[0]);
	vect[1] = (t_vect){1, 0, 0};
	tmp.y = 0;
	ft_norme(&tmp);
	lalo[1] = acos(dot_prod(vect[1], tmp));
	lalo[1] = (tmp.z > 0) ? lalo[1] : 2 * M_PI - lalo[1];
	lalo[1] /= 2 * M_PI;
	x = (int)(o->tex.width * lalo[1]);
	return (y * o->tex.width + x);
}

int			sphere_tex(t_ray r)
{
	t_obj	*o;
	t_vect	tmp;
	int		pix;
	int		sup;

	o = r.o_inter;
	vect_sub(&tmp, r.p[0], o->tex.ori);
	mat_prod(&tmp, o->tr_mat, tmp);
	pix = select_pix(vec_norm(tmp), o);
	sup = o->tex.width * o->tex.height;
	pix = (pix >= sup) ? sup - 1 : pix;
	return (*(o->tex.addr + pix));
}
