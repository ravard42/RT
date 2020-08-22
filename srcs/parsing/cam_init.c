/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:14:42 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/22 12:14:43 by owinckle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	vp_init(t_vp *b)
{
	vect_init(&(b->right));
	vect_init(&(b->up));
	vect_init(&(b->dir));
}

static void	cam_init_base(t_cam *c)
{
	ft_norme(&(c->b.dir));
	ft_norme(&(c->b.up));
	c->b.right = vec_norm(cross(c->b.up, c->b.dir));
	c->b.up = vec_norm(cross(c->b.right, c->b.dir));
}

void		cam_init(t_env *e, xmlNodePtr noeud)
{
	xmlChar		*attr;

	if (e->c)
		ft_error("Multi cam settings not handled\n", NULL);
	e->c = (t_cam *)malloc(sizeof(t_cam));
	(void)noeud;
	if ((attr = xmlGetProp(noeud, (const xmlChar *)"ori")))
		load_vect(&(e->c->ori), (char *)attr);
	if ((attr = xmlGetProp(noeud, (const xmlChar *)"ori")))
	{
		e->c_ori = ft_strdup((char *)attr);
		xmlFree(attr);
	}
	vp_init(&(e->c->b));
	if ((attr = xmlGetProp(noeud, (const xmlChar *)"axe")))
		load_vect(&(e->c->b.dir), (char *)attr);
	if ((attr = xmlGetProp(noeud, (const xmlChar *)"axe")))
	{
		e->c_dir = ft_strdup((char *)attr);
		xmlFree(attr);
	}
	if ((attr = xmlGetProp(noeud, (const xmlChar *)"up")))
		load_vect(&(e->c->b.up), (char *)attr);
	cam_init_base(e->c);
}
