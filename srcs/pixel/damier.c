/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   damier.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:34:33 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/22 12:34:35 by owinckle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vect	damier_plane(t_obj *o, t_vect p)
{
	if (!o->damier)
		return (o->col);
	if ((p.x > 0.0 && p.z > 0.0) || (p.x < 0.0 && p.z < 0.0))
	{
		if (((int)p.x % 2 == 0 && (int)p.z % 2 == 0) ||
			((int)p.x % 2 != 0 && (int)p.z % 2 != 0))
			return (o->col);
		else
			return (o->col_inv);
	}
	else
	{
		if (((int)p.x % 2 == 0 && (int)p.z % 2 == 0) ||
			((int)p.x % 2 != 0 && (int)p.z % 2 != 0))
			return (o->col_inv);
		else
			return (o->col);
	}
	return (o->col);
}
