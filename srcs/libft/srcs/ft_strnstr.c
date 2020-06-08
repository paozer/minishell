/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:24:16 by pramella          #+#    #+#             */
/*   Updated: 2020/03/03 16:24:17 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	size_needle;
	char	*ptr_hay;

	i = 0;
	ptr_hay = (char *)haystack;
	if (!needle[0])
		return (ptr_hay);
	size_needle = ft_strlen(needle);
	while (ptr_hay[i] && (i + size_needle - 1 < len))
	{
		if (ptr_hay[i] == needle[0])
		{
			if (!ft_strncmp((ptr_hay + i), needle, size_needle))
				return (ptr_hay + i);
		}
		++i;
	}
	return (0);
}
