/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 21:22:33 by pramella          #+#    #+#             */
/*   Updated: 2020/05/01 21:22:34 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_split_free(char **split)
{
	int i;

	if (!split)
		return (-1);
	i = 0;
	while (split[i])
	{
		free(split[i]);
		++i;
	}
	free(split);
	return (0);
}
