/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:19:01 by pramella          #+#    #+#             */
/*   Updated: 2020/03/03 16:19:06 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int i;
	int sign;
	int nb;

	i = 0;
	sign = -1;
	nb = 0;
	while (ft_isspace(str[i]))
		++i;
	if (str[i] == '+')
		++i;
	else if (str[i] == '-')
	{
		sign *= -1;
		++i;
	}
	while (ft_isdigit(str[i]))
	{
		nb = nb * 10 - (str[i] - '0');
		++i;
	}
	return (sign * nb);
}
