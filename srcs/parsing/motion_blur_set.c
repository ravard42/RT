/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_blur_set.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:20:10 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/22 12:20:11 by owinckle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	motion_blur_set(t_env *e, xmlNodePtr noeud)
{
	xmlChar		*attr;

	e->o->m_b.is_m_b_obj = 1;
	if ((attr = xmlGetProp(noeud, (xmlChar *)"a")))
		load_vect(&(e->o->m_b.a), (char *)attr);
	if ((attr = xmlGetProp(noeud, (xmlChar *)"b")))
		load_vect(&(e->o->m_b.b), (char *)attr);
	e->o->m_b.saved = e->o->ori;
}
