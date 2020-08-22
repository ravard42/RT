/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbirtel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 17:03:16 by dbirtel           #+#    #+#             */
/*   Updated: 2017/05/16 02:33:25 by dbirtel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		main(int argc, char **argv)
{
	t_env	*e;

	if (argc != 2)
		ft_error("usage : ./RT file.xml\n", NULL);
	e = env_init(argv[1]);
	mlx_string_put(e->ptr, e->win, WIDTH + 10, 0, 0xFFFFFF,
		"Scene Data");
	mlx_string_put(e->ptr, e->win, WIDTH + 10, 10, 0xFFFFFF,
		"----------");
	sommaire(e, argv[1]);
	loop(e);
	return (0);
}
