/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:24:52 by pramella          #+#    #+#             */
/*   Updated: 2020/03/03 16:24:54 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_s;
	char	*sub;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (len_s < start)
		return (ft_calloc(1, 1));
	if (len_s < len)
		len = len_s - start;
	if (!(sub = malloc(sizeof(*sub) * (len + 1))))
		return (NULL);
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}
