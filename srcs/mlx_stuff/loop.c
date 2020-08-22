/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbirtel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 17:11:42 by dbirtel           #+#    #+#             */
/*   Updated: 2017/05/23 22:46:53 by dbirtel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	red_cross(void)
{
	exit(0);
	return (0);
}

void	loop(t_env *e)
{
	mlx_expose_hook(e->win, &expose, e);
	mlx_hook(e->win, 17, 1L << 17, red_cross, e);
	mlx_hook(e->win, 2, 1L << 0, &key_press, e);
	mlx_key_hook(e->win, &key_release, e);
	mlx_loop_hook(e->ptr, &loop_hook, e);
	mlx_loop(e->ptr);
}
