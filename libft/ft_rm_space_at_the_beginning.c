/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_space_at_the_biginning.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 18:53:00 by ravard            #+#    #+#             */
/*   Updated: 2016/10/24 14:06:25 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*rm_space_at_the_beginning(char *str, char c)
{
	int		begin;

	if (str[0] != c)
		return (str);
	begin = -1;
	while (str[++begin] == c)
		;
	ft_strcpy(str, str + begin);
	return (str);
}
