/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/17 00:13:28 by ravard            #+#    #+#             */
/*   Updated: 2016/01/17 00:24:31 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		len;
	int		i;

	new = NULL;
	if (s1 && s2)
	{
		len = ft_strlen(s1) + ft_strlen(s2);
		i = 0;
		if (!(new = malloc(sizeof(char) * len + 1)))
			return (NULL);
		while (*s1)
			new[i++] = *s1++;
		while (*s2)
			new[i++] = *s2++;
		new[i] = '\0';
	}
	else if (s1)
		return (ft_strdup(s1));
	else if (s2)
		return (ft_strdup(s2));
	return (new);
}
