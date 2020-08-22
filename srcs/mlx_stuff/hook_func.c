/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbirtel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 17:15:11 by dbirtel           #+#    #+#             */
/*   Updated: 2017/05/23 10:11:01 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	key_switch(int keycode)
{
	if (keycode == UN)
		return (1);
	else if (keycode == DEUX)
		return (2);
	else if (keycode == TROIS)
		return (3);
	else if (keycode == QUATRE)
		return (4);
	else if (keycode == CINQ)
		return (5);
	else if (keycode == SIX)
		return (6);
	else if (keycode == SEPT)
		return (7);
	else if (keycode == HUIT)
		return (8);
	else if (keycode == NEUF)
		return (9);
	else if (keycode == DIX)
		return (10);
	else if (keycode == ONZE)
		return (11);
	else if (keycode == DOUZE)
		return (12);
	return (-42);
}

int			expose(t_env *e)
{
	rt(e);
	mlx_put_image_to_window(e->ptr, e->win, e->img, 0, 0);
	return (1);
}

int			key_press(int keycode, t_env *e)
{
	int	tmp;

	if ((tmp = key_switch(keycode)) != -42)
		e->move[key_switch(keycode)] = 1;
	else if (keycode == FAUCON)
		e->move[13] = PAS * MILLENIUM;
	return (1);
}

int			key_release(int keycode, t_env *e)
{
	int	tmp;

	if (keycode == EXIT)
		exit(0);
	else if (keycode == EXPOSE)
		expose(e);
	else if (keycode == ZERO)
	{
		e->move[0] = (e->move[0]) ? 0 : 1;
		e->effet = (e->effet == 3) ? 0 : e->effet;
	}
	else if ((tmp = key_switch(keycode)) != -42)
		e->move[tmp] = 0;
	else if (keycode == FAUCON)
		e->move[13] = PAS;
	else if (keycode == ANTIA)
		e->effet = (e->effet == 1) ? 0 : 1;
	else if (keycode == CARTOON)
		e->effet = (e->effet == 2) ? 0 : 2;
	else if (keycode == MOTION_B && !e->move[0])
		e->effet = (e->effet == 3) ? 0 : 3;
	return (1);
}

int			loop_hook(t_env *e)
{
	int		exp;

	exp = 0;
	if (e->move[0])
	{
		if (is_in_motion(e) && ++exp)
			cam_set(e);
		if (e->solar_sys && ++exp)
			ft_solar_sys(e);
		if (exp)
			expose(e);
	}
	return (1);
}
