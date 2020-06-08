/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:23:20 by pramella          #+#    #+#             */
/*   Updated: 2020/03/03 16:23:21 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_word_count(char *str, char *charset)
{
	int i;
	int counter;
	int indicator;

	i = 0;
	counter = 0;
	indicator = 0;
	if (ft_isinset(str[0], charset))
		++indicator;
	if (ft_isinset(str[ft_strlen(str) - 1], charset))
		++indicator;
	while (str[i])
	{
		if (ft_isinset(str[i], charset))
		{
			++counter;
			while (ft_isinset(str[i + 1], charset))
				++i;
		}
		++i;
	}
	return (counter + 1 - indicator);
}

char	*copy_part(char *str, char *charset, int j)
{
	int		i;
	int		start;
	int		counter;
	char	*tab;

	i = 0;
	start = j;
	counter = 0;
	while (!ft_strchr(charset, str[j]))
	{
		++counter;
		++j;
	}
	if (!(tab = malloc(counter + 1)))
		return (NULL);
	while (i < counter)
	{
		tab[i] = str[start + i];
		++i;
	}
	tab[i] = '\0';
	return (tab);
}

char	**ft_split(char const *str, char *charset)
{
	int		i;
	int		j;
	char	**split;
	int		word_count;

	word_count = ft_word_count((char *)str, charset);
	if (!(split = malloc(sizeof(char *) * (word_count + 1))))
		return (NULL);
	if (!str[0])
	{
		split[0] = NULL;
		return (split);
	}
	split[word_count] = NULL;
	i = 0;
	j = 0;
	while (i < word_count)
	{
		while (ft_isinset(str[j], charset))
			++j;
		split[i] = copy_part((char *)str, charset, j);
		j += ft_strlen(split[i]);
		++i;
	}
	return (split);
}
