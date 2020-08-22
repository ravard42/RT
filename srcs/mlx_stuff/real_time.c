/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:09:14 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/23 07:03:47 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	cam_rot(t_env *e)
{
	if (e->move[1] && rot(&(e->c->b.dir), ROT, e->c->b.right))
		vect_prod(&(e->c->b.up), e->c->b.right, e->c->b.dir);
	if (e->move[2] && rot(&(e->c->b.dir), -ROT, e->c->b.right))
		vect_prod(&(e->c->b.up), e->c->b.right, e->c->b.dir);
	if (e->move[3] && rot(&(e->c->b.dir), ROT, e->c->b.up))
		vect_prod(&(e->c->b.right), e->c->b.dir, e->c->b.up);
	if (e->move[4] && rot(&(e->c->b.dir), -ROT, e->c->b.up))
		vect_prod(&(e->c->b.right), e->c->b.dir, e->c->b.up);
	if (e->move[5] && rot(&(e->c->b.right), ROT, e->c->b.dir))
		vect_prod(&(e->c->b.up), e->c->b.right, e->c->b.dir);
	if (e->move[6] && rot(&(e->c->b.right), -ROT, e->c->b.dir))
		vect_prod(&(e->c->b.up), e->c->b.right, e->c->b.dir);
}

static void	cam_shift(t_env *e)
{
	t_vect	tmp;

	if (e->move[7])
		vect_sub(&(e->c->ori), e->c->ori, *vect_multi(&tmp,
			e->move[13], e->c->b.right));
	if (e->move[8])
		vect_sum(&(e->c->ori), e->c->ori, *vect_multi(&tmp,
			e->move[13], e->c->b.right));
	if (e->move[9])
		vect_sub(&(e->c->ori), e->c->ori, *vect_multi(&tmp,
			e->move[13], e->c->b.dir));
	if (e->move[10])
		vect_sum(&(e->c->ori), e->c->ori, *vect_multi(&tmp,
			e->move[13], e->c->b.dir));
	if (e->move[11])
		vect_sum(&(e->c->ori), e->c->ori, *vect_multi(&tmp,
			e->move[13], e->c->b.up));
	if (e->move[12])
		vect_sub(&(e->c->ori), e->c->ori, *vect_multi(&tmp,
			e->move[13], e->c->b.up));
}

char		is_in_motion(t_env *e)
{
	int	i;

	i = 0;
	while (++i < 13 && !e->move[i])
		;
	if (i == 13)
		return (0);
	return (1);
}

static char	*joitoa(t_vect v)
{
	char	*itoa[3];
	char	*joint[6];
	char	*new;

	itoa[0] = ft_itoa((int)v.x);
	itoa[1] = ft_itoa((int)v.y);
	itoa[2] = ft_itoa((int)v.z);
	joint[0] = ft_strjoin("{", itoa[0]);
	joint[1] = ft_strjoin(joint[0], ",");
	joint[2] = ft_strjoin(joint[1], itoa[1]);
	joint[3] = ft_strjoin(joint[2], ",");
	joint[4] = ft_strjoin(joint[3], itoa[2]);
	joint[5] = ft_strjoin(joint[4], "}");
	new = ft_strdup(joint[5]);
	free(joint[0]);
	free(joint[1]);
	free(joint[2]);
	free(joint[3]);
	free(joint[4]);
	free(joint[5]);
	free(itoa[0]);
	free(itoa[1]);
	free(itoa[2]);
	return (new);
}

void		cam_set(t_env *e)
{
	char	*truc;

	cam_shift(e);
	cam_rot(e);
	joitoa(e->c->ori);
	e->c_ori = ft_strdup(joitoa(e->c->ori));
	cam_clear(e);
	truc = ft_strjoin("Origin    : ", e->c_ori);
	mlx_string_put(e->ptr, e->win, WIDTH + 10, 110, 0xFFFFFF, truc);
	free(truc);
}
