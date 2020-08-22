/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 21:31:53 by ravard            #+#    #+#             */
/*   Updated: 2017/05/15 19:43:15 by dbirtel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\f'
			|| c == '\n' || c == '\v' || c == '\r')
		return (1);
	return (0);
}

float	atof_sweet(char *str, float nbr, int sign)
{
	int		i;
	int		dot_len;
	float	dot;

	i = 0;
	dot_len = 0;
	while (str[i] > 47 && str[i] < 58)
	{
		dot = (float)(str[i] - 48);
		++dot_len;
		nbr = nbr + (dot / (float)(pow(10, dot_len)));
		i++;
	}
	return (nbr * (float)sign);
}

float	ft_atof(char *str, char free_xml)
{
	float	nbr[2];
	int		i;
	int		sign;

	i = 0;
	nbr[0] = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		nbr[0] = (float)((nbr[0] * 10) + (str[i] - 48));
		i++;
	}
	if (str[i] == '.')
		i++;
	nbr[1] = atof_sweet(str + i, nbr[0], sign);
	if (free_xml)
		xmlFree(str);
	return (nbr[1]);
}
