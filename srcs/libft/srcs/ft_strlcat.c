/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:23:45 by pramella          #+#    #+#             */
/*   Updated: 2020/03/03 16:23:46 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	char	*p_src;

	i = 0;
	while (i < size)
	{
		if (!dst[i])
			break ;
		if (i == size - 1 && dst[i])
			return (size + ft_strlen(src));
		++i;
	}
	i = ft_strlen(dst);
	j = 0;
	p_src = (char *)src;
	while (i + j < size - 1 && p_src[j] && 0 < size)
	{
		dst[i + j] = src[j];
		++j;
	}
	dst[i + j] = 0;
	if (size < i)
		return (size + ft_strlen(src));
	return (i + ft_strlen(src));
}
