/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:20:34 by pramella          #+#    #+#             */
/*   Updated: 2020/03/03 16:20:35 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_ncharsize(long n)
{
	size_t i;

	i = 0;
	if (n <= 0)
		++i;
	while (n != 0)
	{
		++i;
		n /= 10;
	}
	return (i);
}

static void		ft_catchar(char *str, char c)
{
	size_t i;

	i = ft_strlen(str);
	str[i] = c;
	str[++i] = '\0';
}

static void		ft_rec_itoa(long nb, char *ptr)
{
	if (nb > 9)
		ft_rec_itoa(nb / 10, ptr);
	ft_catchar(ptr, (nb % 10) + '0');
}

char			*ft_itoa(int n)
{
	long	nb;
	size_t	size;
	char	*ptr;

	nb = n;
	size = ft_ncharsize(nb);
	if (!(ptr = malloc(size + 1)))
		return (NULL);
	ptr[0] = '\0';
	ptr[size] = '\0';
	if (n < 0)
	{
		ft_catchar(ptr, '-');
		nb *= -1;
	}
	ft_rec_itoa(nb, ptr);
	return (ptr);
}
