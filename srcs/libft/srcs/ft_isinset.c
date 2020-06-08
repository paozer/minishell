/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isinset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 21:24:18 by pramella          #+#    #+#             */
/*   Updated: 2020/05/01 21:24:19 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isinset(int c, char *set)
{
	size_t i;

	i = 0;
	if (!c)
		return (0);
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		++i;
	}
	return (0);
}
