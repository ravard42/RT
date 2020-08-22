/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 19:29:17 by ravard            #+#    #+#             */
/*   Updated: 2017/05/18 21:11:17 by dbirtel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_error(char *str, char *file_name)
{
	ft_putstr(str);
	if (file_name)
	{
		ft_putstr(file_name);
		ft_putstr(" introuvable\n");
	}
	exit(0);
}

static void	free_split(char **tmp)
{
	int	i;

	i = -1;
	while (tmp[++i])
		free(tmp[i]);
	free(tmp);
}

static int	ft_is_float(char *tmp)
{
	int	i;
	int	k;

	if (!tmp || !((tmp[0] == '-' && tmp[1] != '\0')
				|| (tmp[0] >= '0' && tmp[0] <= '9')))
		ft_error("go rt/scenes/readme.txt\n", NULL);
	i = 0;
	k = 0;
	while (tmp[++i])
		if (!((tmp[i] >= '0' && tmp[i] <= '9')
				|| (tmp[i] == '.' && (k += 1) < 2)))
			ft_error("go rt/scenes/readme.txt\n", NULL);
	return (1);
}

static int	is_valid_coord(char *str)
{
	int		len;
	int		i;
	int		k;
	char	**is_float;

	len = ft_strlen(str);
	if (!(str[0] == '{' && str[len - 1] == '}' && str[len] == '\0'))
		ft_error("go rt/scenes/readme.txt\n", NULL);
	i = -1;
	k = 0;
	while (str[++i])
		if (str[i] == ',')
			k++;
	if (k != 2)
		ft_error("go rt/scenes/readme.txt\n", NULL);
	str = ft_revstr(ft_revstr(str + 1) + 1);
	is_float = ft_strsplit(str, ',');
	i = -1;
	while (++i < 3)
		if (!is_float || !ft_is_float(is_float[i]))
			ft_error("go rt/scenes/readme.txt\n", NULL);
	free_split(is_float);
	return (1);
}

t_vect		*load_vect(t_vect *v, char *s)
{
	char	**tmp;
	char	*to_free;

	to_free = s;
	if (!(s && is_valid_coord(s)))
		ft_error("go rt/scenes/readme.txt\n", NULL);
	s += 2;
	tmp = ft_strsplit(s, ',');
	v->x = ft_atof(tmp[0], 0);
	v->y = ft_atof(tmp[1], 0);
	v->z = ft_atof(tmp[2], 0);
	xmlFree(to_free);
	free_split(tmp);
	return (v);
}
