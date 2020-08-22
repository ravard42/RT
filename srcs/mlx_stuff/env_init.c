/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:08:21 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/23 06:58:58 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_solar_sys(t_env *e)
{
	int		i;

	i = -1;
	while (++i < 6)
		e->astre[i] = NULL;
}

t_env		*env_init(char *path)
{
	t_env	*e;
	int		info[3];

	e = (t_env *)malloc(sizeof(t_env));
	e->ptr = mlx_init();
	e->win = mlx_new_window(e->ptr, WIDTH + 300, HEIGHT, "RT");
	e->img = mlx_new_image(e->ptr, WIDTH, HEIGHT);
	e->addr = (int *)mlx_get_data_addr(e->img, info, info + 1, info + 2);
	e->c = NULL;
	e->o = NULL;
	e->l = NULL;
	ft_memset(e->move, 0, sizeof(char) * 13);
	e->move[13] = PAS;
	e->effet = 0;
	e->amb = 0;
	e->ambi = ft_strdup("0");
	e->filter = NULL;
	e->filter_id = 0;
	e->amb = 0;
	init_solar_sys(e);
	parse(e, path);
	if (!e->c)
		ft_error("aucune config cam en entree\n", NULL);
	return (e);
}
