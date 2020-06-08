/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:24:40 by pramella          #+#    #+#             */
/*   Updated: 2020/03/03 16:24:41 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_getstart(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		++i;
	return (i);
}

static size_t	ft_getend(char const *s1, char const *set)
{
	size_t	i;
	size_t	end;

	i = 0;
	end = 0;
	while (s1[i])
	{
		if (!(ft_strchr(set, s1[i])))
			end = i;
		++i;
	}
	return (end);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	start = ft_getstart(s1, set);
	end = ft_getend(s1, set);
	if (end < start)
		return (ft_calloc(1, 1));
	if (!(str = malloc(end - start + 2)))
		return (NULL);
	ft_strlcpy(str, s1 + start, end - start + 2);
	return (str);
}
