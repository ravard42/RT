/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:23:47 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/23 08:33:11 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	handle_solar_sys(t_env *e)
{
	int		i;

	i = -1;
	while (++i < 6)
		if (e->astre[i] == NULL)
			return (0);
	e->trigo = (t_vect) {1, 0, 0};
	return (1);
}

static void	scene_set_up(t_env *e, xmlNodePtr noeud)
{
	xmlChar *attr;

	if ((attr = xmlGetProp(noeud, (const xmlChar *)"ambiante")))
	{
		if (ft_isdigit(*(char *)attr))
		{
			e->amb = ft_atof((char *)attr, 0) > 1.0f ?
				0.95 : ft_atof((char *)attr, 0);
			if (e->amb != 0)
				e->ambi = ft_strcpy(e->ambi, (char *)attr);
		}
		xmlFree(attr);
	}
	if ((attr = xmlGetProp(noeud, (xmlChar *)"filter")))
		e->filter = ft_strdup((char *)attr);
	xmlFree(attr);
	if (e->filter)
	{
		if (!ft_strcmp("sepia", e->filter))
			e->filter_id = 1;
		if (!ft_strcmp("ice", e->filter))
			e->filter_id = 2;
	}
	if (e->filter_id == 0)
		e->filter = ft_strdup("None");
}

void		loop_parse(t_env *e, xmlNodePtr noeud)
{
	while (noeud)
	{
		if (!ft_strcmp((char *)noeud->name, "cam"))
			cam_init(e, noeud);
		else if (!ft_strcmp((char *)noeud->name, "lumiere"))
			light_set(e, noeud);
		else if (!ft_strcmp((char *)noeud->name, "plan"))
			plan_set(e, noeud);
		else if (!ft_strcmp((char *)noeud->name, "sphere"))
			sphere_set(e, noeud);
		else if (!ft_strcmp((char *)noeud->name, "cylindre"))
			cyl_set(e, noeud);
		else if (!ft_strcmp((char *)noeud->name, "cone"))
			cone_set(e, noeud);
		else if (!ft_strcmp((char *)noeud->name, "cube"))
			cube_set(e, noeud);
		noeud = noeud->next;
	}
}

void		parse(t_env *e, char *path)
{
	xmlDocPtr	doc;
	xmlNodePtr	noeud;

	e->nb_sphere = 0;
	e->nb_plane = 0;
	e->nb_cone = 0;
	e->nb_cyl = 0;
	e->nb_cube = 0;
	e->nb_light = 0;
	xmlKeepBlanksDefault(0);
	doc = xmlParseFile(path);
	if (doc == NULL)
		ft_error("Document XML invalide\n", NULL);
	noeud = xmlDocGetRootElement(doc);
	if (noeud == NULL || ft_strcmp((char *)noeud->name, "scene") ||
		noeud->children == NULL)
	{
		ft_error("fichier scene invalide\n", NULL);
		xmlFreeDoc(doc);
	}
	scene_set_up(e, noeud);
	noeud = noeud->children;
	loop_parse(e, noeud);
	e->solar_sys = handle_solar_sys(e);
	xmlFreeDoc(doc);
}
