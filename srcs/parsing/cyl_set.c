/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:21:03 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/23 02:13:18 by dbirtel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		cyl_child(t_obj *o, xmlNodePtr noeud, t_env *e)
{
	(void)e;
	if ((noeud = noeud->children) != NULL)
	{
		while (noeud)
		{
			if ((!ft_strcmp((char *)noeud->name, "lim")))
				lim_set(o, noeud);
			if ((!ft_strcmp((char *)noeud->name, "realim")))
				realim_set(o, noeud);
			if (!ft_strcmp((char *)noeud->name, "texture"))
				cyl_tex_set(e, noeud);
			if (!ft_strcmp((char *)noeud->name, "neg"))
				o->vide = neg_obj(noeud->children);
			noeud = noeud->next;
		}
	}
}

void			load_cy_effect(t_obj *o, xmlNodePtr noeud)
{
	xmlChar		*attr;

	if ((attr = xmlGetProp(noeud, (const xmlChar *)"refl")))
		if (ft_isdigit(*(char *)attr))
			o->refl = ft_atof((char *)attr, 1);
	if ((attr = xmlGetProp(noeud, (const xmlChar *)"trans")))
		if (ft_isdigit(*(char *)attr))
			o->trans = ft_atof((char *)attr, 1);
}

void			load_cyl(t_obj *o, xmlNodePtr noeud, t_env *e)
{
	xmlChar		*attr;

	if ((attr = xmlGetProp(noeud, (const xmlChar *)"ori")))
		load_vect(&(o->ori), (char *)attr);
	if ((attr = xmlGetProp(noeud, (const xmlChar *)"axe")))
		load_vect(&(o->axe), (char *)attr);
	if ((attr = xmlGetProp(noeud, (const xmlChar *)"col")))
		load_vect(&(o->col), (char *)attr);
	if ((attr = xmlGetProp(noeud, (const xmlChar *)"spec")))
		if (ft_isdigit(*(char *)attr))
			o->spec = ft_atof((char *)attr, 1);
	if ((attr = xmlGetProp(noeud, (const xmlChar *)"rad")))
		if (ft_isdigit(*(char *)attr))
			o->rad = ft_atof((char *)attr, 1);
	if ((attr = xmlGetProp(noeud, (const xmlChar *)"dam")))
		if (ft_isdigit(*(char *)attr))
			o->damier = (int)ft_atof((char *)attr, 1);
	if ((attr = xmlGetProp(noeud, (const xmlChar *)"sin")))
		if (ft_isdigit(*(char *)attr))
			o->sinus = (int)ft_atof((char *)attr, 1);
	load_cy_effect(o, noeud);
	cyl_child(o, noeud, e);
}

void			init_cyl(t_obj *o)
{
	o->ori = (t_vect){0, 0, 0};
	o->axe = (t_vect){0, 1, 0};
	o->col = (t_vect){150, 150, 150};
	o->lim.x = (t_vect){-1, 0, 0};
	o->lim.y = (t_vect){-1, 0, 0};
	o->lim.z = (t_vect){-1, 0, 0};
	o->l.x = (t_vect){-1, 0, 0};
	o->l.y = (t_vect){-1, 0, 0};
	o->l.z = (t_vect){-1, 0, 0};
	o->type = CYLINDER;
	o->id = 0;
	o->rad = 1;
	o->damier = 0;
	o->sinus = 0;
	o->spec = -1;
	o->vide = NULL;
	o->inv = NULL;
	o->refl = -1;
	o->trans = -1;
}

void			cyl_set(t_env *e, xmlNodePtr noeud)
{
	t_obj	*begin;

	begin = new_obj(e);
	init_cyl(e->o);
	load_cyl(e->o, noeud, e);
	fix_color(&(e->o->col));
	ft_norme(&(e->o->axe));
	e->o->col_inv = col_inv(e->o->col);
	e->o->rot = compute_rot_qt(e->o->axe);
	e->nb_cyl++;
	e->o = begin;
}
