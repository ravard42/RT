/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:20:44 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/22 12:20:45 by owinckle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj	*new_obj(t_env *e)
{
	t_obj	*begin;

	if (e->o == NULL)
	{
		e->o = (t_obj *)malloc(sizeof(t_obj));
		begin = e->o;
	}
	else
	{
		begin = e->o;
		while (e->o->next != NULL)
			e->o = e->o->next;
		e->o->next = (t_obj *)malloc(sizeof(t_obj));
		e->o = e->o->next;
	}
	e->o->next = NULL;
	e->o->tex.is_tex_obj = 0;
	e->o->m_b.is_m_b_obj = 0;
	return (begin);
}
