/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 19:30:53 by ravard            #+#    #+#             */
/*   Updated: 2016/10/24 14:14:01 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*symplify(const char *str, char c, int *word)
{
	char	*no_const;
	int		i;

	no_const = ft_strdup(str);
	rm_space_at_the_beginning(no_const, c);
	ft_revstr(no_const);
	rm_space_at_the_beginning(no_const, c);
	ft_revstr(no_const);
	rm_multi_space(no_const, c);
	*word = (!no_const || no_const[0] == '\0') ? 0 : 1;
	if (*word == 1)
	{
		i = -1;
		while (no_const[++i])
			if (no_const[i] == c && no_const[i + 1] != c)
				(*word)++;
	}
	return (no_const);
}

char	**load_tab(char **s, int *word, char c)
{
	int		i;
	char	*ptr;
	char	**tab;

	*ft_strchr(s[0], '\0') = c;
	s[1] = s[0];
	tab = (char **)malloc(sizeof(char *) * (*word + 1));
	i = -1;
	while (++i < *word)
	{
		ptr = ft_strchr(s[1], c);
		*ptr = '\0';
		tab[i] = ft_strdup(s[1]);
		s[1] = ptr + 1;
	}
	tab[i] = NULL;
	return (tab);
}

char	**ft_strsplit(const char *str, char c)
{
	int		*word;
	char	*s[2];
	char	**ret;

	word = (int *)malloc(sizeof(int));
	s[0] = symplify(str, c, word);
	if (*word == 0)
	{
		ret = (char **)malloc(sizeof(char *));
		ret[0] = NULL;
		return (ret);
	}
	else
		ret = load_tab(s, word, c);
	free(s[0]);
	free(word);
	return (ret);
}
