/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:21:30 by pramella          #+#    #+#             */
/*   Updated: 2020/03/03 16:21:30 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t		i;
	char		*p_dst;
	const char	*p_src;

	i = 0;
	p_dst = (char *)dst;
	p_src = (const char *)src;
	while (i < n)
	{
		p_dst[i] = p_src[i];
		if ((unsigned char)p_src[i] == (unsigned char)c)
			return (++p_dst + i);
		++i;
	}
	return (NULL);
}
