/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owinckle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 22:06:17 by owinckle          #+#    #+#             */
/*   Updated: 2017/05/23 22:06:17 by owinckle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	cam_clear(t_env *e)
{
	int		x;
	int		y;

	y = 110;
	while (++y < 135)
	{
		x = WIDTH - 1;
		while (++x < WIDTH + 300)
		{
			mlx_pixel_put(e->ptr, e->win, x, y, 0);
		}
	}
}

void	touches(t_env *e)
{
	mlx_string_put(e->ptr, e->win, WIDTH + 10, 285, 0xFFFFFF,
		"-------");
	mlx_string_put(e->ptr, e->win, WIDTH + 10, 310, 0xFFFFFF,
		"Touches");
	mlx_string_put(e->ptr, e->win, WIDTH + 10, 335, 0xFFFFFF,
		"-------");
	mlx_string_put(e->ptr, e->win, WIDTH + 10, 360, 0xFFFFFF,
		"Antialiasing : +");
	mlx_string_put(e->ptr, e->win, WIDTH + 10, 385, 0xFFFFFF,
		"Cartoon      : C");
	mlx_string_put(e->ptr, e->win, WIDTH + 10, 410, 0xFFFFFF,
		"Motion Blur  : M");
	mlx_string_put(e->ptr, e->win, WIDTH + 10, 435, 0xFFFFFF,
		"Refresh      : Return");
	mlx_string_put(e->ptr, e->win, WIDTH + 10, 460, 0xFFFFFF,
		"-------");
	mlx_string_put(e->ptr, e->win, WIDTH + 10, 535, 0xFFFFFF,
		"     ~~~ Parapluie ~~~");
}

void	sommaire3(t_env *e)
{
	char	*truc;
	char	*bidule;
	char	*chose;

	chose = ft_itoa(e->nb_cyl);
	bidule = ft_strjoin(chose, "x");
	truc = ft_strjoin("Cylinders : ", bidule);
	mlx_string_put(e->ptr, e->win, WIDTH + 10, 210, 0xFFFFFF, truc);
	free(truc);
	free(bidule);
	free(chose);
	chose = ft_itoa(e->nb_cube);
	bidule = ft_strjoin(chose, "x");
	truc = ft_strjoin("Cubes     : ", bidule);
	mlx_string_put(e->ptr, e->win, WIDTH + 10, 235, 0xFFFFFF, truc);
	free(truc);
	free(bidule);
	free(chose);
	chose = ft_itoa(e->nb_light);
	bidule = ft_strjoin(chose, "x");
	truc = ft_strjoin("Lights    : ", bidule);
	mlx_string_put(e->ptr, e->win, WIDTH + 10, 260, 0xFFFFFF, truc);
	free(truc);
	free(bidule);
	free(chose);
}

void	sommaire2(t_env *e)
{
	char	*truc;
	char	*bidule;
	char	*chose;

	chose = ft_itoa(e->nb_plane);
	bidule = ft_strjoin(chose, "x");
	truc = ft_strjoin("Planes    : ", bidule);
	mlx_string_put(e->ptr, e->win, WIDTH + 10, 160, 0xFFFFFF, truc);
	free(truc);
	free(bidule);
	free(chose);
	chose = ft_itoa(e->nb_cone);
	bidule = ft_strjoin(chose, "x");
	truc = ft_strjoin("Cones     : ", bidule);
	mlx_string_put(e->ptr, e->win, WIDTH + 10, 185, 0xFFFFFF, truc);
	free(truc);
	free(bidule);
	free(chose);
	sommaire3(e);
	touches(e);
}

void	sommaire(t_env *e, char *scene)
{
	char	*truc;
	char	*bidule;
	char	*chose;

	truc = ft_strjoin("Scene     : ", scene);
	mlx_string_put(e->ptr, e->win, WIDTH + 10, 35, 0xFFFFFF, truc);
	free(truc);
	truc = ft_strjoin("Filter    : ", e->filter);
	mlx_string_put(e->ptr, e->win, WIDTH + 10, 60, 0xFFFFFF, truc);
	free(truc);
	truc = ft_strjoin("Ambient   : ", e->ambi);
	mlx_string_put(e->ptr, e->win, WIDTH + 10, 85, 0xFFFFFF, truc);
	free(truc);
	truc = ft_strjoin("Origin    : ", e->c_ori);
	mlx_string_put(e->ptr, e->win, WIDTH + 10, 110, 0xFFFFFF, truc);
	free(truc);
	chose = ft_itoa(e->nb_sphere);
	bidule = ft_strjoin(chose, "x");
	truc = ft_strjoin("Spheres   : ", bidule);
	mlx_string_put(e->ptr, e->win, WIDTH + 10, 135, 0xFFFFFF, truc);
	free(truc);
	free(bidule);
	free(chose);
	sommaire2(e);
}
