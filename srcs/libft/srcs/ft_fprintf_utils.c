/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:19:59 by pramella          #+#    #+#             */
/*   Updated: 2020/05/01 21:23:12 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base_fd(long nbr, char *base, int base_len, int fd)
{
	if (nbr < 0)
		nbr *= -1;
	if (nbr >= (long)base_len)
		ft_putnbr_base_fd(nbr / base_len, base, base_len, fd);
	write(fd, &base[nbr % base_len], 1);
}

int		ft_nbr_base_size_fd(long nbr, int base_len)
{
	nbr *= (nbr < 0) ? -1 : 1;
	if (nbr >= base_len)
		return (1 + ft_nbr_base_size_fd(nbr / base_len, base_len));
	return (1);
}

void	ft_dec_helper_fd(t_fields *flags, t_nbr *nbr)
{
	if (ft_strchr("diu", flags->type))
	{
		nbr->unsigned_flag = (flags->type != 'u') ? 0 : 1;
		nbr->len = ft_nbr_base_size_fd(nbr->value, 10);
		nbr->base = ft_strdup("0123456789");
	}
	else
	{
		nbr->unsigned_flag = 1;
		nbr->len = ft_nbr_base_size_fd(nbr->value, 16);
		nbr->base = NULL;
		if (flags->type == 'x')
			nbr->base = ft_strdup("0123456789abcdef");
		else if (flags->type == 'X')
			nbr->base = ft_strdup("0123456789ABCDEF");
	}
}
