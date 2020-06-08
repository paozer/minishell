/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:21:43 by pramella          #+#    #+#             */
/*   Updated: 2020/03/03 16:21:44 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t		i;
	const char	*p_s1;
	const char	*p_s2;

	i = 0;
	p_s1 = s1;
	p_s2 = s2;
	while (i < n)
	{
		if ((unsigned char)p_s1[i] != (unsigned char)p_s2[i])
			return ((unsigned char)p_s1[i] - (unsigned char)p_s2[i]);
		++i;
	}
	return (0);
}
