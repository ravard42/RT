/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lim_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:19:40 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/23 01:39:20 by dbirtel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	realim_set(t_obj *o, xmlNodePtr noeud)
{
	xmlChar		*attr;

	if ((attr = xmlGetProp(noeud, (const xmlChar *)"limx")))
		load_vect(&(o->l.x), (char *)attr);
	if ((attr = xmlGetProp(noeud, (const xmlChar *)"limy")))
		load_vect(&(o->l.y), (char *)attr);
	if ((attr = xmlGetProp(noeud, (const xmlChar *)"limz")))
		load_vect(&(o->l.z), (char *)attr);
}

void	lim_set(t_obj *o, xmlNodePtr noeud)
{
	xmlChar		*attr;

	if ((attr = xmlGetProp(noeud, (const xmlChar *)"limx")))
		load_vect(&(o->lim.x), (char *)attr);
	if ((attr = xmlGetProp(noeud, (const xmlChar *)"limy")))
		load_vect(&(o->lim.y), (char *)attr);
	if ((attr = xmlGetProp(noeud, (const xmlChar *)"limz")))
		load_vect(&(o->lim.z), (char *)attr);
}
