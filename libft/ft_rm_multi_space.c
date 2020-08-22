/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_multi_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 18:53:29 by ravard            #+#    #+#             */
/*   Updated: 2016/10/12 18:57:44 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*rm_multi_space(char *str, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		str[j] = str[i];
		if (str[i] == c)
		{
			while (str[++i] == c)
				;
			i--;
		}
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}
