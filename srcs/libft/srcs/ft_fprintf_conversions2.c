/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_conversions2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 12:23:36 by pramella          #+#    #+#             */
/*   Updated: 2020/05/01 21:23:28 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_dec_left(t_fields *flags, t_nbr *nbr, int *ret)
{
	int i;

	i = 0;
	(flags->prc > 0 && nbr->value < 0) ? ++flags->prc : 1;
	if (nbr->value < 0 && nbr->unsigned_flag == 0)
	{
		*ret += write(flags->fd, "-", 1);
		++i;
	}
	while (i < flags->prc - nbr->len)
	{
		*ret += write(flags->fd, "0", 1);
		++i;
	}
	ft_putnbr_base_fd(nbr->value, nbr->base, ft_strlen(nbr->base), flags->fd);
	*ret += nbr->len;
	i += nbr->len - 1;
	while (i++ < flags->wd - 1)
		*ret += write(flags->fd, " ", 1);
}

static void	ft_dec_zero(t_fields *flags, t_nbr *nbr, int *ret)
{
	int i;

	i = 0;
	(nbr->value < 0) ? ++i : 1;
	if (flags->prc_flag == 1)
	{
		flags->prc = (flags->prc < nbr->len) ? nbr->len : flags->prc;
		while (i++ < flags->wd - flags->prc)
			*ret += write(flags->fd, " ", 1);
	}
	if (nbr->value < 0 && nbr->unsigned_flag == 0)
		*ret += write(flags->fd, "-", 1);
	while (i++ < flags->wd - nbr->len && flags->prc_flag == -1)
		*ret += write(flags->fd, "0", 1);
	i = 0;
	while (i++ < flags->prc - nbr->len && flags->prc > nbr->len)
		*ret += write(flags->fd, "0", 1);
	ft_putnbr_base_fd(nbr->value, nbr->base, ft_strlen(nbr->base), flags->fd);
	*ret += nbr->len;
}

static void	ft_dec_std(t_fields *flags, t_nbr *nbr, int *ret)
{
	int i;

	i = 0;
	nbr->len = (flags->prc > nbr->len) ? flags->prc : nbr->len;
	nbr->len += (nbr->value < 0 && nbr->unsigned_flag == 0) ? 1 : 0;
	while (i++ < flags->wd - nbr->len)
		*ret += write(flags->fd, " ", 1);
	i = 0;
	if (nbr->value < 0 && nbr->unsigned_flag == 0)
	{
		write(flags->fd, "-", 1);
		++i;
	}
	nbr->value *= (nbr->value < 0 && nbr->unsigned_flag == 0) ? -1 : 1;
	while (i++ <
			nbr->len - ft_nbr_base_size_fd(nbr->value, ft_strlen(nbr->base)))
		write(flags->fd, "0", 1);
	ft_putnbr_base_fd(nbr->value, nbr->base, ft_strlen(nbr->base), flags->fd);
	*ret += nbr->len;
}

void		ft_dec_relayer_fd(t_fields *flags, t_nbr *nbr, int *ret)
{
	int i;

	i = 0;
	if (nbr->value == 0 && (flags->prc == 0 || flags->prc_err_flag == 1))
	{
		while (i++ < flags->wd)
			*ret += write(flags->fd, " ", 1);
	}
	else if (flags->left_flag == 1)
		ft_dec_left(flags, nbr, ret);
	else if (flags->zero_flag == 1)
		ft_dec_zero(flags, nbr, ret);
	else
		ft_dec_std(flags, nbr, ret);
}

void		ft_dec_conv_fd(t_fields *flags, va_list *ap, int *ret)
{
	t_nbr			*nbr;

	if (!(nbr = malloc(sizeof(*nbr))))
		return ;
	nbr->value = 0;
	nbr->value = (flags->type != 'd') ? nbr->value : va_arg(*ap, int);
	nbr->value = (flags->type != 'i') ? nbr->value : va_arg(*ap, int);
	nbr->value = (flags->type != 'u') ? nbr->value : va_arg(*ap, unsigned int);
	nbr->value = (flags->type != 'x') ? nbr->value : va_arg(*ap, unsigned int);
	nbr->value = (flags->type != 'X') ? nbr->value : va_arg(*ap, unsigned int);
	ft_dec_helper_fd(flags, nbr);
	ft_dec_relayer_fd(flags, nbr, ret);
	free(nbr->base);
	free(nbr);
	nbr->base = NULL;
	nbr = NULL;
}
