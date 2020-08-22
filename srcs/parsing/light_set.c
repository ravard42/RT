/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:18:55 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/22 12:18:56 by owinckle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	load_light(t_env *e, xmlNodePtr noeud)
{
	xmlChar		*attr;

	e->l->t = 0;
	if ((attr = xmlGetProp(noeud, (const xmlChar *)"ori")))
		load_vect(&(e->l->ori), (char *)attr);
	if ((attr = xmlGetProp(noeud, (const xmlChar *)"spec")))
		if (ft_isdigit(*(char *)attr))
			e->l->t = (int)ft_atof((char *)attr, 1);
	if (e->l->t != 0)
		e->l->t = 1;
}

t_light		*new_light(t_env *e)
{
	t_light	*light;

	if (e->l == NULL)
	{
		e->l = (t_light *)malloc(sizeof(t_light));
		light = e->l;
	}
	else
	{
		light = e->l;
		while (e->l->next != NULL)
			e->l = e->l->next;
		e->l->next = (t_light *)malloc(sizeof(t_light));
		e->l = e->l->next;
	}
	e->l->next = NULL;
	return (light);
}

void		light_set(t_env *e, xmlNodePtr noeud)
{
	t_light	*l;

	l = new_light(e);
	load_light(e, noeud);
	e->nb_light++;
	e->l = l;
}
