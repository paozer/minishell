/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:21:48 by pramella          #+#    #+#             */
/*   Updated: 2020/03/03 16:21:49 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*p_dst;
	const char	*p_src;

	i = 0;
	if (!dst && !src)
		return (NULL);
	p_dst = dst;
	p_src = src;
	while (i < n)
	{
		p_dst[i] = p_src[i];
		++i;
	}
	return (dst);
}
