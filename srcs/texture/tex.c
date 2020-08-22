/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:48:11 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/22 12:48:11 by owinckle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	tex(t_ray r)
{
	if (r.o_inter->type == PLANE)
		return (plan_tex(r));
	else if (r.o_inter->type == SPHERE)
		return (sphere_tex(r));
	else if (r.o_inter->type == CYLINDER)
		return (cyl_tex(r));
	else if (r.o_inter->type == CONE)
		return (cone_tex(r));
	return (0);
}
