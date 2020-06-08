/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:23:35 by pramella          #+#    #+#             */
/*   Updated: 2020/03/03 16:23:35 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char *dup;

	if (!(dup = malloc(sizeof(*dup) * (ft_strlen(src) + 1))))
		return (NULL);
	ft_strlcpy(dup, src, ft_strlen(src) + 1);
	return (dup);
}
