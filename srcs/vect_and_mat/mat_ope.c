/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_ope.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 13:02:05 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/22 13:02:08 by owinckle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vect			*mat_prod(t_vect *dst, t_base b, t_vect src)
{
	dst->x = b.vx.x * src.x + b.vy.x * src.y + b.vz.x * src.z;
	dst->y = b.vx.y * src.x + b.vy.y * src.y + b.vz.y * src.z;
	dst->z = b.vx.z * src.x + b.vy.z * src.y + b.vz.z * src.z;
	return (dst);
}

t_vect			*rot(t_vect *dst, float value, t_vect n)
{
	t_base	b;
	t_vect	src;

	ft_norme(&n);
	vect_set(&(b.vx), cos(value) + (1 - cos(value)) * (pow(n.x, 2)),
		(1 - cos(value)) * (n.x * n.y) - sin(value) * (-n.z),
		(1 - cos(value)) * (n.x * n.z) - sin(value) * (n.y));
	vect_set(&(b.vy), (1 - cos(value)) * (n.x * n.y) - sin(value) * (n.z),
		cos(value) + (1 - cos(value)) * (pow(n.y, 2)),
		(1 - cos(value)) * (n.y * n.z) - sin(value) * (-n.x));
	vect_set(&(b.vz), (1 - cos(value)) * (n.x * n.z) - sin(value) * (-n.y),
		(1 - cos(value)) * (n.y * n.z) - sin(value) * (n.x),
		cos(value) + (1 - cos(value)) * (pow(n.z, 2)));
	vect_copy(&src, *dst);
	mat_prod(dst, b, src);
	return (dst);
}

static float	det(t_base mat)
{
	return (mat.vx.x * mat.vy.y * mat.vz.z
		- mat.vx.x * mat.vy.z * mat.vz.y
		- mat.vx.y * mat.vy.x * mat.vz.z
		+ mat.vx.y * mat.vy.z * mat.vz.x
		- mat.vx.z * mat.vy.y * mat.vz.x
		+ mat.vx.z * mat.vy.x * mat.vz.y);
}

t_base			*transpose(t_base *mat)
{
	float	tmp;

	tmp = mat->vy.x;
	mat->vy.x = mat->vx.y;
	mat->vx.y = tmp;
	tmp = mat->vz.x;
	mat->vz.x = mat->vx.z;
	mat->vx.z = tmp;
	tmp = mat->vz.y;
	mat->vz.y = mat->vy.z;
	mat->vy.z = tmp;
	return (mat);
}

t_base			*inverse(t_base *mat)
{
	t_base		tmp;
	float		k;

	tmp = *mat;
	k = 1 / det(*mat);
	mat->vx.x = k * (tmp.vy.y * tmp.vz.z - tmp.vy.z * tmp.vz.y);
	mat->vx.y = -k * (tmp.vy.x * tmp.vz.z - tmp.vy.z * tmp.vz.x);
	mat->vx.z = k * (tmp.vy.x * tmp.vz.y - tmp.vy.y * tmp.vz.x);
	mat->vy.x = -k * (tmp.vx.y * tmp.vz.z - tmp.vz.y * tmp.vx.z);
	mat->vy.y = k * (tmp.vx.x * tmp.vz.z - tmp.vz.x * tmp.vx.z);
	mat->vy.z = -k * (tmp.vx.x * tmp.vz.y - tmp.vx.y * tmp.vz.x);
	mat->vz.x = k * (tmp.vx.y * tmp.vy.z - tmp.vx.z * tmp.vy.y);
	mat->vz.y = -k * (tmp.vx.x * tmp.vy.z - tmp.vx.z * tmp.vy.x);
	mat->vz.z = k * (tmp.vx.x * tmp.vy.y - tmp.vx.y * tmp.vy.x);
	transpose(mat);
	return (mat);
}
