/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:21:56 by pramella          #+#    #+#             */
/*   Updated: 2020/03/03 16:21:58 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const char	*p_src;
	char		*p_dst;

	p_src = (const char *)src;
	p_dst = (char *)dst;
	if (p_dst < p_src)
		ft_memcpy(p_dst, p_src, len);
	else if (p_dst > p_src)
		while (len)
		{
			p_dst[len - 1] = p_src[len - 1];
			--len;
		}
	return (dst);
}
