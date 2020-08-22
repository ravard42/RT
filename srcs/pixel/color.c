/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:36:23 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/22 12:36:24 by owinckle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	fix_color(t_vect *col)
{
	col->x = (col->x > 255) ? 255 : col->x;
	col->y = (col->y > 255) ? 255 : col->y;
	col->z = (col->z > 255) ? 255 : col->z;
}

t_vect	rfix_color(t_vect col)
{
	col.x = (col.x > 255) ? 255 : col.x;
	col.y = (col.y > 255) ? 255 : col.y;
	col.z = (col.z > 255) ? 255 : col.z;
	return (col);
}

t_vect	filter(int filter, t_data_th *th)
{
	t_vect		color;

	color = (t_vect){0, 0, 0};
	if (th->e->amb != 0 || th->l)
	{
		if (filter == SEPIA)
			color = mult_coord(add_coord(color, (t_vect){112, 66, 20}), 0.5);
		else if (filter == ICE)
			color = mult_coord(add_coord(color, (t_vect){0, 90, 180}), 0.5);
	}
	return (color);
}

t_vect	diffuse(t_ray *r, t_vect light_dir, float dist, int type)
{
	t_vect	c[2];
	float	angle;

	angle = dot(r->normal_hit, light_dir);
	if (angle < 0)
		return ((t_vect){0, 0, 0});
	c[1] = r->col;
	if (r->o_inter->type == PLANE && r->o_inter->damier)
		c[1] = damier_plane(r->o_inter, r->p[1]);
	if (type == 0)
	{
		c[0].x = (DIFFUSE * (c[1].x * angle) - 0.0001) * \
			(1 / (0.5 + 0.0005 * dist + 0.0005 * dist * dist));
		c[0].y = (DIFFUSE * (c[1].y * angle) - 0.0001) * \
			(1 / (0.5 + 0.0005 * dist + 0.0005 * dist * dist));
		c[0].z = (DIFFUSE * (c[1].z * angle) - 0.0001) * \
			(1 / (0.5 + 0.0005 * dist + 0.0005 * dist * dist));
	}
	else
	{
		c[0].x = (DIFFUSE * (c[1].x * angle) - 0.0001) * (1 / (0.5 + 0.001));
		c[0].y = (DIFFUSE * (c[1].y * angle) - 0.0001) * (1 / (0.5 + 0.001));
		c[0].z = (DIFFUSE * (c[1].z * angle) - 0.0001) * (1 / (0.5 + 0.001));
	}
	return (c[0]);
}

t_vect	specular(t_ray *r, t_vect light_dir, float dist)
{
	t_vect	col[2];
	t_vect	spe;
	t_vect	cam_vec;
	float	angle;

	col[0] = (t_vect){0, 0, 0};
	col[1] = r->col;
	if (r->o_inter->type == PLANE && r->o_inter->damier)
		col[1] = damier_plane(r->o_inter, r->p[1]);
	spe = mult_coord(r->normal_hit, 2.0);
	spe = mult_coord(spe, dot(light_dir, r->normal_hit));
	spe = vec_norm(sub_coord(spe, light_dir));
	cam_vec = vec_norm(sub_coord(r->p[0], r->ori));
	angle = dot(spe, cam_vec);
	if (vec_len(add_coord(cam_vec, spe)) > vec_len(cam_vec))
		return (col[0]);
	col[0].x = r->o_inter->spec * (10 + col[1].x) * pow(angle, 16.0) *
		(1.0 / (0.5 + 0.001 * dist + 0.001 * dist * dist));
	col[0].y = r->o_inter->spec * (10 + col[1].y) * pow(angle, 16.0) *
		(1.0 / (0.5 + 0.001 * dist + 0.001 * dist * dist));
	col[0].z = r->o_inter->spec * (10 + col[1].z) * pow(angle, 16.0) *
		(1.0 / (0.5 + 0.001 * dist + 0.001 * dist * dist));
	return (col[0]);
}
