/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/16 23:50:47 by ravard            #+#    #+#             */
/*   Updated: 2016/01/16 23:52:54 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_intlen(int nbr)
{
	int		i;

	i = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
	{
		nbr = -nbr;
		i++;
	}
	while (nbr > 0)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	int		i;
	int		len;
	char	*num;

	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_intlen(n);
	i = len - 1;
	if (!(num = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	if (n < 0)
	{
		n = -n;
		num[0] = '-';
	}
	while (n > 0)
	{
		num[i--] = n % 10 + 48;
		n = n / 10;
	}
	num[len] = '\0';
	return (num);
}
