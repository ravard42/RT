/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:37:33 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/22 12:37:33 by owinckle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		ray_set(t_data_th *data_th, int x, int y, t_vect mid)
{
	mid = translate(mid, data_th->e->c->b.up, y * IND - Y_WOW);
	mid = translate(mid, data_th->e->c->b.right, x * IND - X_WOW);
	vect_copy(&(data_th->r.ori), mid);
	mid = vec_norm(sub_coord(mid, data_th->e->c->ori));
	vect_copy(&(data_th->r.dir), mid);
}

static void		clear_data_th(t_data_th *data_th, int i, t_vect mid)
{
	int		x;
	int		y;

	x = i % (int)WIDTH;
	y = i / (int)WIDTH;
	ray_set(data_th, x, y, mid);
	data_th->r.inter = INTER_MAX;
	data_th->r.o_inter = NULL;
	data_th->r.refl = 0;
	data_th->r.norm_mult = 0;
	data_th->r.c_l = -1;
	data_th->r.c_trans = (t_vect){0, 0, 0};
	data_th->r.bool = -1;
}

static void		*processing(void *arg)
{
	t_data_th	*data_th;
	int			n;
	int			i;
	t_vect		color;
	t_vect		mid;

	data_th = (t_data_th *)arg;
	n = (WIDTH * HEIGHT) / THREAD;
	i = n * data_th->id;
	mid = add_coord(data_th->e->c->ori, data_th->e->c->b.dir);
	while (i < n * (data_th->id + 1))
	{
		clear_data_th(data_th, i, mid);
		color = select_inter_func(data_th);
		*(data_th->e->addr + i) = rgb_to_hexa(color);
		i++;
	}
	return (NULL);
}

void			rt(t_env *e)
{
	int			i;
	pthread_t	th[THREAD];
	t_data_th	data_th[THREAD];
	t_obj		*begin;
	t_light		*light;

	begin = e->o;
	light = e->l;
	i = -1;
	while (++i < THREAD)
	{
		(data_th + i)->id = i;
		(data_th + i)->e = e;
		(data_th + i)->o = begin;
		(data_th + i)->l = light;
		pthread_create(th + i, NULL, processing, data_th + i);
	}
	i = -1;
	while (++i < THREAD)
		pthread_join(th[i], NULL);
}
