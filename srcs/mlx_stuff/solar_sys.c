/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solar_sys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 09:05:48 by ravard            #+#    #+#             */
/*   Updated: 2017/05/23 09:06:33 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	earth_moon_rot(t_env *e)
{
	t_vect	tmp;
	t_obj	*o;

	tmp = (t_vect){0, 1, 0};
	o = e->astre[0];
	rot(&o->ori, -M_PI / (370 * JOUR), tmp);
	o->tex.ori = o->ori;
	inverse(&o->tr_mat);
	rot(&o->tr_mat.vx, -M_PI / JOUR, o->tr_mat.vy);
	rot(&o->tr_mat.vz, -M_PI / JOUR, o->tr_mat.vy);
	inverse(&o->tr_mat);
	o = e->astre[1];
	rot(&e->trigo, -M_PI / (30 * JOUR), tmp);
	vect_sum(&o->ori, e->astre[0]->ori, *vect_multi(&tmp, 77, e->trigo));
	o->tex.ori = o->ori;
	inverse(&o->tr_mat);
	rot(&o->tr_mat.vx, -M_PI / (30 * JOUR), o->tr_mat.vy);
	rot(&o->tr_mat.vz, -M_PI / (30 * JOUR), o->tr_mat.vy);
	inverse(&o->tr_mat);
}

static void	mercure_venus_rot(t_env *e)
{
	t_vect	tmp;
	t_obj	*o;

	tmp = (t_vect){0, 1, 0};
	o = e->astre[2];
	rot(&o->ori, -M_PI / (90 * JOUR), tmp);
	o->tex.ori = o->ori;
	inverse(&o->tr_mat);
	rot(&o->tr_mat.vx, -M_PI / (60 * JOUR), o->tr_mat.vy);
	rot(&o->tr_mat.vz, -M_PI / (60 * JOUR), o->tr_mat.vy);
	inverse(&o->tr_mat);
	o = e->astre[3];
	rot(&o->ori, -M_PI / (220 * JOUR), tmp);
	o->tex.ori = o->ori;
	inverse(&o->tr_mat);
	rot(&o->tr_mat.vx, -M_PI / (240 * JOUR), o->tr_mat.vy);
	rot(&o->tr_mat.vz, -M_PI / (240 * JOUR), o->tr_mat.vy);
	inverse(&o->tr_mat);
}

static void	mars_jupiter_rot(t_env *e)
{
	t_vect	tmp;
	t_obj	*o;

	tmp = (t_vect){0, 1, 0};
	o = e->astre[4];
	rot(&o->ori, -M_PI / (690 * JOUR), tmp);
	o->tex.ori = o->ori;
	inverse(&o->tr_mat);
	rot(&o->tr_mat.vx, -M_PI / JOUR, o->tr_mat.vy);
	rot(&o->tr_mat.vz, -M_PI / JOUR, o->tr_mat.vy);
	inverse(&o->tr_mat);
	o = e->astre[5];
	rot(&o->ori, -M_PI / (4330 * JOUR), tmp);
	o->tex.ori = o->ori;
	inverse(&o->tr_mat);
	rot(&o->tr_mat.vx, -M_PI / (0.4 * JOUR), o->tr_mat.vy);
	rot(&o->tr_mat.vz, -M_PI / (0.4 * JOUR), o->tr_mat.vy);
	inverse(&o->tr_mat);
}

void		ft_solar_sys(t_env *e)
{
	earth_moon_rot(e);
	mercure_venus_rot(e);
	mars_jupiter_rot(e);
}
