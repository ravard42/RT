/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 11:50:47 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/22 11:50:49 by owinckle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	sign_set(char *sign, int i)
{
	if (i == 1)
	{
		sign[0] = -1;
		sign[1] = -1;
	}
	else if (i == 2)
	{
		sign[0] = -1;
		sign[1] = 1;
	}
	else if (i == 3)
	{
		sign[0] = 1;
		sign[1] = 1;
	}
	else if (i == 4)
	{
		sign[0] = 1;
		sign[1] = -1;
	}
}

static void	antia_ray_set(t_ray *r, int i, t_env *e)
{
	float	ind;
	t_vect	pinhole;
	char	sign[2];
	t_vect	tmp;

	vect_sum(&pinhole, r[i].ori, *vect_multi(&tmp, 1.0, r[i].dir));
	ind = IND / 3;
	ind = (e->effet == 2) ? ind * 2.5 : ind;
	sign_set(sign, i);
	vect_sum(&pinhole, pinhole, *vect_multi(&tmp, sign[0] * ind,
		e->c->b.right));
	vect_sum(&pinhole, pinhole, *vect_multi(&tmp, sign[1] * ind, e->c->b.up));
	vect_sub(&(r[i].dir), pinhole, r[i].ori);
	ft_norme(&(r[i].dir));
}

static void	init_antia(t_ray *r, t_data_th *th)
{
	int	i;

	r[0] = th->r;
	i = 0;
	while (++i < 5)
	{
		r[i] = th->r;
		antia_ray_set(r, i, th->e);
	}
}

t_vect		antia_inter(t_data_th *th, int i, int bord)
{
	t_ray	r[5];
	t_vect	color[5];

	init_antia(r, th);
	while (++i < 5)
	{
		find_inter(r + i, th->o);
		if (!r[i].o_inter)
			color[i] = (t_vect){0, 0, 0};
		else
		{
			r[i].p[0] = translate(th->r.ori, r[i].dir, r[i].inter - 0.001f);
			r[i].col = (r[i].o_inter->tex.is_tex_obj) ?
				hexa_to_rgb(tex(r[i])) : r[i].o_inter->col;
			color[i] = find_color(r + i, th->o, th->l, th->e->amb);
		}
	}
	color[0] = (th->e->effet == 1) ?
		mix_color(color, 5) : cartoon(color, r, &bord);
	th->r = r[0];
	color[0] = (th->r.o_inter) ? add_coord(color[0],
		refl_trans(th)) : color[0];
	color[0] = add_coord(color[0], filter(th->e->filter_id, th));
	return (rfix_color(color[0]));
}
