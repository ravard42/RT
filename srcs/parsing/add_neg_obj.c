/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_neg_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:13:02 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/22 12:13:03 by owinckle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	if_neg(t_obj *new, xmlNodePtr noeud, int type)
{
	if (type == PLANE)
	{
		init_plane(new);
		load_plan(new, noeud, NULL);
	}
	if (type == SPHERE)
	{
		init_sphere(new);
		load_sphere(new, noeud, NULL);
	}
	if (type == CYLINDER)
	{
		init_cyl(new);
		load_cyl(new, noeud, NULL);
	}
	if (type == CONE)
	{
		init_cone(new);
		load_cone(new, noeud, NULL);
	}
}

void	neg_set(t_obj **list, xmlNodePtr noeud, int type)
{
	t_obj	*new;

	new = (t_obj *)malloc(sizeof(t_obj));
	if_neg(new, noeud, type);
	new->rot = compute_rot_qt(new->axe);
	new->next = *list;
	*list = new;
}

t_obj	*neg_obj(xmlNodePtr noeud)
{
	t_obj	*list;

	list = NULL;
	while (noeud)
	{
		if (!ft_strcmp((const char *)noeud->name, "plan"))
			neg_set(&list, noeud, PLANE);
		else if (!ft_strcmp((const char *)noeud->name, "sphere"))
			neg_set(&list, noeud, SPHERE);
		else if (!ft_strcmp((const char *)noeud->name, "cylindre"))
			neg_set(&list, noeud, CYLINDER);
		else if (!ft_strcmp((const char *)noeud->name, "cone"))
			neg_set(&list, noeud, CONE);
		noeud = noeud->next;
	}
	return (list);
}
