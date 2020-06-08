/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:24:28 by pramella          #+#    #+#             */
/*   Updated: 2020/03/03 16:24:29 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	i = ft_strlen(s) - 1;
	ptr = (char *)s;
	if (!c)
		return (ptr + i + 1);
	while (0 <= i)
	{
		if (ptr[i] == c)
			return (ptr + i);
		--i;
	}
	return (NULL);
}
